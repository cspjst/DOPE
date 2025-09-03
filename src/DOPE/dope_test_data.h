#include "dope_data_block.h"
#include "dope_errors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void test_dope_is_number() {
    printf("TEST dope_is_number\n");
    dope_argument_t arg;
    assert(dope_is_number("+12.36"));
    assert(dope_is_number("-5"));
    assert(dope_is_number("-.5"));
    assert(!dope_is_number("label"));
    assert(!dope_is_number(""));
    assert(!dope_is_number("  "));

    printf("PASS dope_is_number\n");
}

void test_dope_parse_number() {
    printf("TEST dope_parse_number\n");
    dope_argument_t arg;

    printf("Case 0: null token errors...\n");
    strcpy(arg.value.label, "'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, " ");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "+");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);

    printf("Case 1: Malformed magnitude errors...\n");
    strcpy(arg.value.label, "++5.23'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "+5.2.3'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "+123456.7'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "+.'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);
    strcpy(arg.value.label, "+!'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);

    printf("Case 2: No exponent (implied +00)\n");
    strcpy(arg.value.label, "+5.23'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    strcpy(arg.value.label, "+5.23''");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5.23f) < 0.01f);
    dope_print_arg(&arg);

    printf("Case 3: Malformed exponent errors...\n");
    strcpy(arg.value.label, "+5.23'10");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    dope_panic(1, arg.error_code, arg.value.label);

    /*

    printf("Case 1: Simple number + exponent\n");
    strcpy(arg.value.label, "+5.297'+02'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 529.7f) < 0.1f);
    // 5.297 × 10^10 = 52,970,000,000
    strcpy(arg.value.label, "+5.297'+10'");
    dope_parse_number(&arg);
    //dope_print_arg(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5.297e10f) / 5.297e10f < 0.01f);  // within 1%



    printf("Case 3: Negative exponent\n");
    strcpy(arg.value.label, "+.5'-08'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5e-9f) < 1e-10f);

    printf("Case 4: Negative magnitude\n");
    strcpy(arg.value.label, "-1.29'+20'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(arg.value.number < 0);
    assert(fabs(arg.value.number + 1.29e20f) / 1.29e20f < 0.01f);  // within 1%

    printf("Case 5: Exponent out of range\n");
    strcpy(arg.value.label, "+1.0'+37'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_EXPONENT_OUT_OF_RANGE);

    printf("Case 6: Invalid magnitude format\n");
    strcpy(arg.value.label, "++1.2'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    printf("Case 7: Invalid exponent format\n");
    strcpy(arg.value.label, "+1.0'X00'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    printf("Case 8: Too many digits in magnitude\n");
    strcpy(arg.value.label, "+1234567'+00'");  // 7 digits
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);  // if you enforce 6-digit limit

    printf("Case 9: Valid 6-digit magnitude\n");
    strcpy(arg.value.label, "+123456'+00'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 123456.0f) < 1.0f);

    */

    printf("PASS dope_parse_number\n");
}

void test_dope_input_argument() {
    // Create test input file
    FILE* f = fopen("test_data.txt", "w");
    assert(f != NULL);

    fprintf(f, "+5.297'+10'\n");
    fprintf(f, "+.5'-08'\n");
    fprintf(f, "1.0'+00'\n");
    fprintf(f, "label with spaces\n");
    fprintf(f, "finish'\n");
    fprintf(f, "too'long'exponent'\n");  // invalid
    fclose(f);

    f = fopen("test_data.txt", "r");
    assert(f != NULL);

    dope_argument_t arg;

    // Test 1: Valid number
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 529.7f) < 0.1f);

    // Test 2: Negative exponent
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5e-9f) < 1e-10f);

    // Test 3: +00 exponent
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 1.0f) < 0.01f);

    // Test 4: Label
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_LABEL);
    assert(strcmp(arg.value.label, "label with spaces") == 0);

    // Test 5: finish
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_LABEL);  // or special handling
    assert(strcmp(arg.value.label, "finish") == 0);

    // Test 6: Invalid number
    dope_input_argument(&arg, f);
    assert(arg.type == DOPE_DATA_INVALID);

    fclose(f);
    printf("dope_input_argument: all tests passed\n");
}
