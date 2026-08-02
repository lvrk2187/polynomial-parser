#include "../include/parser.h"
#include "../include/polynomial.h"

int main() {
  polynomial *p = parser("x^2 + 3x^5 - 3x^8 + 2x^4");
  print_poly(*p);
  
  polynomial_free(p);
}
