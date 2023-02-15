#include "vertex.h"
#include <string.h>

#define TAG_LENGTH 64

struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex * vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

Vertex * vertex_init (){ 
  Vertex * v = NULL;   
  v = malloc(sizeof(Vertex));
  if(!v) return NULL;
  v->id = 0;
  strcpy(v->tag, "");
  v->state = WHITE;
  return v;
}

void vertex_free (void * v){
  free(v);
}

long vertex_getId (const Vertex * v){
  if(!v) return -1;

  return v->id;
}

const char* vertex_getTag (const Vertex * v){
  if(!v) return NULL;

  return v->tag;
}

Label vertex_getState (const Vertex * v){
  if(!v) return ERROR_VERTEX;

  return v->state;
}

Status vertex_setId (Vertex * v, const long id){
  if(!v || !id) return ERROR;

  v->id = id;
  return OK;
}

Status vertex_setTag (Vertex * v, const char * tag){
  if(!v || !tag) return ERROR;

  strcpy(v->tag, tag);
  return OK;
}

Status vertex_setState (Vertex * v, const Label state){
  if(!v || !state) return ERROR;

  v->state = state;
  return OK;
}

int vertex_cmp (const void * v1, const void * v2){
  
  if(vertex_getId(v1) < vertex_getId(v2)){
    return -1;
  }

  else if (vertex_getId(v1) > vertex_getId(v2)){
    return 1;
  }

  else if (vertex_getId(v1) == vertex_getId(v2)){
    return strcmp(vertex_getTag(v1), vertex_getTag(v2));
  }

  else return 0;
}

void * vertex_copy (const void * src){
  if(!src) return NULL;

  Vertex * v = NULL;
  v = malloc(sizeof(Vertex));
  
  
  vertex_setId(v, vertex_getId(src));
  vertex_setTag(v, vertex_getTag(src));
  vertex_setState(v, vertex_getState(src));
  return v;
}

int vertex_print (FILE * pf, const void * v){
  if(!pf || !v) return -1;
  
  return fprintf(pf, "[%ld, %s, %d]", vertex_getId(v), vertex_getTag(v), vertex_getState(v));
}