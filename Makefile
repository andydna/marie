test: test_marie
	./test_marie

test_marie: test_marie.c marie.c marie.h
	gcc test_marie.c marie.c -o test_marie
