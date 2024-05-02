#include "s21_array_tests.h"
#include "s21_list_tests.h"
#include "s21_map_tests.h"
#include "s21_queue_tests.h"
#include "s21_set_tests.h"
#include "s21_stack_tests.h"
#include "s21_vector_tests.h"

int main(int argc, const char** argv) {
  testing::InitGoogleTest(&argc, (char**)argv);
  return RUN_ALL_TESTS();
}