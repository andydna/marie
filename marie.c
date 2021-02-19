#include "marie.h"

void fetch(struct marie *m)
{
    m->mar = m->pc;
    m->ir = m->memory[m->mar];
    ++m->pc;
}

void decode(struct marie *m)
{
    m->opcode = (m->ir & 0xf000) >> 12;
    m->mar = m->ir & 0xfff;

    switch(m->opcode)
    {
        case LOAD:
        case STORE:
        case ADD:
        case SUBT:
        case JUMP:
            m->mbr = m->memory[m->mar];
            break;
        default:
            break;
    }
    // if (instruction_requires_operand) copy the contents of memory[mar] to mbr
}

void execute(struct marie *m)
{
    ;
}

/* instructions */

void load(struct marie *m)
{
    m->acc = m->mbr;
}

void store(struct marie *m)
{
    m->memory[m->mar] = m->acc;
}

void add(struct marie *m)
{
    m->acc += m->mbr;
}

void subt(struct marie *m)
{
    m->acc -= m->mbr;
}

void jump(struct marie *m)
{
    m->pc = m->mbr;
}
