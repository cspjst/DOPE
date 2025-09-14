#ifndef DOPE_INTERPRET_H
#define DOPE_INTERPRET_H

typedef void (*opcode_func_t)(dope_program_t*, dope_data_t*);

opcode_func_t dispatch_table[DOPE_INSTRUCTION_COUNT + 1] = {
    [DOPE_OP_ADD] = exec_add,
    [DOPE_OP_SQR] = exec_sqr,
    [DOPE_OP_J]  = exec_j,
    // ...
};

void dope_interpret(dope_program_t* program, dope_data_t* data) {
  for (program->ip = 0; program->ip < program->size; program->ip++) {
      dope_instruction_t* inst = &program->instructions[program->ip];

      opcode_func_t fn = dispatch_table[inst->opcode];
      if (fn) {
          fn(program, data);
      } else {
          dope_panic("unimplemented opcode %d"
      }
  }
}

#endif
