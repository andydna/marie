test: test_marie
	./test_marie

test_marie: test_marie.c test_execute.c marie.c marie.h
	gcc test_marie.c -o test_marie
