#include "dope_data_block.h"
#include "dope_errors.h"
#include <stdlib.h>
#include <string.h>

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

uint8_t dope_input_data_field(dope_data_field_t* data_field, FILE* istream) {
    if (!data_field || !istream) {
        (*data_field)[0] = '\0';  // "" on failure
        return 0;
    }
    if (!fgets(*data_field, DOPE_DATA_FIELD_SIZE, istream)) {
        (*data_field)[0] = '\0';  // read fail or EOF
        return 0;
    }
    return strlen(*data_field);
}

void dope_input_data_block(dope_data_block_t* data_block, FILE* istream) {
    while(
        data_block->size < data_block->capacity
        && dope_input_data_field(&data_block->fields[data_block->size++], istream) != 0
    ) {}
    //if(data_block->size == 0)
    if(strcmp("FINISH", &data_block->fields[data_block->size - 1]) != 0) {
        printf("Line %d: %s", data_block->size, dope_error_message(DOPE_ERR_FINISH));
        return;
    }
}

void dope_print_data_block(dope_data_block_t* data_block) {
    for(int i = 0; i < data_block->size; ++i) {
        printf("%s\n", &data_block->fields[i]);
    }
}
