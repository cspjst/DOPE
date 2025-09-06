#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dope_constants.h"
#include "dope_errors.h"
#include "dope_utility.h"
#include "dope_program.h"

// Nullius in verba testa omnia

void test_dope_is_truncated() {
    dope_line_t buf;

    // Case 1: NULL → false
    assert(!dope_is_truncated(NULL));

    // Case 2: empty string
    buf[0] = '\0';
    assert(!dope_is_truncated(&buf));

    // Case 3: short line with \n
    strcpy(buf, "X\n");
    assert(!dope_is_truncated(&buf));

    // Case 4: full buffer with \n → fits exactly → not truncated
    memset(buf, 'A', DOPE_LINE_SIZE - 2);
    buf[DOPE_LINE_SIZE - 2] = '\n';
    buf[DOPE_LINE_SIZE - 1] = '\0';
    assert(!dope_is_truncated(&buf));

    // Case 5: full buffer, no \n → truncated
    buf[DOPE_LINE_SIZE - 2] = 'B';  // overwrite \n
    buf[DOPE_LINE_SIZE - 1] = '\0'; // still full, but no newline
    assert(dope_is_truncated(&buf));

    // Case 6: one char short, no \n → not full → not truncated
    buf[DOPE_LINE_SIZE - 2] = '\0'; // now len = DOPE_LINE_SIZE - 2
    assert(!dope_is_truncated(&buf));

    printf("dope_is_truncated: all tests passed\n");
}

void test_dope_consume_remaining_manual(FILE* istream) {
    printf("Testing dope_consume_remaining\n");
    printf("Enter a VERY long line (more than %d chars):\n", DOPE_LINE_SIZE);

    dope_line_t line;
    if (fgets(line, DOPE_LINE_SIZE, istream) == NULL) {
        printf("Error reading input.\n");
        return;
    }

    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        printf("Line was short: '%s'\n", line);
    } else {
        printf("Line was truncated — consuming rest...\n");
        dope_consume_remaining(istream);
        printf("...done. Stream is now synchronized.\n");
    }

    // Now try to read the next line
    printf("Now enter a second line:\n");
    if (fgets(line, DOPE_LINE_SIZE, istream)) {
        line[strcspn(line, "\n")] = '\0';
        printf("Second line: '%s'\n", line);
    } else {
        printf("Failed to read second line.\n");
    }

    printf("dope_consume_remaining: manual test complete\n");
}

void test_dope_read_line() {
    // Create test input file
    FILE* f = fopen("test_input.txt", "w");
    assert(f != NULL);

    fprintf(f, "short\n");
    fprintf(f, "this_is_a_very_long_line_exceeding_DOPE_LINE_SIZE_by_far\n");
    fprintf(f, "another\n");
    fprintf(f, "");  // empty line (simulate EOF)
    fclose(f);

    // Reopen for reading
    f = fopen("test_input.txt", "r");
    assert(f != NULL);

    dope_line_t line;

    // Test 1: Normal line with \n
    size_t len = dope_read_line(&line, f);
    assert(len == 5);  // "short" -> 5 chars
    assert(strcmp(line, "short") == 0);

    // Test 2: long line → should be truncated
    len = dope_read_line(&line, f);
    assert(strncmp(line, "this_is_a_", 10) == 0);
    assert(len == DOPE_LINE_SIZE - 1);  // full buffer
    // Check if it's truncated: no \n at end
    if (line[len - 1] != '\n' && len == DOPE_LINE_SIZE - 1) {
        // Consume the rest of the line
        dope_consume_remaining(f);
    }

    // Test 3: Next line after truncation — should be clean
    len = dope_read_line(&line, f);
    assert(len == 7);  // "another"
    assert(strcmp(line, "another") == 0);

    // Test 4: EOF
    len = dope_read_line(&line, f);
    assert(len == 0);  // EOF → returns 0
    assert(line[0] == '\0');  // buffer cleared

    // Test 5: NULL pointer handling
    len = dope_read_line(NULL, f);
    assert(len == 0);

    fclose(f);
    printf("dope_read_line: all tests passed\n");
}

