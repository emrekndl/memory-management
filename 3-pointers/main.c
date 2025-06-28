#include "../munit/munit.h"
#include "exercise.h"
#include <stdio.h>

static MunitResult test_size_of_addr(const MunitParameter params[],
                                     void *data) {
  unsigned long size_16 = size_of_addr(16);
  unsigned long size_64 = size_of_addr(64);
  unsigned long size_128 = size_of_addr(128);

  // printf("Size of addr : %lu\n", size_16);
  munit_assert(size_16 == 8);
  munit_assert(size_64 == 8);
  munit_assert(size_128 == 8);
  return MUNIT_OK;
}
///////
coordinate_t new_coordinate(int x, int y, int z) {
  return (coordinate_t){.x = x, .y = y, .z = z};
}

static MunitResult test_unchanged(const MunitParameter params[], void *data) {
  coordinate_t c = new_coordinate(2, 3, 5);
  munit_assert(c.x == 2);
  coordinate_update_x(c, 4);
  munit_assert(c.x == 2);
  return MUNIT_OK;
}

static MunitResult test_changed(const MunitParameter params[], void *data) {
  coordinate_t old = new_coordinate(2, 3, 5);
  munit_assert(old.x == 2);
  coordinate_t new = coordinate_update_and_return_x(old, 4);
  munit_assert(new.x == 4);
  munit_assert(old.x == 2);
  return MUNIT_OK;
}
///////

static MunitResult test_change_filetype(const MunitParameter params[],
                                        void *data) {
  codefile_t original = {.lines = 10, .filetype = 1};
  codefile_t res = change_file_type(&original, 2);
  munit_assert(res.lines == 10);
  munit_assert(res.filetype == 2);
  return MUNIT_OK;
}

static MunitResult
test_change_filetype_no_mutation(const MunitParameter params[], void *data) {
  codefile_t original = {.lines = 15, .filetype = 5};
  codefile_t backup = original;
  codefile_t res = change_file_type(&original, 8);
  munit_assert(res.filetype == 8);
  munit_assert(original.filetype == backup.filetype);
  munit_assert(original.lines == backup.lines);
  return MUNIT_OK;
}
/////////

static MunitResult test_update_file_basic(const MunitParameter params[],
                                          void *data) {
  int filedata[200];
  update_file(filedata, 1, 100);
  munit_assert(filedata[1] == 100);
  munit_assert(filedata[2] == 1);
  munit_assert(filedata[199] == 0);
  return MUNIT_OK;
}
/////////

static MunitResult test_concat_strings(const MunitParameter params[],
                                       void *data) {
  char str1[100] = "Hello ";
  const char *str2 = "World";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "Hello World");
  return MUNIT_OK;
}

static MunitResult test_concat_nonempty_to_empty(const MunitParameter params[],
                                                 void *data) {
  char str1[100] = "";
  const char *str2 = "Hello";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "Hello");
  return MUNIT_OK;
}
/////////

static MunitResult test_smart_append_full_buffer(const MunitParameter params[],
                                                 void *data) {
  TextBuffer dest;
  strcpy(dest.buffer,
         "This is a very long string that will fill up the entire buffer.");
  dest.length = 63;
  const char *src = " Extra";
  int result = smart_append(&dest, src);
  munit_assert(result == 1);
  munit_assert_string_equal(
      dest.buffer,
      "This is a very long string that will fill up the entire buffer.");
  munit_assert(dest.length == 63);
  return MUNIT_OK;
}

static MunitResult test_smart_append_empty_buffer(const MunitParameter params[],
                                                  void *data) {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;
  const char *src = "Hello";
  int result = smart_append(&dest, src);
  munit_assert(result == 0);
  munit_assert_string_equal(dest.buffer, "Hello");
  munit_assert(dest.length == 5);
  return MUNIT_OK;
}

static MunitResult test_smart_append_overflow(const MunitParameter params[],
                                              void *data) {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a long string");
  dest.length = 21;
  const char *src = " that will fill the whole buffer and leave no space for "
                    "some of the chars.";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);
  munit_assert_string_equal(
      dest.buffer,
      "This is a long string that will fill the whole buffer and leave");
  munit_assert_int(dest.length, ==, 63);
  return MUNIT_OK;
}

static MunitResult test_smart_append_null_value(const MunitParameter params[],
                                                void *data) {
  TextBuffer dest;
  const char *src = NULL;
  int result = smart_append(&dest, src);
  munit_assert(result == 1);
  return MUNIT_OK;
}

static MunitResult test_new_node_simple(const MunitParameter params[],
                                        void *data) {
  snekobject_t node = new_node("root");
  munit_assert_string_equal(node.name, "root");
  munit_assert_null(node.child);
  return MUNIT_OK;
}

static MunitResult test_new_node_with_child(const MunitParameter params[],
                                            void *data) {
  snekobject_t child = new_node("child");
  snekobject_t parent = new_node("parent");
  parent.child = &child;

  munit_assert_string_equal(parent.name, "parent");
  munit_assert_not_null(parent.child);
  munit_assert_string_equal(parent.child->name, "child");
  munit_assert_null(parent.child->child);
  return MUNIT_OK;
}

