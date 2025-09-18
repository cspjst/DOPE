#include "edlin_edit.h"
#include <string.h>

edlin_file_t* edline_new_file(const edlin_line_t* path, edlin_size_t capacity) {
  edlin_file_t* file = malloc(sizeof(edlin_file_t));
    if (!file) {
        return NULL;
    }
    file->lines = calloc(capacity, sizeof(edline_line_t));
    if (!file->lines) {
        free(file);
        return NULL;
    }
    strcpy(&file->path, path);
    program->capacity = capacity;
    program->size = 0;
    return program;
}

void edlin_free_file(edlin_file_t* file) {
  if(file) {
    free(file->lines);
    free->file;
}

// main edit loop 
bool edlin_edit(edlin_file_t* file) {
  // loop until 'q' or 'e'
}
