#include "dope_variables.h"
#include "dope_data.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

dope_vartab_t* dope_new_vartab(dope_size_t capacity) {
    dope_vartab_t* vartab = malloc(sizeof(dope_vartab_t));
    if (!vartab) {
        return NULL;
    }
    vartab->vars = calloc(capacity, sizeof(dope_var_t));
    if (!vartab->vars) {
        free(vartab);
        return NULL;
    }
    vartab->capacity = capacity;
    vartab->size = 0;
    return vartab;
}

void dope_free_vartab(dope_vartab_t* vartab) {
    if (vartab) {
        free(vartab->vars);
        free(vartab);
    }
}

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

float* dope_var_pfloat(const dope_vartab_t* vartab, const dope_var_name_t name) {
    dope_var_t* v = dope_find_var(vartab, name);
    if(v) {
        return &v->value;
    }
    dope_panic(0, DOPE_ERR_VAR_NOT_FOUND, name);
    exit(EXIT_FAILURE);
}

void dope_print_var(const dope_var_t* v) {
    printf(" %s\t%f\t %i\n",
        v->name,
        v->value,
        v->error_code
    );
}

void dope_print_vartab(const dope_vartab_t* vartab) {
    printf("name\tvalue\t\terror\n");
    for(int i = 0; i < vartab->size; ++i) {
        dope_print_var(&vartab->vars[i]);
    }
}
