#ifndef EDLIN_H
#define EDLIN_H

#include "edlin_constants.h" // EDLIN_DEFAULT_LINE_SIZE EDLIN_DEFAULT_CAPACITY 
#include "edlin_types.h"  // edlin_file_t
#include "edlin_parse.h"  // edlin_cmd_line_parse
#include "edlin_edit.h"   // everything else
#include <stdlib.h>

#define EDLIN_DEFAULT_LINE_SIZE   80
#define EDLIN_DEFAULT_CAPACITY    99

int main(int argc, char *argv[]) {
  edlin_file_t* file;
  if(!edlin_cmd_line_parse(argc, argv[], file) {
    return EXIT_FAILURE;
  } 
  if(!edlin_edit(file) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

#endif
