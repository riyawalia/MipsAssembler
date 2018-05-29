//
//  syntaxChecker.hpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#ifndef syntaxChecker_h
#define syntaxChecker_h
#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include "symbolTable.h"
#include <map>


class SyntaxChecker
{
private:
    bool CheckAddSyntax(vector<Token> tokenLine, int i);
    bool IsTokenOP(Token token); 
    
public:
    ~SyntaxChecker();
    
    bool CheckInstructionFormat(vector<Token> tokenLine); 
    bool IsLabelOP(Token label);
    
    bool CheckWordSyntax(vector<Token> tokenLine, int i);
    bool CheckIDSyntax(vector<Token> tokenLine, int i);
    bool CheckRegSyntax(vector<Token> tokenLine, int i);
    bool CheckJumpsSyntax(vector<Token> tokenLine, int i);
    bool CheckTripleArithmeticSyntax(vector<Token> tokenLine, int i);
    bool CheckEquality(vector<Token> tokenLine, int i); 
    
    int* GetRegisterValue(Token reg);
};

#endif /* syntaxChecker_h */
