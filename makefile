CC = g++ -g -Wall -std=c++17
TARGET = BentKnee.exe

ROOT = .
BUILD = build
LIB = lib
SRC = ${ROOT}/src
COMMON = ${SRC}/common
TYPES = ${SRC}/types
DATA_ARCH = ${SRC}/dataArchitecture
ANALYTICS = ${SRC}/analytics
TECHNICALS = ${SRC}/technicals

INT_BUILD = $(BUILD)/internal
INT_FILES = $(TYPES)/include/Definitions.h \
            $(TYPES)/include/DataType1.h \
            $(TYPES)/include/DataType3.h \
            $(COMMON)/include/ClassTemplate.h \
            $(COMMON)/include/ContainerTemplate.h \
            $(DATA_ARCH)/include/DateEngine.h  \
            $(DATA_ARCH)/include/Price.h \
            $(DATA_ARCH)/include/PriceContainer.h \
            $(ANALYTICS)/include/SmoothingEngine.h \
            $(TECHNICALS)/chaikinMoneyFlow/include/ChaikinMoneyFlowEngine.h \
            $(TECHNICALS)/chaikinMoneyFlow/include/ChaikinMoneyFlow.h \

buildInternal: $(INT_FILES)
	@echo
	@echo "-----------------------------------"
	@echo "Beginning INTERNAL build"
	@echo "-----------------------------------"
	@mkdir -p $(INT_BUILD)
	@for inc in $^ ; do \
	    src=`echo $${inc} | sed 's:/include/:/source/:g' | sed 's:\.h:.cpp:g'`; \
	    obj=`echo $${inc} | sed -e 's:^.*/include/:$(INT_BUILD)/:g' | sed 's:\.h:.o:g'`; \
	    cp $${inc} $(INT_BUILD); \
	    if [ -f "$${src}" ]; then \
	        echo "Building target: $${obj}"; \
	        $(CC) -c $${src} -o $${obj} -I $(INT_BUILD); \
	    fi \
	done 

EXT = external
EXT_BUILD = $(BUILD)/external
EXT_ALGLIB = $(EXT)/alglib
EXT_ALGLIB_FILES = $(EXT_ALGLIB)/include/ap.h \
	           $(EXT_ALGLIB)/include/alglibinternal.h \
	           $(EXT_ALGLIB)/include/alglibmisc.h \
	           $(EXT_ALGLIB)/include/linalg.h \
	           $(EXT_ALGLIB)/include/solvers.h \
	           $(EXT_ALGLIB)/include/interpolation.h
	
buildExternal: buildAlglib \
	       lib/alglibSlim.so

buildAlglib: $(EXT_ALGLIB_FILES)
	@echo
	@echo "-----------------------------------"
	@echo "Beginning EXTERNAL build: Alglib"
	@echo "-----------------------------------"
	@mkdir -p $(EXT_BUILD)
	@for inc in $^ ; do \
	    src=`echo $${inc} | sed 's:/include/:/source/:g' | sed 's:\.h:.cpp:g'`; \
	    obj=`echo $${inc} | sed -e 's:^.*/include/:$(EXT_BUILD)/:g' | sed 's:\.h:.o:g'`; \
	    cp $${inc} $(EXT_BUILD); \
	    if [ -f "$${src}" ]; then \
	        echo "Building target: $${obj}"; \
	        $(CC) -fPIC -c $${src} -o $${obj} -I $(EXT_BUILD); \
	    fi \
	done
	
lib/alglibSlim.so: $(build/external/alglib/%.o)
	@echo
	@echo "-----------------------------------"
	@echo "Building library: alglibSlim.so"
	@echo "-----------------------------------"
	@mkdir -p $(LIB)
	@$(CC) -shared $^ -o $@ -Wl,--no-whole-archive

cleanInternal:
	@echo
	@echo "-----------------------------------"
	@echo "Cleaning Internal Build Directories"
	@echo "-----------------------------------"
	@rm -rf $(INT_BUILD)
		
cleanExternal:
	@echo
	@echo "-----------------------------------"
	@echo "Cleaning External Build Directories"
	@echo "-----------------------------------"
	@rm -rf $(EXT_BUILD)
	
clean:
	@echo
	@echo "-----------------------------------"
	@echo "Cleaning Build Directory"
	@echo "-----------------------------------"
	@rm -rf $(BUILD)
	@echo
	@echo "-----------------------------------"
	@echo "Cleaning Library Directory"
	@echo "-----------------------------------"
	@rm -rf $(LIB)

buildApplication:
	@echo
	@echo "-----------------------------------"
	@echo "Beginning Application build"
	@echo "-----------------------------------"
	ls $(EXT_BUILD)
	$(CC) -o TestExec src/main.cpp -I $(EXT_BUILD) -L lib -l :alglibSlim.so

TestExec: src/main.cpp 
	$(CC) -o TestExec src/main.cpp build/external/*.o -I build/external

all: buildExternal \
     buildInternal
