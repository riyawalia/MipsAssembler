//
//  translater.hpp
//  MIPSAssembler
//
//  Created by Riya Walia on 2018-05-26.
//  Copyright © 2018 Riya Walia. All rights reserved.
//

#ifndef translater_hpp
#define translater_hpp

#include "assembler.h"

class Translator
{
public:
    Translator();
    int Translate(vector<Token> tokenLine);
    
};
#endif /* translater_h */
