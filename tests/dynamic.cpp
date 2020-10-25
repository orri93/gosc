#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/dynamic.h>

#define GOS_DYNAMIC_TEST_SIZE 4

namespace gos {
namespace dynamic {

TEST(GosDynamicTest, DoubleArray) {
  gos_dynamic_double_array a;
  double sum;
  bool result;
  int i;

  result = gos_dynamic_double_array_initialize(&a, GOS_DYNAMIC_TEST_SIZE);
  EXPECT_TRUE(result);
  EXPECT_FALSE(a.items == NULL);
  EXPECT_EQ(GOS_DYNAMIC_TEST_SIZE, a.size);
  EXPECT_EQ(0, a.used);

  for (i = 0; i < 2 * GOS_DYNAMIC_TEST_SIZE; i++) {
    result = gos_dynamic_double_array_add(&a, (double)i);
    EXPECT_TRUE(result);
    EXPECT_FALSE(a.items == NULL);
  }
  EXPECT_EQ(2 * GOS_DYNAMIC_TEST_SIZE, a.size);
  EXPECT_EQ(2 * GOS_DYNAMIC_TEST_SIZE, a.used);

  sum = 0.0;
  for (i = 0; i < a.used; i++) {
    sum += a.items[i];
  }
  EXPECT_DOUBLE_EQ(28.0, sum);

  gos_dynamic_double_array_shutdown(&a);
  EXPECT_TRUE(a.items == NULL);
  EXPECT_EQ(0, a.size);
  EXPECT_EQ(0, a.used);

  result = gos_dynamic_double_array_initialize_zero(&a, GOS_DYNAMIC_TEST_SIZE);
  EXPECT_TRUE(result);
  EXPECT_FALSE(a.items == NULL);
  EXPECT_EQ(GOS_DYNAMIC_TEST_SIZE, a.size);
  EXPECT_EQ(0, a.used);

  sum = 0.0;
  for (i = 0; i < a.size; i++) {
    sum += a.items[i];
  }
  EXPECT_DOUBLE_EQ(0.0, sum);
}

}
}
