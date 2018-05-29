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
    unsigned long int PC;
    
    bool IsSyntaxCorrect(vector<Token> tokenLine);
    
    bool Translate(vector<Token> tokenLine, unsigned int* instr);
    void OutputMachineCode(unsigned int* instruction);
   // void OutputMachineCode(int* instruction);
    void PrintToError(string message = "");
    
    /* Translators */
    unsigned int TranslateJumps(vector<Token> tokenLine, int i);
    
    unsigned int TranslateTripleArithmetic(vector<Token> tokenLine, int i);
    bool IsTokenTripleArithmetic(Token token);
    
    bool TranslateEquality(vector<Token> tokenLine, int i, unsigned int *instr);
    
    bool TranslateMoves(vector<Token> tokenLine, int i, unsigned int *instr);
    bool IsTokenMoves(Token token);
    
    bool TranslateDoubleArithmetic(vector<Token> tokenLine, int i, unsigned int *instr);
    bool IsTokenDoubleArithmetic(Token token); 
    
    bool TranslateLoadAndStore(vector<Token> tokenLine, int i, unsigned int *instr);
    bool IsTokenLoadAndStore(Token token);
    
    bool IsTokenEquality(Token token); 
    
    
    
public:
    Assembler();
    ~Assembler(); 
    
    void AddTokens(vector<Token> tokenLine);
    
    bool Analyse();
    
    void Synthesize();
    
};


#endif /* assembler_h */
