#include "../include/polynomial.h"
#include "../include/parser.h"
#include <ctype.h>
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


bool check_end_match_state(MATCH_STATE s) {
  if (s == PARSING_NUMBER) return true;
  return false;
}

void print_match_state(MATCH_STATE state) {
  switch (state) {
    case STRING_START: printf("STRING_START"); break;
    case PARSING_START_OPERATOR: printf("PARSING_START_OPERATOR"); break;
    case PARSING_NUMBER: printf("PARSING_NUMBER"); break;
    case PARSING_END_OPERATOR: printf("PARSING_END_OPERTOR"); break;
    case PASS: printf("PASS"); break;
  }
  printf("\n");
}

int sizenofpoly(char *expr) {
  int size = 0;
  MATCH_STATE state = STRING_START;

  for (int i = 0; i < strlen(expr); i++) {
    char next_character = expr[i];

    if (next_character == 'x') size++;

    if (next_character == ' ') continue;

    switch (state) {
      case STRING_START:

        if (isoperator(next_character))   state = PARSING_START_OPERATOR;
        else if (isdigit(next_character)) state = PARSING_NUMBER;
        else                              state = PASS;

        break;

      case PARSING_START_OPERATOR:

        if (isdigit(next_character)) state = PARSING_NUMBER;
        else                         state = PASS;
        
        break;

      case PARSING_NUMBER:

        if (isoperator(next_character))   state = PARSING_END_OPERATOR;
        else if (isdigit(next_character)) state = PARSING_NUMBER;
        else                              state = PASS;

        break;

      case PARSING_END_OPERATOR:

        size++;

        if (isoperator(next_character)) state = PARSING_START_OPERATOR;
        else                            state = PASS;
        
        break;

      case PASS:

        if (isoperator(next_character)) state = PARSING_START_OPERATOR;
        break;
    }

    /* DEBUGGING PRINT STATEMENTS

    printf("%c: ", next_character);
    print_match_state(state);
    */
  }

  if (check_end_match_state(state)) size++;

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
