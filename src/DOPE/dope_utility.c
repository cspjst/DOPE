#include "dope_utility.h"
#include <string.h>

bool dope_is_truncated(dope_line_t* line) {
   if (!line) {
       return false;
   }
   uint8_t len = strlen(*line);
   // truncated if...
   return ((*line)[len - 1] != '\n') &&     // true no newline
          (len == DOPE_LINE_SIZE - 1);      // true buffer full
}

void dope_consume_remaining(FILE* istream) {
    int ch;
    while ((ch = fgetc(istream)) != '\n' && ch != EOF);
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
