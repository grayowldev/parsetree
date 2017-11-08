/*
 * parser.cpp
 *
 */

#include <string>
using std::string;

#include "parser.h"
#include "lexer.h"

class ParserToken {
private:
    Token	tok;
    bool	pushedBack;

public:
    ParserToken() : pushedBack(false) {}

    Token getToken(istream *in) {
        if( pushedBack ) {
            pushedBack = false;
            return tok;
        }

        return ::getToken(in);
    }
    void pushbackToken(const Token& t) {
        if( pushedBack ) {
            // error
        }
        tok = t;
        pushedBack = true;
    }

} ParserToken;

ParseTree *
Prog(istream* in)
{
    if (getToken(in)!= T_DONE) return 0;
    return StmtList(in);
}

ParseTree *
StmtList(istream* in)
{
    ParseTree *stmt = Stmt(in);
    if( stmt == 0 )
        return 0;

    return new StatementList( stmt, StmtList(in) );
}

ParseTree *	Stmt(istream* in) {
    ParseTree *decl = Decl(in);
    ParseTree *set = Set(in);
    ParseTree *print = Print(in);
    if(decl != 0) {
        return new ParseTree(decl);
    }
    else if(set != 0) {
        return new ParseTree(set);
    }
    else if(print != 0) {
        return new ParseTree(print);
    }
    return 0;
}

ParseTree *	Decl(istream* in) {
    return 0;
}

ParseTree *	Set(istream* in) {
    return 0;
}

ParseTree *	Print(istream* in) {
    Token token = ParserToken.getToken(in);
    if (token == T_PRINT){
        ParseTree *expression = Expr(in);
        token = ParserToken.getToken(in);
        if (t == T_SC){
            return new ParseTree(expression);
        } else{
            ParserToken.pushbackToken(token);
        }

    }
}

ParseTree *Expr(istream* in) {
    ParseTree *t1 = Term(in);
    if( t1 == 0 )
        return 0;

    for(;;) {
        Token op = ParserToken.getToken(in);
        if( op != T_PLUS && op != T_MINUS ) {
            ParserToken.pushbackToken(op);
            return t1;
        }

        ParseTree *t2 = Expr(in);
        if( t2 == 0 ) {
            error(op.GetLinenum(), "expression required after + or - operator");
            return 0;
        }

        // combine t1 and t2 together
        if( op == T_PLUS )
            t1 = new Addition(op.GetLinenum(), t1, t2);
        else
            t1 = new Subtraction(op.GetLinenum(), t1, t2);
    }

    // should never get here...
    return 0;
}

ParseTree *	Term(istream* in) {
    ParseTree *prime = Primary(in);
    Token token = ParserToken.getToken(in);
    if (!token == T_STAR){
        ParserToken.pushbackToken(token);
    }
    return prime;

}

ParseTree *	Primary(istream* in) {
    Token token = ParserToken.getToken(in);
    if (token == T_ICONST){
        return new IntegerConstant(token);
    }
}

