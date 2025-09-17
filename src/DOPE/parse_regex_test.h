#ifndef PARSE_REGEX_TEST_H
#define PARSE_REGEX_TEST_H

#include "parse_regex.h"
#include <stdio.h>
#include <assert.h>

void test_regex_group1() {
    printf("TEST: regex  predictive group\n");
    // Test 1.1: Simple exact match
    assert(parse_regex("hello", "hello") == true);
    // Test 1.2: Match fails on wrong string
    assert(parse_regex("hello", "world") == false);
    // Test 2.1: Start anchor ^
    assert(parse_regex("^abc", "abc") == true);
    assert(parse_regex("^abc", "xabc") == false); // Should fail - not at start

    // Test 2.2: End anchor $
    assert(parse_regex("abc$", "abc") == true);
    assert(parse_regex("abc$", "abcx") == false); // Should fail - not at end

    // Test 2.3: Both anchors
    assert(parse_regex("^abc$", "abc") == true);  // Exact match
    assert(parse_regex("^abc$", "xabc") == false); // Not at start
    assert(parse_regex("^abc$", "abcx") == false); // Not at end
    // Test 3.1: Basic wildcard
    assert(parse_regex("a.c", "abc") == true);
    assert(parse_regex("a.c", "axc") == true);
    assert(parse_regex("a.c", "ac") == false);   // Too short - needs a char between
    assert(parse_regex("a.c", "abbc") == false); // Too long - . matches only one char

    // Test 3.2: Wildcard at start/end
    assert(parse_regex(".bc", "abc") == true);
    assert(parse_regex("ab.", "abc") == true);

    // Test 3.3: Multiple wildcards
    assert(parse_regex("a..c", "abxc") == true);
    assert(parse_regex("^a.b$", "axb"));
    // Test 4.1: Empty string behavior
    // These define your engine's specification:
    assert(parse_regex("", "") == true);   // Empty pattern matches empty string?
    assert(parse_regex("", "a") == false); // Empty pattern shouldn't match non-empty string
    assert(parse_regex("a", "") == false); // Non-empty pattern shouldn't match empty string

    // Test 4.2: Pattern longer than text
    assert(parse_regex("abc", "ab") == false);

    // Test 1: Basic Functionality - escaping a meta-character
    assert(parse_regex("\\.", ".") == true);   // Escape wildcard -> literal '.'
    assert(parse_regex("\\*", "*") == true);   // Escape quantifier -> literal '*'
    assert(parse_regex("\\^", "^") == true);   // Escape anchor -> literal '^'
    assert(parse_regex("\\$", "$") == true);   // Escape anchor -> literal '$'
    assert(parse_regex("\\\\", "\\") == true); // Escape itself -> literal '\'

    // Test 2: Escaping a normal character (should still work)
    assert(parse_regex("\\a", "a") == true); // Escape literal -> literal 'a'

    // Test 3: Non-matching escaped characters
    assert(parse_regex("\\.", "a") == false); // Escaped '.' should not match 'a'
    assert(parse_regex("\\a", "b") == false); // Escaped 'a' should not match 'b'

    // Test 4: Invalid escape at end of pattern
    assert(parse_regex("\\", "a") == false);   // Pattern ends with \ -> fail
    assert(parse_regex("abc\\", "abc") == false); // Pattern ends with \ -> fail

    // Test 5: Integration with other features
    assert(parse_regex("^\\.$", ".") == true);   // Exact match of a literal dot
    assert(parse_regex("^\\.$", "a") == false);  // Should not match
    assert(parse_regex("^a\\.b$", "a.b") == true); // Literal dot in the middle
    assert(parse_regex("^a\\.b$", "axb") == false); // Should not match wildcard

    // Test 6: Complex combination
    assert(parse_regex("^Hello\\, world!$", "Hello, world!") == true);
    assert(parse_regex("^Hello\\, world!$", "HelloX world!") == false);

    printf("PASS: predictive group\n\n");
}

#endif
/*
Test with Group 1 Patterns
Pattern: ^a.b$

Let's simulate the call match("^a.b$", "axb"):

regex_ptr points to '^', text_ptr points to 'a'.

Index = '^' (94) - 36 = 58. Handler handle_caret is called.

handle_caret: Checks text_ptr is at start ('a' != '\0') -> success. Advances regex_ptr to 'a'.

regex_ptr points to 'a', text_ptr points to 'a'.

'a' (97) - 36 = 61. 61 is outside table range (0-58) -> Use handle_literal.

handle_literal: Compares 'a' == 'a' -> success. Advances both ptrs. regex_ptr now at '.', text_ptr at 'x'.

regex_ptr points to '.', text_ptr points to 'x'.

Index = '.' (46) - 36 = 10. Handler handle_dot is called.

handle_dot: Checks text_ptr isn't '\0' -> success. Advances both ptrs. regex_ptr now at 'b', text_ptr at 'b'.

regex_ptr points to 'b', text_ptr points to 'b'.

'b' (98) - 36 = 62 -> Use handle_literal.

handle_literal: Compares 'b' == 'b' -> success. Advances both ptrs. regex_ptr now at '$', text_ptr at '\0'.

regex_ptr points to '$', text_ptr points to '\0'.

Index = '$' (36) - 36 = 0. Handler handle_dollar is called.

handle_dollar: Checks *text_ptr == '\0' -> success. Advances regex_ptr to '\0'.

regex_ptr is now '\0'. The while loop in match_here exits. Returns true.
*/
