//
//  symbolTable.cpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-25.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#include "symbolTable.h"
SymbolTable::SymbolTable() { }

// returns true if label was inserted successfully, false if it already existed 
bool SymbolTable::InsertLabel(Token label, int address)
{
    string labelName = label.getLexeme();
    // getting rid of the colon in the definition
    labelName.pop_back();
    
    if (this->Table.count(labelName) == 0)
    {
        this->Table[labelName] = address; 
        return true;
    }
    return false;
}

void SymbolTable::Print()
{
    for (auto &pair : this->Table)
    {
        std::cerr << pair.first << ' ' << pair.second << '\n';
    }
    /*
    int labelWidth = 30;
    int addressWidth = 10;
    
    std::cerr << "SYMBOL TABLE\n" << "--------------------------------------------\n";
    std::cerr << '|' << "LABEL" << setw(labelWidth) << setfill(' ');
    std::cerr << '|' << "ADDRESS" << '|' << setw(labelWidth) << setfill(' ') << '\n';
    
    for(auto &pair : this->Table)
    {
        std::cerr << '|' << pair.first << setw(labelWidth) << setfill(' ');
        std::cerr << '|' << pair.second << '|' <<setw(addressWidth) << setfill(' ')  << '\n';
    }
    
    
    std::cerr << "--------------------------------------------\n"; */
}
/*ostream& operator << (ostream &os, const SymbolTable &st)
{
    int labelWidth = 30;
    int addressWidth = 10;
    
    os << "SYMBOL TABLE\n" << "----------------------------------------\n";
    os << '|' << "LABEL" << setw(labelWidth) << setfill(' ');
    os << '|' << "ADDRESS" << setw(labelWidth) << setfill(' ') << '\n';
    
    for(auto &pair : st.Table)
    {
        os << '|' << pair.first << setw(labelWidth) << setfill(' ');
        os << '|' << pair.second << setw(addressWidth) << setfill(' ') << '\n';
    }
    
    os << "----------------------------------------\n";
    return os;
} */
