#include "../include/polynomial.h"
#include "../include/parser.h"
#include <ctype.h>
#include <string.h>
#include <math.h>

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

//ax^2 + bx + c
enum {
  a = 2,
  b = 1,
  c = 0
} quadratic_term;


struct solutions_for_quadratic solve_quadratic(polynomial p) {

  u_int8_t number_of_terms_quadratic     = 3;
  u_int8_t number_of_solutions_quadratic = 0;

  if (p.size > number_of_terms_quadratic) {
    printf("invalid arguments");
    exit(1);
  }
  
  //list lays it out as {c, b, a} as it gets using raw exponent
  int terms[number_of_terms_quadratic];

  //get a, b c
  for (int i = 0; i < p.size; i++) {
    int exponent = p.items[i].e_operator * p.items[i].exponent;
    if (exponent >= 0 && exponent < number_of_terms_quadratic) {
      terms[exponent] = p.items[i].c_operator * p.items[i].coefficient;
    } else {
      printf("does not follow structure of a quadratic");
      exit(1);
    }
  }

  if (terms[a] == 0) {
    printf("a cannot be 0");
    exit(1);
  }

  //discriminant: b^2 - 4ac
  //  b^2 - 4ac > 0 -> 2 real sol
  //  b^2 - 4ac = 0 -> 1 real sol
  //  b^2 - 4ac < 0 -> 0 real sol
  int discriminat = pow(terms[b], 2) - (4 * terms[a] * terms[c]);

  if (discriminat > 0) {
    number_of_solutions_quadratic = 2;  
  } else if (discriminat == 0) {
    number_of_solutions_quadratic = 1;
  } else if (discriminat < 0) {
    number_of_terms_quadratic = 0;
  }
  
  struct solutions_for_quadratic *solutions = malloc(sizeof(struct solutions_for_quadratic));
  
  solutions->number_of_solutions = number_of_solutions_quadratic;

  //quadratic equation
  if (number_of_solutions_quadratic == 0) {
    solutions->solution1 = NAN;
    solutions->solution2 = NAN;
  } else {  
    solutions->solution1 = (-terms[b] + sqrt(pow(terms[b], 2) - 4 * terms[a] * terms[c])) / 2 * terms[a];
    solutions->solution2 = (-terms[b] - sqrt(pow(terms[b], 2) - 4 * terms[a] * terms[c])) / 2 * terms[a];
  }
  return *solutions;

}