void test_dope_instruction_tokenize() {
    dope_instruction_record_t tokens;
    dope_line_t line;

    // Case 1: NULL line
    assert(dope_instruction_tokenize(NULL, tokens) == 0);

    // Case 2: NULL tokens
    assert(dope_instruction_tokenize(&line, NULL) == 0);

    // Case 3: empty line
    strcpy(line, "");
    assert(dope_instruction_tokenize(&line, tokens) == 0);

    // Case 4: single token
    strcpy(line, "SQR");
    assert(dope_instruction_tokenize(&line, tokens) == 1);
    assert(strcmp(tokens[0], "SQR") == 0);

    // Case 5: multiple tokens
    strcpy(line, "SQR X Y");
    assert(dope_instruction_tokenize(&line, tokens) == 3);
    assert(strcmp(tokens[0], "SQR") == 0);
    assert(strcmp(tokens[1], "X") == 0);
    assert(strcmp(tokens[2], "Y") == 0);

    // Case 6: whitespace variations
    strcpy(line, "  +\t\tA   B \r C");
    assert(dope_instruction_tokenize(&line, tokens) == 4);
    assert(strcmp(tokens[0], "+") == 0);
    assert(strcmp(tokens[1], "A") == 0);
    assert(strcmp(tokens[2], "B") == 0);
    assert(strcmp(tokens[3], "C") == 0);

    // Case 7: max tokens (6)
    strcpy(line, "1 2 3 4 5 6");
    assert(dope_instruction_tokenize(&line, tokens) == 6);
    for (int i = 0; i < 6; i++) {
        char expected[2];
        expected[0] = '1' + i;
        expected[1] = '\0';
        assert(strcmp(tokens[i], expected) == 0);
    }

    // Case 8: overlong token (clamped)
    strcpy(line, "TOOLONGVALUE X");
    size_t count = dope_instruction_tokenize(&line, tokens);
    assert(count == 2);
    assert(strlen(tokens[0]) == DOPE_FIELD_SIZE - 1);  // clamped
    assert(tokens[0][DOPE_FIELD_SIZE - 1] == '\0');     // null-terminated

    // Verify it starts with "TOOLONGVAL" (if DOPE_FIELD_SIZE == 10)
    char expected_clamped[DOPE_FIELD_SIZE];
    memset(expected_clamped, 'T', DOPE_FIELD_SIZE - 1);
    expected_clamped[0] = 'T'; expected_clamped[1] = 'O'; expected_clamped[2] = 'O';
    expected_clamped[3] = 'L'; expected_clamped[4] = 'O'; expected_clamped[5] = 'N';
    expected_clamped[6] = 'G'; expected_clamped[7] = 'V'; expected_clamped[8] = 'A';
    expected_clamped[9] = '\0';
    // Adjust based on actual long token
    strncpy(expected_clamped, "TOOLONGV", 8);  // first 8 chars
    expected_clamped[8] = 'A';  // 9th
    expected_clamped[9] = '\0';
    // Just check prefix
    assert(strncmp(tokens[0], "TOOLONGV", 8) == 0);

    printf("test_dope_instruction_tokenize: all tests passed\n");
}

void test_dope_lookup_opcode() {
    // Case 1: NULL pointer
    assert(dope_lookup_opcode(NULL) == 0);

    // Case 2: empty string
    assert(dope_lookup_opcode("") == 0);

    // Case 3: whitespace string (not trimmed, so invalid)
    assert(dope_lookup_opcode(" ") == 0);
    assert(dope_lookup_opcode("\t") == 0);

    // Case 4: valid opcodes — test all 19
    assert(dope_lookup_opcode("+") == 1);
    assert(dope_lookup_opcode("-") == 2);
    assert(dope_lookup_opcode(".") == 3);
    assert(dope_lookup_opcode("/") == 4);
    assert(dope_lookup_opcode(";") == 5);
    assert(dope_lookup_opcode("SQR") == 6);
    assert(dope_lookup_opcode("EXP") == 7);
    assert(dope_lookup_opcode("LOG") == 8);
    assert(dope_lookup_opcode("SIN") == 9);
    assert(dope_lookup_opcode("C") == 10);
    assert(dope_lookup_opcode("T") == 11);
    assert(dope_lookup_opcode("A") == 12);
    assert(dope_lookup_opcode("P") == 13);
    assert(dope_lookup_opcode("N") == 14);
    assert(dope_lookup_opcode("J") == 15);
    assert(dope_lookup_opcode("Z") == 16);
    assert(dope_lookup_opcode("E") == 17);
    assert(dope_lookup_opcode("F") == 18);
    assert(dope_lookup_opcode("S") == 19);

    // Case 5: unknown instruction
    assert(dope_lookup_opcode("X") == 0);
    assert(dope_lookup_opcode("FOO0") == 0);
    assert(dope_lookup_opcode("123jjjjjjjjjjjjjjjjjjjj") == 0);

    // Case 6: case-sensitive? (assumed yes)
    assert(dope_lookup_opcode("sqr") == 0);
    assert(dope_lookup_opcode("Sqr") == 0);
    assert(dope_lookup_opcode("sQR") == 0);

    // Case 7: partial match
    assert(dope_lookup_opcode("SQ") == 0);
    assert(dope_lookup_opcode("S") == 19);  // but "S" is valid
    assert(dope_lookup_opcode("Z") == 16);  // "Z" is valid
    assert(dope_lookup_opcode("ZZ") == 0);

    printf("test_dope_lookup_opcode: all tests passed\n");
}

