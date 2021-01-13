#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/scale.h>

namespace gos {
namespace scale {

TEST(GosScaleTest, Value) {
  gos_scale scale;
  double s;

  scale.domain.from = 1.0;
  scale.domain.to = 2.0;
  scale.range.from = 10.0;
  scale.range.to = 20.0;
  s = gos_scale_value(&scale, 0.0);
  EXPECT_DOUBLE_EQ(0.0, s);
  s = gos_scale_value(&scale, 1.0);
  EXPECT_DOUBLE_EQ(10.0, s);
  s = gos_scale_value(&scale, 1.5);
  EXPECT_DOUBLE_EQ(15.0, s);
  s = gos_scale_value(&scale, 2.0);
  EXPECT_DOUBLE_EQ(20.0, s);
  s = gos_scale_value(&scale, 3.0);
  EXPECT_DOUBLE_EQ(30.0, s);

  scale.domain.from = 1.0;
  scale.domain.to = 2.0;
  scale.range.from = 20.0;
  scale.range.to = 10.0;
  s = gos_scale_value(&scale, 1.0);
  EXPECT_DOUBLE_EQ(20.0, s);
  s = gos_scale_value(&scale, 1.5);
  EXPECT_DOUBLE_EQ(15.0, s);
  s = gos_scale_value(&scale, 2.0);
  EXPECT_DOUBLE_EQ(10.0, s);
}

TEST(GosScaleTest, Reverse) {
  gos_scale scale;
  double r;

  scale.domain.from = 1.0;
  scale.domain.to = 2.0;
  scale.range.from = 10.0;
  scale.range.to = 20.0;
  r = gos_scale_reverse(&scale, 0.0);
  EXPECT_DOUBLE_EQ(0.0, r);
  r = gos_scale_reverse(&scale, 10.0);
  EXPECT_DOUBLE_EQ(1.0, r);
  r = gos_scale_reverse(&scale, 15.0);
  EXPECT_DOUBLE_EQ(1.5, r);
  r = gos_scale_reverse(&scale, 20.0);
  EXPECT_DOUBLE_EQ(2.0, r);
  r = gos_scale_reverse(&scale, 30.0);
  EXPECT_DOUBLE_EQ(3.0, r);

  scale.domain.from = 1.0;
  scale.domain.to = 2.0;
  scale.range.from = 20.0;
  scale.range.to = 10.0;
  r = gos_scale_reverse(&scale, 20.0);
  EXPECT_DOUBLE_EQ(1.0, r);
  r = gos_scale_reverse(&scale, 15.0);
  EXPECT_DOUBLE_EQ(1.5, r);
  r = gos_scale_reverse(&scale, 10.0);
  EXPECT_DOUBLE_EQ(2.0, r);
}

} // namespace scale
} // namespace gos
