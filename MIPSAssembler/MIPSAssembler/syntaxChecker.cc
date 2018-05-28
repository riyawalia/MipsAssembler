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
bool SyntaxChecker::CheckWordSyntax(vector<Token> tokenLine, int i)
{
    // Correct Syntax: .WORD INT/HEXINT
    bool correctSyntax = (i + 1 < tokenLine.size());
    
    if (correctSyntax)
    {
        Token::Kind nextTokenKind = tokenLine[i + 1].getKind();
        
        correctSyntax = ((nextTokenKind == Token::INT) || (nextTokenKind == Token::HEXINT)) && (tokenLine.size() == i + 2);
    }
    
    
    return correctSyntax;
}

SyntaxChecker::~SyntaxChecker() { }
