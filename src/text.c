#include <ctype.h>

#include <gos/text.h>

int gos_text_are_all_char_digits(const char* text) {
  int result = 1;
  char* at;
  for (at = ((char*)text); *at != '\0' && result != 0; at++) {
    result *= isdigit(*at);
  }
  return result;
}

int gos_text_are_all_char_digits_l(const char* text, int count) {
  int i, result = 1;
  for (i = 0; i < count; i++) {
    result *= isdigit(text[i]);
    if (result == 0) {
      return result;
    }
  }
  return result;
}
