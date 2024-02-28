/* ------------------------------------------------------------------------- **
 *
 * Source code for MIPT ILab
 * Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
 * Licensed after GNU GPL v3
 *
 * ------------------------------------------------------------------------- **
 *
 *  Grammar with shift/reduce, but correct
 *  EQL -> EQ; EQL | empty
 *  EQ -> E = E
 *  E -> number | E + number | E - number
 *
 * ------------------------------------------------------------------------- */

%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires
{
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// forward decl of argument to parser
namespace yy { class Driver; }
}

%code
{
#include "driver.hpp"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver);
}
}

%token
  EQUAL   "="
  MINUS   "-"
  PLUS    "+"
  MUL    "*"
  DIV    "/"
  SCOLON  ";"
  LBR     "("    
  RBR     ")"
  LCBR     "{"    
  RCBR     "}"
  LVAL     
  IF       "if"
  WHILE    "while"
  PRINT    "print"
  ERR
;

// %token <int> NUMBER
// %nterm <std::vector<int>> expr
// %nterm <std::pair<std::vector<int>, std::vector<int>>> equals
// %nterm <std::vector<std::pair<std::vector<int>, std::vector<int>>>> eqlist

%token <int> NUMBER
%nterm <int> tree
%nterm <int> scope
%nterm <int> statement
%nterm <int> assign
%nterm <int> expr
%nterm <int> mult
%nterm <int> term

%left '+' '-' '*' '/'
%right '='

%start program

%%

program: tree               { std::cout << "tree\n"; 
                              std::cout << driver << "\n";}
;

tree : scope                { std::cout << "scope\n"; }
;

scope: LCBR statement_list RCBR scope { std::cout << "LCBR statement_list RCBR statement_list\n"; }
      | statement_list { std::cout << "statement in scope\n"; }
;

statement_list : statement SCOLON statement_list { std::cout << "statement SCOLON statement\n"; }
               | statement SCOLON           { std::cout << "statement SCOLON\n"; }
               | IF LBR statement RBR  scope                 { std::cout << "if\n"; }
               | WHILE LBR statement RBR  scope                { std::cout << "while\n"; }
               | PRINT statement SCOLON                               { std::cout << "print\n"; } // scope ???

statement: assign               { std::cout << "assign\n";}
        | expr                { std::cout << "expr\n";}
;

assign: LVAL EQUAL expr        { std::cout << "LVAL EQ expr\n";}
;

expr: mult                  { std::cout << "mult\n"; }
    | mult PLUS expr        { std::cout << "mult PLUS expr\n"; }
    | mult MINUS expr       { std::cout << "mult MINUS expr\n"; }
;

mult: term                  { std::cout << "term\n"; }
    | term MUL mult        { std::cout << "term MUL mult\n"; }
    | term DIV mult       { std::cout << "term DIV mult\n"; }
;

term: LBR expr RBR                  { std::cout << "LBR expr RBR\n"; }
    | LVAL        { std::cout << "LVAL\n"; }
    | NUMBER       { std::cout << "NUMBER\n"; }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}