#include "polynomial.h"
#include <stdbool.h>

#ifndef PARSER

#define PARSER

#define POLYNOMIAL_PARSING_ERROR 38

typedef enum {
  START,
  PARSING_COEFFICIENT_OPERATOR,
  PARSING_COEFFICIENT,
  VARIABLE_FOUND,
  EXPONENT_FOUND,
  PARSING_EXPONENT_OPERATOR,
  PARSING_EXPONENT,
  ERROR
} STATE;

//printing functions
void print_state (STATE s);

//helper functions
int convert_sign_to_int (char _c);
bool isoperator         (char _c);

//state modification functions
void push_num                        (char _c, int *store);
void push_num_and_change_state       (char _c, int *store, STATE _s, STATE *dest);
void start_new_term_and_change_state (int *p, STATE _p, STATE *dest);

//state machine parser components
void check_end_state (STATE s, polynomial *m);
void modify_state    (char next_c, STATE *state, polynomial *poly, int *p_pointer);
polynomial *parser   (char *expr);

#endif
