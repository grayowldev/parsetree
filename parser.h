/*
 * parser.h
 *
 *  Created on: Oct 23, 2017
 *      Author: gerardryan
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
using std::istream;
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::stoi;

#include "lexer.h"

extern void error(int linenum, const string& message);

enum TypeForNode { INT_TYPE, STRING_TYPE, ERROR_TYPE };

class ParseTree {
    int			linenumber;
    ParseTree	*left;
    ParseTree	*right;

public:
    ParseTree(int n, ParseTree *l = 0, ParseTree *r = 0) : linenumber(n), left(l), right(r) {}
    virtual ~ParseTree() {}

    ParseTree* getLeft() const { return left; }
    ParseTree* getRight() const { return right; }
    int getLineNumber() const { return linenumber; }

    virtual TypeForNode GetType() const { return ERROR_TYPE; }
    virtual int GetIntValue() const { throw "no integer value"; }
    virtual string GetStringValue() const { throw "no string value"; }

    static void traversl(ParseTree* RootNode){
        if (RootNode->getLeft()){
            cout << "L" << endl;
            traversl(RootNode->getLeft());
            cout << "u" << endl;
        }
        if (RootNode->getLeft()){
            cout << "R" << endl;
            traversl(RootNode->getRight());
            cout << "U" << endl;
        }
        cout << "N" << endl;
    }
};

class StatementList : public ParseTree {
public:
    StatementList(ParseTree *first, ParseTree *rest) : ParseTree(0, first, rest) {}

};

class Addition : public ParseTree {
public:
    Addition(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

    // will need to fill in type and value;
    // remember type is a function of
};

class Subtraction : public ParseTree {
public:
    Subtraction(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

    // will need to fill in type and value;
    // remember type is a function of
};

class IntegerConstant : public ParseTree {
    int	value;

public:
    IntegerConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
        value = stoi( tok.GetLexeme() );
    }

    TypeForNode GetType() const { return INT_TYPE; }
    int GetIntValue() const { return value; }
};

extern ParseTree *	Prog(istream* in);
extern ParseTree *	StmtList(istream* in);
extern ParseTree *	Stmt(istream* in);
extern ParseTree *	Decl(istream* in);
extern ParseTree *	Set(istream* in);
extern ParseTree *	Print(istream* in);
extern ParseTree *	Expr(istream* in);
extern ParseTree *	Term(istream* in);
extern ParseTree *	Primary(istream* in);


#endif /* PARSER_H_ */
