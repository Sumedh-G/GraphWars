#include "functions.h"
#include <stdlib.h>
#include <string.h>

int StrToSymbols(char stringExpression[], Symbol outputBuffer[], int n)
{
  int count=0;
  char snippet[8] = {0};
  char* snipPtr = snippet;
  char type=TypeOf(stringExpression[0]);

  char charType;
  for (int i=0; i<n; ++i) {
    if (snipPtr-snippet > 7) return -1;
    if (!stringExpression[i]) {
      *outputBuffer++ = ParseSnippet(snippet, type);
      return (count+1);
    }
    if (stringExpression[i] == ' ' || stringExpression[i] == '\n') continue;

    if ((charType = TypeOf(stringExpression[i])) == type) *snipPtr++ = stringExpression[i];
    else {
      *outputBuffer++ = ParseSnippet(snippet, type);
      type = charType;
      memset(snippet, 0, 8);
      snipPtr = snippet;
      *snipPtr++ = stringExpression[i];
      ++count;
    }
  }

  return count;
}

Symbol ParseSnippet(char snip[8], char type)
{
  Symbol output;
  output.type = type;
  switch (type) {
    case 'n':
      output.data.value = atof(snip);
      break;
    case 'f': case 'F': case 'v': case 'b': case 'B':
      strncpy(output.data.name, snip, 8);
      break;
  }
  return output;
}

char TypeOf(char inp)
{
  switch (inp) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
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

