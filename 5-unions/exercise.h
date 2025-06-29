#ifndef exercise_h
#define exercise_h

#include <stdint.h>

typedef enum TypeObjectData {
  INTEGER,
  STRING
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  char *v_string;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t new_integer(int);
snek_object_t new_string(char *str);
void format_object(snek_object_t obj, char *buffer);

//////////

typedef union {
  int value;
  unsigned int err;
} val_or_err_t;

//////////

typedef union PacketHeader{
  struct {
   uint16_t src_port;
   uint16_t dest_port;
   uint32_t seq_num;
  }tcp_header;
  uint8_t raw[8];
} packet_header_t;


#endif
