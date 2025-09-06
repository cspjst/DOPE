#include "dope_constants.h"
#include "dope_program.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Helper: Create test input file
void create_test_input_file() {
    FILE* f = fopen("test_program.txt", "w");
    assert(f != NULL);

    fprintf(f, "SQR'X'Y'\n");                    // valid
    fprintf(f, "this_line_is_way_too_long_exceeding_DOPE_LINE_SIZE_by_far'\n");
    fprintf(f, "+'A'B'C'\n");                    // valid
    fprintf(f, "J'Z'\n");                        // valid
    fprintf(f, "J'Z'15'\n");                     // too many args
    fprintf(f, "FOO'\n");                        // unknown
    fprintf(f, "'\n");                           // empty
    fprintf(f, "E'\n");                          // valid, no operands
    fprintf(f, "P'X'\n");                        // valid
    fprintf(f, "P'\n");                          // too few
    fprintf(f, "Z'X'Y'Z'1'\n");                    // too many (Z takes 3)
    fprintf(f, "+'A B'C'\n");                    // space → invalid
    fprintf(f, "+'a'b'c'\n");                    // lowercase → uppercase
    fprintf(f, "F'\n");                          // stop instruction
    fprintf(f, "S'\n");                          // start
    fclose(f);
}

// ----------------------------------------------------------------
// TEST: dope_is_truncated
// ----------------------------------------------------------------

