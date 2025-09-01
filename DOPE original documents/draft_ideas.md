# DRAFT

## Motivation

Recreating DOPE isn’t an act of nostalgia. It’s an act of understanding — of tracing the roots of accessible computing. It's about understanding the foundational ideas of making computing accessible and the constraints under which early pioneers worked. It forces a confrontation with the simplicity that was possible when the goal was clarity over capability.

The motivation is not utility in the modern sense, but understanding. DOPE represents a pure distillation of Kemeny's goal: to make programming learnable in a few hours by non-specialists. Its constraints – the LGP-30's limited memory, the lack of advanced features, the single-character commands – shaped its design in a way that I found fascinating to dissect. 

## Archeology of our Digital Past

So, emulating DOPE is not just reconstructing a language, but recovering intent, context, and pedagogical spirit from the fragile, fragmented original sources that the Rauner Special Collections Library had preserved. Reading through the copies of those original teaching notes for this long-forgotten but seminal precursor to BASIC, I had to imagine how Professor Kemeny taught those freshmen for that single semester in 1962.

It must have taken days to produce a working program of a few lines and feed it the data to work on. We seldom use flowcharts these days, and even less often to painstakingly construct an algorithm before converting each step to code and then running it. We do not have to prepare separate hand-written sheets for the data inputs nor wait for a typewriter to clatter out the responses or, worse still, an error message!

Our developer experience now is more free-form, interacting in real time with our development environments. With Large Language Model (LLM) assistants baked into our editors, code completion, debuggers, and immediate compile-and-trial using Test-Driven Development (TDD), our pace and productivity are a world away from John Kemeny, Sydney Marshall, and their freshman class of '62.

## DOPE (Dartmouth Oversimplified Programming Experiment) Instruction Set

The following table presents the complete DOPE instruction set as recovered from the original 1962 Teaching Notes. Each instruction corresponds to a single box in a flowchart, making translation between diagram and code trivial.

| Instruction | Fields       | Description                                                  |
| ----------- | ------------ | ------------------------------------------------------------ |
| `+`         | A B C        | Add: `C ← A + B`                                             |
| `-`         | A B C        | Subtract: `C ← A - B`                                        |
| `.`         | A B C        | Multiply: `C ← A × B`                                        |
| `/`         | A B C        | Divide: `C ← A ÷ B`                                          |
| `;`         | A B          | Copy: `B ← A`                                                |
| `SQR`       | A B          | Square root: `B ← √A`                                        |
| `EXP`       | A B          | Exponential: `B ← eᴬ`                                        |
| `LOG`       | A B          | Natural logarithm: `B ← ln(A)`                               |
| `SIN`       | A B          | Sine (radians): `B ← sin(A)`                                 |
| `C`         | A B L1 L2 L3 | Compare A and B: < → L1, = → L2, > → L3                      |
| `T`         | L            | Unconditional jump to line L                                 |
| `A`         |              | Print the next label from the data stream                    |
| `P`         | A            | Print value of A (whole numbers printed as integers)         |
| `N`         |              | Output a new line                                            |
| `J`         | A            | Input: Read next value from data stream into A               |
| `Z`         | A B C        | Initialize loop: loop variable `A` from `B` to `C` (step 1.0) |
| `E`         |              | End of loop: increment `A` by 1.0; if `A > C`, exit loop; else, jump to line after `Z` |
| `F`         |              | Stop! — Halt execution (final step for single-data programs) |
| `S`         |              | Start computing — Must appear at the end of all programs; triggers execution |

Below is a brief explanation of each command, with example code. All examples assume the use of `#` for comments — a modern convenience not present in the original, but helpful for clarity. 

### Command Explanations

Although the commands are described to some degree in the original notes, I have included fresh examples to illustrate each command's usage and how to integrate data into DOPE programs.

#### `+ A B C` — Addition

Stores the sum of `A` and `B` in `C`.
```
1 ; 5 X        # X ← 5
2 ; 3 Y        # Y ← 3
3 + X Y Z      # Z ← X + Y = 8
4 P Z          # Print 8
5 F            # Stop
6 S            # Start computing
```

#### `- A B C` — Subtraction

Stores `A - B` in `C`.

```
1 ; 10 A       # A ← 10
2 ; 4 B        # B ← 4
3 - A B C      # C ← 10 - 4 = 6
4 P C          # Print 6
5 F
6 S
```

#### `. A B C` — Multiplication

Stores `A × B` in `C`.

```
1 ; 7 P        # P ← 7
2 ; 6 Q        # Q ← 6
3 . P Q R      # R ← 42
4 P R          # Print 42
5 F
6 S
```

#### `/ A B C` — Division

Stores `A ÷ B` in `C`. Uses floating-point arithmetic.

```
1 ; 1.0 A      # A ← 1.0
2 ; 3.0 B      # B ← 3.0
3 / A B C      # C ← 0.333...
4 P C          # Print 0.333
5 F
6 S
```

