#ifndef GOS_TEXT_H_
#define GOS_TEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

int gos_text_are_all_char_digits(const char* text);
int gos_text_are_all_char_digits_l(const char* text, int count);

#ifdef __cplusplus
}
#endif

#endif
