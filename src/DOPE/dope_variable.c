#include "dope_variable.h"
#include <stdio.h>
#include <stdlib.h>

const char* DOPE_TYPE_NAMES[] = {
    "null",
    "number",
    "vector"
};

dope_vartab_t* dope_new_vartab(dope_size_t capacity)  {
    dope_vartab_t* vartab = malloc(sizeof(dope_vartab_t));
    if (!vartab) {
        return NULL;
    }
    vartab->vars = calloc(capacity, sizeof(dope_variable_t));
    if (!vartab->vars) {
        free(vartab);
        return NULL;
    }
    vartab->capacity = capacity;
    vartab->size = 0;
    return vartab;
}

void dope_free_vartab(dope_vartab_t* vartab)  {
    if (vartab) {
        free(vartab->vars);
        free(vartab);
    }
}

//dope_variable_t* dope_find_var(const dope_vartab_t* vartab, const dope_var_name_t name);

//const float* dope_pfloat_read_var(const dope_vartab_t* vartab, const dope_var_name_t name);

//float* dope_pfloat_write_var(const dope_vartab_t* vartab, const dope_var_name_t name);

void dope_print_var(const dope_variable_t* var) {
    printf("%s\t%s\t%f\n",
        DOPE_TYPE_NAMES[var->type],
        var->name,
        var->value.number
    );
}

void dope_print_vartab(const dope_vartab_t* vartab) {
    printf("type\tname\tvalue\n");
    for(int i = 0; i < vartab->capacity; ++i) {
        dope_print_var(&vartab->vars[i]);
    }
}


/*
dope_var_t* dope_find_var(const dope_vartab_t* vartab, const dope_var_name_t name) {
    for(int i = 0; i < vartab->size; ++i) {
        if(strcmp(name, vartab->vars[i].name) == 0) {
            return &vartab->vars[i];
        }
    }
    return NULL;
}

dope_var_t* dope_alloc_var(dope_vartab_t* vartab, const dope_var_name_t name) {
    if(vartab->size == vartab->capacity) {
        dope_panic(vartab->size, DOPE_ERR_OUT_OF_VARS, name);
        exit(EXIT_FAILURE);
    }
    if(dope_find_var(vartab, name)) {
        dope_panic(vartab->size + 1, DOPE_ERR_LINE_TOO_LONG, name);
        exit(EXIT_FAILURE);
    }
    if(strlen(name) == DOPE_VAR_NAME_SIZE) {
        dope_panic(vartab->size + 1, DOPE_ERR_LINE_TOO_LONG, name);
        exit(EXIT_FAILURE);
    }
    if(dope_is_number((char*)name)) {
        dope_panic(vartab->size + 1, DOPE_ERR_INVALID_CHAR, name);
        exit(EXIT_FAILURE);
    }
    dope_string_toupper((char*)name);
    strcpy(vartab->vars[vartab->size].name, name);
    // calloc zeroed the rest
    return &vartab->vars[vartab->size++];
}
*/
