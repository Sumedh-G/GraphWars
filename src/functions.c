#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int StrToSymbols(char stringExpression[], Symbol outputBuffer[], int expressionLength)
{
  int count=1;
  char snippet[8] = {0};
  char* snipPtr = snippet;
  char type=TypeOf(stringExpression[0]);

  *outputBuffer++ = (Symbol) { .type = 'b', .contents.name = '(' };

  char charType;
  for (int i=0; i<expressionLength; ++i) {
    if (snipPtr-snippet > 7) return -1;
    if (!stringExpression[i]) {
      *outputBuffer++ = ParseSnippet(snippet, type);
      *outputBuffer++ = (Symbol) { .type = 'B', .contents.name = ')' };
      return (count+2);
    }
    if (stringExpression[i] == ' ' || stringExpression[i] == '\n') continue;

    if ((charType = TypeOf(stringExpression[i])) == type) {
      if (type == 'F') return -1;
      *snipPtr++ = stringExpression[i];
    }
    else {
      if (charType == 'F' && type == 'b') return -1;

      *outputBuffer++ = ParseSnippet(snippet, type);
      type = charType;
      memset(snippet, 0, 8);
      snipPtr = snippet;
      *snipPtr++ = stringExpression[i];
      ++count;
    }
  }

  *outputBuffer++ = (Symbol) { .type = 'B', .contents.name = ')' };
  return (count+1);
}

double ShuntingYard(Symbol expression[], int expressionLength, Variable variables[], int variablesLength)
{
  // argument stack
  double numStack[expressionLength];
  double *numStackPtr = numStack;

  // function stack
  Symbol fStack[expressionLength];
  Symbol *fStackPtr = fStack;

  char startingBracket[8] = {0};
  for (int i=0, j=0, inValidVar; i < expressionLength; ++i) {
    switch (expression[i].type) {
      case 'n':
        *numStackPtr++ = expression[i].contents.value;
        break;

      case 'f': case 'F':
        while (
          Precedence(expression[i]) < Precedence(*(fStackPtr-1)) ||
          (Precedence(expression[i]) == Precedence(*(fStackPtr-1)) && IsLeftAssociative(expression[i]))
        ) {
          EvaluateFunction(*--fStackPtr, &numStackPtr);
        }
        *fStackPtr++ = expression[i];
        break;

      case 'v':
        inValidVar = 1;
        for (j=0; j<variablesLength; ++j) {
          if (strncmp(variables[j].name, expression[i].contents.name, 8) == 0) {
            *numStackPtr++ = variables[j].value;
            inValidVar = 0;
            break;
          }
        }
        if (inValidVar) *numStackPtr++ = 0.00;
        break;

      case 'b':
        *fStackPtr++ = expression[i];
        break;

      case 'B':
        GetMatching(expression[i], startingBracket);
        while (strncmp((*(fStackPtr-1)).contents.name, startingBracket, 8) != 0) {
          EvaluateFunction(*--fStackPtr, &numStackPtr);
        }
        --fStackPtr;
        memset(startingBracket, 0, 8);
        break;
    }
  }

  return numStack[0];
}

Symbol ParseSnippet(char snip[8], char type)
{
  Symbol output;
  output.type = type;
  switch (type) {
    case 'n':
      output.contents.value = atof(snip);
      break;
    case 'f': case 'F': case 'v': case 'b': case 'B':
      strncpy(output.contents.name, snip, 8);
      break;
  }
  return output;
}

char TypeOf(char inp)
{
  switch (inp) {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
      return 'n';
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
    case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
    case 'Q': case 'R': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y':
    case 'Z':
      return 'v';
    case '(': case '[': case '{':
      return 'b';
    case ')': case ']': case '}':
      return 'B';
    case '+': case '-': case '*': case '/': case '%': case '^':
      return 'F';
    default:
      return 'f';
  }
}

void EvaluateFunction(Symbol function, double **argumentStackPtrPtr)
{
  double arg1, arg2;
  switch (function.type) {
    case 'f':
      return;

    case 'F':
      arg2 = *--*argumentStackPtrPtr;
      arg1 = *--*argumentStackPtrPtr;
      switch (function.contents.name[0]) {
        case '+': *(*argumentStackPtrPtr)++ = arg1 + arg2; break;
        case '-': *(*argumentStackPtrPtr)++ = arg1 - arg2; break;
        case '*': *(*argumentStackPtrPtr)++ = arg1 * arg2; break;
        case '^': *(*argumentStackPtrPtr)++ = pow(arg1, arg2); break;
        case '/': if (arg2) *(*argumentStackPtrPtr)++ = arg1 / arg2; break;
        case '%': if ((int)arg2) *(*argumentStackPtrPtr)++ = (float)((int)arg1 % (int)arg2); break;
      }
      return;

    default:
      return;
  }
}

int Precedence(Symbol function)
{
  if (function.type == 'f' || function.type == 'b') return 0;
  switch (function.contents.name[0]) {
    case '+': case '-': return 1;
    case '*': case '/': case '%': return 2;
    case '^': return 3;
    default: return 0;
  }
}

int IsLeftAssociative(Symbol function)
{
  if (function.type == 'f') return 0;
  else if (function.contents.name[0] == '^') return 0;
  return 1;
}

void GetMatching(Symbol bracket, char output[8])
{
  switch (bracket.contents.name[0]) {
    case ')':
      output[0] = '(';
      return;
    case '}':
      output[0] = '{';
      return;
    case ']':
      output[0] = '[';
      return;
  }
}
