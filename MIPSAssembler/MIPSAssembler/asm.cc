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
    std::string line;
    Assembler *assembler = new Assembler();

  try
    {
        while (getline(std::cin, line))
        {
            std::vector<Token> tokenLine = scan(line);
            assembler->AddTokens(tokenLine);
        }
    }
    catch (ScanningFailure &f)
        {
            std::cout << "ERROR\n";
            std::cerr << f.what() << std::endl;
            return 1;
        }
    
    bool success = assembler->Analyse();
    if (success)
    {
        assembler->Synthesize();
    }
    
    delete assembler;
    return 0;
}
