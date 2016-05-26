//Samuel Williams
//CSS 342
//evaulator.cpp.h

// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error. 
template<class NumericType>
NumericType Evaluator<NumericType>::getValue() {

	Tokenizer<NumericType> tok(str);
	Token<NumericType> lastToken;

	do {
		lastToken = tok.getToken(); //MULT, DIV, ECT
		processToken(lastToken);
	} while (lastToken.getType() != EOL);

	if (postFixStack.empty()) {
		cerr << "Missing operatnd!" << endl;
		return 0;
	}

	NumericType theResult = postFixStack.back();
	postFixStack.pop_back();
	if (!postFixStack.empty())
		cerr << "Warning: missing operators!" << endl;

	return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken(const Token<NumericType> &lastToken) {
	TokenType topOp;
	TokenType lastType = lastToken.getType();

	switch (lastType) { //if it is a value, var, cparen, or else
	case VALUE:
		postFixStack.push_back(lastToken.getValue());
		postFixVarStack.push_back(' ');
		return;
	case VAR_A:
		postFixStack.push_back(var_a);
		postFixVarStack.push_back('a');
		return;
	case VAR_B:
		postFixStack.push_back(var_b);
		postFixVarStack.push_back('b');
		return;
	case VAR_C:
		postFixStack.push_back(var_c);
		postFixVarStack.push_back('c');
		return;
	case CPAREN:
		while ((topOp = opStack.back()) != OPAREN &&
			topOp != EOL)
			binaryOp(topOp);
		if (topOp == OPAREN)
			opStack.pop_back(); // get rid of opening parethesis
		else
			cerr << "Missing open parenthesis" << endl;
		break;

		// general operator case
	default:
		while (PREC_TABLE[lastType].inputSymbol <=
			PREC_TABLE[topOp = opStack.back()].topOfStack)
			binaryOp(topOp);

		if (lastToken.getType() != EOL)
			opStack.push_back(lastType);

		break;
	}
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp(TokenType topOp) {
	if (topOp == OPAREN) {
		cerr << "Unbalanced parenthss" << endl;
		opStack.pop_back();
		return;
	}

	else { 
		NumericType rhs = getTop(); //rhs value
		if (topOp == DIR_ASSIGN) { //if a direct assign
			NumericType tmp = getTop(); //for binary operations
			NumericType var = postFixVarStack.back(); //var
			postFixVarStack.pop_back();
			var = rhs;
			if (tmp == 'a') {
				postFixStack.push_back(var_a = rhs);
				postFixVarStack.push_back('a');
				break;
			}
			else if (tmp == 'b') {
				postFixStack.push_back(var_b = rhs);
				postFixVarStack.push_back('b');
				break;
			}
			else if (tmp == 'c') {
				postFixStack.push_back(var_c = rhs);
				postFixVarStack.push_back('c');
				break;
			}
		}

		//else a unary operator
		else if (topOp == UN_PLUS || topOp == UN_MINUS || topOp == NOT ||
			topOp == BIT_COMP)
		{
			if (topOp == UN_PLUS)
				postFixStack.push_back(+rhs);
			else if (topOp == UN_MINUS)
				postFixStack.push_back(-rhs);
			else if (topOp == NOT)
				postFixStack.push_back(!rhs);
			else if (topOp == BIT_COMP)
				postFixStack.push_back(~rhs);
		}

		else { //else binary operator
			NumericType lhs = getTop(); //for binary operations

			// the original operators
			if (topOp == PLUS)
				postFixStack.push_back(lhs + rhs);
			else if (topOp == MINUS)
				postFixStack.push_back(lhs - rhs);
			else if (topOp == MULT)
				postFixStack.push_back(lhs * rhs);
			else if (topOp == DIV)
				if (rhs != 0)
					postFixStack.push_back(lhs / rhs);
				else {
					cerr << "Division by zero" << endl;
					postFixStack.push_back(lhs);
				}

				// C++ operators
			else if (topOp == MODULUS)
				postFixStack.push_back(lhs % rhs);
			else if (topOp == SHIFT_L)
				postFixStack.push_back(lhs << rhs);
			else if (topOp == SHIFT_R)
				postFixStack.push_back(lhs >> rhs);
			else if (topOp == LT)
				postFixStack.push_back(lhs < rhs);
			else if (topOp == LE)
				postFixStack.push_back(lhs <= rhs);
			else if (topOp == GT)
				postFixStack.push_back(lhs > rhs);
			else if (topOp == GE)
				postFixStack.push_back(lhs >= rhs);
			else if (topOp == EQUAL)
				postFixStack.push_back(lhs == rhs);
			else if (topOp == NOTEQUAL)
				postFixStack.push_back(lhs != rhs);
			else if (topOp == BIT_AND)
				postFixStack.push_back(lhs & rhs);
			else if (topOp == BIT_EOR)
				postFixStack.push_back(lhs ^ rhs);
			else if (topOp == BIT_IOR)
				postFixStack.push_back(lhs | rhs);
			else if (topOp == LOG_AND)
				postFixStack.push_back(lhs && rhs);
			else if (topOp == LOG_OR)
				postFixStack.push_back(lhs || rhs);
		}
	}
	opStack.pop_back();
}

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop() {
	if (postFixStack.empty()) {
		cerr << "Missing operand" << endl;
		return 0;
	}

	NumericType tmp = postFixStack.back();
	postFixStack.pop_back();
	return tmp;
}

