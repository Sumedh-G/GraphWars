#include <math.h>
#include "functions.h"

// main idea of blitting functions
//
// 1) Convert input into RPN using shunting yard algorithm
// 2) Build a parser that takes RPN and evaluates it at an input
// 3) Maintain a linked list containing all functions drawn to the screen, sorted
//    to have least time of life to most time of life
// 4) Create a function the walks through the list and draws all functions to the screen
//
// Nice would-haves
// -> Create a chunking system that only renders functions which are visible

int StrToSymbols(char infixExpr[], Symbol output[], int n)
{
  float cnumber = 0;
  int isDecimal = 0;
  int ddeg = 0;
  int symbolCount = 0;
  for (int i=0;infixExpr[i]; i++) {
    if (infixExpr[i] >= '0' && infixExpr[i] <= '9') {
      cnumber = (isDecimal) ? cnumber + infixExpr[i] - '0' * pow(10, -ddeg++) : cnumber * 10 + infixExpr[i] - '0';
    }
    else {
      if ((isDecimal = (infixExpr[i] == '.')) == 1) continue;
      if (cnumber) {
        output[symbolCount].type = 'n';
        output[symbolCount].data.value = cnumber;
        isDecimal = ddeg = cnumber = 0;
        ++symbolCount;
      }

      switch (infixExpr[i]) {
        case 'x': case 'y': output[symbolCount].type = 'v'; break;
        case '(':           output[symbolCount].type = 'b'; break;
        case ')':           output[symbolCount].type = 'B'; break;
        default:            output[symbolCount].type = 'o'; break;
      }
      output[symbolCount].data.op = infixExpr[i];
      ++symbolCount;
    }
  }
  if (cnumber) {
    output[symbolCount].type = 'n';
    output[symbolCount].data.value = cnumber;
    isDecimal = ddeg = 0;
    ++symbolCount;
  }
  return symbolCount;
}

int getPrecedence(char op)
{
  switch (op) {
    case '+': case '-':           return 1;
    case '*': case '/': case '%': return 2;
    case '^':                     return 3;
    default:                      return 0;
  }
}

float getOut(char op, float in1, float in2)
{
  switch (op) {
    case '+': return in1 + in2;
    case '-': return in1 - in2;
    case '*': return in1 * in2;
    case '/': return (in2) ? in1 / in2 : 0.0f;
    case '%': return (in2) ? (int)in1 % (int)in2 : 0.0f;
    case '^': return pow(in1, in2);
    default: return 0.0f;
  }
}

float evalExpression(Symbol expr[], int n, Var vars[], int m)
{
  float operands[n];
  char operators[n];
  float* topNum = operands;
  char* topOp = operators;
  float result = 0.0f;
  *topOp = 'b';

  int j;
  float in1, in2;
  char currOp;
  for (int i=0; i<n; ++i) {
    switch (expr[i].type) {
      case 'b':   // open brackets
        *(++topOp) = 'b';
        break;
      case 'B':   // close brackets
        while (*topOp != 'b') {
          if (topOp == operators) {
            return 0.0f;      // if close brace is unmatched
          }
          in2 = *(--topNum);
          in1 = *(--topNum);
          currOp = *topOp--;
          *topNum++ = getOut(currOp, in1, in2);
        }
        --topOp;
        break;
      case 'n':
        *topNum++ = expr[i].data.value;
        break;
      case 'o':
        while (getPrecedence(expr[i].data.op) < getPrecedence(*topOp)) {
          in2 = *(--topNum);
          in1 = *(--topNum);
          currOp = *topOp--;
          *topNum++ = getOut(currOp, in1, in2);
        }
        *(++topOp) = expr[i].data.op;
        break;
      case 'v':
        for (j=0; j<m; ++j) {
          if (vars[j].name == expr[i].data.op) {
            *topNum++ = vars[j].value;
            break;
          }
        }
        break;
      default:
        break;
    }
  }
  while (topOp > operators) {
    if (*topOp == 'b') {
      --topOp;
      continue;
    }
    in2 = *(--topNum);
    in1 = *(--topNum);
    currOp = *topOp--;
    *topNum++ = getOut(currOp, in1, in2);
  }
  result = *(--topNum);
  return result;
}
