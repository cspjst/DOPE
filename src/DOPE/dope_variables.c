#include "dope_variables.h" 
#include <string.h>

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

dope_var_t* dope_find_var(dope_vartab_t* vartab, const dope_var_name_t name) {
    for(int i = 0; i < vartab->size; ++i) {
        if(strcmp(name, vartab->vars[i]->name) == 0) {
            return vartab->vars[i];
        }
    }
    return NULL;
}

dope_var_t* dope_alloc_var(dope_vartab_t* vartab, const dope_var_name_t name) {
    if(vartab->size == vartab->capacity) {
        return NULL;
    }
    dope_var_t* v = vartab->vars[++vartab->size];
    strcpy(v->name, name);
    // calloc zeroed the rest
    return v;
}

void dope_set_var(dope_vartab_t* vartab, const dope_var_name_t name, float value) {
    dope_var_t* v = dope_find_var(vartab, name);
    if(v) {
        v = dope_alloc_var(vartab, name);
    }
    if(v) {
        // dope_panic
        return;
    }
    v->value = value;
}

float dope_get_var(const dope_vartab_t* vartab, const dope_var_name_t name) {
    dope_var_t* v = dope_find_var(vartab, name);
    if(v) {
        return v->value;
    }
    // else dope_panic;
    return 0.0;
}
