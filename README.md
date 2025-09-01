# The Dartmouth Oversimplified Programming Experiment (DOPE)
## A Historical Re-creation in C
Exploring the spirit and implementation of Dartmouth's precursor to BASIC as an interpreter written in C.

## Synopsis
The Dartmouth Oversimplified Programming Experiment (DOPE) was a pioneering programming language developed at Dartmouth College. Designed by Professor John G. Kemeny, its goal was radical for its time:

> "...to be used in an experiment to teach a large number of freshmen the rudiments of programming in a course of three one-hour lectures."

— *Teaching Notes - Dartmouth Oversimplified Programming Experiment, May 1962*

The DOPE compiler was written and tested by Sydney Marshall, a freshman research assistant, for the Dartmouth Computation Center's LGP-30 computer. Despite its simplicity, its ambition was vast:

> “It is a universal language. Any problem that the machine is capable of handling can be written in DOPE.”

— Teaching Notes, May 1962

Yet, DOPE was largely lost to history, overshadowed by its famous successor - BASIC. For decades, DOPE existed mostly in academic footnotes and a single, unpublished manuscript by Kemeny. Recently, thanks to the work of researchers like Sean Haas for VICE and the Advent of Computing Podcast, crucial documents have been unearthed. These offer a rare glimpse into this radically different approach to programming. A stepping stone that, while not successful on its own, was essential to the creation of BASIC.

I am grateful to the Rauner Special Collections Library for locating the Thomas Kurtz papers and providing copies of the original DOPE teaching notes, which made this project possible.

## Why Recreate DOPE?
Recreating DOPE is not an act of nostalgia; it is an act of understanding. It's about tracing the roots of accessible computing.

In the early 1960s, computing was undergoing a profound shift. The idea was forming in several minds that computers should not be tools for experts alone, but for everyone. This was the watershed moment of transition from an era where only trained programmers could use computers, toward a more egalitarian future.

DOPE was a seminal, if forgotten, step in that direction — a direction that would soon lead to one of the most liberating programming languages ever created: the Beginner's All-purpose Symbolic Instruction Code (BASIC).

## The Zeitgeist and The Machine: The LGP-30
To understand DOPE, we must understand the computing world of the late 1950s and early 1960s. Massive, room-sized computers were beginning to shrink, moving out of government and military labs and into universities and large businesses. They were now small enough to fit in the back of a truck.

One such machine, the LGP-30 (Librascope General Purpose), arrived at the Dartmouth Computation Center. For its time, it was a marvel of miniaturization and affordability—a "desk-sized" computer, though its 800-pound weight belied the name. This relatively compact and simple computer, powered by just 113 vacuum tubes, was the perfect catalyst for Professor Kemeny's ambition. It was on this specific machine, with its magnetic drum memory and typewriter-based input, that he launched his radical experiment to teach computing to non-programmers. The constraints of the LGP-30, its limited memory and processing power, directly shaped the design of the language created for it: a language that had to be oversimplified by necessity, yet powerful enough to be universal. This language was DOPE.

