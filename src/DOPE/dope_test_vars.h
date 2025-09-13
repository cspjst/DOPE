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
/*
    // Case 1: alloc new var
    dope_var_t* a = dope_alloc_var(vartab, "A");
    assert(a != NULL);
    assert(dope_find_var(vartab, "A") == a);
    assert(dope_find_var(vartab, "a") == NULL);
    assert(*dope_var_pfloat(vartab, "A") == 0.0f);
    *dope_var_pfloat(vartab, "A") = 13.5f;
    assert(*dope_var_pfloat(vartab, "A") == 13.5f);

    // Case 2: alloc new with digit
    dope_var_t* t7 = dope_alloc_var(vartab, "T7");
    assert(t7 != NULL);
    assert(strcmp(t7->name, "T7") == 0);
    *dope_var_pfloat(vartab, "T7") = 100.0f;
    assert(*dope_var_pfloat(vartab, "T7") == 100.0f);

    // Case 3: set get 2 char
    dope_alloc_var(vartab, "pi");
    dope_alloc_var(vartab, "p2");
    *dope_var_pfloat(vartab, "PI") = 3.14159f;
    assert(*dope_var_pfloat(vartab, "PI") == 3.14159f);
    *dope_var_pfloat(vartab, "p2") = 2.0 * 3.14159f;
    assert(*dope_var_pfloat(vartab, "P2") == 2.0 * 3.14159f);
    *dope_var_pfloat(vartab, "p2") = 3.0 * 3.14159f;
    assert(*dope_var_pfloat(vartab, "P2") == 3.0 * 3.14159f);
*/

    dope_print_vartab(vartab);

    dope_free_vartab(vartab);
    printf("PASS: dope_variables\n\n");
}

#endif
