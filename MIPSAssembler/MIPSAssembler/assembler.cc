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
void Assembler::OutputMachineCode(unsigned int *instruction)
{
    unsigned int instr = *instruction;
    std::cout << char(instr >> 24) << char(instr >> 16) << char (instr >> 8) << char(instr);
}

/* TRANSLATORS */
bool Assembler::Translate(vector<Token> tokenLine, unsigned int* instr)
{
    *instr = 0;
    for (int i = 0; i < tokenLine.size(); ++i)
    {
        Token opToken = tokenLine[i];
        Token::Kind tokenKind = opToken.getKind();
        
        switch(tokenKind)
        {
            case Token::WORD:
            {
                PC += 4;
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
                        int temp = std::stoi(nextTokenLexemme);
                        *instr = nextTokenLexemme[0] == '-'? temp & 0xffffffff : temp;
                        
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
                    if (false == this->syntaxChecker->IsHexValid(nextTokenLexemme))
                    {
                        return false;
                    }
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
                    PC += 4;
                    *instr = this->TranslateJumps(tokenLine, i);
                    return true;
                }
                else if (this->IsTokenTripleArithmetic(opToken))
                {
                    PC += 4;
                    *instr = this->TranslateTripleArithmetic(tokenLine,i);
                    return true;
                }
                else if (this->IsTokenEquality(opToken))
                {
                    PC += 4;
                    bool result = this->TranslateEquality(tokenLine,i, instr);
                    return result;
                }
                else if (this->IsTokenMoves(opToken))
                {
                    PC += 4;
                    bool result = this->TranslateMoves(tokenLine, i, instr);
                    return result;
                }
                else if (this->IsTokenDoubleArithmetic(tokenLine[i]))
                {
                    PC += 4;
                    bool result = this->TranslateDoubleArithmetic(tokenLine, i,instr);
                    return result; 
                }
                else if (this->IsTokenLoadAndStore(tokenLine[i]))
                {
                    PC += 4;
                    bool result = this->TranslateLoadAndStore(tokenLine,i, instr);
                    return result; 
                }
                else
                {
                    if (i == 0)
                    {
                        this->PrintToError();
                        return false;
                    }
                    
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

bool Assembler::TranslateMoves(vector<Token> tokenLine, int i, unsigned int *instr)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;
    int funCode = 0;
    
    int *regValue = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);
    
    if (regValue == NULL) return false;
    
    if (op == "lis")
    {
        funCode = 20;
    }
    else if (op == "mflo")
    {
        funCode = 18;
    }
    else if (op == "mfhi")
    {
        funCode = 16;
    }
    else
    {
        throw exception();
    }
    
    *instr = (opCode << 16) | (*regValue << 11 ) | (funCode);
    return true;
}
unsigned int Assembler::TranslateJumps(vector<Token> tokenLine, int i)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;
    int funCode = (op == "jr")? 8 : 9;
    
    int *regValue = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);

    unsigned int instr = opCode << 26 | *regValue << 21 | funCode;
    
    return instr;
}

unsigned int Assembler::TranslateTripleArithmetic(vector<Token> tokenLine, int i)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;;
    int funCode = -1;
    
    int *d = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);
    int *s = this->syntaxChecker->GetRegisterValue(tokenLine[i + 3]);
    int *t = this->syntaxChecker->GetRegisterValue(tokenLine[i + 5]);
    
    unsigned int instr = -1;
    
    if (op == "add")
    {
        funCode = 32;
    }
    else if (op == "sub")
    {
        funCode = 34;
    }
    else if (op == "slt")
    {
        funCode = 42;
    }
    else if (op == "sltu")
    {
        funCode = 43;
    }
    else
    {
        throw exception();
    }
    
    instr = (opCode << 26) | (*s << 21) | (*t << 16) | (*d << 11) | (funCode);
    
    return instr;
}

bool Assembler::TranslateDoubleArithmetic(vector<Token> tokenLine, int i, unsigned int *instr)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;
    int funCode = 0;
    
    int *s = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);
    int *t = this->syntaxChecker->GetRegisterValue(tokenLine[i + 3]);
    
    if (s == NULL || t == NULL)
    {
        this->PrintToError("Error to do with registers.");
        return false;
    }
    
    
    if (op == "mult")
    {
        funCode = 24;
    }
    else if (op == "multu")
    {
        funCode = 25;
    }
    else if (op == "div")
    {
        funCode = 26;
    }
    else if (op == "divu")
    {
        funCode = 27;
    }
    else
    {
        throw exception(); 
    }
    
    *instr = (opCode << 26) | (*s << 21) | (*t << 16) | funCode;
    return true;
}

