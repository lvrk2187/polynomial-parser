#include <stdlib.h>
#include <stdio.h>

#ifndef POLYNOMIAL

#define POLYNOMIAL

typedef struct {
  int c_operator; //-1: minus & 1: plus 
  int coefficient;
  int e_operator;
  int exponent;
} monomial;

typedef struct {
  size_t size;
  monomial* items;
} polynomial;

//states for mini state machine in polynomial size
typedef enum {
  STRING_START,
  PARSING_START_OPERATOR,
  PARSING_NUMBER,
  PARSING_END_OPERATOR,
  PASS
} MATCH_STATE;

int sizenofpoly(char *expr);

//printing functions
void print_mono (monomial m);
void print_poly (polynomial p);

//polynomial struct configuration functions
int sizeofpoly         (char *expr);
polynomial* poly_innit (size_t size);
void polynomial_free   (polynomial *p);
 
#endif
