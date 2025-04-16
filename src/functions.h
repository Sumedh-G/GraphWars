#pragma once

typedef struct Var {
  char name;
  float value;
} Var;

typedef struct Symbol {
  union {
    float value;
    char op;
  } data;
  char type;
} Symbol;

int getPrecedence(char op);
float getOut(char op, float in1, float in2);
float evalExpression(Symbol expr[], int n, Var vars[], int m);
