//
//  syntaxChecker.cpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#include "syntaxChecker.h"

bool SyntaxChecker::IsLabelOP(Token label)
{
    if (label.getKind() != Token::LABEL)
    {
        return false;
    }
    std::string labelName = label.getLexeme();
    
    return labelName [ labelName.length() - 1] != ':';
    
}

bool SyntaxChecker::IsTokenOP(Token token)
{
    Token::Kind tokenKind = token.getKind();
    if (tokenKind == Token::Kind::LABEL)
    {
        return IsLabelOP(token);
    }
    else if (tokenKind == Token::Kind::WORD || tokenKind == Token::Kind::ID)
    {
        return true;
    }
    return false;
}
bool SyntaxChecker::CheckWordSyntax(vector<Token> tokenLine, int i)
{
    // Correct Syntax: .WORD INT/HEXINT
    bool correctSyntax = (i + 1 < tokenLine.size());
    
    if (correctSyntax)
    {
        Token nextToken = tokenLine[i + 1];
        Token::Kind nextTokenKind = nextToken.getKind();
        
        correctSyntax = ((nextTokenKind == Token::ID) || (nextTokenKind == Token::INT) || (nextTokenKind == Token::HEXINT));
        // if comment, then last
        correctSyntax = (i + 3 < tokenLine.size())?  tokenLine[i + 3].getKind() == Token::COMMENT : correctSyntax;
    }
    
    
    return correctSyntax;
}

bool SyntaxChecker::CheckJumpsSyntax(vector<Token> tokenLine, int i)
{
    bool result = (i + 1 == tokenLine.size() - 1);
    if (result)
    {
        int *reg = this->GetRegisterValue(tokenLine[i + 1]);
        result = reg != NULL; 
    }
    
    return result;
}

bool SyntaxChecker::CheckTripleArithmeticSyntax(vector<Token> tokenLine, int i)
{
    /* ID REG COMMA REG COMMA REG COMMENT*/
    bool result = i + 5 ==  tokenLine.size() || i + 6 == tokenLine.size();
    
    for (int j = i + 1; j < tokenLine.size() && result == true; ++j)
    {
        Token token = tokenLine[j];
        Token::Kind tokenKind = token.getKind();
        
        if (j == i + 1 || j == i + 3 || j == i + 5 )
        {
            result = this->GetRegisterValue(token) != NULL;
        }
        else if (j == i + 6)
        {
            result = tokenKind == Token::Kind::COMMENT;
        }
        else
        {
            result = tokenKind == Token::Kind::COMMA;
        }
    }
    
    return result;
}
bool SyntaxChecker::CheckMovesSyntax(vector<Token> tokenLine, int i)
{
    /* ID REG COMMENT*/
    bool result = ((i + 1) <= tokenLine.size() - 1);
    
    for (int j = i + 1; j < tokenLine.size() && result; ++j)
    {
        if (j == i + 1)
        {
            result = this->GetRegisterValue(tokenLine[j]) != NULL;
        }
        else if (j == i + 2)
        {
            result = tokenLine[j].getKind() == Token::Kind::COMMENT;
        }
        else
        {
            result = false;
        }
    }
    
    return result; 
}

bool SyntaxChecker::CheckDoubleArithmeticSyntax(vector<Token> tokenLine, int i)
{
    /* ID REG COMMA REG COMMENT*/
    bool result = (i + 3 == tokenLine.size() - 1) || (i + 4 == tokenLine.size() - 1);
    for (int j = i + 1; j < tokenLine.size() - 1 && result; ++j)
    {
        if (j == i + 1 || j == i + 3)
        {
            result = this->GetRegisterValue(tokenLine[j]) != NULL;
        }
        else if (j == i + 2)
        {
            result = tokenLine[j].getKind() == Token::Kind::COMMA;
        }
        else if (j == i + 4)
        {
            result = tokenLine[i].getKind() == Token::Kind::COMMENT;
        }
        else
        {
            result = false; 
        }
    }
    
    return result;
}

