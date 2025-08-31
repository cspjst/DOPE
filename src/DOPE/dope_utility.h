#ifndef DOPE_UTILITY_H
#define DOPE_UTILITY_H

#include "dope_types.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Compute 10 raised to an integer power, accurately for DOPE format.
 * @param exp Integer exponent, must be in range [-36, +36]
 * @return 10^exp as a float, or 0.0f if exponent out of range
 *
 * @details
 * This function is used to scale magnitude values by powers of 10 during
 * data input in the DOPE interpreter. It avoids the inaccuracies of the
 * standard pow(10.0, exp) function, which uses transcendental math
 * (log/exp) and can introduce floating-point errors even for integer powers.
 *
 * For example:
 *   pow(10.0, 2) may return 99.999999 or 100.000001 due to rounding,
 *   leading to incorrect results like 12.36 * 99.999999 = 1235.999988.
 *
 * This function instead uses iterative multiplication or division by 10.0f,
 * which is exact within the precision of IEEE 754 single-precision float
 * for exponents in the range [-36, +36], as required by the DOPE specification.
 *
 * According to the original "Dartmouth Oversimplified Programming Experiment"
 * teaching notes (May 1962), exponents must lie between -36 and +36:
 * > "The exponent must have three characters consisting of sign and two digits.
 * > The exponent indicates a power of 10, and must lie between -36 and +36."
 *
 * This implementation ensures that input such as:
 *   +12.36 +02
 * is correctly interpreted as 12.36 × 10² = 1236.0, without floating-point drift.
 */
float power_of_10(int exp);

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

/*

cmake_minimum_required(VERSION 3.10)

# Warning: This skips critical compiler checks. Only use this if Watcom fails CMake's detection
# Necessary to suppress compiler checks for cross compilation using OW2 and C under ARM environments
set(CMAKE_C_COMPILER_WORKS 1)

project(
    TUI
    VERSION 0.1.0
    LANGUAGES C
)

# Toolchain setup
set(CMAKE_SYSTEM_NAME DOS)      # Target DOS
set(CMAKE_C_COMPILER wcl)
set(CMAKE_CXX_COMPILER wcl)
set(CMAKE_LINKER wlink)         # Use Watcom's linker
set(CMAKE_EXECUTABLE_SUFFIX ".exe")


# watcom compiler options
# https://users.pja.edu.pl/~jms/qnx/help/watcom/compiler-tools/cpopts.html
if(WATCOM)
add_compile_options(
    -0                  # Generate 8086/8088 instructions ONLY (no 286+)
    -e1                 # Minimal stack checking (saves bytes for 64KB segments)
    -za99               # undocumented switch enable partial C99 compatibility
    -ml                 # memory model options - large model
    -bt=dos             # Target DOS
    -l=dos              # DOS library
    -fpi                # Enable fp (required for powf etc)
    -od                 # Disable optimizations (prevents 286+ instruction sneaking in)
    -w1                 # Mild warnings (avoid /w3 due to 8086 quirks)
    -zq                 # Quiet mode (cleaner output)
    #-dNDEBUG
)
add_definitions(
    -D__DOS__
    -D__8086__  # Explicit 8086 target
  )
endif()

# WARNING: Using GLOB for convenience. If adding new files, rerun:
#   ./cmk.sh
file(GLOB SOURCES
    CONFIGURE_DEPENDS
    *.c
    DOPE/*.c
)

# message(Source list="${SOURCES}")

add_executable(DOPE ${SOURCES})

# Optional: Install target
# rename me...
#install(TARGETS example DESTINATION bin)


 */
