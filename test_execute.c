void test_execute_calls_load()
{
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 123;
    m->opcode = LOAD;

    execute(m);

    assert(m->acc == 123);
    free(m);
}

void test_execute_calls_store()
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 123;
    m->opcode = STORE;

    execute(m);

    assert(m->memory[m->mar] == 123);

    free(m);
}

void test_execute_calls_add()
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 1;
    m->mbr = 1;
    m->opcode = ADD;

    execute(m);

    assert(m->acc == 2);

    free(m);
}
