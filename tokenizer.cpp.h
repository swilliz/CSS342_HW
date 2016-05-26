//Samuel Williams
//CSS 342
//tokenizer.cpp.h

//Tokenizer implementation.  Takes a sting and creates tokens
//from the string based on what tokenType the string contains
template <class NumericType>
bool Tokenizer<NumericType>::getChar(char &ch) {
	char tmp;
	// skip blanks
	while (in.get(tmp) && tmp == ' ');

	// read a char 
	if (in.good() && tmp != '\n'&& tmp != '\0') {
		ch = tmp;
		return true; // if it is not a delimiter
	}
	else
		return false; // if it's a delimitter
}

//Gets the next token.
//Default returns EOL, else if there is a tokenType,
//returns the token with tokenType and sets prevToken to tokenType
template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken() {

	char ch;
	NumericType theValue;

	if (getChar(ch) == true) {
		switch (ch) {

		case 'a':
			prevToken = VAR_A;
			return Token<NumericType>(VAR_A, 0);
		case 'b':
			prevToken = VAR_B;
			return Token<NumericType>(VAR_B, 0);
		case 'c':
			prevToken = VAR_C;
			return Token<NumericType>(VAR_C, 0);

		case '(': return (prevToken = OPAREN);
		case ')': return (prevToken = CPAREN);

		case '!':
			if (getChar(ch) == true && ch == '=')
				return (prevToken = NOTEQUAL);
			in.putback(ch);
			//cerr << "no negation allowed" << endl;
			return (prevToken = NOT);
		case '~': return (prevToken = BIT_COMP);

		case '*': return (prevToken = MULT);

		case '/': return (prevToken = DIV);

		case '%': return (prevToken = MODULUS);

		case '+': 
			if(prevToken == OPAREN)
				return (prevToken = UN_PLUS);
			else
				return (prevToken = PLUS);

		case '-': 
			if (prevToken == OPAREN)
				return (prevToken = UN_MINUS);
			else
				return (prevToken = MINUS);

		case '<':
			if (getChar(ch) == true) {
				switch (ch) {
				case '<': return (prevToken = SHIFT_L);
				case '=': return (prevToken = LE);
				default:
					in.putback(ch);
					return (prevToken = LT);
				}
			}
			in.putback(ch);
			return (prevToken = LT);

		case '>':
			if (getChar(ch) == true) {
				switch (ch) {
				case '>': return (prevToken = SHIFT_R);
				case '=': return (prevToken = GE);
				default:
					in.putback(ch);
					return (prevToken = GT);
				}
			}
			in.putback(ch);
			return (prevToken = GT);

		case '&':
			if (getChar(ch) == true && ch == '&')
				return (prevToken = LOG_AND);
			in.putback(ch);
			return (prevToken = BIT_AND);

		case '^': return (prevToken = BIT_EOR);

		case '|':
			if (getChar(ch) == true && ch == '|')
				return (prevToken = LOG_OR);
			in.putback(ch);
			return (prevToken = BIT_IOR);

		case '=': 
			if (getChar(ch) == true && ch == '=')
				return (prevToken = EQUAL);
			in.putback(ch);

			return (prevToken = DIR_ASSIGN);

		default:
			in.putback(ch);
			if (!(in >> theValue)) {
				cerr << "Parse error" << endl;
				return (prevToken = EOL);
			}
			prevToken = VALUE;
			return Token<NumericType>(VALUE, theValue);
		}
	}
	return (prevToken = EOL);
}