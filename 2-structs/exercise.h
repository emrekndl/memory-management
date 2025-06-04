#ifndef exercise_h
#define exercise_h

typedef struct Coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

coordinate_t new_coord(int x, int y, int z);

coordinate_t scale_coordinate(coordinate_t coord, int factor);

// NOTE: As a rule of thumb, ordering your fields from largest to smallest will help
// the compiler minimize padding

//  Size of sneklang_var_t: 32 bytes
/*typedef struct SneklangVar {*/
/*  char type;*/
/*  char *name;*/
/*  int value;*/
/*  char is_constant;*/
/*  int scope_level;*/
/*} sneklang_var_t;*/

//  Size of sneklang_var_t: 24 bytes
typedef struct SneklangVar {
  char *name;
  int value;
  int scope_level;
  char is_constant;
  char type;
} sneklang_var_t;

#endif
