#ifndef DOPE_TEST_VARS_H
#define DOPE_TEST_VARS_H

#include "dope_variables.h"
#include "dope_errors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_dope_vars() {
    printf("TEST: dope_variables\n");

    dope_vartab_t* vartab = dope_new_vartab(10);
    assert(vartab != NULL);
    assert(vartab->capacity == 10);
    assert(vartab->size == 0);

    // Case 1: alloc new var
    float* a = dope_pvar(vartab, "A");
    assert(a != NULL);
    assert(*dope_const_pvar(vartab, "A") == 0.0f);
    *dope_pvar(vartab, "A") = 1.1f;
    assert(*dope_const_pvar(vartab, "A") == 1.1f);

    // Case 2: alloc new with digit
    assert(dope_pvar(vartab, "T7") != NULL);
    assert(*dope_pvar(vartab, "T7") == 0);
    *dope_pvar(vartab, "T7") = 100.0f;
    assert(*dope_const_pvar(vartab, "T7") == 100.0f);

    // Case 3: set get 2 char
    *dope_pvar(vartab, "pi") = 3.14159;
    *dope_pvar(vartab, "p2") = *dope_const_pvar(vartab, "PI");
    assert(*dope_const_pvar(vartab, "PI") == *dope_const_pvar(vartab, "P2"));
    *dope_pvar(vartab, "P2") = 2.0 * 3.14159f;
    assert(*dope_const_pvar(vartab, "P2") == 2.0 * *dope_const_pvar(vartab, "PI"));
    *dope_pvar(vartab, "P2") = *dope_const_pvar(vartab, "PI") + *dope_const_pvar(vartab, "P2");
    assert(*dope_const_pvar(vartab, "P2") == 3.0 * *dope_const_pvar(vartab, "PI"));

    dope_print_vartab(vartab);

    dope_free_vartab(vartab);
    printf("PASS: dope_variables\n\n");
}

#endif
