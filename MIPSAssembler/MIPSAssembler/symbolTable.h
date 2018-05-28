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
    map<string, unsigned long int> Table;
    
public:
    SymbolTable();
    ~SymbolTable(); 
    
    bool InsertLabel(Token label, unsigned long int address);
    unsigned int* GetAddressIfExists (string labelName);
    void Print(); 
    
};


#endif /* symbolTable_h */