static MunitResult test_new_node_nested_children(const MunitParameter params[],
                                                 void *data) {
  snekobject_t grandchild = new_node("grandchild");
  snekobject_t child = new_node("child");
  snekobject_t parent = new_node("parent");

  child.child = &grandchild;
  parent.child = &child;

  munit_assert_string_equal(parent.name, "parent");
  munit_assert_not_null(parent.child);
  munit_assert_string_equal(parent.child->name, "child");
  munit_assert_not_null(parent.child->child);
  munit_assert_string_equal(parent.child->child->name, "grandchild");
  munit_assert_null(parent.child->child->child);
  return MUNIT_OK;
}
//////


static MunitResult test_assign_employee1(const MunitParameter params[],
                                                void *data) {
  employee_t emp = create_employee(2, "CEO Dax");
  department_t dept = create_department("C Suite");
  assign_employee(&emp, &dept);
  munit_assert_string_equal(emp.department->name, "C Suite");
  return MUNIT_OK;
}

static MunitResult test_assign_manager1(const MunitParameter params[],
                                                void *data) {
  employee_t manager = create_employee(3, "Influencer Prime");
  department_t dept = create_department("Marketing");
  assign_manager(&dept, &manager);
  munit_assert_string_equal(dept.manager->name, "Influencer Prime");
  return MUNIT_OK;
}

static MunitResult test_assign_manager2(const MunitParameter params[],
                                                void *data) {
  employee_t manager = create_employee(5, "CDO David");
  department_t dept = create_department("C Suite");
  assign_manager(&dept, &manager);
  munit_assert_string_equal(dept.manager->name, "CDO David");
  munit_assert_int(manager.id, ==, 5);
  return MUNIT_OK;
}


static MunitTest tests[] = {
    {"/size_of_addr", test_size_of_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    ////////
    {"/unchanged", test_unchanged, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/changed", test_changed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/change_filetype", test_change_filetype, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/change_filetype_no_mutation", test_change_filetype_no_mutation, NULL,
     NULL, MUNIT_TEST_OPTION_NONE, NULL},
    ////////
    {"/concat_strings", test_concat_strings, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/concat_nonempty_to_empty", test_concat_nonempty_to_empty, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    ////////
    {"/smart_append_full_buffer", test_smart_append_full_buffer, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/smart_append_null_value", test_smart_append_null_value, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/smart_append_empty_buffer", test_smart_append_empty_buffer, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/smart_append_overflow", test_smart_append_overflow, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    ////////
    {"/new_node_simple", test_new_node_simple, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/new_node_empty_name", test_new_node_with_child, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/new_node_with_child", test_new_node_nested_children, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    ////////
    {"/assign_manager1", test_assign_manager1, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/assign_manager2", test_assign_manager2, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/assign_employee1", test_assign_employee1, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    ///////
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"pointers", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  ///////////////////
  int numbers[5] = {1, 2, 3, 4, 5};
  printf("numbers : ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", numbers[i]);
  }
  printf("\n");

  // Accessing elements using array indexing
  printf("numbers[2] = %d\n", numbers[2]); // Output: 3

  // Accessing elements using pointers
  printf("*(numbers + 2) = %d\n", *(numbers + 2)); // Output: 3

  // Pointer arithmetic
  int *ptr = numbers;
  printf("Pointer ptr points to numbers[0]: %d\n", *ptr); // Output: 1
  ptr += 2;
  printf("Pointer ptr points to numbers[2]: %d\n", *ptr); // Output: 3
  ////////////////

  coordinate_t points[3] = {{5, 4, 1}, {7, 3, 2}, {9, 6, 8}};

  printf("points[1].x = %d\n", points[1].x);
  int *points_start = (int *)points;

  printf("points_start[0] = %d\n", points_start[0]);
  printf("points_start[1] = %d\n", points_start[1]);
  printf("points_start[2] = %d\n", points_start[2]);
  printf("points_start[3] = %d\n", points_start[3]);
  //////////////////

  graphics_t graphics_array[10] = {
      {60, 1080, 1920},  {30, 720, 1280},  {144, 1440, 2560}, {75, 900, 1600},
      {120, 1080, 1920}, {60, 2160, 3840}, {240, 1080, 1920}, {60, 768, 1366},
      {165, 1440, 2560}, {90, 1200, 1920}};
  dump_graphics(graphics_array);

  /////////////////
  int *intPtr;
  char *charPtr;
  double *doublePtr;
  printf("Size of int pointer: %zu bytes\n", sizeof(intPtr));
  printf("Size of char pointer: %zu bytes\n", sizeof(charPtr));
  printf("Size of double pointer: %zu bytes\n", sizeof(doublePtr));
  int intArray[10];
  char charArray[10];
  double doubleArray[10];
  printf("Size of int array: %zu bytes\n", sizeof(intArray));
  printf("Size of char array: %zu bytes\n", sizeof(charArray));
  printf("Size of double array: %zu bytes\n", sizeof(doubleArray));

  /////////
  int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12};
  int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
  printf("sizeof core_utilization in main: %zu\n", sizeof(core_utilization));
  printf("len of core_utilization: %d\n", len);
  // due to the array decaying to a pointer, the reported size is the size of a
  // pointer, not the size of the actual array.
  core_utils_func(core_utilization);
  ////////////////////////

  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
  // clang -o main.o main.c exercise.c ../munit/munit.c
}
