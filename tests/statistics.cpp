#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/statistics.h>

#define GOS_STATISTICS_TEST_SIZE 4

namespace gos {
namespace statistics {

TEST(GosStatisticsTest, Sum) {
  double sum;
  double values[GOS_STATISTICS_TEST_SIZE] = { 1.1, 2.2, 3.3, 4.4 };
  sum = gos_statistics_sum(values, GOS_STATISTICS_TEST_SIZE);
  EXPECT_DOUBLE_EQ(1.1 + 2.2 + 3.3 + 4.4, sum);
}

TEST(GosStatisticsTest, Sd) {
  double sum, average, sd;
  double values[GOS_STATISTICS_TEST_SIZE] = { 1.1, 2.2, 3.3, 4.4 };

  sum = gos_statistics_sum(values, GOS_STATISTICS_TEST_SIZE);
  average = sum / ((double)GOS_STATISTICS_TEST_SIZE);
  EXPECT_DOUBLE_EQ((1.1 + 2.2 + 3.3 + 4.4) / 4.0, average);

  sd = gos_statistics_sd(values, average, GOS_STATISTICS_TEST_SIZE);
  EXPECT_DOUBLE_EQ(1.2298373876248845, sd);
}

}
}