#### `; A B` — Copy

Copies the value of `A` to `B`.

```
1 ; 42 V       # V ← 42
2 ; V T        # T ← V
3 P T          # Print 42
4 F
5 S
```

#### `SQR A B` — Square Root

Stores `√A` in `B`. If `A < 0`, I am certain that an error would be generated but from the resources available to me there is no mention of DOPE's error handling.

```
1 ; 16.0 X     # X ← 16.0
2 SQR X Y      # Y ← 4.0
3 P Y          # Print 4
4 F
5 S
```

#### `EXP A B` — Exponential

Stores `eᴬ` in `B`.

```
1 ; 1.0 X      # X ← 1.0
2 EXP X Y      # Y ← e ≈ 2.718
3 P Y          # Print 2.718
4 F
5 S
```

#### `LOG A B` — Natural Logarithm

Stores `ln(A)` in `B`. If `A ≤ 0`, result undefined.

```
1 ; 2.718 E    # E ← e
2 LOG E X      # X ← 1.0
3 P X          # Print 1
4 F
5 S
```

#### `SIN A B` — Sine

The `SIN` function computes the sine of A, and stores it in B. This is assumed to be in radians — consistent with scientific practice of the era and the likely implementations of trigonometric functions in software on the LGP-30.

```
1 ; 1.5708 X   # π/2 ≈ 1.5708
2 SIN X Y      # Y ← sin(π/2) ≈ 1.0
3 P Y          # Print 1
4 F
5 S
```



#### `C A B L1 L2 L3` — Compare and Branch

Compares `A` and `B`, then jumps:

- To `L1` if `A < B`
- To `L2` if `A = B`
- To `L3` if `A > B`

```
1 ; 5 A        # A ← 5
2 ; 3 B        # B ← 3
3 C A B 6 5 4  # A > B → jump to 4
4 A            # Print label "Greater"
5 F            # Equal case
6 A            # Less case
7 S            # Start
```

*Data Sheet:*

```
"Greater"
"Equal"
"Less"
"FINISH"
```

#### `T L` — Unconditional Jump

Jumps to line `L`.

```
1 A            # Print "Start"
2 T 4          # Skip next line
3 A            # (Skipped) "Skipped"
4 A            # Print "End"
5 F
6 S
```

*Data Sheet:*

```
"Start"
"Skipped"
"End"
"FINISH"
```

#### `A` — Print Label

Prints the next label from the data stream.

```
1 A            # Print "Hello"
2 A            # Print "World"
3 F
4 S
```

*Data Sheet:*

```
"Hello"
"World"
"FINISH"
```

#### `P A` — Print Value

Prints the value of `A`. If it’s a whole number (e.g., `5.0`), it prints as `5`.

```
1 ; 3.1416 P1  # P1 ← 3.1416
2 ; 2.0 T1   	 # T1 ← 2.0
3 P P1         # Print 3.1416
4 P T1         # Print 2
5 F
6 S
```

#### `N` — New Line

Advances the output to the next line.

```
1 P 1.0        # Print on current line
2 P 2.0        # Still on same line
3 N            # New line
4 P 3.0        # Now on next line
5 F
6 S
```

#### `J A` — Input

Reads the next numeric value from the data stream into `A`.

```
1 J X          # Read +5.0 +00 → X ← 5.0
2 J Y          # Read +3.0 +00 → Y ← 3.0
3 + X Y Z      # Z ← 8.0
4 P Z          # Print 8
5 F
6 S
```

*Data Sheet:*

```
+5.0 +00
+3.0 +00
"FINISH"
```

#### `Z A B C` — Initialize Loop

Sets up a loop: variable `A` starts at `B`, runs to `C` (inclusive), step `1.0`.

```
1 Z I 1.0 3    # I = 1, 2, 3
2 ; I X        # X ← I
3 P X          # Print I
4 N            # New line
5 E            # End loop
6 F
7 S
```

*Output:*

```
1
2
3
```

#### `E` — End Loop

Marks the end of a loop. Increments the loop variable by `1.0`. If it exceeds the limit, exits; otherwise, jumps back to the line after `Z`.

See `Z` example above — `E` completes the loop.

#### `F` — Stop

Halts execution. Used at the end of single-run programs.

```
1 A            # Print "Done"
2 F            # Stop here
3 S
```

#### `S` — Start Computing

Must appear at the end of every program. Triggers execution after compilation.

This instruction is **not executed** in the normal flow — it signals the end of input and starts the run.

```
1 A            # Print label
2 F            # Stop
3 S            # ← Required: Start computing
```

### DOPE Programming & Data Sheets

According to the teaching notesprograms and data were written by hand on standardised forms, then typed into the LGP-30 via teletype. Each sheet served a distinct purpose and followed a strict layout.

#### 1. DOPE Programming Sheet

Used to write the program before input. Lines are numbered from `1` to `20`, with the last line always containing `S` in the instruction column.

                            DOPE SHEET
