#include "dope_data_block.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <stdlib.h>
#include <string.h>

dope_data_block_t* dope_new_data_block(uint8_t line_count) {
    dope_data_block_t* data = malloc(sizeof(dope_data_block_t));
    if(!data) {
        return NULL;
    }
    data->args = calloc(line_count, sizeof(dope_argument_t));
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

void dope_input_argument(dope_argument_t* arg, FILE* istream) {
    // 1. read the line and catch truncated and invalid character errors
    uint8_t length = dope_read_line(&arg->value.string, istream);
    if(dope_is_truncated(&arg->value.string)) {
        arg->error_code = DOPE_ERR_LINE_TOO_LONG;
        dope_consume_remaining(istream);
        return;
    }
    // 2. sanitize line
    arg->value.string[strcspn(arg->value.string, "\n")] = '\0';
    // 3. parse if number
    /*
    if(dope_is_number(&arg->value.string)) {
        dope_parse_number(arg);
        return;
        }*/
    // 4. otherwise plain string
    arg->type = DOPE_DATA_LABEL;
    return;
}
