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

//string test data for possible polynomials
char p_string_1[] = "x^2 + 43x + 22";
char p_string_2[] = "x^2 + 3x^5 - 3 + 2x^0";
char p_string_3[] = "32";
char p_string_4[] = "4x^2 + 3x^5 - 3x^8 + 2x";


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

void assert_with_print(bool condition, const char* message) {
  assert(condition);
  printf("%s: PASSED\n", message);
}

void tests_for_size_of_poly() {

  assert_with_print(sizenofpoly(p_string_1) == 3, "p_string1 length TEST PASSED");
  assert_with_print(sizenofpoly(p_string_2) == 4, "p_string2 length TEST PASSED");
  assert_with_print(sizenofpoly(p_string_3) == 1, "p_string3 length TEST PASSED");
}

void poly_one() {
  polynomial *p = parser(p_string_4);
  EXPECTED_POLY (
                  *p,
                  sizeofpoly(p_string_4) * (int) (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
                   1, 4, 1, 2,
                   1, 3, 1, 5,
                  -1, 3, 1, 8,
                   1, 2, 1, 1
                );
    
  polynomial_free(p);
}

void poly_two() {

}

int main() {

  tests_for_size_of_poly(); 
  poly_one();
}
