#include "dope_data_block.h"
#include <stdlib.h>

dope_data_block_t* dope_new_data_block(uint8_t line_count) {
    dope_data_block_t* data = malloc(sizeof(dope_data_block_t));
    if(!data) {
        return NULL;
    }
    data->fields = calloc(line_count, sizeof(dope_data_field_t));
    if(!data->fields) {
        free(data);
        return NULL;
    }
    data->capacity = line_count;
    data->size = 0;
    data->si = 0;
    return data;
}

void dope_free_data_block(dope_data_block_t* data_block) {
    if (data_block) {
        free(data_block->fields);
        free(data_block);
    }
}



void dope_print_data_block(dope_data_block_t* data_block) {
    for(int i = 0; i < data_block->size; ++i) {
        printf("%s\n", &data_block->fields[i]);
    }
}
