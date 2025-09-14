#include "dope_interpret.h"
#include "dope_constants.h"
#include "dope_types.h"
#include "dope_vectors.h"
#include <assert.h>

dope_fn_t dispatch_table[] = {
    [DOPE_OP_ADD] = NULL,
    [DOPE_OP_SUB] = NULL,
    [DOPE_OP_MUL] = NULL,
    [DOPE_OP_DIV] = NULL,
    [DOPE_OP_STORE] = NULL,
    [DOPE_OP_SQR] = NULL,
    [DOPE_OP_EXP] = NULL,
    [DOPE_OP_LOG] = NULL,
    [DOPE_OP_SIN] = NULL,
    [DOPE_OP_COMPARE] = NULL,
    [DOPE_OP_GOTO] = NULL,
    [DOPE_OP_LABEL] = NULL,
    [DOPE_OP_PRINT] = NULL,
    [DOPE_OP_NEWLN] = NULL,
    [DOPE_OP_INPUT] = NULL,
    [DOPE_OP_LOOP] = NULL,
    [DOPE_OP_END] = NULL,
    [DOPE_OP_STOP] = dope_stop,
    [DOPE_OP_START] = dope_start
};

void dope_interpret(
    dope_size_t vartab_size,
    dope_program_t* program,
    dope_data_t* data
) {
    dope_vartab_t* vartab = dope_new_vartab(vartab_size);
    dope_vectab_t* vectab = dope_new_vectab();
    assert(vartab);
    assert(vectab);
    dope_size_t ip = program->size - 1;
    while(program->instructions[ip].opcode != DOPE_OP_STOP) {
        dope_instruction_t* p = &program->instructions[ip];
        dope_fn_t fn =dispatch_table[p->opcode];
        fn(&ip, vartab, vectab, data);
    }

    dope_free_vectab(vectab);
    dope_free_vartab(vartab);
}

void dope_stop(dope_size_t* ip, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {

}

void dope_start(dope_size_t* ip, dope_vartab_t* vars, dope_vectab_t* vecs, dope_data_t* data) {
    *ip = 0;
}
