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
    this->SymbolTable = new class SymbolTable();
    this->SyntaxChecker = new class SyntaxChecker();
   // this->Translator = new class Translator(); 
}



void Assembler::OutputMachineCode(unsigned int *instr)
{
    if (instr == NULL)
    {
        // there is nothing to output 
        return;
    }
    std::cout << PC << ": ";
    
    unsigned char c = *instr >> 24;
    
    c = *instr >> 16;
    std::cout << c;
    
    c = *instr >> 8;
    std::cout << c;
    
    c = *instr;
    std::cout << instr;
}


unsigned int *Assembler::Translate(vector<Token> tokenLine)
{
    Token opToken = tokenLine[0];
    Token::Kind tokenKind = opToken.getKind();
    
    unsigned int* instr = NULL;
    
    switch(tokenKind)
    {
        case Token::WORD:
        {
            int i = std::stoi(tokenLine[1].getLexeme());
            *instr =  i; //(0 << 26) | (0 << 21) | (0 << 16) | (0 << 11) | (i & 0xffff);
            return instr;
        }
            break;
        case Token::ID:
            break;
        case Token::LABEL:
            break;
        case Token::INT:
            break;
        case Token::COMMA:
            break;
        case Token::LPAREN:
            break;
        case Token::RPAREN:
            break;
        case Token::HEXINT:
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
                correctSyntax = SyntaxChecker->CheckWordSyntax(tokenLine, i);
            }
                break;
                
            case Token::LABEL:
            {
                // add label to symbol table if it is a declaration
                if (this->SyntaxChecker->IsLabelOP(token))
                {
                    PC += 4;
                    // do other stuff
                }
                else
                {
                    correctSyntax = this->SymbolTable->InsertLabel(token, PC);
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
            this->SymbolTable->Print();
            return false;
        }
    }
    
    this->SymbolTable->Print();
    return true; 
}

// Pass 2: Synthesize() translates labels to addresses, translates vector of token list to machine code
void Assembler::Synthesize()
{
    for (auto &tokenLine : this->Tokens)
    {
        unsigned int* machineCode = this->Translate(tokenLine);
        this->OutputMachineCode(machineCode);
        
        delete machineCode;
       // for (auto &token : tokenLine)
       // {
        //    string lexemme = token.getLexeme();
            // Translate(i); for non .word instructions
         //   OutputMachineCode(std::stoi(lexemme));
        //}
    }
    
}