Programmer: __________   Problem: __________   Date: __________

| Instr. No. | Instr. | Field 1 | Field 2 | Field 3 | Field 4 | Field 5 |
| ---------- | ------ | ------- | ------- | ------- | ------- | ------- |
| 1          |        |         |         |         |         |         |
| 2          |        |         |         |         |         |         |
| 3          |        |         |         |         |         |         |
.
.
| 18         |        |         |         |         |         |         |
| 19         |        |         |         |         |         |         |
| LAST       | S      |         |         |         |         |         |

- Programs must begin at line `1` and increase consecutively.
- Only one instruction per line.
- The final line is labeled `LAST` and must contain `S` in the **Instr.** column.
- Fields 1–5 hold operands: variables, constants, or line numbers.
- This sheet holds up to 19 instructions + `S` but the maximum permitted length was 99 instructions.

#### 2. DOPE Data Sheet

Used to prepare input values and output labels. Data is read sequentially during execution.

                         DOPE DATA SHEET
Programmer: __________   Problem: __________   Date: __________

| Run No. | Variable | Magnitude (or label) | Exponent |
| ------- | -------- | -------------------- | -------- |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          |                      |          |
|         |          | FINISH               |          |

- Each row provides either a **value** (for `J A`) or a **label** (for `A`).
- The **Variable** column is for human reference only — the machine ignores it.
- Numeric entries include a **magnitude** (e.g., `+12.3`) and **exponent** (e.g., `+02`).
- Labels are plain text (e.g., `"Initial Run"`).
- `"FINISH"` marks the end of all data.
- Multiple runs are stacked sequentially.

### Example: Square Roots of Integers (1 to 100)

A complete DOPE program that computes and prints the square roots of integers from 1 to 100.

#### DOPE Programming Sheet (Filled)

                            DOPE SHEET
Programmer: J. Kemeny      Problem: Square Roots      Date: 1962-05-15

| Instr. No. | Instr. | Field 1 | Field 2 | Field 3 | Field 4 | Field 5 |
| ---------- | ------ | ------- | ------- | ------- | ------- | ------- |
| 1          | A      |         |         |         |         |         |
| 2          | Z      | A       | 1.0     | 100     |         |         |
| 3          | SQR    | A       | B       |         |         |         |
| 4          | P      | A       |         |         |         |         |
| 5          | P      | B       |         |         |         |         |
| 6          | N      |         |         |         |         |         |
| 7          | E      |         |         |         |         |         |
| 8          | F      |         |         |         |         |         |
| 9          | S      |         |         |         |         |         |
| 10         |        |         |         |         |         |         |
| 11         |        |         |         |         |         |         |
| 12         |        |         |         |         |         |         |
| 13         |        |         |         |         |         |         |
| 14         |        |         |         |         |         |         |
| 15         |        |         |         |         |         |         |
| 16         |        |         |         |         |         |         |
| 17         |        |         |         |         |         |         |
| 18         |        |         |         |         |         |         |
| 19         |        |         |         |         |         |         |
| LAST       | S      |         |         |         |         |         |

- Line 1: `A` → Print the first label from the data sheet.
- Line 2: `Z A 1.0 100` → Loop with `A` from 1.0 to 100 (step 1.0).
- Lines 3–6: Compute √A, print A and B, then new line.
- Line 7: `E` → End of loop; increment `A`, continue if ≤ 100.
- Line 8: `F` → Stop after one run.
- Line 9: `S` → Start computing (required).

#### DOPE Data Sheet (Filled)

                         DOPE DATA SHEET
Programmer: J. Kemeny      Problem: Square Roots      Date: 1962-05-15

| Run No. | Variable | Magnitude (or label) | Exponent |
| ------- | -------- | -------------------- | -------- |
| 1       |          | Square root table    |          |
|         |          | FINISH               |          |

- The first entry is a **label**: `"Square root table"` → printed by line 1 (`A`).
- There are no `J` instructions, so no numeric inputs are needed.
- `"FINISH"` indicates no further runs.
- Only one run is performed (ends with `F`).

### Expected Output

```
Square root table
1    1.000
2    1.414
3    1.732
...
100  10.0
```

> " (Formatted as 4 values per line on the Flexowriter; shown here line-by-line for clarity.) "

## DOPE Error Handling

The original DOPE system provided minimal feedback when programs contained errors. As noted by Kemeny and Kurtz in *Back to Basic* (1985), the error messages were “terse and unhelpful” — often limited to simple codes like `ERROR` or `STOP` with no indication of location or cause.

The original *Teaching Notes* make no mention of error diagnostics, suggesting that while errors were detected, the system offered little guidance. A student might see:

``` 
1 ERROR
```

… and then spend hours checking each line by hand.

This version of DOPE, however, offers rich, contextual error messages — not to break authenticity, but to honour DOPE’s true purpose, that of teaching programming.
