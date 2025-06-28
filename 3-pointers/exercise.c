#include "exercise.h"
#include <stdio.h>
#include <string.h>

unsigned long size_of_addr(long long i) {
  unsigned long size_of_snek_version = sizeof(&i);
  return size_of_snek_version;
}
/////

void coordinate_update_x(coordinate_t coord, int new_x) { coord.x = new_x; }

coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x) {
  coord.x = new_x;
  return coord;
}
/////

codefile_t change_file_type(codefile_t *f, int new_filetype) {
  codefile_t new_f = *f;
  new_f.filetype = new_filetype;
  return new_f;
}

////

void update_file(int filedata[200], int new_filetype, int new_num_lines) {
  filedata[1] = new_num_lines;
  filedata[2] = new_filetype;
  filedata[199] = 0;
}

/////
void dump_graphics(graphics_t gsettings[10]) {
  int *ptr = (int *)gsettings;
  for (int i = 0; i < 30; i++) {
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

//////
void core_utils_func(int core_utilization[]) {
  int s = sizeof(core_utilization);
  printf("sizeof core_utilization in core_utils_func: %d\n", s);
}

//////
void concat_strings(char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0') {
    i++;
  }
  for (int j = 0; str2[j] != '\0'; j++) {
    str1[i] = str2[j];
    i++;
  }
  str1[i] = '\0';
}

//////
int smart_append(TextBuffer *dest, const char *src) {
  if (!src) {
    return 1;
  }

  const int b_msize = 64;
  int len_src = strlen(src);

  int remaining_space_dest = b_msize - (int)dest->length;

  if (len_src > remaining_space_dest) {
    strncat(dest->buffer, src, remaining_space_dest - 1);
    dest->length += remaining_space_dest - 1;
    dest->buffer[b_msize] = '\0';
    return 1;
  } else {
    strcat(dest->buffer, src);
    dest->length += len_src;
    return 0;
  }
}

//////
snekobject_t new_node(char *name) {
  snekobject_t node = {
    .name = name,
    .child = NULL
  };
  return node;
}

/////
employee_t create_employee(int id, char *name) {
  employee_t emp = {
    .id = id,
    .name = name,
    .department = NULL
  };
  return emp;
}

department_t create_department(char *name) {
  department_t dept = {
    .name = name,
    .manager = NULL
  };
  return dept;
}

void assign_employee(employee_t *emp, department_t *department) {
  emp->department = department;
}

void assign_manager(department_t *dept, employee_t *manager) {
  dept->manager = manager;
}
