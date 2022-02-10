#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * OutputFileName  = malloc((strlen(inputName) + 4 + 7) * sizeof(*OutputFileName));
  strcpy(OutputFileName, inputName);
  strcat(OutputFileName, ".counts");
  return OutputFileName;
}