void test_dope_input_instruction() {
    // Create test input file
    FILE* f = fopen("test_input.txt", "w");
    assert(f != NULL);

    fprintf(f, "SQR'X'Y'\n");                     // valid
    fprintf(f, "this_line_is_way_too_long_exceeding_DOPE_LINE_SIZE'\n");  // truncated
    fprintf(f, "+'A'B'C'\n");                     // valid, 3 operands
    fprintf(f, "J'Z'\n");                         // valid, 1 operand white space accounted for
    fprintf(f, "J'Z'15'\n");                      // invalid, too many operands
    fprintf(f, "FOO'\n");                         // unknown instruction
    fprintf(f, "'\n");                         // empty line
    fprintf(f, "E'\n");                           // valid, no operands
    fprintf(f, "P'X'\n");                         // valid, 1 operand
    fprintf(f, "P'\n");                           // too few args
    fprintf(f, "Z'X'Y'Z'A'\n");                   // too many args (Z takes 3, this is 3? check DOPE_FEILDS)
    fprintf(f, "+'A B'C'\n");                     // space found
    fprintf(f, "+'a'b'c'\n");                     // valid, toupper
    fprintf(f, "s\n");
    fclose(f);

    f = fopen("test_input.txt", "r");
    assert(f != NULL);

    dope_instruction_t inst;

    printf("Test 1: Valid instruction\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_SQR);
    assert(inst.error_code == DOPE_ERR_SUCCESS);
    assert(strcmp(inst.fields[0], "SQR") == 0);
    assert(strcmp(inst.fields[1], "X") == 0);
    assert(strcmp(inst.fields[2], "Y") == 0);

    printf("Test 2: Truncated line\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_LINE_TOO_LONG);

    printf("Test 3: Next line after truncation should be clean\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_ADD);
    assert(strcmp(inst.fields[0], "+") == 0);
    assert(strcmp(inst.fields[1], "A") == 0);

    printf("Test 4: Another valid\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INPUT);
    assert(strcmp(inst.fields[0], "J") == 0);

    printf("Test 4.1: too many operands\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_MANY_ARGS);

    printf("Test 5: Unknown instruction\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_UNKNOWN_INSTR);
    assert(strcmp(inst.fields[0], "FOO") == 0);  // preserved for error reporting

    printf("Test 6: Empty line\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_NO_INSTR);

    printf("Test 7: Valid: E (opcode 17, 0 operands)\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_END);
    assert(inst.error_code == DOPE_ERR_SUCCESS);

    printf("Test 8: Valid: P (opcode 13, 1 operand)\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_PRINT);
    assert(strcmp(inst.fields[1], "X") == 0);

    printf("Test 9: Too few args: P requires 1, got 0\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_FEW_ARGS);
    assert(strcmp(inst.fields[0], "P") == 0);

    printf("Test 10: Z takes 3 operands, so \"Z X Y Z A\" is 4 too many\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_TOO_MANY_ARGS);
    assert(strcmp(inst.fields[0], "Z") == 0);

    printf("Test 11: space found\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_INVALID);
    assert(inst.error_code == DOPE_ERR_INVALID_CHAR);

    printf("Test 12: valid after toupper\t");
    dope_input_instruction(&inst, f);
    dope_print_instruction(&inst);
    assert(inst.opcode == DOPE_OP_ADD);
    assert(strcmp(inst.fields[0], "+") == 0);
    assert(strcmp(inst.fields[1], "A") == 0);

    fclose(f);
    printf("test_dope_input_instruction: all tests passed\n");
}

void test_dope_input_program() {
    FILE* f = fopen("test_input.txt", "r");
    assert(f != NULL);

    dope_program_t* prog = dope_new_program(15);

    dope_input_program(prog, f);
    getchar();
    dope_print_program(prog);

    fclose(f);
    dope_free_program(prog);

    printf("test_dope_input_program: all tests passed\n");
}
