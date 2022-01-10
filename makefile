CC = g++ -g -std=c++17
TARGET = bentKnee
OBJECTS = -I build
ROOT = C:/Users/derri/Desktop/Project/CppFirstProgram

CMN = src/common
DATA_ARCH= src/dataArchitecture
TECH = src/technicals
TYPES = src/types
CMF = $(TECH)/chaikinMoneyFlow
ANLYS = src/analytics

# Build all, in order of dependency
all: CloneHeaders \
	Common \
	Types \
	Analytics \
	DataArchitecture \
	Technicals \
	TestExec

CloneHeaders:
	cp -f $(TYPES)/include/* \
	$(CMN)/include/* \
	$(ANLYS)/include/* \
	$(DATA_ARCH)/include/* \
	$(CMF)/include/* \
	build

Common: ClassTemplate 
ClassTemplate: $(CMN)/source/ClassTemplate.cpp 
	$(CC) -c $(CMN)/source/ClassTemplate.cpp -o build/ClassTemplate.o -I build

Types: Definitions \
	DataType1 \
	DataType3
Definitions: $(TYPES)/source/Definitions.cpp
	$(CC) -c $(TYPES)/source/Definitions.cpp -o build/Definitions.o -I build
DataType1: $(TYPES)/source/DataType1.cpp
	$(CC) -c $(TYPES)/source/DataType1.cpp -o build/DataType1.o -I build
DataType3: $(TYPES)/source/DataType3.cpp
	$(CC) -c $(TYPES)/source/DataType3.cpp -o build/DataType3.o -I build

Analytics: SmoothingEngine \
	DerivativeEngine
SmoothingEngine: $(ANLYS)/source/SmoothingEngine.cpp
	$(CC) -c $(ANLYS)/source/SmoothingEngine.cpp -o build/SmoothingEngine.o -I build
DerivativeEngine: $(ANLYS)/source/DerivativeEngine.cpp
	$(CC) -c $(ANLYS)/source/DerivativeEngine.cpp -o build/DerivativeEngine.o -I build

DataArchitecture: DateEngine \
	Price \
	PriceContainer
DateEngine: $(DATA_ARCH)/source/DateEngine.cpp
	$(CC) -c $(DATA_ARCH)/source/DateEngine.cpp -o build/DateEngine.o -I build
Price: $(DATA_ARCH)/source/Price.cpp
	$(CC) -c $(DATA_ARCH)/source/Price.cpp -o build/Price.o -I build
PriceContainer: $(DATA_ARCH)/source/PriceContainer.cpp
	$(CC) -c $(DATA_ARCH)/source/PriceContainer.cpp -o build/PriceContainer.o -I build

Technicals: ChaikinMoneyFlow
	
ChaikinMoneyFlow: ChaikinMoneyFlowEngine \
	ChaikinMoneyFlow
ChaikinMoneyFlowEngine: $(CMF)/source/ChaikinMoneyFlowEngine.cpp 
	$(CC) -c $(CMF)/source/ChaikinMoneyFlowEngine.cpp -o build/ChaikinMoneyFlowEngine.o -I build
ChaikinMoneyFlow: $(CMF)/source/ChaikinMoneyFlow.cpp 
	$(CC) -c $(CMF)/source/ChaikinMoneyFlow.cpp -o build/ChaikinMoneyFlow.o -I build
	
TestExec: src/main.cpp 
	$(CC) -o TestExec src/main.cpp build/Price.o build/DateEngine.o build/ClassTemplate.o \
	      build/PriceContainer.o build/ChaikinMoneyFlow.o build/ChaikinMoneyFlowEngine.o \
	      build/SmoothingEngine.o build/DerivativeEngine.o build/DataType1.o \
	      build/DataType3.o -I build 