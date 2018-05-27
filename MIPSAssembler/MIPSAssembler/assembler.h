//
//  assembler.h
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#ifndef assembler_h
#define assembler_h

#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include "symbolTable.h"
#include "syntaxChecker.h"
#include "translator.h"
#include <map>


using namespace std;

class Assembler
{
private:
    vector<vector<Token>> Tokens;
    SymbolTable *symbolTable;
    SyntaxChecker *syntaxChecker;
    int PC; 
    
    bool IsSyntaxCorrect(vector<Token> tokenLine);
    int Translate(vector<Token> tokenLine);
    void OutputMachineCode(int instr);
    
public:
    Assembler();
    ~Assembler(); 
    
    void AddTokens(vector<Token> tokenLine);
    
    bool Analyse();
    
    void Synthesize();
    
};


#endif /* assembler_h */