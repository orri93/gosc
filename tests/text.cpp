#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/text.h>

namespace gos {
namespace text {

TEST(GosTextTest, AreAllCharDigits) {
  int areDigits;

  areDigits = gos_text_are_all_char_digits("0123456789");
  EXPECT_TRUE(areDigits != 0);

  areDigits = gos_text_are_all_char_digits("01bb");
  EXPECT_TRUE(areDigits == 0);

  areDigits = gos_text_are_all_char_digits("0.123456789");
  EXPECT_TRUE(areDigits == 0);

  areDigits = gos_text_are_all_char_digits_or_period("0.123456789");
  EXPECT_TRUE(areDigits != 0);

  areDigits = gos_text_are_all_char_digits_or_period("0.1bb");
  EXPECT_TRUE(areDigits == 0);
}

} // namespace signal
} // namespace gos
