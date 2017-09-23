# Makefile
VERSION = 3.02
CC      = /usr/bin/gcc
OBJ	 = hp8648c_hp436a_sweeper.o gpib-functions.o callback-gpib.o callback_widget.o widget.o signal_connect.o run_sweep_f.o run_sweep_p.o init.o
CFLAGS  = -Wall -ggdb
LDFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0` -rdynamic -lgpib -lm  
PRG 	= hp8648c_hp436a_sweeper
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm -f $(PRG) *~ *.o a.out core prototyp*

install:
	sudo cp $(PRG) /usr/local/bin

uninstal:
	cd /usr/local/bin
	sudo rm -f $(PRG)
