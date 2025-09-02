# The Dartmouth Oversimplified Programming Experiment (DOPE)
## A Historical Re-creation in C
Exploring the spirit and implementation of Dartmouth's precursor to BASIC as an interpreter written in C.

+ [Transcription of the Original DOPE Teaching Notes (PDF)](https://github.com/cspjst/DOPE/blob/main/DOPE%20Teaching%20Notes.pdf)

+ The DOPE Language: A Technical Overview (coming soon)

## Synopsis
The Dartmouth Oversimplified Programming Experiment (DOPE) was a pioneering programming language developed at Dartmouth College. Designed by Professor John G. Kemeny, its goal was radical for its time:

> "...to be used in an experiment to teach a large number of freshmen the rudiments of programming in a course of three one-hour lectures."

— *Teaching Notes - Dartmouth Oversimplified Programming Experiment, May 1962*

The DOPE compiler was written and tested by Sydney Marshall, a freshman research assistant, for the Dartmouth Computation Center's LGP-30 computer. Despite its simplicity, its ambition was vast:

> “It is a universal language. Any problem that the machine is capable of handling can be written in DOPE.”

— *Teaching Notes - Dartmouth Oversimplified Programming Experiment, May 1962*

Yet, DOPE was largely lost to history, overshadowed by its famous successor - BASIC. For decades, DOPE existed mostly in academic footnotes and a single, unpublished manuscript by Kemeny. Recently, thanks to the work of researchers like Sean Haas for VICE and the Advent of Computing Podcast, crucial documents have been unearthed. These offer a rare glimpse into this radically different approach to programming. A stepping stone that, while not successful on its own, was essential to the creation of BASIC.

I am grateful to the Rauner Special Collections Library for locating the Thomas Kurtz papers and providing copies of the original DOPE teaching notes, which made this project possible.

## Why Recreate DOPE?
Recreating DOPE is not an act of nostalgia; it is an act of understanding. It's about tracing the roots of accessible computing.

In the early 1960s, computing was undergoing a profound shift. The idea was forming in several minds that computers should not be tools for experts alone, but for everyone. This was the watershed moment of transition from an era where only trained programmers could use computers, toward a more egalitarian future.

DOPE was a seminal, if forgotten, step in that direction — a direction that would soon lead to one of the most liberating programming languages ever created: the Beginner's All-purpose Symbolic Instruction Code (BASIC).

## The Zeitgeist and The Machine: The LGP-30
To understand DOPE, we must understand the computing world of the late 1950s and early 1960s. Massive, room-sized computers were beginning to shrink, moving out of government and military labs and into universities and large businesses. They were now small enough to fit in the back of a truck.

One such machine, the LGP-30 (Librascope General Purpose), arrived at the Dartmouth Computation Center. For its time, it was a marvel of miniaturization and affordability—a "desk-sized" computer, though its 800-pound weight belied the name. This relatively compact and simple computer, powered by just 113 vacuum tubes, was the perfect catalyst for Professor Kemeny's ambition. It was on this specific machine, with its magnetic drum memory and typewriter-based input, that he launched his radical experiment to teach computing to non-programmers. The constraints of the LGP-30, its limited memory and processing power, directly shaped the design of the language created for it: a language that had to be oversimplified by necessity, yet powerful enough to be universal. This language was DOPE.

## Programming with DOPE: A Three-Stage Journey
The DOPE teaching experiment was conducted over a single semester in 1962 and was, in large part, a meticulous paper exercise. This was not a course in typing or machine operation, but, rather, a course in computational thinking. The process was broken up into three distinct stages, each designed to separate the logic of programming from the mechanics of the machine.

### Stage 1: Visual Thinking with Flowcharts
Before a single line of code was written, students were taught to reason about a problem visually. They would map out the entire logic of their program using flowcharts. This step forced them to think about the sequence of operations, decisions, and loops in a language-agnostic way, establishing the fundamental algorithm before confronting the syntax of DOPE.

### Stage 2: The Paper Program - Converting Logic to Code
Once the flowchart was complete, students began the precise work of translating their visual logic into a machine-readable DOPE program — by hand. They used pre-printed, forms, the "DOPE sheet" for the DOPE program itself and the "DOPE DATA sheet" for the data. Both were structured in a way that aided clarity and consistency. 

This paper stage was where the thinking happened. The machine was an abstract concept; the programmer's battle was with their formulation of the problem into a flowchart and then converting each flowchart step into its corresponding DOPE instruction and the data it would work on - all done with pencil and paper.

#### The Program Sheet: 
This form was used to write the code itself. Each line corresponded to one instruction, meticulously filled into columns.

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

Rules were strict:

Programs must begin at line 1 and increase consecutively.

Only one instruction per line.

The final line, labeled LAST, must contain the stop instruction S.

Fields 1–5 held the operands: variables, constants, or line numbers (for loop and jump instructions).

#### The Data Sheet: 
A separate form was used to prepare all the input values and output labels the program would use, to be read sequentially during execution.

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
                            

Each row provided either a numeric value or a text label.

Numeric entries had to be specified with a magnitude (e.g., +12.3) and an exponent (e.g., +02).

"FINISH" marked the absolute end of all data.



### Stage 3: The Machine - Teletypes, Tapes, and Terse Errors
The final stage was the transition from the abstract to the physical—a process, the man-machine interface itself. The carefully handwritten forms were now transcribed onto a teletype machine to create a paper tape - an interaction likley fraught with error and  frustration. 

#### Program Entry: 
The rules for typing were exacting. As per the teaching notes:

> "Do not type instruction number. Type only instruction followed by 0 to 5 fields, each followed by ' (a single quote was the stop code). Do not leave any spaces. Type one instruction per line. Remember to type s' at the end of the program."

For example, a program was typed as a continuous stream like:
```
        a'
        z'a'1.0'100'
        sqr'a'b'
        p'a'
        p'b'
        n'
        e'
        f'
        s'
```
#### Data Entry: 
Data had even more complex rules, a fascinating glimpse into the extreme constraints of the era:

> "For data you must type two numbers of up to 5 characters each, followed by stop-codes... The exponent must have three characters consisting of sign and two digits."

A value like 5.297 x 10¹⁰ was painstakingly typed as `5.297'+10'`.

#### Compilation and Execution: 
Finally, the user would load the "DOPE COMPILER" tape via the photoelectric reader, then feed their newly created program/data tape into the typewriter reader. A specific sequence of button presses on the LGP-30's console would set the compilation in motion.

The moment of truth was often harsh. Error reporting was primitive and cryptic. The machine might simply stop and print:

`+.` for a floating-point exponent overflow.

`e` for too many characters in a data field.

`log` for an attempt to take a negative logarithm.

This frustration was a direct lesson in the machine's unforgiving literalness. A misplaced stop code or a single typo meant a failed run. It was this very frustration, experienced by Kemeny and Kurtz's students, that would directly lead to a core design principle of its famous successor, BASIC: clear, informative error messages that helped the learner understand what they did wrong, rather than simply telling them they had failed.

### Legacy: The Blueprint for BASIC
The DOPE experiment concluded after that single semester. The language itself was slow, burdened by the mechanical process of the drum compiler, and never intended for widespread use. In the short term, it was not a success.

But its true value was as a prototype—a "proof of concept" for a radically new approach. The frustrations experienced by those first students—the cryptic errors, the complex data entry—were not in vain. They provided the crucial, real-world feedback that shaped the next iteration.

As Thomas Kurtz, co-inventor of BASIC, later reflected:

> “Though not a success in itself, DOPE presaged BASIC.”

The lessons learned from DOPE were direct and practical. Kemeny and Kurtz saw that true accessibility required clear error messages, interactive editing, and instant feedback. More than that, DOPE provided the foundational ideas that evolved into BASIC:

Simple Variables: Variable names were a single letter or a letter followed by a digit.

Easy Arrays: Arrays (vectors) did not need to be declared and had a default size.

The FOR-Loop: The primary loop construct was a straightforward FOR loop.

Line Numbers: Every line required a numeric label, which also served as the target for jumps and GOTO statements—a major simplification over the labels in Fortran or Algol.

DOPE was the rough draft. It proved that a language could be both simple for beginners and powerful enough to be universal. Within a year, its core ideas would be refined, stripped of their clunky paper-tape mechanics, and reborn on a revolutionary time-sharing system. The result was the Beginner's All-purpose Symbolic Instruction Code (BASIC), a language that would open up computing to millions and change the world.

## Explore DOPE Further
The story doesn't end here. The DOPE interpreter lives on in this repository. You can move from reading about history to actively participating in it.

### Run DOPE Yourself: 
The core of this project is a faithful re-creation of the DOPE interpreter written in C. You can clone this repository, compile the code, and run original DOPE programs from the command line, just as you would have in 1962 (minus the paper tape!).

git clone https://github.com/cspjst/DOPE.git

cd DOPE/src

cmake

### Learn the Language: 
If you're curious about the technical details and instructions that make up the DOPE language, read the full overview:

The DOPE Language: A Technical Overview

### See the Original Source: 
For the truly adventurous, you can explore the original teaching notes that made this accurate re-creation possible:

[Transcription of the Original DOPE Teaching Notes (PDF)](https://github.com/cspjst/DOPE/blob/main/DOPE%20Teaching%20Notes.pdf)

The repository includes several example programs and their corresponding data sheets. Feel free to run them, modify them, or try writing your own simple DOPE program based on the rules in the overview. It's the best way to appreciate both the simplicity and the constraints of this pioneering language.

