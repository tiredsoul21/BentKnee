CC = g++
TARGET = bentKnee
OBJECTS = -I build
ROOT = C:/Users/derri/Desktop/Project/CppFirstProgram

# Build all, in order of dependency
#all: CoreArchitecture

# Compile Core architecture objects
#CoreArchitecture: CloneHeaders \
	CommonUtility \
	Definitions \
	ClassTemplate \
	DataScructures \
	ConfigReader \
	TD_APIs \
	TestExec

#CloneHeaders: 
#	cp -f $(CMN_ARCH)/header/* \
#	$(CMN_UTL)/header/* \
#	$(CMN_DEFS)/header/* \
#	$(TD_APIS)/header/* \
#	$(CMN_DATA)/header/* \
#	build/

CMN = src/common
DEFS = src/definitions
DATA_ARCH= src/dataArchitecture

# Build all, in order of dependency
all: CloneHeaders \
	Common \
	Definitions \
	DataArchitecture \
	TestExec

CloneHeaders:
	cp -f $(CMN)/include/* \
	$(DEFS)/include/* \
	$(DATA_ARCH)/include/* \
	build

Common: $(CMN)/source/ClassTemplate.cpp 
	$(CC) -c $(CMN)/source/ClassTemplate.cpp -o build/ClassTemplate.o -I build

Definitions: $(DEFS)/source/typeDefinitions.cpp
	$(CC) -c $(DEFS)/source/typeDefinitions.cpp -o build/typeDefinitions.o -I build

DataArchitecture: Datenum \
	PriceContainer \
	HistoryContainer
Datenum: $(DATA_ARCH)/source/Datenum.cpp
	$(CC) -c $(DATA_ARCH)/source/Datenum.cpp -o build/Datenum.o -I build
PriceContainer: $(DATA_ARCH)/source/PriceContainer.cpp
	$(CC) -c $(DATA_ARCH)/source/PriceContainer.cpp -o build/PriceContainer.o -I build
HistoryContainer: $(DATA_ARCH)/source/HistoryContainer.cpp
	$(CC) -c $(DATA_ARCH)/source/HistoryContainer.cpp -o build/HistoryContainer.o -I build
	
TestExec:  src/main.cpp 
	$(CC) -o TestExec src/main.cpp build/PriceContainer.o build/Datenum.o build/ClassTemplate.o \
	      build/HistoryContainer.o -I build 