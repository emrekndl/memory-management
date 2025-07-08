#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

char *get_full_greeting(char *greeting, char *name, int size) {
  char *full_greeting = (char *)malloc(size * sizeof(char *));
  if (full_greeting == NULL) {
    return NULL;
  }
  snprintf(full_greeting, size, "%s %s", greeting, name);
  return full_greeting;
}

// char *get_full_greeting(char *greeting, char *name, int size) {
//   char full_greeting[100];
//   snprintf(full_greeting, 100, "%s %s", greeting, name);
//   return full_greeting;
// }

///////

int *allocate_scalar_array(int size, int multiplier) {

  int *ptr = malloc(size * sizeof(int));
  if (ptr == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    ptr[i] = i * multiplier;
  }

  return ptr;
}
