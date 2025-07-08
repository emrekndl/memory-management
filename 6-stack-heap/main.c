#include "../munit/munit.h"
#include "exercise.h"
#include <stdbool.h>
#include <stdio.h>

// Helper function to check if a pointer is on the stack
bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;

  // Check within a threshold in both directions (e.g., 1MB)
  uintptr_t threshold = 1024;

  return ptr_addr >= (stack_top_addr - threshold) &&
         ptr_addr <= (stack_top_addr + threshold);
}

static MunitResult test_basic_greeting(const MunitParameter params[],
                                       void *data) {

  char *result = get_full_greeting("Hello", "Alice", 20);
  munit_assert_string_equal(result, "Hello Alice");
  munit_assert_false(is_on_stack(result));
  return MUNIT_OK;
}

static MunitResult test_short_buffer(const MunitParameter params[],
                                     void *data) {

  char *result = get_full_greeting("Hey", "Bob", 4);
  munit_assert_string_equal(result, "Hey");
  munit_assert_false(is_on_stack(result));
  free(result);
  return MUNIT_OK;
}
///////////////////////

static MunitResult
test_allocate_scalar_array_size(const MunitParameter params[], void *data) {

  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);
  munit_assert_not_null(result);
  free(result);
  return MUNIT_OK;
}

static MunitResult
test_allocate_scalar_array_values(const MunitParameter params[], void *data) {

  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);
  int expected[5];
  expected[0] = 0;
  expected[1] = 2;
  expected[2] = 4;
  expected[3] = 6;
  expected[4] = 8;
  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, expected[i]);
  }
  free(result);
  return MUNIT_OK;
}

static MunitResult
test_allocate_scalar_array_zero_multiplier(const MunitParameter params[],
                                           void *data) {

  int size = 3;
  int multiplier = 0;
  int *result = allocate_scalar_array(size, multiplier);
  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, 0);
  }
  free(result);
  return MUNIT_OK;
}

static MunitResult test_allocate_too_much(const MunitParameter params[],
                                          void *data) {

  int size = 1024 * 1024 * 100;
  int multiplier = 1;
  int *result = allocate_scalar_array(size, multiplier);
  munit_assert_null(result);
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/basic_greeting", test_basic_greeting, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/short_buffer", test_short_buffer, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/allocate_scalar_array_size", test_allocate_scalar_array_size, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/allocate_scalar_array_values", test_allocate_scalar_array_values, NULL,
     NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/allocate_scalar_array_zero_multiplier",
     test_allocate_scalar_array_zero_multiplier, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/allocate_too_much", test_allocate_too_much, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"stack-heap", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {

  printMessageOne();
  printMessageTwo();
  printMessageThree();

  ////////
  // stack overflow
  // const int pool_size = 1024 * 1024 * 20; // 20 Mb
  const int pool_size = 1024 * 20; // 20 Kb
  char snek_pool[pool_size];
  snek_pool[0] = 's';
  snek_pool[1] = 'n';
  snek_pool[2] = 'e';
  snek_pool[3] = 'k';
  snek_pool[4] = '\0';

  printf("Size of pool: %d\n", pool_size);
  printf("Initial string: %s\n", snek_pool);

  ////////

  coord_t c1 = new_coord(10, 20);
  coord_t c2 = new_coord(30, 40);
  coord_t c3 = new_coord(50, 60);
  // coord_t *c1 = new_coord(10, 20);
  // coord_t *c2 = new_coord(30, 40);
  // coord_t *c3 = new_coord(50, 60);

  printf("c1: %d, %d\n", c1.x, c1.y);
  printf("c2: %d, %d\n", c2.x, c2.y);
  printf("c3: %d, %d\n", c3.x, c3.y);
  // printf("c1: %d, %d\n", c1->x, c1->y);
  // printf("c2: %d, %d\n", c2->x, c2->y);
  // printf("c3: %d, %d\n", c3->x, c3->y);

  ///////////////////

  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
  // clang -o main.o main.c exercise.c ../munit/munit.c
}

// coord_t *new_coord(int x, int y) {
coord_t new_coord(int x, int y) {
  coord_t c;
  c.x = x;
  c.y = y;
  return c;
  // return &c;
}

void printMessageOne() {
  const char *message = "Dark mode?\n";
  printStackPointerDiff();
  printf("%s\n", message);
  // printMessageTwo();
}

void printMessageTwo() {
  const char *message = "More like...\n";
  printStackPointerDiff();
  printf("%s\n", message);
  // printMessageThree();
}

void printMessageThree() {
  const char *message = "dark roast.\n";
  printStackPointerDiff();
  printf("%s\n", message);
}

void printStackPointerDiff() {
  static void *last_sp = NULL;
  void *current_sp;
  current_sp = __builtin_frame_address(0);
  long diff = (char *)last_sp - (char *)current_sp;
  if (last_sp == NULL) {
    last_sp = current_sp;
    diff = 0;
  }
  printf("---------------------------------\n");
  printf("Stack pointer offset: %ld bytes\n", diff);
  printf("---------------------------------\n");
}
