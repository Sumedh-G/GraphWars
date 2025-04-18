#pragma once

typedef struct Symbol {
  char type;
  union {
    double value;
    char name[8];
  } data;
} Symbol;


int StrToSymbols(char stringExpression[], Symbol outputBuffer[], int n);
Symbol ParseSnippet(char snip[8], char type);
char TypeOf(char inp);
