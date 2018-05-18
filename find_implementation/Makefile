CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	main.o \
		execute.o \
		filter.o \
		search.o \
		utilities.o \
		search

all:		$(TARGETS)

main.o:		main.c
		@echo Compiling main.o...
		@ $(CC) $(CFLAGS) -c -o main.o main.c

execute.o:	execute.c
		@echo Compiling execute.o...
		@$(CC) $(CFLAGS) -c -o execute.o execute.c

filter.o:	filter.c
		@echo Compiling filter.o...
		@$(CC) $(CFLAGS) -c -o filter.o filter.c

search.o:	search.c
		@echo Compiling search.o...
		@$(CC) $(CFLAGS) -c -o search.o search.c

utilities.o:	utilities.c
		@echo Compiling utilities.o...
		@$(CC) $(CFLAGS) -c -o utilities.o utilities.c

search:		main.o execute.o filter.o search.o utilities.o
		@echo Linking search...
		@ $(LD) $(LDFLAGS) -o search main.o execute.o filter.o search.o utilities.o

test:		search test_search.sh
		@echo Testing $<...
		@./test_search.sh

syscalls:	syscalls.sh
		@echo Compiling syscalls...
		@./syscalls.sh
clean:
		@echo Cleaning...
		@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all test benchmark clean

