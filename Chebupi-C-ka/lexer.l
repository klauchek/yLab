%option c++

%{

#include "grammar.tab.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
VAR     [a-zA-Z][a-zA-Z_0-9]*
%%

{WS}              /* skip blanks and tabs */
"+"               return yy::parser::token_type::PLUS;
"-"               return yy::parser::token_type::MINUS;
"="               return yy::parser::token_type::EQUAL;
";"               return yy::parser::token_type::SCOLON;
"*"               return yy::parser::token_type::MUL;
"/"               return yy::parser::token_type::DIV;
{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
"if"              return yy::parser::token_type::IF;
"while"           return yy::parser::token_type::WHILE;
"print"           return yy::parser::token_type::PRINT;
{VAR}             return yy::parser::token_type::LVAL;
"("               return yy::parser::token_type::LBR;
")"               return yy::parser::token_type::RBR;
"{"               return yy::parser::token_type::LCBR;
"}"               return yy::parser::token_type::RCBR;
.			            return yy::parser::token_type::ERR;

%%

// nothing