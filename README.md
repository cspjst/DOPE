# Dartmouth Oversimplified Programming Experiment (DOPE)
## A Recreation in C
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

Why implement a language that was deemed "too primitive to be useful" by its own creator, surviving only a single semester?

The motivation is not utility in the modern sense, but understanding. DOPE represents a pure distillation of Kemeny's goal: to make programming learnable in a few hours by non-specialists. Its constraints – the LGP-30's limited memory, the lack of advanced features, the single-character commands – shaped its design in a way that I found fascinating to dissect.

Implementing DOPE in C99 was an exercise in minimalism. Could I simulate the unique experience of programming on an LGP-30 with its drum memory and lack of hardware floating-point support?

The answer, embodied in the code in this repository, was a surprisingly functional, if extremely quirky, recreation. It is not a practical tool, but it's a tangible way to engage with a pivotal moment in programming history.

## DOPE Instructions 
