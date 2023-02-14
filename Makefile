CC = g++

PROJECT = output

SRC = main.cpp

LIBS = `pkg-config --cflags --libs opencv4` -lballistics

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS) -lballistics

clear:
	/bin/rm output

run:
	./$(PROJECT)
