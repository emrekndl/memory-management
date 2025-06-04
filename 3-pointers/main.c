#include "../munit/munit.h"
#include "exercise.h"
#include <stdio.h>

static MunitResult test_new_coordinate(const MunitParameter params[],
                                        void *data) {
  // coordinate_t c = new_coord(4, 2, 0);
  // printf("Size of coordinate_t: %zu bytes\n", sizeof(coordinate_t));
  // munit_assert(c.x == 4);
  // munit_assert(c.y == 2);
  // munit_assert(c.z == 0);
  return MUNIT_OK;
}



static MunitTest tests[] = {
    {"/new_coordinate", test_new_coordinate, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
   {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"pointers", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
}
