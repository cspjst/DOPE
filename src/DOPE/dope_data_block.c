#include "dope_data_block.h"
#include "dope_errors.h"
#include "dope_types.h"
#include <stdlib.h>
#include <string.h>

dope_data_block_t* dope_new_data_block(uint8_t line_count) {
    dope_data_block_t* data = malloc(sizeof(dope_data_block_t));
    if(!data) {
        return NULL;
    }
    data->args = calloc(line_count, sizeof(dope_data_argument_t));
    if(!data->args) {
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
        free(data_block->args);
        free(data_block);
    }
}

uint8_t dope_input_data_value(dope_data_value_t* data_value, FILE* istream) {
    if (!data_value || !istream) {
        return 0;
    }
    if (!fgets(data_value->string, DOPE_DATA_STRING_SIZE, istream)) {
        data_value->number = 0.0;
        data_value->string[0] = '\0';  // read fail or EOF
        return 0;
    }
    return strlen(data_value->string);
}

void dope_parse_argument(dope_data_argument_t* arg, FILE* istream) {
    dope_size_t len = dope_input_data_value(&arg->value, istream);

}

void dope_input_data_block(dope_data_block_t* data_block, FILE* istream) {
    while(
        data_block->size < data_block->capacity
        //&& dope_input_data_arguement(data_block->args[data_block->size], istream) != 0
    ) {

        data_block->size++;
    }
    if(data_block->size == 0) {
        dope_panic(data_block->size, DOPE_ERR_NO_INPUT, "");
        return;
    }
    if(strcmp("FINISH", (char*)&data_block->fields[data_block->size - 1]) != 0) {
        dope_panic(data_block->size, DOPE_ERR_FINISH, "");
        return;
    }
}

void dope_print_data_block(dope_data_block_t* data_block) {
    for(int i = 0; i < data_block->size; ++i) {
        printf("%s\n", (char*)&data_block->fields[i]);
    }
}
