#ifndef PARSE_REGEX_H
#define PARSE_REGEX_H

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

#endif
