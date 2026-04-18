#include <stdlib.h>
#include <stdio.h>

#ifndef POLYNOMIAL

#define POLYNOMIAL

typedef struct {
  int c_operator;
  int coefficient;
  int e_operator;
  int exponent;
} monomial;

typedef struct {
  size_t size;
  monomial* items;
} polynomial;

//printing functions
void print_mono (monomial m);
void print_poly (polynomial p);

//polynomial struct configuration functions
int sizeofpoly         (char *expr);
polynomial* poly_innit (size_t size);
void polynomial_free   (polynomial *p);
 
#endif
