test-power_obj: test-power.c
	gcc -c -o test-power.o -pedantic -std=gnu99 -Wall -Werror test-power.c

power_obj: power.c
	gcc -c -o power.o -pedantic -std=gnu99 -Wall -Werror power.c

my_power: power.o test-power.o
	gcc -o power -pedantic -std=gnu99 -Wall -Werror test-power.o power.o