bool Assembler::TranslateLoadAndStore(vector<Token> tokenLine, int i, unsigned int *instr)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;
    
    int *d = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);
    int *s = this->syntaxChecker->GetRegisterValue(tokenLine[i + 5]);
    
    if (s == NULL || d == NULL)
    {
        this->PrintToError("Error to do with registers");
        return false;
    }
    
    Token param = tokenLine[i + 3];
    int immediate = -1;
    
    if (param.getKind() == Token::INT)
    {
        immediate = std::stoi(param.getLexeme());
       // if (param.getLexeme()[0] == '-')
        //{
            immediate = immediate & 0xffff;
       // }
    }
    else if (param.getKind() == Token::HEXINT)
    {
        immediate = std::stoul(param.getLexeme(), 0, 16);
    }
    
    if (op == "lw")
    {
        opCode = 35;
    }
    else if (op == "sw")
    {
        opCode = 43;
    }
    else
    {
        throw exception();
    }
    
    *instr = (opCode << 26) | (*s << 21) | (*d << 16) | (immediate);
    return true;
}

bool Assembler::TranslateEquality(vector<Token> tokenLine, int i, unsigned int *instr)
{
    string op = tokenLine[i].getLexeme();
    int opCode = 0;;
    
    int *s = this->syntaxChecker->GetRegisterValue(tokenLine[i + 1]);
    int *t = this->syntaxChecker->GetRegisterValue(tokenLine[i + 3]);
    *instr = -1;
    
    string lexemme = tokenLine[i + 5].getLexeme();
    Token::Kind immediateKind = tokenLine[i + 5].getKind();
    int immediate = -1;
   // unsigned int finali = 1;
    
    if (immediateKind == Token::INT)
    {
        immediate = std::stoi(lexemme);
        if(lexemme [0] == '-')
        {
            immediate = immediate & 0xffff;
        }
        
    }
    else if (immediateKind == Token::HEXINT)
    {
        string maxHex = "0xffff";
        if (this->syntaxChecker->IsHexValid(lexemme, maxHex) == false)
        {
            return false;
        }
        immediate = std::stoul(lexemme, 0, 16);
    }
    else if (immediateKind == Token::ID)
    {
        unsigned int* address = this->symbolTable->GetAddressIfExists(lexemme);
        if (address == NULL)
        {
            this->PrintToError("Label has not been defined before");
            return false;
        }
        immediate = (*address - PC - 4) / 4;
        
        if (immediate < -32768 || immediate > 32767)
        {
            this->PrintToError("Label offset exceeds limits");
            return false;
        }
        
    }
    
    if (op == "bne")
    {
        opCode = 5;
    }
    else if (op == "beq")
    {
        opCode = 4;
    }
    else
    {
        throw exception();
    }

    
    *instr = (opCode << 26) | (*s << 21) | (*t << 16) | (immediate & 0xffff);
    return true;
}

/* HELPERS */
bool Assembler::IsTokenTripleArithmetic(Token token)
{
    string lexemme = token.getLexeme();
    
    return (lexemme == "add" || lexemme == "sub" || lexemme == "slt" || lexemme == "sltu");
}

bool Assembler::IsTokenEquality(Token token)
{
    string lexemme = token.getLexeme();
    return lexemme == "beq" || lexemme == "bne";
}

bool Assembler::IsTokenDoubleArithmetic(Token token)
{
    string lexemme = token.getLexeme();
    
    return lexemme == "mult" || lexemme == "multu" || lexemme == "div" || lexemme == "divu";
}
bool Assembler::IsTokenLoadAndStore(Token token)
{
    string lexemme = token.getLexeme();
    return lexemme == "lw" || lexemme == "sw";
}
bool Assembler::IsTokenMoves(Token token)
{
    string lexemme = token.getLexeme();
    return lexemme == "lis" || lexemme == "mflo" || lexemme == "mfhi"; 
 }
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
                string lexemme = tokenLine[i].getLexeme();
                if (lexemme == "jr" || lexemme == "jalr")
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckJumpsSyntax(tokenLine, i);
                    return correctSyntax; 
                }
                else if (this->IsTokenTripleArithmetic(token))
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckTripleArithmeticSyntax(tokenLine,i);
                    return correctSyntax;
                }
                else if (this->IsTokenEquality(token))
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckEquality(tokenLine,i);
                    return correctSyntax; 
                }
                else if (this->IsTokenMoves(tokenLine[i]))
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckMovesSyntax(tokenLine, i);
                    return correctSyntax; 
                }
                else if (this->IsTokenDoubleArithmetic(tokenLine[i]))
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckDoubleArithmeticSyntax(tokenLine,i);
                    return correctSyntax;
                }
                else if (this->IsTokenLoadAndStore(tokenLine[i]))
                {
                    PC += 4;
                    correctSyntax = this->syntaxChecker->CheckLoadAndStoreSyntax(tokenLine, i);
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
                // add label to symbol table
                correctSyntax = this->symbolTable->InsertLabel(token, PC);
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

void Assembler::PrintToError(string message)
{
    std::cerr << "ERROR" << message << std::endl;
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
    // reset PC
    PC = -4;
    
    for (auto &tokenLine : this->Tokens)
    {
        if (tokenLine.size() == 0)
        {
            continue;
        }
        unsigned int* instr = new unsigned int(0);
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
