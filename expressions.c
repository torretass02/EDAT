
#include "expressions.h"
#include "stack.h"
#include "types.h"
#include <ctype.h> // for isdigit()
#include <stdio.h>
#include <stdlib.h>

#define OPERATORS "+-*/%"
#define OPENINGPARENTH "("
#define CLOSINGPARENTH ")"

// is char c an operator?
Bool isOperator(char c)
{
  char *oper = OPERATORS;
  char *pc;

  // exclude the char '\0' as operator
  if (c == '\0')
    return FALSE;

  // search for c in operators
  pc = strchr(oper, c);

  if (!pc)
    return FALSE;
  return TRUE;
}

// is char c an operand?
// accepts anything that is not an operator
Bool isOperand(char c)
{
  Bool b;
  b = (isOperator(c) == TRUE) ? FALSE : TRUE;
  return b;
}

// is char c a digit
Bool isIntOperand(char c) { return isdigit(c) ? TRUE : FALSE; }

// evaluate expresion with operator oper
int evaluate(int arg1, int arg2, char oper)
{
  int p = 0;

  switch (oper)
  {
  case '+':
    p = arg1 + arg2;
    break;
  case '-':
    p = arg1 - arg2;
    break;
  case '*':
    p = arg1 * arg2;
    break;
  case '/':
    p = arg1 / arg2;
    break;
  default:
    printf("Invalid operator");
  }

  return p;
}
/******************************************/
// START YOUR CODE
Bool isOpeningParenth(char c);
Bool isClosingParenth(char c);

Bool isOpeningParenth(char c){
  char * p;
  char * pc;

  p = OPENINGPARENTH;

  if (c == '\0') return FALSE;

  pc = strchr(p, c);

  if (!pc)
    return FALSE;
  return TRUE;
}

Bool isClosingParenth(char c){
  char * p;
  char * pc;

  p = CLOSINGPARENTH;

  if (c == '\0') return FALSE;

  pc = strchr(p, c);

  if (!pc)
    return FALSE;
  return TRUE;
}

// return TRUE if string str has well-balanced parenthesis

Bool balancedParens(char *str){
  Status st = OK;
  Stack *s;
  int i;

  if(!str) return FALSE;

  s = stack_init();
  if (!s) st = ERROR;

  for (i = 0; i < strlen(str) && st == OK; i++){
    if (isOpeningParenth(str[i])==TRUE){
      st = stack_push(s, &str[0]);
    }
    else if(isClosingParenth(str[i])==TRUE){
      if(stack_pop(s)==NULL) st = ERROR;
    }
  }

  if(st == OK && stack_isEmpty(s) == FALSE) st = ERROR;

  stack_free(s);

  if(st == OK) return TRUE;
  else return FALSE;
}

// evaluate the postfix expression in expr
// return OK or ERROR
// if no error, *result contains the result of evaluating the expression

Status evalPostfix(char *expr, int *result){
  Stack * s = NULL;
  int i, e, a1, a2;
  Status st = OK;
  char * arg2;
  char * arg1;

  if(!expr || !result) return ERROR;
  s = stack_init();

  for(i=0; i<strlen(expr); i++){
    if(isOperand(expr[i])==TRUE){
      if(stack_push(s, &expr[i])==ERROR){
        st = ERROR;
      }
    }
    else if(isOperator(expr[i])==TRUE){
      arg2 = stack_pop(s);
      arg1 = stack_pop(s);

      a1 = arg1[0]-48;
      a2 = arg2[0]-48;

      e = evaluate(a1, a2, expr[i]);

      printf("EVALUATED = %d %c %d = %d\n", a1, expr[i], a2, e);
      
      if(stack_push(s, &e)==ERROR){
        st = ERROR;
      }
    }
  }

  result = stack_pop(s);

  if(stack_isEmpty(s)==FALSE){
    st = ERROR;
  }

  stack_free(s);
  
  return st;
}
// END CODE