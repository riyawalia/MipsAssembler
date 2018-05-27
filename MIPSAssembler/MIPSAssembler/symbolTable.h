//
//  symbolTable.hpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#ifndef symbolTable_h
#define symbolTable_h

#include <stdio.h>
#include <map>
#include <string>
#include <iomanip>
#include <iostream>
#include "scanner.h"

using namespace std; 

class SymbolTable
{
private:
    map<string, int> Table;
    
public:
    SymbolTable();
    ~SymbolTable(); 
    
    bool InsertLabel(Token label, int address);
    void Print(); 
    
  //  friend ostream& operator << (ostream &os, const SymbolTable &st);
};


#endif /* symbolTable_h */
