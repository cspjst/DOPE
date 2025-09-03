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

vartab

typedef struct {
    char name[2];        // "A", "X", etc.
    float value;
} dope_var_t;

dope_var_t vartab[DOPE_VAR_CAPACITY];  // e.g., 26 variables
int vartab_count = 0;

float* dope_find_var(const char* name);
float* dope_alloc_var(const char* name);

arrtab

typedef struct {
    char name;           // 'E', 'F', 'G', 'H'
    float data[16];      // 1-based indexing
} dope_array_t;

dope_array_t arrtab[4];  // E, F, G, H

// E[5] = X
float* dest = dope_array_ref('E', 5);
float* src  = dope_find_var("X");
*dest = *src;
