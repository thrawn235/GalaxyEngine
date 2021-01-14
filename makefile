#makefile
#for compiling and testing of the Galaxy Engine
#by Sebastian Gurlin

UNAME_S := $(shell uname -s)

assetsDir	= ./assets/
sourceDir 	= ./source/
binDir		= ./bin/
emuDir		= ./emulator/
CCDowDir    = /home/sebastian/Programming/compiler/djgpp-linux64-gcc1020/djgpp/bin/
CCDos 		= $(CCDosDir)i586-pc-msdosdjgpp-g++
CCLinux 	= g++
CCWin 		= x86_64-w64-mingw32-g++
CC 			= $(CCDosDir)i586-pc-msdosdjgpp-g++
CFLAGS		= -Wall -O3 -s
emulator	= dosbox
EFLAGS		= -conf $(emuDir)dosbox.conf #-exit
sourceFiles	= $(wildcard $(sourceDir)*.cpp)
objectFiles = $(sourceFiles:.cpp=.o)
#VPATH 		= $(sourceDir)

$(sourceDir)Object.o: $(sourceDir)Object.cpp $(sourceDir)GameEngine.o
	$(CC) $(CFLAGS) -o $@ -c $<

$(sourceDir)GameEngine.o: $(sourceDir)GameEngine.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(binDir)main.exe: $(sourceDir)main.cpp $(sourceDir)Object.o $(sourceDir)GameEngine.o
	$(CC) $(CFLAGS) -o $@ $^
	cp $(assetsDir)* $(binDir)

setdos:
	$(eval CC = $(CCDos))

.PHONY: dos
dos: setdos $(binDir)main.exe

.PHONY: linux
linux:
	CC = $(CCLinux)
	$(binDir)main.exe

.PHONY: win
win:
	CC = $(CCWin)
	$(binDir)main.exe
	
.PHONY: all
all: dos linux win

.PHONY: run
run:
	$(emulator) $(binDir)main.exe $(EFLAGS)

.PHONY: clean
clean:
	rm -f $(binDir)*
	rm -f $(sourceDir)*.o

.PHONY: push
push:
	git add *
	git commit -m "commit"
	git push origin master

.PHONY: pull
pull:
	git pull origin master
