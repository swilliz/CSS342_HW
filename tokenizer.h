//Samuel Williams
//CSS 342
//tokenizer.h

//Tokenizer creates tokens from a given string
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>

#include "token.h"
using namespace std;

template <class NumericType>
class Tokenizer {
public:
	Tokenizer(istream &is) : in(is), prevToken(OPAREN) { //initializer
	}
	Token<NumericType> getToken();

private:
	istream &in; //in stream
	bool getChar(char &ch); //bool and reassigns ch
	TokenType prevToken; //previous token
};

#include "tokenizer.cpp.h"
#endif