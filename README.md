# Dartmouth Oversimplified Programming Experiment (DOPE)
## A re-creation in C
Exploring the spirit and implementation of Dartmouth's precursor to BASIC as an interpreter written in C.

## Synopsis
The Dartmouth Oversimplified Programming Experiment (DOPE) was a programming language developed at Dartmouth College. It was designed by Professor John G. Kemeny:

> "...to be used in an experiment to teach a large number of freshmen the rudiments of programming in a course of three one-hour lectures."

_Teaching Notes - Dartmouth Oversimplified Programming Experiment, May 1962_

The DOPE compiler was written and tested by Sydney Marshall, a freshman research assistant at Dartmouth for the Dartmouth Computation Center's LGP-30 computer. 

DOPE has been largely lost to history, overshadowed by its famous successor, BASIC. For decades, details were scarce, existing mostly in academic footnotes and a single, unpublished manuscript by Kemeny. Recently, efforts like Sean Haas's work for VICE unearthed crucial documents, offering a rare glimpse into this "radically different approach to programming" that, while not successful in its own right, was the essential stepping stone to BASIC.

I am grateful to the Rauner Special Collections Library, for locating the Thomas Kurtz papers and photocopying the "Dartmouth Oversimplified Programming Experiment (DOPE)" teaching notes and providing them to me for this work.

## Motivation

Recreating DOPE, even in a simplified form, isn't about nostalgia. It's about understanding the foundational ideas of making computing accessible and the constraints under which early pioneers worked. It forces a confrontation with the simplicity that was possible when the goal was clarity over capability.

The motivation is not utility in the modern sense, but understanding. DOPE represents a pure distillation of Kemeny's goal: to make programming learnable in a few hours by non-specialists. Its constraints – the LGP-30's limited memory, the lack of advanced features, the single-character commands – shaped its design in a way that I found fascinating to dissect. 

## Archeology of our Digitial Past

So, emulating DOPE is not just reconstructing a language, but recovering intent, context, and pedagogical spirit from the fragile, fragmented orginal sources that the Rauner Special Collections Library had preserved. Reading through the copies of those original teaching notes for this long forgotten but seminal precursor to BASIC, I had to imagine how Professor Kemeny taught those freshmen for that single semester in 1962. 

It must have taken days to produce a working program of a few lines and feed it the data to work on. We seldom use flowcharts these days, and even less often to painstakingly construct an algorithm before converting each step to code and then running it. We do not have to prepare separate hand written sheets for the data inputs nor wait for a typewriter to clatter out the repsonses or, worse still, an error message! Our developer experience now is more free-form, interacting in real time with our development environments. With Large Language Model(LLM) assistants baked into our editors, code completion, debuggers and immediate compile and trial using Test Driven Development(TDD), our pace and producitivity are a world away from John Kemeny, Sydney Marshall and their freshman class of '62.

## DOPE Instructions 

