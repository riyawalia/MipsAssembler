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
        Token::Kind nextTokenKind = tokenLine[i + 1].getKind();
        
        correctSyntax = ((nextTokenKind == Token::INT) || (nextTokenKind == Token::HEXINT)) && (tokenLine.size() == i + 2);
        
        if (i != 0)
        {
            for (int j = i; j > -1 && correctSyntax == true; j--)
            {
                correctSyntax = correctSyntax && (tokenLine[j].getKind() == Token::Kind::LABEL);
            }
        }
    }
    
    
    return correctSyntax;
}

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
        // there can be no label definitions, .word op, id op
        
        for (int j = labelsEnd + 2; j < tokenLine.size() && result == true; ++j)
        {
            Token token = tokenLine[j];
            Token::Kind tokenKind = token.getKind();
            if (tokenKind == Token::Kind::COMMENT && j != tokenLine.size() - 1)
            {
                result = false;
            }
            else if (IsTokenOP(token))
            {
                result = false;
            }
        }
    }
    
    return result;
}

SyntaxChecker::~SyntaxChecker() { }
