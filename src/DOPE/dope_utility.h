#ifndef DOPE_UTILITY_H
#define DOPE_UTILITY_H

#include "dope_types.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Check if a line was truncated during input.
 * @param line Pointer to line buffer
 * @return true if buffer full and no newline, false otherwise
 * @details
 * Used to detect lines longer than DOPE_LINE_SIZE. Relies on
 * fgets not including \n when buffer fills.
 */
bool dope_is_truncated(dope_line_t* line);

/**
 * @brief Consume remaining characters in current logical line.
 * @param istream Input stream
 * @details
 * Reads and discards input until '\n' or EOF. Call after
 * dope_is_truncated() returns true to keep stream synchronized.
 */
void dope_consume_remaining(FILE* istream);

void dope_string_toupper(char* str);

/**
 * @brief Read a line from stream into buffer.
 * @param line Target buffer
 * @param istream Input stream
 * @return Length of line after stripping \r\n, or 0 on EOF/error
 * @details
 * Uses fgets, then removes trailing \r and \n. Returns raw length
 * before any further processing. May return full buffer length
 * without \n if line was truncated.
 */
dope_size_t dope_read_line(dope_line_t* line, FILE* istream);

/**
 * @brief Check if a string contains any whitespace characters.
 * @param str Null-terminated input string (may be NULL)
 * @return true if any whitespace is found, false otherwise
 *
 * @details
 * This function is used to enforce DOPE's strict input format, which
 * requires that instructions be entered without spaces, tabs, or other
 * whitespace. Each field must be followed by a stop code (') and fields
 * must be contiguous.
 *
 * According to the original "Dartmouth Oversimplified Programming Experiment"
 * teaching notes (May 1962), page 13:
 *
 *   "Do not leave any spaces. Type one instruction per line."
 */
bool dope_has_space(const char* str);

#endif
