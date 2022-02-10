#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * cts = malloc(sizeof(*cts));
  if(cts != NULL){
    cts->oc = NULL;
    cts->sz = 0;
    cts->unktimes = 0;
  }
  return cts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int str_is_found=0;
  char * str = NULL;

  if(name == NULL){
    c->unktimes++;  
    str_is_found=1;
  }else{
    str=strdup(name);
  }

  
  if(c->sz>0 && name != NULL){
    for(size_t i=0; i<c->sz; i++){
      if(!strcmp(c->oc[i]->name, str)){
        c->oc[i]->times++;
        str_is_found=1;
      }
    }
  }

  if(!str_is_found){
    one_count_t * oc = malloc(sizeof(*oc));
    assert(oc!=NULL);
    oc->name=str;
    oc->times=1;
    c->oc=realloc(c->oc, (c->sz + 1) * sizeof(*c->oc));
    c->sz++;
    c->oc[c->sz - 1] = oc;
  }else{
    free(str);
  }
}



void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i=0; i<c->sz; i++){
    fprintf(outFile, "%s: %d\n", c->oc[i]->name, c->oc[i]->times);  
  }
  if(c->unktimes>0){
    fprintf(outFile, "<unknown> : %d\n", c->unktimes);
  }
}


void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0; i<c->sz; i++){
    free(c->oc[i]->name);
    free(c->oc[i]);
  }
  free(c->oc);
  free(c);
}

