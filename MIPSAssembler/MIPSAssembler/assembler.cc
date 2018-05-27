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



void Assembler::OutputMachineCode(int instr)
{
    std::cout << char(instr >> 24) << char(instr >> 16) << char (instr >> 8) << char(instr);
}


int Assembler::Translate(vector<Token> tokenLine)
{
    if (tokenLine.size() == 0)
    {
        return -1; 
    }
    Token opToken = tokenLine[0];
    Token::Kind tokenKind = opToken.getKind();
    
    int instr = -1;
    
    switch(tokenKind)
    {
        case Token::WORD:
        {
            Token::Kind nextTokenKind = tokenLine[1].getKind();
            string nextTokenLexemme = tokenLine[1].getLexeme();
            
            if (nextTokenKind == Token::INT)
            {
                instr = std::stoi(nextTokenLexemme);
            }
            else if (nextTokenKind == Token::HEXINT)
            {
                instr = (int) std::stoul(nextTokenLexemme, 0, 16);
            }
          //  instr =  i; //(0 << 26) | (0 << 21) | (0 << 16) | (0 << 11) | (i & 0xffff);
            return instr;
        }
            break;
        case Token::ID:
            break;
        case Token::LABEL:
        {
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
    return instr;
}


void Assembler::AddTokens(vector<Token> tokenLine)
{
    this->Tokens.emplace_back(tokenLine);
}

bool Assembler::IsSyntaxCorrect(vector<Token> tokenLine)
{
    bool correctSyntax = true;
    for (int i = 0; i < tokenLine.size() && correctSyntax == true; ++i)
    {
        
        Token token = tokenLine[i];
        Token::Kind tokenKind = token.getKind();
        
        switch(tokenKind)
        {
                // opcode
            case Token::ID:
            {
                PC += 4;
            }
                break;
                
            case Token::WORD:
            {
                correctSyntax = syntaxChecker->CheckWordSyntax(tokenLine, i);
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

// Pass 1: Analyse() is called when the text file has been read.
// Checks for errors
// If error is found, intermediate representation and symbol table is outputted
bool Assembler::Analyse()
{
    for (auto &tokenLine: this->Tokens)
    {
        if (this->IsSyntaxCorrect(tokenLine) == false)
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
        int machineCode = this->Translate(tokenLine);
        Token::Kind tokenKind = tokenLine[0].getKind();
        
        if (tokenKind == Token::WORD || tokenKind == Token::ID)
        {
            this->OutputMachineCode(machineCode);
        }
    }
    
}

Assembler::~Assembler()
{
    delete this->syntaxChecker;
    delete this->symbolTable; 
}
