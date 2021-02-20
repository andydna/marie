#include <err.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "marie.h"
#include "marie.c" // so i can test static methods

int test_fetch_decode_execute_cycle(void)
{
    struct marie *m = calloc(1, sizeof(struct marie)); 

    /* fetch */
    // setup PC, Memory[MAR]

    m->pc = 1;
    m->memory[1] = 10;

    fetch(m);

    // copy PC to MAR
    // copy Memory[MAR] to IR
    // ++PC

    assert(m->mar == 1);
    assert(m->pc == 2);
    assert(m->ir == 10);

    /* decode */

    // decode the instruction and place bits ir[11-0] in the mar

    decode(m);
    assert(m->ir == 10);

    /* execute */

    execute(m);

    // can't test yet without instructions

    free(m);
}

void test_decode_only_copies_12_bits(void)
{
    struct marie *m = calloc(1, sizeof(struct marie));
    m->ir = 0xffff;
    decode(m);
    assert(m->mar == 0xfff);
    free(m);
}

void test_decoding_opcodes(void)
{
    struct marie *m = calloc(1, sizeof(struct marie));

    m->ir = 0x1fff;
    decode(m);
    assert(m->opcode == LOAD);

    m->ir = 0x2fff;
    decode(m);
    assert(m->opcode == STORE);

    m->ir = 0x3fff;
    decode(m);
    assert(m->opcode == ADD);

    m->ir = 0x4fff;
    decode(m);
    assert(m->opcode == SUBT);

    m->ir = 0x5fff;
    decode(m);
    assert(m->opcode == INPUT);

    m->ir = 0x6fff;
    decode(m);
    assert(m->opcode == OUTPUT);

    m->ir = 0x7fff;
    decode(m);
    assert(m->opcode == HALT);

    m->ir = 0x8fff;
    decode(m);
    assert(m->opcode == SKIPCOND);

    m->ir = 0x9fff;
    decode(m);
    assert(m->opcode == JUMP);

    free(m);
}

void test_decoding_opcodes_that_dont_require_operands_doesnt_change_mbr()
{
    // input, output, halt, skipcond
    // mbr shouldn't change

    struct marie *m = calloc(1, sizeof m);

    m->mbr = 0x111;
    m->ir  = INPUT << 12;
    decode(m);
    assert(m->mbr == 0x111);

    m->mbr = 0x111;
    m->ir  = OUTPUT << 12;
    decode(m);
    assert(m->mbr == 0x111);

    m->mbr = 0x111;
    m->ir  = HALT << 12;
    decode(m);
    assert(m->mbr == 0x111);

    m->mbr = 0x111;
    m->ir  = SKIPCOND << 12;
    decode(m);
    assert(m->mbr == 0x111);
}

void test_decoding_opcodes_that_require_operands_changes_mbr()
{
    // load, store, add, subt, jump
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 0x111;
    m->ir  = (LOAD << 12) | 0xfff;
    decode(m);
    assert(m->mbr == 0x000);

    m->mbr = 0x111;
    m->ir  = (STORE << 12) | 0xfff;
    decode(m);
    assert(m->mbr == 0x000);

    m->mbr = 0x111;
    m->ir  = (ADD << 12) | 0xfff;
    decode(m);
    assert(m->mbr == 0x000);

    m->mbr = 0x111;
    m->ir  = (SUBT << 12) | 0xfff;
    decode(m);
    assert(m->mbr == 0x000);

    m->mbr = 0x111;
    m->ir  = (JUMP << 12) | 0xfff;
    decode(m);
    assert(m->mbr == 0x000);
}

void test_load(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 123;
    load(m);
    assert(m->acc == 123);
    free(m);
}

void test_store(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 123;
    store(m);
    assert(m->memory[m->mar] == 123);

    free(m);
}

void test_add(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 1;
    m->mbr = 1;
    add(m);
    assert(m->acc == 2);

    free(m);
}

void test_subt(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 2;
    m->mbr = 1;
    subt(m);
    assert(m->acc == 1);

    free(m);
}

void test_input()
{
    errx(1, "not yet implemented");
}

void test_output()
{
    errx(1, "not yet implemented");
}

void test_halt()
{
    errx(1, "not yet implemented");
}

void test_skipcond()
{
    errx(1, "not yet implemented");
}

void test_jump(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 123;
    jump(m);
    assert(m->pc == 123);

    free(m);
}

#include "test_execute.c"

int main(void)
{
    test_fetch_decode_execute_cycle();

    /* decode */

    test_decode_only_copies_12_bits();
    test_decoding_opcodes();
    test_decoding_opcodes_that_dont_require_operands_doesnt_change_mbr();
    test_decoding_opcodes_that_require_operands_changes_mbr();

    /* instructions - calling directly */

    test_load();
    test_store();
    test_add();
    test_subt();
    // test_input();
    // test_output();
    // test_halt();
    // test_skipcond();
    test_jump();

    test_execute_calls_load();
    test_execute_calls_store();
    test_execute_calls_add();
//    test_execute_calls_subt();
}
