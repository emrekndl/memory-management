#include "../munit/munit.h"
#include "exercise.h"
#include <stdio.h>

static MunitResult test_new_coordinate(const MunitParameter params[],
                                       void *data) {
  coordinate_t c;
  /*struct Coordinate c;*/
  c.x = 2;
  c.y = 3;
  c.z = 5;
  munit_assert(c.x == 2);
  munit_assert(c.y == 3);
  munit_assert(c.z == 5);
  return MUNIT_OK;
}

static MunitResult test_new_coordinate2(const MunitParameter params[],
                                        void *data) {
  coordinate_t c = new_coord(4, 2, 0);
  printf("Size of coordinate_t: %zu bytes\n", sizeof(coordinate_t));
  munit_assert(c.x == 4);
  munit_assert(c.y == 2);
  munit_assert(c.z == 0);
  return MUNIT_OK;
}

static MunitResult test_scale_coordinate(const MunitParameter params[],
                                         void *data) {
  coordinate_t c = new_coord(3, 5, 7);
  coordinate_t scaled = scale_coordinate(c, 3);
  /*printf("Size of coordinate_t: %zu bytes\n", sizeof(coordinate_t));*/
  munit_assert(scaled.x == 9);
  munit_assert(scaled.y == 15);
  munit_assert(scaled.z == 21);
  return MUNIT_OK;
}

static MunitResult test_optimal_size(const MunitParameter params[], void *data) {
    
    /*sneklang_var_t temp_var;*/
    /*printf("Size of sneklang_var_t: %zu bytes\n", sizeof(sneklang_var_t));*/
    /*printf("Size of sneklang_var_t.name: %zu bytes\n", sizeof(temp_var.name));*/
    /*printf("Size of sneklang_var_t.value: %zu bytes\n", sizeof(temp_var.value));*/
    /*printf("Size of sneklang_var_t.scope_level: %zu bytes\n", sizeof(temp_var.scope_level));*/
    /*printf("Size of sneklang_var_t.is_constant: %zu bytes\n", sizeof(temp_var.is_constant));*/
    /*printf("Size of sneklang_var_t.type: %zu bytes\n", sizeof(temp_var.type));*/

    /*printf("Size of sneklang_var_t.type: %zu bytes\n", sizeof(temp_var.type));*/
    /*printf("Size of sneklang_var_t.name: %zu bytes\n", sizeof(temp_var.name));*/
    /*printf("Size of sneklang_var_t.value: %zu bytes\n", sizeof(temp_var.value));*/
    /*printf("Size of sneklang_var_t.is_constant: %zu bytes\n", sizeof(temp_var.is_constant));*/
    /*printf("Size of sneklang_var_t.scope_level: %zu bytes\n", sizeof(temp_var.scope_level));*/
    munit_assert(sizeof(sneklang_var_t) == 24);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/new_coordinate", test_new_coordinate, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/new_coordinate2", test_new_coordinate2, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/scale_coordinate", test_scale_coordinate, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/optimal_size", test_optimal_size, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"structs", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
}
