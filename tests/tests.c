#include "../include/polynomial.h"
#include "../include/parser.h"
#include <assert.h>
#include <stdarg.h>

  //each element has exactly 4 elements:
  //  int c_operator
  //  int coefficient
  //  int e_operator
  //  int exponent
  
#define NUMBER_OF_ELEMENTS_IN_A_MONOMIAL 4


void EXPECTED_POLY(polynomial p, int argc, ...) {

  va_list elements;
  va_start(elements, argc);

  for (int i = 0; i < (argc >> 2); i++) {
    // assert();  
  }
}

void poly_one() {


  char p_string[] = "x^2 + 3x^5 - 3x^8 + 2";
  polynomial *p = parser(p_string);
  EXPECTED_POLY(*p, sizeofpoly(p_string) * (int) (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL), 3);
  
  assert(p->items[0].coefficient == 1);
  assert(p->items[0].exponent == 2); 
  
  polynomial_free(p);
}

int main() {
 
  // poly_one();
  char p_string_1[] = "x^2 + 3x + 2x^0";

  char p_string_2[] = "x^2 + 3x^5 - 3x^8 + 2x^0";
  // polynomial *p = parser(p_string);

  printf("%d\n", sizeofpoly(p_string_1));

  printf("%d", sizeofpoly(p_string_2));
}
