######################################################
# makefile
# for compiling and testing of the Galaxy Engine
#
# by Sebastian Gurlin
######################################################



#========================================== variables ========================================
UNAME_S         := $(shell uname -s)

assetsDir       = ./assets/
sourceDir       = ./source/
binDir          = ./bin/
emuDir          = ./emulator/
CompilerDosDir  = /home/sebastian/Programming/compiler/djgpp-linux64-gcc1020/djgpp/bin/
CompilerDos     = $(CompilerDosDir)i586-pc-msdosdjgpp-g++
CompilerLinux   = g++
CompilerWin     = x86_64-w64-mingw32-g++
Compiler        = $(CompilerDosDir)i586-pc-msdosdjgpp-g++
CFLAGS          = -Wall -O3 -s
CFLAGSWin       = -static-libgcc -static-libstdc++ -static -Dwin
CFLAGSDos       = -Ddos
CFLAGSLinux     = -Dlinux
emulator        = dosbox
EFLAGS          = -conf $(emuDir)dosbox.conf #-exit
sourceFiles     = $(wildcard $(sourceDir)*.cpp)
objectFiles     = $(sourceFiles:.cpp=.o)
#VPATH          = $(sourceDir)
#==============================================================================================



#========================================== DOS ===============================================
$(sourceDir)dos/NetEngine.o: $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/DerivedObjects.o: $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/Object.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/Object.o: $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TextEngineIOStream.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TextEngineSTDIO.o: $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameClient.o: $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameServer.o: $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/NetEngineLocal.o: $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(binDir)dos/main.exe: $(sourceDir)main.cpp $(sourceDir)dos/Object.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/TextEngineSTDIO.o $(sourceDir)dos/GameClient.o $(sourceDir)dos/GameServer.o $(sourceDir)dos/NetEngineLocal.o $(sourceDir)dos/DerivedObjects.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ $^
	cp $(assetsDir)* $(binDir)dos/

$(binDir)dos/DedicatedServer.exe: $(sourceDir)DedicatedServer.cpp $(sourceDir)dos/Object.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/TextEngineSTDIO.o $(sourceDir)dos/GameClient.o $(sourceDir)dos/GameServer.o $(sourceDir)dos/NetEngineLocal.o $(sourceDir)dos/DerivedObjects.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ $^
	cp $(assetsDir)* $(binDir)dos/

.PHONY: dos
dos: $(binDir)dos/main.exe

.PHONY: dosDedicatedServer
dosDedicatedServer: $(binDir)dos/DedicatedServer.exe
#==============================================================================================



#============================================= win ============================================
$(sourceDir)win/NetEngine.o: $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/DerivedObjects.o: $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)win/GameEngine.o $(sourceDir)win/Object.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/Object.o: $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)win/GameEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin)  -o $@ -c $<

$(sourceDir)win/TextEngineIOStream.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/TextEnginSTDIOe.o: $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameClient.o: $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameServer.o: $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/NetEngineLocal.o: $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)win/GameEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(binDir)win/main.exe: $(sourceDir)main.cpp $(sourceDir)win/Object.o $(sourceDir)win/GameEngine.o $(sourceDir)win/TextEngineIOStream.o $(sourceDir)win/GameClient.o $(sourceDir)win/GameServer.o $(sourceDir)win/NetEngineLocal.o $(sourceDir)win/DerivedObjects.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ $^

$(binDir)win/DedicatedServer.exe: $(sourceDir)DedicatedServer.cpp $(sourceDir)win/Object.o $(sourceDir)win/GameEngine.o $(sourceDir)win/TextEngineIOStream.o $(sourceDir)win/GameClient.o $(sourceDir)win/GameServer.o $(sourceDir)win/NetEngineLocal.o $(sourceDir)win/DerivedObjects.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ $^

.PHONY: win
win: $(binDir)win/main.exe

.PHONY: winDedicatedServer
winDedicatedServer: $(binDir)win/DedicatedServer.exe
#==============================================================================================



#============================================== linux =========================================
$(sourceDir)linux/NetEngine.o:  $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFlagsLinux) -o $@ -c $<

$(sourceDir)linux/DerivedObjects.o: $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/Object.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFlagsLinux) -o $@ -c $<

$(sourceDir)linux/Object.o:         $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TextEngineIOStream.o: $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TextEngineSTDIO.o: $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameEngine.o: $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.cpp $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameClient.o: $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameServer.o: $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineLocal.o: $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineLinuxSockets.o: $(sourceDir)NetEngineLinuxSockets.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(binDir)linux/main: $(sourceDir)main.cpp $(sourceDir)linux/Object.o $(sourceDir)linux/GameEngine.o $(sourceDir)linux/TextEngineIOStream.o $(sourceDir)linux/GameClient.o $(sourceDir)linux/GameServer.o $(sourceDir)linux/NetEngineLinuxSockets.o $(sourceDir)linux/DerivedObjects.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ $^

$(binDir)linux/DedicatedServer: $(sourceDir)DedicatedServer.cpp $(sourceDir)linux/Object.o $(sourceDir)linux/GameEngine.o $(sourceDir)linux/TextEngineIOStream.o $(sourceDir)linux/GameClient.o $(sourceDir)linux/GameServer.o $(sourceDir)linux/NetEngineLinuxSockets.o $(sourceDir)linux/DerivedObjects.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ $^

.PHONY: linux
linux: $(binDir)linux/main

.PHONY: linuxDedicatedServer
linuxDedicatedServer: $(binDir)linux/DedicatedServer
#==============================================================================================



#============================================= all ============================================
.PHONY: all
all: dos dosDedicatedServer linux linuxDedicatedServer win winDedicatedServer
#==============================================================================================



#=========================================== testing ==========================================
.PHONY: run
run:
	$(emulator) $(binDir)dos/main.exe $(EFLAGS)

.PHONY: rundos
rundos: run

.PHONY: rundosDedicatedServer
rundosDedicatedServer:
	$(emulator) $(binDir)dos/DedicatedServer.exe $(EFLAGS)

.PHONY: runwin
runwin: 
	$(binDir)win/main.exe

.PHONY: runwinDedicatedServer
runwinDedicatedServer: 
	$(binDir)win/DedicatedServer.exe

.PHONY: runlinux
runlinux: 
	$(binDir)linux/main

.PHONY: runlinuxDedicatedServer
runlinuxDedicatedServer: 
	$(binDir)linux/DedicatedServer
#==============================================================================================



#============================================ clean ===========================================
.PHONY: clean
clean:
	rm -Rf $(binDir)*.exe
	rm -Rf $(binDir)dos/*
	rm -Rf $(binDir)win/*
	rm -Rf $(binDir)linux/*
	rm -Rf $(sourceDir)dos/*
	rm -Rf $(sourceDir)win/*
	rm -Rf $(sourceDir)linux/*
#==============================================================================================



#============================================== git ===========================================
.PHONY: push
push:
	git add *
	git commit -m "commit"
	git push origin main

.PHONY: pull
pull:
	git pull origin main
#==============================================================================================
