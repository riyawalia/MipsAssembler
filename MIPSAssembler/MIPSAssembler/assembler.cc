//
//  assembler.cpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#include "assembler.h"

Assembler::Assembler() : PC{0}
{
    this->symbolTable = new SymbolTable();
    this->syntaxChecker = new SyntaxChecker();
   // this->Translator = new class Translator(); 
}

/* OUTPUT */
void Assembler::OutputMachineCode(int *instruction)
{
    int instr = *instruction;
    std::cout << char(instr >> 24) << char(instr >> 16) << char (instr >> 8) << char(instr);
}

void Assembler::OutputMachineCode(unsigned int *instruction)
{
    unsigned int instr = *instruction;
    std::cout << char(instr >> 24) << char(instr >> 16) << char (instr >> 8) << char(instr);
}

/* TRANSLATORS */
bool Assembler::Translate(vector<Token> tokenLine, int* instr)
{
    for (int i = 0; i < tokenLine.size(); ++i)
    {
        Token opToken = tokenLine[i];
        Token::Kind tokenKind = opToken.getKind();
        
        switch(tokenKind)
        {
            case Token::WORD:
            {
                if (i + 1 >= tokenLine.size())
                {
                    this->PrintToError();
                    return false;
                }
                
                Token::Kind nextTokenKind = tokenLine[i + 1].getKind();
                string nextTokenLexemme = tokenLine[i + 1].getLexeme();
                
                if (nextTokenKind == Token::INT)
                {
                    try
                    {
                        *instr = std::stoi(nextTokenLexemme);
                        return true;
                    }
                    catch(std::out_of_range &e)
                    {
                        unsigned int *unsignedInstr = new unsigned int();
                        try
                        {
                            *unsignedInstr = std::stoul(nextTokenLexemme);
                            
                            this->OutputMachineCode(unsignedInstr);
                            return false;
                        }
                        catch(std::out_of_range &exp)
                        {
                            this->PrintToError();
                            return false;
                        }
                    }
                }
                else if (nextTokenKind == Token::HEXINT)
                {
                    *instr = (int) std::stoul(nextTokenLexemme, 0, 16);
                    return true; 
                }
                else if(nextTokenKind == Token::ID)
                {
                    unsigned int *unsignedInstr = new unsigned int();
                    try
                    {
                        unsignedInstr = this->symbolTable->GetAddressIfExists(nextTokenLexemme); //[nextTokenLexemme];
                        
                        this->OutputMachineCode(unsignedInstr);
                        return false;
                    }
                    catch(std::out_of_range &exp)
                    {
                        this->PrintToError();
                        return false;
                    }
                }
                else
                {
                    this->PrintToError();
                    return false;
                }
                return true;
            }
                break;
            case Token::ID:
            {
                string lexemme = tokenLine[i].getLexeme();
                if (lexemme == "jr" || lexemme == "jalr")
                {
                    *instr = this->TranslateJumps(tokenLine, i);
                    return true;
                }
            }
                break;
            case Token::LABEL:
            {
                // need to translate to address later?
            }
                break;
            case Token::INT:
            {
                // for now
            }
                break;
            case Token::COMMA:
                break;
            case Token::LPAREN:
                break;
            case Token::RPAREN:
                break;
            case Token::HEXINT:
            {
            }
                break;
            case Token::WHITESPACE:
                break;
            case Token::REG:
                break;
            case Token::COMMENT:
                break;
        }
        
    }
    
    return false;
}

int Assembler::TranslateJumps(vector<Token> tokenLine, int i)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;
    int funCode = (op == "jr")? 8 : 9;
    
    int *regValue = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);

    int instr = opCode << 26 | *regValue << 21 | funCode;
    
    return instr;
}
/* HELPERS */

/* SYNTAX CHECKER */
void Assembler::AddTokens(vector<Token> tokenLine)
{
    this->Tokens.emplace_back(tokenLine);
}

bool Assembler::IsSyntaxCorrect(vector<Token> tokenLine)
{
    bool correctSyntax = syntaxChecker->CheckInstructionFormat(tokenLine);
    if (correctSyntax == false)
    {
        return false;
    }
    
    for (int i = 0; i < tokenLine.size() && correctSyntax == true; ++i)
    {
        Token token = tokenLine[i];
        Token::Kind tokenKind = token.getKind();
        
        switch(tokenKind)
        {
            case Token::ID:
            {
                PC += 4;

                string lexemme = tokenLine[i].getLexeme();
                if (lexemme == "jr" || lexemme == "jalr")
                {
                    correctSyntax = this->syntaxChecker->CheckJumpsSyntax(tokenLine, i);
                    return correctSyntax; 
                }
                
            }
                break;
                
            case Token::WORD:
            {
                correctSyntax = syntaxChecker->CheckWordSyntax(tokenLine, i);
                if (correctSyntax) PC += 4; 
            }
                break;
                
            case Token::LABEL:
            {
                // add label to symbol table if it is a declaration
                if (this->syntaxChecker->IsLabelOP(token))
                {
                    PC += 4;
                    // do other stuff
                }
                else
                {
                    correctSyntax = this->symbolTable->InsertLabel(token, PC);
                }
            }
                break;
            
            case Token::COMMA:
            {
                // do nothing
            }
                break;
            
            case Token::LPAREN:
            {
                
            }
                break;
                
            case Token::RPAREN:
            {
                
            }
                break;
                
            case Token::INT:
            {
                
            }
                break;
                
            case Token::HEXINT:
            {
                
            }
                break;
                
            case Token::COMMENT:
            {
                // do nothing
            }
                break;
                
            case Token::WHITESPACE:
            {
                // do nothing
            }
                break;
                
            case Token::REG:
            {
                
            }
                break;
        }
    }
    
    return correctSyntax;
}

void Assembler::PrintToError()
{
    std::cerr << "ERROR" << std::endl;
    for (auto &printTokenLine: this->Tokens)
    {
        for (auto &printToken: printTokenLine)
        {
            std::cerr << printToken << ' ';
        }
        std::cerr << std::endl;
    }
    this->symbolTable->Print();
}
// Pass 1: Analyse() is called when the text file has been read.
// Checks for errors
// If error is found, intermediate representation and symbol table is outputted
bool Assembler::Analyse()
{
    for (auto &tokenLine: this->Tokens)
    {
        if (this->IsSyntaxCorrect(tokenLine) == false)
        {
            this->PrintToError();
            return false;
        }
    }
    
    this->symbolTable->Print();
    return true; 
}

// Pass 2: Synthesize() translates labels to addresses, translates vector of token list to machine code
void Assembler::Synthesize()
{
    for (auto &tokenLine : this->Tokens)
    {
        if (tokenLine.size() == 0)
        {
            continue;
        }
        int* instr = new int(0);
        bool shouldIOutput = this->Translate(tokenLine, instr);
       // Token::Kind tokenKind = tokenLine[0].getKind();
        
        if (shouldIOutput == true)
        {
            this->OutputMachineCode(instr);
        }
    }
    
}

Assembler::~Assembler()
{
    delete this->syntaxChecker;
    delete this->symbolTable; 
}
