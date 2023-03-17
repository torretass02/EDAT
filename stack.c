#include "stack.h"
#include "file_utils.h"
#include "graph.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
 void **item; /*!<Static array of elements*/
 int top; /*!<index of the top element in the stack*/
 int capacity; /*!<xcapacity of the stack*/
};