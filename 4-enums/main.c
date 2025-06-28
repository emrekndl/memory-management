#include "../munit/munit.h"
#include "exercise.h"
#include <stdio.h>

static MunitResult test_color_enum1(const MunitParameter params[], void *data) {
  munit_assert_int(RED, ==, 55);
  munit_assert_int(GREEN, ==, 176);
  munit_assert_int(BLUE, ==, 38);
  return MUNIT_OK;
}

static MunitResult test_color_enum2(const MunitParameter params[], void *data) {
  munit_assert_int(RED, !=, 4);
  munit_assert_int(GREEN, !=, 2);
  munit_assert_int(BLUE, !=, 0);
  return MUNIT_OK;
}
///////

static MunitResult test_switch_enum(const MunitParameter params[], void *data) {

  munit_assert_string_equal(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request");
  munit_assert_string_equal(http_to_str(HTTP_UNAUTHORIZED), "401 Unauthorized");
  munit_assert_string_equal(http_to_str(HTTP_NOT_FOUND), "404 Not Found");
  munit_assert_string_equal(http_to_str(HTTP_TEAPOT), "418 I Am a Teapot");
  munit_assert_string_equal(http_to_str(HTTP_INTERNAL_SERVER_ERROR), "500 Internal Server Error");
  return MUNIT_OK;
}

static MunitResult test_switch_enum_default(const MunitParameter params[], void *data) {
  munit_assert_string_equal(http_to_str((http_error_code_t)999), "Unknown HTTP status code");
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/color_enum1", test_color_enum1, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/color_enum2", test_color_enum2, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    ///////
    {"/switch_enum", test_switch_enum, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/switch_enum_default", test_switch_enum_default, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"enums", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {

  printf("The size of BigNumbers is %zu bytes\n", sizeof(BigNumbers));
  printf("The size of HttpErrorCode is %zu bytes\n", sizeof(http_error_code_t));

  /////////

  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
  // clang -o main.o main.c exercise.c ../munit/munit.c
}
