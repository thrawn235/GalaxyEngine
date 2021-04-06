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
CFLAGSWin       = -static-libgcc -static-libstdc++ -DTARGET_WIN -lws2_32 -lmingw32 -lSDL2main -lSDL2
CFLAGSDos       = -DTARGET_DOS
CFLAGSLinux     = -DTARGET_LINUX -lSDL2
emulator        = dosbox
EFLAGS          = -conf $(emuDir)dosbox.conf #-exit
sourceFiles     = $(wildcard $(sourceDir)*.cpp)
objectFiles     = $(sourceFiles:.cpp=.o)
#VPATH          = $(sourceDir)
#==============================================================================================



#========================================== DOS ===============================================
$(sourceDir)dos/NetEngine.o:                    $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/DerivedObjects.o:               $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/Object.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/Object.o:                       $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TextEngineDummy.o:              $(sourceDir)TextEngineDummy.cpp $(sourceDir)TextEngineDummy.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GraphicsEngineDummy.o:          $(sourceDir)GraphicsEngineDummy.cpp $(sourceDir)GraphicsEngineDummy.h $(sourceDir)GraphicsEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TimeEngineDummy.o:              $(sourceDir)TimeEngineDummy.cpp $(sourceDir)TimeEngineDummy.h $(sourceDir)TimeEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TimeEngineDOS.o:              	$(sourceDir)TimeEngineDOS.cpp $(sourceDir)TimeEngineDOS.h $(sourceDir)TimeEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GraphicsEngineVESA.o:           $(sourceDir)GraphicsEngineVESA.cpp $(sourceDir)GraphicsEngineVESA.h $(sourceDir)GraphicsEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TextEngineIOStream.o:           $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/TextEngineSTDIO.o:              $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameEngine.o:                   $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameNode.o:                     $(sourceDir)GameNode.cpp $(sourceDir)GameNode.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameClient.o:                   $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/NetEngine.o $(sourceDir)dos/GameNode.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/GameServer.o:                   $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)dos/GameEngine.o $(sourceDir)dos/NetEngine.o $(sourceDir)dos/GameNode.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/NetEngineDummy.o:               $(sourceDir)NetEngineDummy.cpp $(sourceDir)NetEngineDummy.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/NetEngineLocal.o:               $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/NetEngineDosPacketDriverUDP.o:  $(sourceDir)NetEngineDosPacketDriverUDP.cpp $(sourceDir)NetEngineDosPacketDriverUDP.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/InputEngineDummy.o:             $(sourceDir)InputEngineDummy.cpp $(sourceDir)InputEngineDummy.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(sourceDir)dos/InputEngineDOS.o:               $(sourceDir)InputEngineDOS.cpp $(sourceDir)InputEngineDOS.h $(sourceDir)dos/GameEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ -c $<

