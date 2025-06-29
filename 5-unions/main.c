#include "../munit/munit.h"
#include "exercise.h"
#include <limits.h>
#include <stdio.h>

static MunitResult test_format_int1(const MunitParameter params[], void *data) {

  char buffer[100];
  snek_object_t i = new_integer(5);
  format_object(i, buffer);

  munit_assert_string_equal("int:5", buffer);
  return MUNIT_OK;
}

static MunitResult test_format_string1(const MunitParameter params[],
                                       void *data) {
  char buffer[100];
  snek_object_t s = new_string("Hello!");
  format_object(s, buffer);

  munit_assert_string_equal("string:Hello!", buffer);
  return MUNIT_OK;
}

static MunitResult test_format_int2(const MunitParameter params[], void *data) {
  char buffer[100];
  snek_object_t i = new_integer(2014);
  format_object(i, buffer);

  munit_assert_string_equal("int:2014", buffer);
  return MUNIT_OK;
}

static MunitResult test_format_string2(const MunitParameter params[],
                                       void *data) {
  char buffer[100];
  snek_object_t s = new_string("nvim btw");
  format_object(s, buffer);

  munit_assert_string_equal("string:nvim btw", buffer);
  return MUNIT_OK;
}

///////////


static MunitResult test_packet_header_size(const MunitParameter params[],
                                       void *data) {
  munit_assert_size(sizeof(packet_header_t), ==, 8);
  return MUNIT_OK;
}

static MunitResult test_tcp_header_fields(const MunitParameter params[],
                                       void *data) {
  packet_header_t header;
  header.tcp_header.src_port = 0x1234;
  header.tcp_header.dest_port = 0x5678;
  header.tcp_header.seq_num = 0x9ABCDEF0;

  munit_assert_uint16(header.tcp_header.src_port, ==, 0x1234);
  munit_assert_uint16(header.tcp_header.dest_port, ==, 0x5678);
  munit_assert_uint32(header.tcp_header.seq_num, ==, 0x9ABCDEF0);
  return MUNIT_OK;
}

static MunitResult test_field_raw_size(const MunitParameter params[],
                                       void *data) {
   munit_assert_size(sizeof(((packet_header_t *)0)->raw), ==, 8);
  return MUNIT_OK;
}


static MunitResult test_field_to_raw_consistency(const MunitParameter params[],
                                       void *data) {
  packet_header_t header = {0};
  header.tcp_header.src_port = 0x1234;
  header.tcp_header.dest_port = 0x5678;
  header.tcp_header.seq_num = 0x9ABCDEF0;

  munit_assert_uint8(header.raw[0], ==, 0x34);
  munit_assert_uint8(header.raw[1], ==, 0x12);
  munit_assert_uint8(header.raw[2], ==, 0x78);
  munit_assert_uint8(header.raw[3], ==, 0x56);
  munit_assert_uint8(header.raw[4], ==, 0xF0);
  munit_assert_uint8(header.raw[5], ==, 0xDE);
  munit_assert_uint8(header.raw[6], ==, 0xBC);
  munit_assert_uint8(header.raw[7], ==, 0x9A);
  return MUNIT_OK;
}

static MunitTest tests[] = {
    {"/format_int1", test_format_int1, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/format_int2", test_format_int2, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/format_string1", test_format_string1, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/format_string2", test_format_string2, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/packet_header_size", test_packet_header_size, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/tcp_header_fields", test_tcp_header_fields, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/field_raw_size", test_field_raw_size, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/field_to_raw_consistency", test_field_to_raw_consistency, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {"unions", tests, NULL, 1,
                                 MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {

  val_or_err_t lanes_score = {.value = -420};
  printf("value (set): %d\n", lanes_score.value);
  printf("err (unset): %u\n", lanes_score.err);

  val_or_err_t teejs_score = {
    .err = UINT_MAX
  };
  printf("value (unset): %d\n", teejs_score.value);
  printf("err (set): %u\n", teejs_score.err);

  ////////////

  return munit_suite_main(&suite, NULL, argc, argv);
  // gcc -o test main.c exercise0.c munit/munit.c
  // clang -o main.o main.c exercise.c ../munit/munit.c
}
