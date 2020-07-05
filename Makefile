#BY KAUZARC
#COMPUTER SCIENCE STUDENT

#A MODIFIER EN FONCTION DU BESOIN

#Compilateur
CC = g++

#Deux dossier doivent etre present dans le meme dossier que le Makefile
#Un dossier contenant les sources
SRC_PATH = src
#Nom des dossier des sources et des header
SRC_FOLDER = src
HEADER_FOLDER = header

#Un dossier qui servira a stocker les fichier entre la compilation et le link
BUILD_PATH = build

#Entree de l'aplication
MAIN = main

#Les extension des fichiers
SRC_EXT = cpp
BUILD_EXT = o

#Differentes option de compilation
#et option de link pour les librairies
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs

#Le nom de l'executable
EXEC = app

#Debug option
DEBUG_FOLDER = debug
DBGCFLAGS = -g -O0 -DDEBUG

#Release option
RELEASE_FOLDER = release
RELCFLAGS = -O2 -DNDEBUG

#################################################################
#NE PAS MODIFIER LA SUITE !
#################################################################

SRC:= $(wildcard $(SRC_PATH)/$(SRC_FOLDER)/*.$(SRC_EXT))

DBEXEC = $(BUILD_PATH)/$(DEBUG_FOLDER)/$(EXEC)
DBOBJ:= $(SRC:$(SRC_PATH)/$(SRC_FOLDER)/%.$(SRC_EXT)=$(BUILD_PATH)/$(DEBUG_FOLDER)/%.$(BUILD_EXT))
DBOBJ:= $(DBOBJ) $(BUILD_PATH)/$(DEBUG_FOLDER)/$(MAIN).$(BUILD_EXT)

REEXEC = $(BUILD_PATH)/$(RELEASE_FOLDER)/$(EXEC)
REOBJ:= $(SRC:$(SRC_PATH)/$(SRC_FOLDER)/%.$(SRC_EXT)=$(BUILD_PATH)/$(RELEASE_FOLDER)/%.$(BUILD_EXT))
REOBJ:= $(REOBJ) $(BUILD_PATH)/$(RELEASE_FOLDER)/$(MAIN).$(BUILD_EXT)

all: debug

#Release rules
debug: prep $(DBEXEC) dbgcp

$(DBEXEC): $(DBOBJ)
	$(CC) -o $@ $(LDFLAGS) $(DBGCFLAGS) $^

$(BUILD_PATH)/$(DEBUG_FOLDER)/%.$(BUILD_EXT): $(SRC_PATH)/$(SRC_FOLDER)/%.$(SRC_EXT)
	$(CC) -c $^ $(CXXFLAGS) $(DBGCFLAGS) -o $@

$(BUILD_PATH)/$(DEBUG_FOLDER)/%.$(BUILD_EXT): $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) -c $^ $(CXXFLAGS) $(DBGCFLAGS) -o $@

dbgcp:
	cp $(DBEXEC) $(EXEC)

#Debug rules
release:prep $(REEXEC) relcp

$(REEXEC): $(REOBJ)
	$(CC) -o $@ $(LDFLAGS) $(RELCFLAGS) $^

$(BUILD_PATH)/$(RELEASE_FOLDER)/%.$(BUILD_EXT): $(SRC_PATH)/$(SRC_FOLDER)/%.$(SRC_EXT)
	$(CC) -c $^ $(CXXFLAGS) $(RELCFLAGS) -o $@

$(BUILD_PATH)/$(RELEASE_FOLDER)/%.$(BUILD_EXT): $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) -c $^ $(CXXFLAGS) $(RELCFLAGS) -o $@

relcp:
	cp $(REEXEC) $(EXEC)

#Clean
clean:
	rm -f $(BUILD_PATH)/$(DEBUG_FOLDER)/*.$(BUILD_EXT) $(BUILD_PATH)/$(RELEASE_FOLDER)/*.$(BUILD_EXT) $(EXEC)

prep:
	mkdir -p $(BUILD_PATH) $(BUILD_PATH)/$(RELEASE_FOLDER) $(BUILD_PATH)/$(DEBUG_FOLDER)

#Remake
remake: clean all

#Faire "make folder" initialise corectement le projet
folder:
	mkdir $(BUILD_PATH) $(BUILD_PATH)/$(RELEASE_FOLDER) $(BUILD_PATH)/$(DEBUG_FOLDER)
	mkdir $(SRC_PATH) $(SRC_PATH)/$(HEADER_FOLDER) $(SRC_PATH)/$(SRC_FOLDER)
	touch $(SRC_PATH)/$(MAIN).$(SRC_EXT)
	echo $$'#include <iostream>\n\nint main()\n{\n    std::cout << "Hello world !" << std::endl;\nreturn 0;\n}' > $(SRC_PATH)/$(MAIN).$(SRC_EXT)