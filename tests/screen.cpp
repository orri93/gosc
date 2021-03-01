#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/screen.h>

namespace gos {
namespace screen {

TEST(GosScreenTest, Index) {
  gos_screen screen;
  size_t i;

  screen.width = 600;
  screen.height = 400;
  i = gos_screen_index(&screen, 0, 0);
  EXPECT_EQ(0, i);
  i = gos_screen_index(&screen, 1, 0);
  EXPECT_EQ(1, i);
  i = gos_screen_index(&screen, 2, 0);
  EXPECT_EQ(2, i);
  i = gos_screen_index(&screen, 599, 0);
  EXPECT_EQ(599, i);
  i = gos_screen_index(&screen, 0, 1);
  EXPECT_EQ(600, i);
  i = gos_screen_index(&screen, 0, 2);
  EXPECT_EQ(1200, i);
  i = gos_screen_index(&screen, 1, 2);
  EXPECT_EQ(1201, i);
  i = gos_screen_index(&screen, 11, 2);
  EXPECT_EQ(1211, i);
}

} // namespace screen
} // namespace gos
