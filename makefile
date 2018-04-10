det: det.c
	gcc -g -Wall -Werror -pedantic $^ -o $@ -lm

.PHONY: clean

clean:
	-rm det