$(binDir)dos/main.exe:                          $(sourceDir)main.cpp $(sourceDir)dos/Object.o $(sourceDir)dos/TimeEngineDummy.o $(sourceDir)dos/TimeEngineDOS.o $(sourceDir)dos/InputEngineDOS.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/InputEngineDummy.o $(sourceDir)dos/GraphicsEngineDummy.o $(sourceDir)dos/GraphicsEngineVESA.o $(sourceDir)dos/GameNode.o $(sourceDir)dos/TextEngineDummy.o $(sourceDir)dos/NetEngineDummy.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/TextEngineSTDIO.o $(sourceDir)dos/TextEngineIOStream.o $(sourceDir)dos/GameClient.o $(sourceDir)dos/GameServer.o $(sourceDir)dos/NetEngineLocal.o $(sourceDir)dos/NetEngineDosPacketDriverUDP.o $(sourceDir)dos/DerivedObjects.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ $^
	cp $(assetsDir)dos/* $(binDir)dos/

$(binDir)dos/DedicatedServer.exe:               $(sourceDir)DedicatedServer.cpp $(sourceDir)dos/InputEngineDOS.o $(sourceDir)dos/TimeEngineDummy.o $(sourceDir)dos/TimeEngineDOS.o $(sourceDir)dos/Object.o $(sourceDir)dos/GraphicsEngineVESA.o $(sourceDir)dos/GameNode.o $(sourceDir)dos/GraphicsEngineDummy.o $(sourceDir)dos/InputEngineDummy.o $(sourceDir)dos/NetEngineDummy.o $(sourceDir)dos/TextEngineDummy.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/GameEngine.o $(sourceDir)dos/TextEngineSTDIO.o $(sourceDir)dos/TextEngineIOStream.o $(sourceDir)dos/GameClient.o $(sourceDir)dos/GameServer.o $(sourceDir)dos/NetEngineLocal.o $(sourceDir)dos/NetEngineDosPacketDriverUDP.o $(sourceDir)dos/DerivedObjects.o $(sourceDir)dos/NetEngine.o
	$(CompilerDos) $(CFLAGS) $(CFLAGSDos) -o $@ $^
	cp $(assetsDir)dos/* $(binDir)dos/

.PHONY: dos
dos: $(binDir)dos/main.exe

.PHONY: dosDedicatedServer
dosDedicatedServer: $(binDir)dos/DedicatedServer.exe
#==============================================================================================



#============================================= win ============================================
$(sourceDir)win/NetEngine.o:                    $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/DerivedObjects.o:               $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)win/GameEngine.o $(sourceDir)win/Object.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/Object.o:                       $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)win/GameEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin)  -o $@ -c $<

$(sourceDir)win/TextEngineDummy.o:              $(sourceDir)TextEngineDummy.cpp $(sourceDir)TextEngineDummy.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GraphicsEngineDummy.o:          $(sourceDir)GraphicsEngineDummy.cpp $(sourceDir)GraphicsEngineDummy.h $(sourceDir)GraphicsEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/TimeEngineDummy.o:              $(sourceDir)TimeEngineDummy.cpp $(sourceDir)TimeEngineDummy.h $(sourceDir)TimeEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GraphicsEngineSDL.o:            $(sourceDir)GraphicsEngineSDL.cpp $(sourceDir)GraphicsEngineSDL.h $(sourceDir)GraphicsEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/TextEngineIOStream.o:           $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/TextEngineSTDIO.o:              $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameEngine.o:                   $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.h $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameNode.o:                     $(sourceDir)GameNode.cpp $(sourceDir)GameNode.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameClient.o:                   $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o $(sourceDir)win/GameNode.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/GameServer.o:                   $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o $(sourceDir)win/GameNode.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/NetEngineDummy.o:               $(sourceDir)NetEngineDummy.cpp $(sourceDir)NetEngineDummy.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/NetEngineLocal.o:               $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/NetEngineWinSocketsUDP.o:       $(sourceDir)NetEngineWinSocketsUDP.cpp $(sourceDir)NetEngineWinSocketsUDP.h $(sourceDir)win/GameEngine.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/InputEngineDummy.o:             $(sourceDir)InputEngineDummy.cpp $(sourceDir)InputEngineDummy.h $(sourceDir)InputEngine.h $(sourceDir)win/GameEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(sourceDir)win/InputEngineSDL.o:               $(sourceDir)InputEngineSDL.cpp $(sourceDir)InputEngineSDL.h $(sourceDir)InputEngine.h $(sourceDir)win/GameEngine.o
	$(CompilerWin) $(CFLAGS) $(CFLAGSWin) -o $@ -c $<

$(binDir)win/main.exe:                          $(sourceDir)main.cpp $(sourceDir)win/Object.o $(sourceDir)win/TimeEngineDummy.o $(sourceDir)win/GameEngine.o $(sourceDir)win/GraphicsEngineDummy.o $(sourceDir)win/GraphicsEngineSDL.o $(sourceDir)win/InputEngineDummy.o $(sourceDir)win/NetEngineDummy.o $(sourceDir)win/TextEngineDummy.o $(sourceDir)win/GameNode.o $(sourceDir)win/TextEngineIOStream.o $(sourceDir)win/TextEngineSTDIO.o $(sourceDir)win/GameClient.o $(sourceDir)win/GameServer.o $(sourceDir)win/NetEngineLocal.o $(sourceDir)win/NetEngineWinSocketsUDP.o $(sourceDir)win/DerivedObjects.o $(sourceDir)win/NetEngine.o $(sourceDir)win/InputEngineSDL.o
	$(CompilerWin) $(CFLAGS) -o $@ $^ $(CFLAGSWin)
	cp $(assetsDir)win/* $(binDir)win/

$(binDir)win/DedicatedServer.exe:               $(sourceDir)DedicatedServer.cpp $(sourceDir)win/Object.o $(sourceDir)win/TimeEngineDummy.o $(sourceDir)win/InputEngineDummy.o $(sourceDir)win/GraphicsEngineDummy.o $(sourceDir)win/GraphicsEngineSDL.o $(sourceDir)win/NetEngineDummy.o $(sourceDir)win/GameEngine.o $(sourceDir)win/TextEngineDummy.o $(sourceDir)win/GameNode.o $(sourceDir)win/InputEngineSDL.o $(sourceDir)win/TextEngineIOStream.o $(sourceDir)win/TextEngineSTDIO.o $(sourceDir)win/GameClient.o $(sourceDir)win/GameServer.o $(sourceDir)win/NetEngineLocal.o $(sourceDir)win/NetEngineWinSocketsUDP.o $(sourceDir)win/DerivedObjects.o $(sourceDir)win/NetEngine.o
	$(CompilerWin) $(CFLAGS) -o $@ $^ $(CFLAGSWin)
	cp $(assetsDir)win/* $(binDir)win/

.PHONY: win
win: $(binDir)win/main.exe

.PHONY: winDedicatedServer
winDedicatedServer: $(binDir)win/DedicatedServer.exe
#==============================================================================================



#============================================== linux =========================================
$(sourceDir)linux/NetEngine.o:                  $(sourceDir)NetEngine.cpp $(sourceDir)NetEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/DerivedObjects.o:             $(sourceDir)DerivedObjects.cpp $(sourceDir)DerivedObjects.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/Object.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/Object.o:                     $(sourceDir)Object.cpp $(sourceDir)Object.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TextEngineDummy.o:            $(sourceDir)TextEngineDummy.cpp $(sourceDir)TextEngineDummy.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GraphicsEngineDummy.o:        $(sourceDir)GraphicsEngineDummy.cpp $(sourceDir)GraphicsEngineDummy.h $(sourceDir)GraphicsEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TimeEngineDummy.o:            $(sourceDir)TimeEngineDummy.cpp $(sourceDir)TimeEngineDummy.h $(sourceDir)TimeEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GraphicsEngineSDL.o:          $(sourceDir)GraphicsEngineSDL.cpp $(sourceDir)GraphicsEngineSDL.h $(sourceDir)GraphicsEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TextEngineIOStream.o:         $(sourceDir)TextEngineIOStream.cpp $(sourceDir)TextEngineIOStream.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/TextEngineSTDIO.o:            $(sourceDir)TextEngineSTDIO.cpp $(sourceDir)TextEngineSTDIO.h $(sourceDir)TextEngine.h
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameEngine.o:                 $(sourceDir)GameEngine.cpp $(sourceDir)GameEngine.cpp $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameNode.o:                   $(sourceDir)GameNode.cpp $(sourceDir)GameNode.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameClient.o:                 $(sourceDir)GameClient.cpp $(sourceDir)GameClient.h $(sourceDir)GameNode.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/NetEngine.o $(sourceDir)linux/GameNode.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/GameServer.o:                 $(sourceDir)GameServer.cpp $(sourceDir)GameServer.h $(sourceDir)GameNode.h $(sourceDir)linux/GameEngine.o $(sourceDir)linux/NetEngine.o $(sourceDir)linux/GameNode.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineDummy.o:             $(sourceDir)NetEngineDummy.cpp $(sourceDir)NetEngineDummy.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineLocal.o:             $(sourceDir)NetEngineLocal.cpp $(sourceDir)NetEngineLocal.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineLinuxSocketsUDP.o:   $(sourceDir)NetEngineLinuxSocketsUDP.cpp $(sourceDir)NetEngineLinuxSocketsUDP.h $(sourceDir)NetEngineLocal.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/InputEngineDummy.o:           $(sourceDir)InputEngineDummy.cpp $(sourceDir)InputEngineDummy.h $(sourceDir)InputEngine.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/InputEngineSDL.o:             $(sourceDir)InputEngineSDL.cpp $(sourceDir)InputEngineSDL.h $(sourceDir)InputEngine.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(sourceDir)linux/NetEngineLinuxSocketsTCP.o:   $(sourceDir)NetEngineLinuxSocketsTCP.cpp $(sourceDir)NetEngineLinuxSocketsTCP.h $(sourceDir)NetEngineLocal.h $(sourceDir)linux/GameEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ -c $<

$(binDir)linux/main:                            $(sourceDir)main.cpp $(sourceDir)linux/Object.o $(sourceDir)linux/TimeEngineDummy.o $(sourceDir)linux/GameEngine.o $(sourceDir)linux/InputEngineDummy.o $(sourceDir)linux/GraphicsEngineDummy.o $(sourceDir)linux/GraphicsEngineSDL.o $(sourceDir)linux/NetEngineDummy.o $(sourceDir)linux/TextEngineDummy.o $(sourceDir)linux/GameNode.o $(sourceDir)linux/InputEngineSDL.o $(sourceDir)linux/TextEngineIOStream.o $(sourceDir)linux/TextEngineSTDIO.o $(sourceDir)linux/GameClient.o $(sourceDir)linux/GameServer.o $(sourceDir)linux/NetEngineLinuxSocketsUDP.o $(sourceDir)linux/NetEngineLocal.o $(sourceDir)linux/NetEngineLinuxSocketsTCP.o $(sourceDir)linux/DerivedObjects.o $(sourceDir)linux/NetEngine.o
	$(CompilerLinux) $(CFLAGS) $(CFLAGSLinux) -o $@ $^

$(binDir)linux/DedicatedServer:                 $(sourceDir)DedicatedServer.cpp $(sourceDir)linux/Object.o $(sourceDir)linux/TimeEngineDummy.o $(sourceDir)linux/GraphicsEngineDummy.o $(sourceDir)linux/GraphicsEngineSDL.o $(sourceDir)linux/NetEngineDummy.o $(sourceDir)linux/InputEngineDummy.o $(sourceDir)linux/GameNode.o $(sourceDir)linux/TextEngineDummy.o $(sourceDir)linux/GameEngine.o $(sourceDir)linux/InputEngineSDL.o $(sourceDir)linux/TextEngineIOStream.o $(sourceDir)linux/TextEngineSTDIO.o $(sourceDir)linux/GameClient.o $(sourceDir)linux/GameServer.o $(sourceDir)linux/NetEngineLinuxSocketsUDP.o $(sourceDir)linux/NetEngineLocal.o $(sourceDir)linux/NetEngineLinuxSocketsTCP.o $(sourceDir)linux/DerivedObjects.o $(sourceDir)linux/NetEngine.o
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
