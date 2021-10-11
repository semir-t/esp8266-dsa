
PROGRAM = server
MAIN = main.c

CC = gcc
CFLAGS = -pthread
LFLAGS = -pthread
TARGET = $(strip $(basename $(MAIN)))
SRC = $(TARGET).c
SRC += $(LOCAL_SOURCE)

## List of all header files
HEADERS = $(SRC:.c=.h) 

## For every .c file, compile an .o object file
OBJ = $(SRC:.c=.o) 

all: $(PROGRAM)
%.o: %.c
	$(CC) $(CFLAGS) -c  $< # $@
$(PROGRAM) : $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(PROGRAM)
clean:
	rm *.o
squeaky_clean :
	rm *.o $(PROGRAM)
