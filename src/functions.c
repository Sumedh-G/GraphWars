#include <math.h>
#include "functions.h"

float polynomial(float x, int n, float coeff[n+1])
{
  float result = 0;
  for (int i=0; i<=n; ++i) {
    result += powf(x, i) * coeff[i];
  }
  return result;
}
