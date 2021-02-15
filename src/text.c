#include <ctype.h>

#include <gos/text.h>

int gos_text_are_all_char_digits(const char* text) {
  int result = 1;
  char* at;
  for (at = ((char*)text); *at != '\0' && result; at++) {
    result &= isdigit(*at) > 0;
  }
  return result;
}

int gos_text_are_all_char_digits_l(const char* text, int count) {
  int i, result = 1;
  for (i = 0; i < count; i++) {
    result &= isdigit(text[i]) > 0;
    if (result == 0) {
      return result;
    }
  }
  return result;
}

int gos_text_are_all_char_digits_or_period(const char* text) {
  int result = 1;
  char* at;
  for (at = ((char*)text); *at != '\0' && result; at++) {
    result &= isdigit(*at) > 0 || *at == '.';
  }
  return result;
}

int gos_text_are_all_char_digits_or_period_l(const char* text, int count) {
  int i, result = 1;
  for (i = 0; i < count; i++) {
    result &= isdigit(text[i]) > 0 || text[i] == '.';
    if (result == 0) {
      return result;
    }
  }
  return result;
}
