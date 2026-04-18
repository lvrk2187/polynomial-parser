#include "../include/parser.h"
#include <ctype.h>
#include <string.h>

void print_state(STATE s) {
  switch (s) {
      case START: printf("START"); break;
      case PARSING_COEFFICIENT_OPERATOR: printf("PARSING_COEFFICIENT_OPERATOR"); break;
      case PARSING_COEFFICIENT: printf("PARSING_COEFFICIENT"); break;
      case VARIABLE_FOUND: printf("VARIABLE_FOUND"); break;
      case EXPONENT_FOUND: printf("EXPONENT_FOUND"); break;
      case PARSING_EXPONENT_OPERATOR: printf("PARSING_EXPONENT_OPERATOR"); break;
      case PARSING_EXPONENT: printf("PARSING_EXPONENT"); break;
      case ERROR: printf("ERROR"); break;
  }
  printf("\n");
}

int convert_sign_to_int(char _c) {
  return (_c == '+') ? 1 : -1;
}

bool isoperator(char _c) {
  switch (_c) {
    case '+': case '-': return true;
    default: return false; 
  }
}

void push_num(char _c, int *store) {
  *store *= 10;
  *store += _c - '0';
}

void push_num_and_change_state(char _c, int *store, STATE _s, STATE *dest) {
  *dest = _s;
  *store *= 10;
  *store += _c - '0';
}

void start_new_term_and_change_state(int *p, STATE _s, STATE *dest) {
  *dest = _s;
  (*p)++;
}

void check_end_state(STATE s, polynomial *m) {
  switch (s) {
    /*
      It would be invalid to end on any of these states 
    */
      case START: 
      case PARSING_COEFFICIENT_OPERATOR: 
      case PARSING_COEFFICIENT: 
      case EXPONENT_FOUND: 
      case PARSING_EXPONENT_OPERATOR: 
      case ERROR: printf("ERROR parsing polynomial! - "); exit(POLYNOMIAL_PARSING_ERROR); break;
      

      case VARIABLE_FOUND: m->items[m->size-1].exponent = 1; break;      
      case PARSING_EXPONENT: break;
  }
}

void modify_state(char next_c, STATE *state, polynomial *poly, int *p_pointer) {

  switch (*state) {

    //----------------START----------------
    case START:
      if (isoperator(next_c)) {
        *state = PARSING_COEFFICIENT_OPERATOR;
        poly->items[*p_pointer].c_operator = convert_sign_to_int(next_c);
      } else if (isdigit(next_c)) {
        push_num_and_change_state(next_c, &poly->items[*p_pointer].coefficient, PARSING_COEFFICIENT, state);
      } else if (next_c == 'x') {
        *state = VARIABLE_FOUND;

        /*
          special case for the omittance of both the operator and the number within the premodification of a monomial 
          -> x^n => {c_operator = 1, c_coefficient = 1, ...}, where n is any number
        */
        poly->items[*p_pointer].c_operator = 1;
        poly->items[*p_pointer].coefficient = 1;

      } else {
        *state = ERROR;
      }
      break;
    
    //----------------PARSING OPERATOR OF COEFFICIENT----------------
    case PARSING_COEFFICIENT_OPERATOR:

      if (isdigit(next_c)) {
        push_num_and_change_state(next_c, &poly->items[*p_pointer].coefficient, PARSING_COEFFICIENT, state);
      } else if (next_c == 'x') {
        *state = VARIABLE_FOUND;
        /*
          another speical case where the premodifcation for a given variable omits the number, it is implied to be one
          -> -x^n  or x^n => {... , coefficient = 1, ...}, where n is any number
        */
        poly->items[*p_pointer].coefficient = 1; 
      }
      else {
        *state = ERROR;
      }
      break;

    
    //----------------PARSING COEFFICIENT----------------
    case PARSING_COEFFICIENT:

      if (isdigit(next_c)) {
        push_num(next_c, &poly->items[*p_pointer].coefficient);
      } else if (next_c == 'x') {
        /*
          ERROR checking for negative coefficient
          -> 0x^2 => ERROR, as it is an invalid monomial
        */
        if (poly->items[*p_pointer].coefficient == 0) {*state = ERROR; return;} 
        *state = VARIABLE_FOUND;
      } else {
        *state = ERROR;
      }  
      break;

    
    //----------------VARIABLE FOUND----------------
    case VARIABLE_FOUND:

      if (next_c == '^') {
        *state = EXPONENT_FOUND;
      }
      else if (isoperator(next_c)) {
        /*
          this is for the special case for the ommitance of the postmodifying exponent implying 1
          -> eg: 3x or 15x => {..., exponent = 1}
        */
        poly->items[*p_pointer].exponent = 1;
        
        start_new_term_and_change_state(p_pointer, PARSING_COEFFICIENT_OPERATOR, state);
        poly->items[*p_pointer].c_operator = convert_sign_to_int(next_c);

      } else {
        *state = ERROR;
      }
      break;

    //----------------EXPONENT FOUND----------------
    case EXPONENT_FOUND:

      if (isdigit(next_c)) {
        push_num_and_change_state(next_c, &poly->items[*p_pointer].exponent, PARSING_EXPONENT, state);
        poly->items[*p_pointer].e_operator = 1;
      } else if (next_c == '-') {
        /*
          another special case specifically for when parsing the exponent of a monomial 
          -> 4x^-3 => {..., e_operator = -1, ...}, as it is in fact negative
        */
        *state = PARSING_EXPONENT_OPERATOR;
        poly->items[*p_pointer].e_operator = convert_sign_to_int(next_c); 
      } else {
        *state = ERROR;
      }

      break;

    //----------------PARSING EXPONENT OPERATOR----------------
    case PARSING_EXPONENT_OPERATOR:

      if (isdigit(next_c)) {
        push_num_and_change_state(next_c, &poly->items[*p_pointer].exponent, PARSING_EXPONENT, state);        
      } else {
        *state = ERROR;
      }

      break;

    
    //----------------PARSING EXPONENT----------------
    case PARSING_EXPONENT:

      if (isdigit(next_c)) {
        push_num(next_c, &poly->items[*p_pointer].exponent);
      } else if (isoperator(next_c)) {
        start_new_term_and_change_state(p_pointer, PARSING_COEFFICIENT_OPERATOR, state);
        poly->items[*p_pointer].c_operator = convert_sign_to_int(next_c);
      } else {
        *state = ERROR;
      }
      break;

    //----------------ERROR CHECKING----------------
    case ERROR:
      printf("ERROR in parsing polynomial");      
      exit(POLYNOMIAL_PARSING_ERROR);
      break;
  }

}

polynomial *parser(char *expr) {


  polynomial *m = poly_innit(sizeofpoly(expr));
  int polynomial_pointer = 0;

  STATE *state;
  state = malloc(sizeof(STATE));
  *state = START;

  for (int i = 0; i < strlen(expr); i++) {
    if (expr[i] != ' ') {
      modify_state(expr[i], state, m, &polynomial_pointer);
    }
  }

  check_end_state(*state, m);

  free(state);
  return m;
}

