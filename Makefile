PROJECT =  trove
HEADERS =  $(PROJECT).h
OBJ     =  trove.o list_files.o

C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)