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

bool EXPECTED_POLY(polynomial p, int argc, ...) {

  bool pass = true;
  va_list elements;
  va_start(elements, argc);

  int expected_elements_in_c_mono[NUMBER_OF_ELEMENTS_IN_A_MONOMIAL];
  int actual_elements_in_c_mono[NUMBER_OF_ELEMENTS_IN_A_MONOMIAL];

  for (int i = 0; i < (argc >> 2); i++) {

    actual_elements_in_c_mono[0] = p.items[i].c_operator;
    actual_elements_in_c_mono[1] = p.items[i].coefficient;
    actual_elements_in_c_mono[2] = p.items[i].e_operator;
    actual_elements_in_c_mono[3] = p.items[i].exponent;

     for (int k = 0; k < NUMBER_OF_ELEMENTS_IN_A_MONOMIAL; k++) {

        int actual = actual_elements_in_c_mono[k];
        int expected = va_arg(elements, int);

        if (actual == expected) {
          printf("passed: ");
        } else {
          pass = false;
          printf("failed: ");
        }

        printf("expected %d, actual %d\n", expected, actual);
    }    
  }
  return pass;
}

void poly_one() {
  char p_string[] = "x^2 + 3x^5 - 3x^8 + 2x^0";
  polynomial *p = parser(p_string);
  EXPECTED_POLY (
                  *p,
                  sizeofpoly(p_string) * (int) (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
                   1, 1, 1, 2,
                   1, 3, 1, 5,
                  -1, 3, 1, 8,
                   1, 2, 1, 0
                );
    
  polynomial_free(p);
}

void poly_two() {
  
}

int main() {
 
  // poly_one();
  char p_string_1[] = "x^2 + 43x + 22";
  char p_string_2[] = "x^2 + 3x^5 - 3 + 2x^0";
  char p_string_3[] = "32";
  printf("%d", sizenofpoly(p_string_3));
}