void test_dope_is_truncated() {
    printf("TEST: dope_is_truncated\n");
    dope_line_t buf;

    assert(!dope_is_truncated(NULL));

    buf[0] = '\0';
    assert(!dope_is_truncated(&buf));

    strcpy(buf, "X\n");
    assert(!dope_is_truncated(&buf));

    memset(buf, 'A', DOPE_LINE_SIZE - 2);
    buf[DOPE_LINE_SIZE - 2] = '\n';
    buf[DOPE_LINE_SIZE - 1] = '\0';
    assert(!dope_is_truncated(&buf));

    buf[DOPE_LINE_SIZE - 2] = 'B';
    buf[DOPE_LINE_SIZE - 1] = '\0';
    assert(dope_is_truncated(&buf));

    buf[DOPE_LINE_SIZE - 2] = '\0';
    assert(!dope_is_truncated(&buf));

    printf("PASS: dope_is_truncated\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_read_line
// ----------------------------------------------------------------

void test_dope_read_line() {
    printf("TEST: dope_read_line\n");
    create_test_input_file();

    FILE* f = fopen("test_program.txt", "r");
    assert(f != NULL);
    dope_line_t line;

    size_t len = dope_read_line(&line, f);
    assert(len == 9); // \n is not stripped
    assert(strcmp(line, "SQR'X'Y'\n") == 0);

    len = dope_read_line(&line, f);
    assert(len == DOPE_LINE_SIZE - 1);
    assert(dope_is_truncated(&line));
    dope_consume_remaining(f);

    len = dope_read_line(&line, f);
    assert(len == 9);
    assert(strcmp(line, "+'A'B'C'\n") == 0);

    fclose(f);
    printf("PASS: dope_read_line\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_instruction_tokenize
// ----------------------------------------------------------------

void test_dope_instruction_tokenize() {
    printf("TEST: dope_instruction_tokenize\n");
    dope_instruction_record_t tokens;
    dope_line_t line;

    assert(dope_instruction_tokenize(NULL, tokens) == 0);
    assert(dope_instruction_tokenize(&line, NULL) == 0);

    strcpy(line, "");
    assert(dope_instruction_tokenize(&line, tokens) == 0);

    strcpy(line, "SQR");
    assert(dope_instruction_tokenize(&line, tokens) == 1);
    assert(strcmp(tokens[0], "SQR") == 0);

    strcpy(line, "SQR'X'Y");
    assert(dope_instruction_tokenize(&line, tokens) == 3);
    assert(strcmp(tokens[0], "SQR") == 0);
    assert(strcmp(tokens[1], "X") == 0);
    assert(strcmp(tokens[2], "Y") == 0);

    strcpy(line, "TOOLONGVALUE'X");
    size_t count = dope_instruction_tokenize(&line, tokens);
    assert(count == 2);
    assert(strlen(tokens[0]) <= DOPE_FIELD_SIZE - 1);

    printf("PASS: dope_instruction_tokenize\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_lookup_opcode
// ----------------------------------------------------------------

void test_dope_lookup_opcode() {
    printf("TEST: dope_lookup_opcode\n");

    assert(dope_lookup_opcode(NULL) == 0);
    assert(dope_lookup_opcode("") == 0);
    assert(dope_lookup_opcode(" ") == 0);
    assert(dope_lookup_opcode("\t") == 0);

    assert(dope_lookup_opcode("SQR") == DOPE_OP_SQR);
    assert(dope_lookup_opcode("+") == DOPE_OP_ADD);
    assert(dope_lookup_opcode("F") == DOPE_OP_STOP);
    assert(dope_lookup_opcode("S") == DOPE_OP_START);

    assert(dope_lookup_opcode("sqr") == 0);
    assert(dope_lookup_opcode("Sqr") == 0);
    assert(dope_lookup_opcode("sQR") == 0);

    assert(dope_lookup_opcode("FOO") == 0);

    printf("PASS: dope_lookup_opcode\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_input_instruction
// ----------------------------------------------------------------

void test_dope_input_instruction() {
    printf("TEST: dope_input_instruction\n");
    create_test_input_file();

    FILE* f = fopen("test_program.txt", "r");
    assert(f != NULL);
    dope_instruction_t inst;

    // Test 1: Valid instruction
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_SQR);
    assert(inst.error_code == DOPE_ERR_SUCCESS);
    assert(strcmp(inst.fields[0], "SQR") == 0);
    assert(strcmp(inst.fields[1], "X") == 0);
    assert(strcmp(inst.fields[2], "Y") == 0);

    // Test 2: Truncated line
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_LINE_TOO_LONG);

    // Test 3: Valid instruction after truncate
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_ADD);
    assert(strcmp(inst.fields[0], "+") == 0);
    assert(strcmp(inst.fields[1], "A") == 0);

    // Test 4: J Z → valid
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INPUT);
    assert(strcmp(inst.fields[1], "Z") == 0);

    // Test 5: J Z 15 → too many
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_MANY_ARGS);

    // Test 6: FOO → unknown
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_UNKNOWN_INSTR);

    // Test 7: Empty line
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_NO_INSTR);

    // Test 8: E → valid
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_END);
    assert(inst.error_code == DOPE_ERR_SUCCESS);

    // Test 9: P X → valid
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_PRINT);
    assert(strcmp(inst.fields[1], "X") == 0);

    // Test 10: P → too few
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_FEW_ARGS);

    // Test 11: Z X Y Z → too many
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_MANY_ARGS);

    // Test 12: + A B C with space → invalid char
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_INVALID_CHAR);

    // Test 13: + a b c → lowercase → uppercase
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_ADD);
    assert(strcmp(inst.fields[1], "A") == 0);

    // Test 14: F → stop
    dope_input_instruction(&inst, f);
    assert(inst.opcode == DOPE_OP_STOP);
    assert(inst.error_code == DOPE_ERR_SUCCESS);

    fclose(f);
    printf("PASS: dope_input_instruction\n\n");
}

// ----------------------------------------------------------------
// TEST: dope_input_program
// ----------------------------------------------------------------

void test_dope_input_program() {
    printf("TEST: dope_input_program\n");
    create_test_input_file();

    FILE* f = fopen("test_program.txt", "r");
    assert(f != NULL);

    dope_program_t* prog = dope_new_program(15);
    assert(prog != NULL);

    dope_input_program(prog, f);
    fclose(f);

    dope_print_program(prog);

    // Should have read 8 instructions, stopped at S
    assert(prog->size == 8);

    assert(prog->instructions[0].opcode == DOPE_OP_SQR);

    // F and S should be included
    assert(prog->instructions[6].opcode == DOPE_OP_STOP);
    assert(prog->instructions[7].opcode == DOPE_OP_START);

    dope_free_program(prog);
    printf("PASS: dope_input_program\n\n");
}