bool SyntaxChecker::CheckLoadAndStoreSyntax(vector<Token> tokenLine, int i)
{
    /*ID REG COMMA INT/HEXINT LPAREN REG RPAREN COMMENT*/
    bool result = i + 6 == tokenLine.size() - 1 || i + 7 == tokenLine.size() - 1;
    
    for (int j = i + 1; j < tokenLine.size() && result; ++j)
    {
        Token::Kind tokenKind = tokenLine[j].getKind();
        
        if (j == i + 1 || j == i + 5)
        {
            result = this->GetRegisterValue(tokenLine[j]) != NULL;
        }
        else if (j == i + 2)
        {
            result = tokenKind == Token::Kind::COMMA;
        }
        else if (j == i + 3)
        {
           // result = tokenKind == Token::INT || tokenKind == Token::HEXINT;
            if (tokenKind == Token::INT)
            {
                try
                {
                    int immediate = std::stoi(tokenLine[j].getLexeme());
                    result = (immediate >= -32768) && (immediate <= 32767);
                    
                }
                catch (std::out_of_range &e)
                {
                    result = false;
                }
            }
            else if (tokenKind == Token::HEXINT)
            {
                int immediate = std::stoul(tokenLine[j].getLexeme(), 0, 16);
                int maxHex = std::stoul("0xffff", 0, 16);
                
                result = immediate <= maxHex;
            }
            else
            {
                result = false;
            }
            // do stuff
        }
        else if (j == i + 4)
        {
            result = tokenKind == Token::LPAREN;
        }
        else if (j == i + 6)
        {
            result = tokenKind == Token::RPAREN;
        }
        else if (j == i + 7)
        {
            result = tokenKind == Token::COMMENT;
        }
        
    }
        return result;
}

bool SyntaxChecker::CheckEquality(vector<Token> tokenLine, int i)
{
    /*ID REG COMMA REG COMMA INT/HEXINT/LABEL COMMENT */
    bool result = i + 5 ==  tokenLine.size() || i + 6 == tokenLine.size();
    
    for (int j = i + 1; j < tokenLine.size() && result == true; ++j)
    {
        Token::Kind tokenKind = tokenLine[j].getKind();
        
        if (j == i + 1 || j == i + 3)
        {
            result = tokenKind == Token::Kind::REG;
        }
        else if (j == i + 2 || j == i + 4)
        {
            result = tokenKind == Token::Kind::COMMA;
        }
        else if (j == i + 5)
        {
            int immediate;
            
            if (tokenKind == Token::Kind::INT)
            {
                try
                {
                    immediate = std::stoi(tokenLine[j].getLexeme());
                }
                catch (std::out_of_range &e)
                {
                    return false;
                }
                result = immediate >= -32768 && immediate <= 32767;
            }
            else if (tokenKind == Token::Kind::HEXINT)
            {
                immediate = std::stoul(tokenLine[j].getLexeme(), 0, 16);
                int maxHex = std::stoul("0xffff", 0, 16);
                
                result = immediate <= maxHex;
            }
            else if (tokenKind == Token::Kind::ID)
            {
                // do stuff
                result = true;
                // is checked in translate
            }
            else
            {
                result = false;
            }
        }
        else if (j == i + 6)
        {
            result = tokenKind == Token::Kind::COMMENT;
        }
    }
    
    return result;
}
int* SyntaxChecker::GetRegisterValue(Token reg)
{
    int * value = new int();
    if(reg.getKind() != Token::Kind::REG)
    {
        return NULL;
    }
    string lexemme = reg.getLexeme();
    if (lexemme[0] != '$')
    {
        return NULL;
    }
    lexemme.erase(0, 1);
    value = new int(stoi(lexemme));
    
    if (*value >= 0 && *value <= 31)
    {
        return value;
    }
    return NULL;
}
/* LABEL .WORD/ID ... COMMENT */
bool SyntaxChecker::CheckInstructionFormat(vector<Token> tokenLine)
{
    if (tokenLine.size() == 0)
    {
        return true;
    }
    
    bool result = true;
    
    // check if first few are labels
    int labelsEnd = -1;
    for (int i = 0; i < tokenLine.size(); ++i)
    {
        // if the next token after a label is a label definition
        if ((tokenLine[i].getKind() == Token::Kind::LABEL) && (IsLabelOP(tokenLine[i]) == false))
        {
            ++labelsEnd;
        }
        else
        {
            break;
        }
    }
    
    // once labels end, check if next is op or comment (if comment then last)
    // possible op: .word, ID, non label definition
    if (labelsEnd  + 1 < tokenLine.size())
    {
        Token nextToken = tokenLine[labelsEnd + 1];
        Token::Kind nextTokenKind = tokenLine[labelsEnd + 1].getKind();
        
        result = IsTokenOP(nextToken) || (nextTokenKind == Token::Kind::COMMENT && (labelsEnd + 2) == tokenLine.size());
        
        // make sure if comment then last
        // there can be no label definitions, .word op
        // there can only be ID, register, rparen, lparen, comma, int, hexint, white space,
        
        for (int j = labelsEnd + 2; j < tokenLine.size() && result == true; ++j)
        {
            Token token = tokenLine[j];
            Token::Kind tokenKind = token.getKind();
            if (tokenKind == Token::Kind::COMMENT)
            {
                result = j == tokenLine.size() - 1;
            }
            else if (tokenKind == Token::Kind::LABEL)
            {
                result = false;
            }
            else if (tokenKind == Token::Kind::WORD)
            {
                result = false;
            }
        }
    }
    
    return result;
}

SyntaxChecker::~SyntaxChecker() { }
