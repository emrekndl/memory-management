#ifndef exercise_h
#define exercise_h

#include <string.h>

////
unsigned long size_of_addr(long long i);
////

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

void coordinate_update_x(coordinate_t coord, int new_x);
coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x);
////

typedef struct CodeFile {
  int lines;
  int filetype;
} codefile_t;

codefile_t change_file_type(codefile_t *f, int new_filetype);
/////

void update_file(int filedata[200], int new_filetype, int new_num_lines);

//////

typedef struct Graphics {
  int fps;
  int height;
  int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]);
///////

void core_utils_func(int core_utilization[]);
///////

void concat_strings(char *str1, const char *str2);
///////

typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src);
////////

typedef struct SnekObject snekobject_t;

typedef struct SnekObject {
  char *name;
  snekobject_t *child;
} snekobject_t;

snekobject_t new_node(char *name);
//////

typedef struct Employee employee_t;
typedef struct Department department_t;

struct Employee {
    int id;
    char * name;
    department_t * department;
};

struct Department {
    char * name;
    employee_t * manager;
};

employee_t create_employee(int id, char *name);
department_t create_department(char *name);

void assign_employee(employee_t *emp, department_t *department);
void assign_manager(department_t *dept, employee_t *manager);

#endif
