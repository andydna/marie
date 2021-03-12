void test_execute_calls_load()
{
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 123;
    m->op = LOAD;

    execute(m);

    assert(m->acc == 123);
    free(m);
}

void test_execute_calls_store()
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 123;
    m->op = STORE;

    execute(m);

    assert(m->memory[m->mar] == 123);

    free(m);
}

void test_execute_calls_add()
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 1;
    m->mbr = 1;
    m->op = ADD;

    execute(m);

    assert(m->acc == 2);

    free(m);
}

void test_execute_calls_subt(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->acc = 2;
    m->mbr = 1;
    m->op = SUBT;

    execute(m);

    assert(m->acc == 1);

    free(m);
}

void test_execute_calls_jump(void)
{
    struct marie *m = calloc(1, sizeof m);

    m->mbr = 123;
    m->op = JUMP;

    execute(m);

    assert(m->pc == 123);

    free(m);
}
