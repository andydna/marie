#include <stdint.h>

#define WORDS 4000

enum isa { BAD, LOAD, STORE, ADD, SUBT, INPUT, OUTPUT, HALT, SKIPCOND, JUMP };

struct marie {
    enum isa opcode; // last decoded opcode
    // registers
    uint16_t acc;
    uint16_t ir;
    uint16_t mbr;
    uint16_t pc : 12;
    uint16_t mar : 12;
    uint16_t in : 8;
    uint16_t out : 8;
    // memory
    uint16_t memory[WORDS];
};

void fetch(struct marie *m);

void decode(struct marie *m);

void execute(struct marie *m);

/* instructions */

void load(struct marie *m);

void store(struct marie *m);

void add(struct marie *m);

void subt(struct marie *m);

void jump(struct marie *m);
