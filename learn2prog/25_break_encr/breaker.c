#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define ABCD 26

int check_higher(int * arr){
  int idx=0;
  for(size_t i=1; i<26; i++){
    if(arr[i] > arr[idx]){
      idx=i;
    }
  }
  return idx;
}


int breaker(FILE * f){
  int c;
  int letter[ABCD] = {0};
  while( (c = fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      c -= 97;
      letter[c]+=1;
    }
  }
  int max = check_higher(letter);
  max += 22;
  max %= 26;
  return max;
}


int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr, "Usage: breaker inputFileName\n");  
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL){
    perror("Could not open file\n");
    return EXIT_FAILURE;
  } 

  int ans = breaker(f);

  if (fclose(f) != 0){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  assert(0<=ans);
  assert(ans<26);
  
  printf("%d\n",ans); 

  return EXIT_SUCCESS;
}
