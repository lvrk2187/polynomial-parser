#include "../include/polynomial.h"
#include <string.h>

void print_mono(monomial m) {
  printf("coef: %d\nexponent: %d\n", m.coefficient * m.c_operator, m.exponent * m.e_operator);
}

void print_poly(polynomial p) {
  for (int i = 0; i < p.size; i++) {
    print_mono(p.items[i]);
  }
}

int sizeofpoly(char *expr) {
  int size = 0;

  for (int i = 0; i < strlen(expr); i++) {
    if (expr[i] == 'x') {
      size++;
    }    
  }

  return size;
}

polynomial* poly_innit(size_t size) {
  polynomial* p; p = malloc(sizeof(polynomial));
  p->size = size;
  p->items = malloc(sizeof(monomial) * p->size);
  
  for (int i = 0; i < size; i++) {
    p->items[i].c_operator = 1;
    p->items[i].coefficient = 0;
    p->items[i].e_operator = 1;
    p->items[i].exponent = 0; 
  }

  return p;
}

void polynomial_free(polynomial *p) {
  free(p->items);
  free(p);
}
