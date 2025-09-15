#include "dope_variables.h"
#include "dope_errors.h"
#include "dope_types.h"
#include "dope_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool dope_is_valid_var_name(const char* name) {
    if (!name || !*name) return false;
    size_t len = strlen(name);
    if (len == 1) {    
        return ( // variable is a capital letter not L or O (ambiguity 1 and 0)...
            islower(name[0]) ||
            isdigit(name[0]) || 
            name[0] == 'L' || 
            name[0] == 'O'
        ) ? false : true;  
    }
    if (len == 2) { 
        return( // ...or letter followed by a single digit.
            islower(name[0]) ||
            isdigit(name[0]) || 
            name[0] == 'L' || 
            name[0] == 'O' || 
            !isdigit(name[1])
        ) ? false : true;
    }
    return false; // Anything else — invalid
}

dope_variable_t* private_find_var(const dope_vartab_t* vartab, const dope_var_name_t name) {
    for(int i = 0; i < vartab->size; ++i) {
        if(strcmp(name, vartab->vars[i].name) == 0) {
            return &vartab->vars[i];
        }
    }
    return NULL;
}

// call find var first
dope_variable_t* private_alloc_var(dope_vartab_t* vartab, const dope_var_name_t name) {
    if(vartab->size == vartab->capacity) {
        dope_panic(vartab->size, DOPE_ERR_OUT_OF_VARS, name);
        exit(EXIT_FAILURE);
    }
    dope_string_toupper((char*)name);
    if(!dope_is_valid_var_name(name) {
        dope_panic(0, DOPE_ERR_INVALID_FIELD, name);
        exit(EXIT_FAILURE);
    }
    strcpy(vartab->vars[vartab->size].name, name);
    vartab->vars[vartab->size].type = DOPE_NUMBER;
    // calloc zeroed the rest
    return &vartab->vars[vartab->size++];
}

// read so variable must exist
const dope_float_t* dope_const_pvar(const dope_vartab_t* vartab, const dope_var_name_t name) {
    dope_variable_t* var = private_find_var(vartab, name);
    if(!var) {
        dope_panic(vartab->size, DOPE_ERR_VAR_NOT_FOUND, name);
        exit(EXIT_FAILURE);
    }
    return &(var->value.number);
}

dope_float_t* dope_pvar(dope_vartab_t* vartab, const dope_var_name_t name) {
    dope_variable_t* var = private_find_var(vartab, name);
    if(!var) {
        var = private_alloc_var(vartab, name);
    }
    return &(var->value.number);
}

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
