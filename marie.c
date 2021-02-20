#include "marie.h"

/* instructions */

static void load(struct marie *m)
{
    m->acc = m->mbr;
}

static void store(struct marie *m)
{
    m->memory[m->mar] = m->acc;
}

static void add(struct marie *m)
{
    m->acc += m->mbr;
}

static void subt(struct marie *m)
{
    m->acc -= m->mbr;
}

static void jump(struct marie *m)
{
    m->pc = m->mbr;
}

/* fetch decode execute cycle */

static void fetch(struct marie *m)
{
    m->mar = m->pc;
    m->ir = m->memory[m->mar];
    ++m->pc;
}

static void decode(struct marie *m)
{
    m->opcode = (m->ir & 0xf000) >> 12; // top 4 bits of 16
    m->mar = m->ir & 0xfff; // bottom 12 bits of 16

    switch(m->opcode)
    {
        // if (instruction requires operand) copy the contents of memory[mar] to mbr
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
}

static void execute(struct marie *m)
{
    switch(m->opcode)
    {
        case LOAD:
            load(m);
            break;
        case STORE:
            store(m);
            break;
        case ADD:
            add(m);
            break;
        default:
            break;
    }
}
