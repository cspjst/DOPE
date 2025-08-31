#include "dope_utility.h"
#include <string.h>
#include <ctype.h>
#include <assert.h>

static const float LOOKUP_POWER10[] = {
    1e-36f, 1e-35f, 1e-34f, 1e-33f, 1e-32f, 1e-31f, 1e-30f,
    1e-29f, 1e-28f, 1e-27f, 1e-26f, 1e-25f, 1e-24f, 1e-23f,
    1e-22f, 1e-21f, 1e-20f, 1e-19f, 1e-18f, 1e-17f, 1e-16f,
    1e-15f, 1e-14f, 1e-13f, 1e-12f, 1e-11f, 1e-10f, 1e-9f,
    1e-8f, 1e-7f, 1e-6f, 1e-5f, 1e-4f, 1e-3f, 1e-2f, 1e-1f,
    1e0f, 1e1f, 1e2f, 1e3f, 1e4f, 1e5f, 1e6f, 1e7f, 1e8f, 1e9f,
    1e10f, 1e11f, 1e12f, 1e13f, 1e14f, 1e15f, 1e16f, 1e17f,
    1e18f, 1e19f, 1e20f, 1e21f, 1e22f, 1e23f, 1e24f, 1e25f,
    1e26f, 1e27f, 1e28f, 1e29f, 1e30f, 1e31f, 1e32f, 1e33f,
    1e34f, 1e35f, 1e36f
};

float power_of_10(int e) {
    // 1. Convert exponent to array index
    int i = e + 36;
    // 2.
    if (i >= 0 && i < (int)(sizeof(LOOKUP_POWER10)/sizeof(LOOKUP_POWER10[0]))) {
        return LOOKUP_POWER10[i];
    }
    // 3. out of range
    assert(false && "exponent is out of range");
    return 0.0;
}

bool dope_is_truncated(dope_line_t* line) {
   if (!line) {
       return false;
   }
   uint8_t len = strlen(*line);
   // truncated if...
   return (*line)[len - 1] != '\n' &&     // true no newline
          (len == DOPE_LINE_SIZE - 1);      // true buffer full
}

void dope_consume_remaining(FILE* istream) {
    int ch;
    while ((ch = fgetc(istream)) != '\n' && ch != EOF);
}

void dope_string_toupper(char* str) {
   while (*str) {
      *str = (char)toupper((unsigned char)*str);
      str++;
   }
}

// line is ...\n\0 on success or ...\0 on truncation or \0 on fail
dope_size_t dope_read_line(dope_line_t* line, FILE* istream) {
    if (!line || !istream) {
        (*line)[0] = '\0';  // "" on failure
        return 0;
    }
    if (!fgets(*line, DOPE_LINE_SIZE, istream)) {
        (*line)[0] = '\0';  // read fail or EOF
        return 0;
    }
    return strlen(*line);
}

bool dope_has_space(const char* str) {
    if (!str) {
       return false;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            return true;
        }
    }
    return false;
}
