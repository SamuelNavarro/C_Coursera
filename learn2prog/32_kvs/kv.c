#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvpair_t * readSinglePair(char * line){
  char * eqlPtr = strchr(line, '=');
  char * eolPtr = strchr(line, '\n');
  kvpair_t * kv = malloc(sizeof(*kv));

  kv->k = malloc((eqlPtr - line) * sizeof(char*));
  strncpy(kv->k, line, eqlPtr - line);

  kv->v = malloc((eolPtr - eqlPtr - 1) * sizeof(char*));
  strncpy(kv->v, eqlPtr + 1, eolPtr - eqlPtr - 1);

  kv->v[eolPtr - eqlPtr - 1] = '\0';
  kv->k[eqlPtr - line] = '\0';

  
  return kv;
}


kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r"); 

  if(f == NULL){
    perror("Could not open file");
    exit(EXIT_FAILURE);	
  }

  kvarray_t * ans = malloc(sizeof(*ans));
  ans->numKVpairs = 0;
  ans->kvpairs = malloc(ans->numKVpairs * sizeof(*ans->kvpairs));
  // Error if allocation failed
  if(ans->kvpairs == NULL){
    free(ans->kvpairs);
    return NULL;
  }

  char * line = NULL;
  size_t sz;

  while(getline(&line, &sz, f) != -1){
    ans->kvpairs = realloc(ans->kvpairs, (ans->numKVpairs + 1) * sizeof(*ans->kvpairs));    
    ans->kvpairs[ans->numKVpairs] = readSinglePair(line);
    ans->numKVpairs++;
    //line = NULL;
  }
  free(line);
  
  int closed = fclose(f);
  if(closed!=0){
    fprintf(stderr, "could not close the file\n");
    exit(EXIT_FAILURE);
  } 

  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i=0; i<pairs->numKVpairs; i++){
    free(pairs->kvpairs[i]->k);
    free(pairs->kvpairs[i]->v);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);
}


void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i=0; i<pairs->numKVpairs; i++){
    printf("key = '%s' value = '%s'\n",
                                       pairs->kvpairs[i]->k,
                                       pairs->kvpairs[i]->v);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(size_t i=0; i<pairs->numKVpairs; i++){
    if(strcmp(pairs->kvpairs[i]->k, key) == 0){
      return pairs->kvpairs[i]->v;
    }
  }
  return NULL; 
}

