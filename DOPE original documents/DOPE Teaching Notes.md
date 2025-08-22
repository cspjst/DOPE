DARTMOUTH
OVERSIMPLIFIED
PROGRAMMING
EXPERIMENT

Dartmouth Computation Center
may 1962

Page 1.

Preface
The Dartmouth Oversimplified Programming Experiment (to be referred to by its initials) was designed for a dual purpose. It will first of all be used in an experiment designed to teach a large number of freshmen the rudiments of programming in a course of three one-hour lectures. For this experiment DOPE provides a fast and efficient method of running programs written by the students. It is also hoped that DOPE will prove sufficiently convenient to serve for programming of simple research problems.

The language of DOPE was designed by Professor John G. Kemeny, with the following principles in mind: (1) It is a universal language. That is, any problem that the machine is capable of handling can be written in DOPE. (2) Each instruction in DOPE corresponds to a box in a flow-diagram. Hence it is trivial to translate a flow-diagram into a DOPE program. (3) The language is so designed that it can be quickly translated into machine language, and hence the usual lengthy compiling time is avoided when the program is actually run. To achieve these goals, some flexibility had to be sacrificed. However, the rigidity of the language actually makes it easier to teach to the novice.

A programming language is useful only if it can be translated into machine language. The compiler (translator) for DOPE compiles any program for the LGP-30 almost as fast as the flexo-writer can read it. One minute is a typical compiling time. If the DOPE program and its data have been pre-punched on a tape, the machine will immediately after compiling start its computation, and will run the problem for as many sets of data as have been provided. The running time of a program is roughly found by allowing one minute for 200 arithmetical operations.

The DOPE compiler was written and tested by Sidney Marshall '65, a freshman research assistant at Dartmouth.

Page 2. 

Flow diagrams.
A flow-diagram is a simple device for stating precisely a set of computational rules. Four types of components occur in a flow-diagram: Arithmetical, comparison, loop, and input-output. In addition, there are arrows to show the order of instructions.

Arithmetical boxes.

Each such box contains the order for one arithmetical operation. For example:

[ X + Y → Z ] Compute X + Y and call the result Z

[ Z / Y → W₃ ] Divide Z by Y and call the result W₃

[ SIN(X₅) → X₅ ] Compute the sin of X₅ and call the result X₅

[ X → Y ] Let Y equal X.

An arithmetical order is indicated by enclosing it in a rectangular box.

Comparison.

A comparison is of the form: Compare X₂ with Y. The comparison results in one of three decisions: X₂ > Y, X₂ = Y, or X₂ < Y. The comparison is placed inside a circle, and it has three arrows coming out of the circle, corresponding to the three possible results. For example, in the following diagram we compute Z = |X - Y|:

Page 3.

Loop.
A loop is a very powerful device. It serves to carry out a sequence of orders repeatedly, for varying values of an index or a parameter. The key order of a loop is enclosed in a diamond:

One enters the diamond on top. It then sets I = 3, and proceeds to whatever instructions are to be carried out in the loop. When the diamond is reentered (from the left) the value of I is increased by 1, and the loop-instructions are repeated. When the instructions have been carried out for I=10, then the loop is 'exited' to the instruction on its right.

For example, the diagram below computes Z = 2 · 3⁸ + 5:

Page 4.

As another example, let Z = 5 + 6 + 7 + … + 82 + 83:

Input and output.

Most programs have small variable data. That is, some quantities may change from one run of the problem to another. For example, if one writes a program to compute a power of 2, one might as well compute 2^N, where N is to be specified as data. For this we need an input order. We also need a print order to have the flexowriter type an answer. These orders are indicated in dotted boxes, and usually occur at the beginning and the end of the program, respectively.

Consider the following example:

