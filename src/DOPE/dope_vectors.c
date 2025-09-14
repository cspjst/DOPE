#include "dope_vectors.h"
#include "dope_constants.h"
#include "dope_types.h"
#include <stdlib.h>

dope_vectab_t* dope_new_vectab() {
    dope_vectab_t* vectab = malloc(sizeof(dope_vectab_t));
    if (!vectab) {
        return NULL;
    }
    vectab->capacity = DOPE_VECTORS_MAX;
    vectab->size = 0;
    return vectab;
}

void dope_free_vectab(dope_vectab_t* vectab) {
    if (vectab) {
        free(vectab);
    }
}
