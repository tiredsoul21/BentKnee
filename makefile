CC = g++ -g -std=c++17
TARGET = bentKnee
OBJECTS = -I build
ROOT = C:/Users/derri/Desktop/Project/CppFirstProgram

CMN = src/common
DEFS = src/definitions
DATA_ARCH= src/dataArchitecture
TECH = src/technicals
CMF = $(TECH)/chaikinMoneyFlow

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
	$(CMF)/include/* \
	build

Common: ClassTemplate 
ClassTemplate: $(CMN)/source/ClassTemplate.cpp 
	$(CC) -c $(CMN)/source/ClassTemplate.cpp -o build/ClassTemplate.o -I build

Definitions: $(DEFS)/source/typeDefinitions.cpp
	$(CC) -c $(DEFS)/source/typeDefinitions.cpp -o build/typeDefinitions.o -I build

DataArchitecture: DateEngine \
	Price \
	PriceContainer
DateEngine: $(DATA_ARCH)/source/DateEngine.cpp
	$(CC) -c $(DATA_ARCH)/source/DateEngine.cpp -o build/DateEngine.o -I build
Price: $(DATA_ARCH)/source/Price.cpp
	$(CC) -c $(DATA_ARCH)/source/Price.cpp -o build/Price.o -I build
PriceContainer: $(DATA_ARCH)/source/PriceContainer.cpp
	$(CC) -c $(DATA_ARCH)/source/PriceContainer.cpp -o build/PriceContainer.o -I build

TestExec: src/main.cpp 
	$(CC) -o TestExec src/main.cpp build/Price.o build/DateEngine.o build/ClassTemplate.o \
	      build/PriceContainer.o -I build 