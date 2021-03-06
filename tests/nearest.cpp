#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/nearest.h>

namespace gos {
namespace nearest {

TEST(GosNearestTest, Neighbor) {
  double first, second, value;
  double result;

  first = 10.0;
  second = 20.0;

  value = 5.0;
  result = gos_nearest_neighbor(first, second, value);
  EXPECT_GT(0.0, result);

  value = 12.0;
  result = gos_nearest_neighbor(first, second, value);
  EXPECT_GT(0.0, result);

  value = 18.0;
  result = gos_nearest_neighbor(first, second, value);
  EXPECT_LT(0.0, result);

  value = 25.0;
  result = gos_nearest_neighbor(first, second, value);
  EXPECT_LT(0.0, result);
}

#ifdef GOSC_NEAREST_NEIGHBOR_TIME_
TEST(GosNearestTest, TimeNeighbor) {
  time_t first, second, value;
  time_t result;

  first = 10;
  second = 20;

  value = 5;
  result = gos_nearest_neighbor_time(first, second, value);
  EXPECT_GT(0, result);

  value = 12;
  result = gos_nearest_neighbor_time(first, second, value);
  EXPECT_GT(0, result);

  value = 18;
  result = gos_nearest_neighbor_time(first, second, value);
  EXPECT_LT(0, result);

  value = 25;
  result = gos_nearest_neighbor_time(first, second, value);
  EXPECT_LT(0, result);
}
#endif

}
}
