#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include "assembler.h"
#include <map>

/*
 * C++ Starter code for CS241 A3
 * All code requires C++14, so if you're getting compile errors make sure to
 * use -std=c++14.
 *
 * This file contains the main function of your program. By default, it just
 * prints the scanned list of tokens back to standard output.
 */
using namespace std;

int main() {
    std::string line = "";
    Assembler *assembler = new Assembler();

  try
    {
        while (getline(std::cin, line))
        {
            std::vector<Token> tokenLine = scan(line);
            if (tokenLine.size() != 0)
            {
                assembler->AddTokens(tokenLine);
            }
            
        }
        
        bool success = assembler->Analyse();
        if (success)
        {
            assembler->Synthesize();
        }
        
    }
    catch (ScanningFailure &f)
        {
            std::cerr << f.what() << std::endl;
            return 1;
        }
    
    
    delete assembler; 
    return 0;
}
