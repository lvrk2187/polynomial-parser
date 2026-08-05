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
char p_string_5[] = "-37x^2 - 3x^-82 + 33x";
char p_string_6[] = "-3x^2 + 23";


bool HANDLE_EXPECTED_POLY(polynomial p, int argc, ...) {

  bool pass = true;
  va_list elements;
  va_start(elements, argc);

  for (int i = 0; i < (argc >> 2); i++) {

    int actual_elements[NUMBER_OF_ELEMENTS_IN_A_MONOMIAL] = {
      p.items[i].c_operator,
      p.items[i].coefficient,
      p.items[i].e_operator,
      p.items[i].exponent
    };

     for (int k = 0; k < NUMBER_OF_ELEMENTS_IN_A_MONOMIAL; k++) {

        int actual = actual_elements[k];
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

  printf("\n");
  va_end(elements);
  
  return pass;
}

void assert_with_print(bool condition, const char* given_expr_test) {
  if (condition) printf("passed: ");
  else printf("failed: ");

  printf("for %s\n", given_expr_test);
  
}

void tests_for_size_of_poly() {

  assert_with_print(sizenofpoly(p_string_1) == 3, p_string_1);
  assert_with_print(sizenofpoly(p_string_2) == 4, p_string_2);
  assert_with_print(sizenofpoly(p_string_3) == 1, p_string_3);
}

void poly_one() {
  polynomial *p = parser(p_string_4);
  HANDLE_EXPECTED_POLY (
    *p,
    sizeofpoly(p_string_4) * (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
     1, 4, 1, 2,
     1, 3, 1, 5,
    -1, 3, 1, 8,
     1, 2, 1, 1
  );
    
  polynomial_free(p);
}

void poly_two() {
  polynomial *p = parser(p_string_5);

  HANDLE_EXPECTED_POLY(
    *p,
    sizeofpoly(p_string_5) * (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
    -1, 37, 1, 2,
    -1, 3, -1, 82,
     1, 33, 1, 1 
  );

  polynomial_free(p);
}

//char p_string_1[] = "x^2 + 43x + 22";
void poly_three() {
  polynomial *p = parser(p_string_1);

  HANDLE_EXPECTED_POLY(
    *p,
    sizenofpoly(p_string_1) * (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
    1, 1, 1, 2,
    1, 43, 1, 1,
    1, 22, 1, 0
  );

  polynomial_free(p);
}


void poly_four() {
  
  polynomial *p = parser(p_string_6);

  HANDLE_EXPECTED_POLY(
    *p,
    sizenofpoly(p_string_6) * (NUMBER_OF_ELEMENTS_IN_A_MONOMIAL),
    -1, 3, 1, 2,
    1, 23, 1, 0
  );

  polynomial_free(p);
}

int main() {

  // tests_for_size_of_poly(); 
  // poly_one();
  // poly_two();
  // poly_three();
  // poly_four();

  // polynomial *p = parser("x^2 - 3x + 2");
  // polynomial *p = parser("x^2 - 4x + 4");
  
  // print_poly(*p);

  // struct solutions_for_quadratic s = solve_quadratic(*p);
  // printf("%.1f", s.solution1);
}
