#include "memory/arena.h"
#include "munit/munit.h"

void test_pointers_exist_after_realloc() {
  Arena arena = {0};
  arena_init(&arena, 16);
  int *ptrs[16];

  for (int i = 0; i < 16; ++i) {
    ptrs[i] = arena_alloc(&arena, sizeof(int));
    *ptrs[i] = i;
  }

  arena_alloc(&arena, 1024 * 1024);

  for (int i = 0; i < 16; ++i) {
    munit_assert_int(*ptrs[i], ==, i);
  }
}

int main(void) { test_pointers_exist_after_realloc(); }
