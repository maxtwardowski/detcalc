det: det.c
	gcc -g -Wall -Werror -O3 -pedantic $^ -o $@ -lm

.PHONY: clean

clean:
	-rm det
