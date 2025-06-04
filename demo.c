#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

float add(int x, int y) { return (float)(x + y); }

void print_hello(void) { printf("Void function!\n"); }

int main() {
  int max_recursive_calls = 100;
  char io_mode = 'w';
  float throttle_speed = 0.2;
  char *filename = "demo.txt";

  printf("Max recursive calls: %d\n", max_recursive_calls);
  printf("IO mode: %c\n", io_mode);
  printf("Throttle speed: %f\n", throttle_speed);
  printf("Filename: %s\n", filename);

  float result = add(1, 2);
  printf("Result: %.2f\n", result);

  print_hello();

  // Ternary operator
  int a = 5;
  int b = 10;
  int max = a > b ? a : b;
  printf("max: %d\n", max);

  // sizeof
  printf("sizeof(char)   = %zu\n", sizeof(char));
  printf("sizeof(bool)   = %zu\n", sizeof(bool));
  printf("sizeof(int)   = %zu\n", sizeof(int));
  printf("sizeof(float)   = %zu\n", sizeof(float));
  printf("sizeof(double)   = %zu\n", sizeof(double));
  printf("sizeof(size_t)   = %zu\n", sizeof(size_t));

  int arr[] = {1, 2, 3, 4, 5};
  size_t length = sizeof(arr) / sizeof(arr[0]);
  printf("sizeof(arr)   = %zu\n", sizeof(arr));
  printf("sizeof(arr[0])   = %zu\n", sizeof(arr[0]));
  printf("Array length: %zu\n", length);

  // Data structure alignment, padding
  typedef struct Human {
    char first_inital;
    int age;
    double height;
  } human_t;

  human_t person;
  printf("Struct address: %p\n", (void *)&person);
  printf("first_initial address: %p (offset: %zu)\n",
         (void *)&person.first_inital, offsetof(human_t, first_inital));
  printf("age address: %p (offset: %zu)\n", (void *)&person.age,
         offsetof(human_t, age));
  printf("height address: %p (offset: %zu)\n", (void *)&person.height,
         offsetof(human_t, height));

  printf("sizeof(human_t)   = %zu\n", sizeof(human_t));
  // gcc -Wpadded demo.c

  return 0;
}
