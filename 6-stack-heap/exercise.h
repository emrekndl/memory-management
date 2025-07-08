#ifndef exercise_h
#define exercise_h

void printMessageOne();
void printMessageTwo();
void printMessageThree();
void printStackPointerDiff();

///////

typedef struct {
  int x;
  int y;
} coord_t;

coord_t new_coord(int x, int y);
// coord_t *new_coord(int x, int y);

///////

char* get_full_greeting(char *greeting, char *name, int size);

///////

int *allocate_scalar_array(int size, int multiplier);

#endif
