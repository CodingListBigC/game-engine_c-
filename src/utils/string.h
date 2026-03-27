#include <codecvt>
#include <cstdint>
#include <locale>
#include <string>

std::u32string to_utf32(const std::string &s) {
  std::u32string result;
  for (size_t i = 0; i < s.length();) {
    unsigned char c = s[i];
    uint32_t cp;
    int len;

    if (c <= 0x7F) {
      cp = c;
      len = 1;
    } else if ((c & 0xE0) == 0xC0) {
      cp = c & 0x1F;
      len = 2;
    } else if ((c & 0xF0) == 0xE0) {
      cp = c & 0x0F;
      len = 3;
    } else if ((c & 0xF8) == 0xF0) {
      cp = c & 0x07;
      len = 4;
    } else {
      i++;
      continue;
    } // Invalid UTF-8

    for (int j = 1; j < len && (i + j) < s.length(); j++) {
      cp = (cp << 6) | (s[i + j] & 0x3F);
    }
    result.push_back(static_cast<char32_t>(cp));
    i += len;
  }
  return result;
}
