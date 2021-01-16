######################################################
# makefile
# for compiling and testing of the Galaxy Engine
#
# by Sebastian Gurlin
######################################################

#========================================== variables ========================================
UNAME_S 		:= $(shell uname -s)

assetsDir		= ./assets/
sourceDir 		= ./source/
binDir			= ./bin/
emuDir			= ./emulator/
CompilerDosDir  = /home/sebastian/Programming/compiler/djgpp-linux64-gcc1020/djgpp/bin/
CompilerDos 	= $(CompilerDosDir)i586-pc-msdosdjgpp-g++
CompilerLinux 	= g++
CompilerWin 	= x86_64-w64-mingw32-g++
Compiler 		= $(CompilerDosDir)i586-pc-msdosdjgpp-g++
CFLAGS			= -Wall -O3 -s
CFLAGSWin		= -static-libgcc -static-libstdc++ -static
emulator		= dosbox
EFLAGS			= -conf $(emuDir)dosbox.conf #-exit
sourceFiles		= $(wildcard $(sourceDir)*.cpp)
objectFiles 	= $(sourceFiles:.cpp=.o)
#VPATH 			= $(sourceDir)
#==============================================================================================

#========================================== DOS ===============================================
$(sourceDir)dos/Object.o: $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)GameEngine.o
	$(CompilerDos) $(CFLAGS) -o $@ -c $<

$(sourceDir)dos/TextEngine.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) -o $@ -c $<

$(sourceDir)dos/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h
	$(CompilerDos) $(CFLAGS) -o $@ -c $<

$(binDir)dos/main.exe: $(sourceDir)main.cpp $(sourceDir)dos/Object.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/TextEngine.o
	$(CompilerDos) $(CFLAGS) -o $@ $^
	cp $(assetsDir)* $(binDir)dos/

.PHONY: dos
dos: $(binDir)dos/main.exe
#==============================================================================================

#============================================= win ============================================
$(sourceDir)win/Object.o: $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)GameEngine.o
	$(CompilerWin) $(CFLAGS) -o $@ -c $<

$(sourceDir)win/TextEngine.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) -o $@ -c $<

$(sourceDir)win/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h
	$(CompilerWin) $(CFLAGS) -o $@ -c $<

$(binDir)win/main.exe: $(sourceDir)main.cpp $(sourceDir)win/Object.o $(sourceDir)win/GameEngine.o $(sourceDir)win/TextEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ $^

.PHONY: win
win: $(binDir)win/main.exe
#==============================================================================================

#============================================== linux =========================================
$(sourceDir)linux/Object.o: $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)GameEngine.o
	$(CompilerLinux) $(CFLAGS) -o $@ -c $<

$(sourceDir)linux/TextEngine.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) -o $@ -c $<

$(sourceDir)linux/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.cpp
	$(CompilerLinux) $(CFLAGS) -o $@ -c $<

$(binDir)linux/main: $(sourceDir)main.cpp $(sourceDir)linux/Object.o $(sourceDir)linux/GameEngine.o $(sourceDir)linux/TextEngine.o
	$(CompilerLinux) $(CFLAGS) -o $@ $^

.PHONY: linux
linux: $(binDir)linux/main
#==============================================================================================


	
.PHONY: all
all: dos linux win

#=========================================== testing ==========================================
.PHONY: run
run:
	$(emulator) $(binDir)dos/main.exe $(EFLAGS)

.PHONY: rundos
rundos: run

.PHONY: runwin
runwin: 
	$(binDir)win/main.exe

.PHONY: runlinux
runlinux: 
	$(binDir)linux/main
#==============================================================================================

.PHONY: clean
clean:
	rm -Rf $(binDir)*.exe
	rm -Rf $(binDir)dos/*
	rm -Rf $(binDir)win/*
	rm -Rf $(binDir)linux/*
	rm -Rf $(sourceDir)dos/*
	rm -Rf $(sourceDir)win/*
	rm -Rf $(sourceDir)linux/*

#============================================== git =============================================
.PHONY: push
push:
	git add *
	git commit -m "commit"
	git push origin main

.PHONY: pull
pull:
	git pull origin main
#==============================================================================================
