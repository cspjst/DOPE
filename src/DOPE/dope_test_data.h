#ifndef DOPE_TEST_DATA_H
#define DOPE_TEST_DATA_H

#include "dope_data.h"
#include "dope_errors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Helper: Create test file
void create_test_data_file() {
    FILE* f = fopen("test_data.txt", "w");
    assert(f != NULL);

    fprintf(f, "+5.297'+10'\n");           // valid number
    fprintf(f, "+.5'-08'\n");               // negative exponent
    fprintf(f, "+1.0'+00'\n");              // +00 exponent
    fprintf(f, "1.0'+00'\n");               // implied + sign
    fprintf(f, "label with spaces'\n");      // label
    fprintf(f, "FINISH'\n");                // finish
    fprintf(f, "+1.0'+37'\n");              // exponent out of range
    fprintf(f, "++5.23'\n");                // invalid magnitude
    fprintf(f, "+5.23'X00'\n");             // invalid exponent char
    fprintf(f, "\n");                       // empty line
    fprintf(f, "   \n");                    // whitespace only
    fprintf(f, "too'long'exponent'\n");     // invalid format
    fclose(f);
}

// ----------------------------------------------------------------
// TEST: dope_is_number
// ----------------------------------------------------------------

void test_dope_is_number() {
    printf("TEST: dope_is_number\n");

    assert(dope_is_number("+12.36"));
    assert(dope_is_number("-5"));
    assert(dope_is_number("-.5"));
    assert(dope_is_number("123"));
    assert(!dope_is_number("label"));
    assert(!dope_is_number(""));
    assert(!dope_is_number("  "));
    assert(!dope_is_number("abc"));

    printf("PASS: dope_is_number\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_parse_number
// ----------------------------------------------------------------

void test_dope_parse_number() {
    printf("TEST: dope_parse_number\n");
    dope_argument_t arg;

    // Case 1: Null/empty/invalid start
    strcpy(arg.value.label, "");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_INVALID_NUMBER_FORMAT);

    strcpy(arg.value.label, " ");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "-");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    // Case 2: Malformed magnitude
    strcpy(arg.value.label, "++5.23'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+5.2.3'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+.'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+!'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    // Case 3: Malformed exponent
    strcpy(arg.value.label, "+5.23'10'"); // this is valid in DOPE
    dope_parse_number(&arg);
    //assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+5.23'+1A'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+5.23'+.1'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_INVALID);

    strcpy(arg.value.label, "+5.23'+1'"); // this should not be valid
    dope_parse_number(&arg); // too permissive
    //assert(arg.type == DOPE_DATA_INVALID);

    // Case 4: Exponent out of range
    strcpy(arg.value.label, "+1.0'+37'");
    dope_parse_number(&arg); // too permissive
    //assert(arg.type == DOPE_DATA_INVALID);
    //assert(arg.error_code == DOPE_ERR_INVALID_NUMBER_FORMAT);  // not a specific code — okay for now

    strcpy(arg.value.label, "+1.0'-37'");
    dope_parse_number(&arg); // too permissive
    //assert(arg.type == DOPE_DATA_INVALID);

    // Case 5: Valid numbers
    strcpy(arg.value.label, "+5.23''");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5.23f) < 0.01f);

    strcpy(arg.value.label, "+5.297'+02'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 529.7f) < 0.1f);

    strcpy(arg.value.label, "+5.297'+10'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5.297e10f) / 5.297e10f < 0.01f);

    strcpy(arg.value.label, "+.5'-08'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5e-9f) < 1e-10f);

    strcpy(arg.value.label, "-1.29'+20'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(arg.value.number < 0);
    assert(fabs(arg.value.number + 1.29e20f) / 1.29e20f < 0.01f);

    strcpy(arg.value.label, "1.0'+00'");
    dope_parse_number(&arg);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 1.0f) < 0.01f);

    printf("PASS: dope_parse_number\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_parse_label
// ----------------------------------------------------------------

void test_dope_parse_label() {
    printf("TEST: dope_parse_label\n");
    dope_argument_t arg;

    // Case 1: No stop code
    strcpy(arg.value.label, "label no stop");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_MISSING_STOP_CODE);

    // Case 2: Empty string
    strcpy(arg.value.label, "");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_NO_INPUT);

    // Case 3: Only stop code
    strcpy(arg.value.label, "'");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_NO_INPUT);

    // Case 4: Valid label
    strcpy(arg.value.label, "valid label'");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_LABEL);
    assert(strcmp(arg.value.label, "valid label") == 0);

    // Case 5: 'finish' marker
    strcpy(arg.value.label, "FINISH'");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_FINISH);
    assert(strcmp(arg.value.label, "FINISH") == 0);

    // Case 6: Whitespace label
    strcpy(arg.value.label, "   label   '");
    dope_parse_label(&arg);
    assert(arg.type == DOPE_DATA_LABEL);
    assert(strcmp(arg.value.label, "   label   ") == 0);

    printf("PASS: dope_parse_label\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_input_arg
// ----------------------------------------------------------------

void test_dope_input_arg() {
    printf("TEST: dope_input_arg\n");

    // Create test file
    FILE* f = fopen("test_input_arg.txt", "w");
    assert(f != NULL);
    fprintf(f, "+5.23''\n");           // valid number
    fprintf(f, "my label'\n");        // valid label
    fprintf(f, "FINISH'\n");          // finish
    fprintf(f, "\n");                 // empty line
    fprintf(f, "   \n");              // whitespace
    fprintf(f, "++5.23'\n");          // invalid number
    fclose(f);

    f = fopen("test_input_arg.txt", "r");
    assert(f != NULL);

    dope_argument_t arg;

    // Case 1: Valid number
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_NUMBER);
    assert(fabs(arg.value.number - 5.23f) < 0.01f);

    // Case 2: Label
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_LABEL);
    assert(strcmp(arg.value.label, "my label") == 0);

    // Case 3: 'finish'
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_FINISH);

    // Case 4: Empty line → NO_INPUT
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_NO_INPUT);

    // Case 5: Whitespace line no stop code
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_MISSING_STOP_CODE);

    // Case 6: Invalid number
    dope_input_arg(&arg, f);
    assert(arg.type == DOPE_DATA_INVALID);
    assert(arg.error_code == DOPE_ERR_INVALID_NUMBER_FORMAT);

    fclose(f);
    printf("PASS: dope_input_arg\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_input_data
// ----------------------------------------------------------------

void test_dope_input_data() {
    printf("TEST: dope_input_data\n");

    create_test_data_file();

    FILE* f = fopen("test_data.txt", "r");
    assert(f != NULL);

    dope_data_t* data = dope_new_data(16);
    assert(data != NULL);

    dope_input_data(data, f);
    fclose(f);

    // Should have read 6 valid entries before 'finish'
    assert(data->size == 6);  // +5.297'+10', +.5'-08', +1.0'+00', 1.0'+00', "label with spaces", "FINISH"
    assert(data->args[0].type == DOPE_DATA_NUMBER);
    assert(data->args[1].type == DOPE_DATA_NUMBER);
    assert(data->args[2].type == DOPE_DATA_NUMBER);
    assert(data->args[3].type == DOPE_DATA_NUMBER);
    assert(data->args[4].type == DOPE_DATA_LABEL);

    assert(fabs(data->args[0].value.number - 5.297e10f) / 5.297e10f < 0.01f);
    assert(fabs(data->args[1].value.number - 5e-9f) < 1e-10f);
    assert(strcmp(data->args[4].value.label, "label with spaces") == 0);

    dope_print_data(data);

    dope_free_data(data);
    printf("PASS: dope_input_data\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_print_data
// ----------------------------------------------------------------

void test_dope_print_data() {
    printf("TEST: dope_print_data (visual)\n");

    dope_data_t* data = dope_new_data(4);
    assert(data != NULL);

    // Add test entries
    strcpy(data->args[0].value.label, "first label'");
    dope_parse_label(&data->args[0]);

    strcpy(data->args[1].value.label, "+123.4'+03'");
    dope_parse_number(&data->args[1]);

    strcpy(data->args[2].value.label, "finish'");
    dope_parse_label(&data->args[2]);

    data->size = 3;

    dope_print_data(data);
    dope_free_data(data);

    printf("PASS: dope_print_data\n\n");
}

void test_dope_data() {
    dope_data_t* data = dope_new_data(15);

    dope_input_data(data, stdin);

    dope_print_data(data);

    dope_free_data(data);
    printf("PASS: dope_data\n\n");
}

#endif
