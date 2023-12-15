INPUT_FILE := ./modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell sed 's/$$/.cpp/' "$(INPUT_FILE)")
SOURCES += $(wildcard utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  $(foreach dir,$(DIRS), -I$(dir)/inc)

include avr.mk
include tools.mk

.PHONY: all clean build 

all:build-avr style-check
	@echo -n "[Doxygen] : "
	@sh $(DOXYGEN_SCRIPT) $(DOXYGEN_CONFIG) $(TREAT_WARN_AS_WARN) 

debug:
	@echo " Includes = $(INC)"
	@echo " Sources = $(SOURCES)"
	@echo " objects = $(AVR_OBJS)"
	@echo " objects dire = $(AVR_OBJDIR)"

# ------------------------------------------
# Rule to build avr for debug and test mode 
# make build-avr
# ------------------------------------------
build-avr: $(AVR_OBJS) style-check
	@$(AVR_GCC) $(AVR_GCCFLAGS) $(AVR_OBJS) ./main.cpp -o $(AVR_ELF_TARGET)
	@$(AVR_OBJ_COPY) $(AVR_OBJ_COPY_OPTS) $(AVR_ELF_TARGET) $(AVR_HEX_TARGET)
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build avr for real applications
# make opt-build-avr
# ------------------------------------------
build-avr-opt:$(AVR_OBJS)
	@$(AVR_GCC) $(AVR_OPT_CCFLAGS) $(AVR_OBJS) ./main.cpp -o $(AVR_ELF_TARGET)
	@$(AVR_OBJ_COPY) $(AVR_OBJ_COPY_OPTS) $(AVR_ELF_TARGET) $(AVR_HEX_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

compile-hardware-test:
	@$(AVR_GCC) $(AVR_OPT_CCFLAGS) $(AVR_OBJS) $(test) -o $(dir $(test))/$(name).elf
# --------------------------------------------------------
# Rule to compile test 
# make compile-test src=path/to/main/file target=test_name
# --------------------------------------------------------
compile-test:$(AVR_OBJS)
	$(AVR_GCC) $(AVR_GCC_TEST_FLAGS) $(AVR_OBJS) $(src) -o $(target).testelf
	@echo "\n[Makefile]: Test compiled successfully."

# ------------------------------------------
# Rule to run regression tests
# There are two modes depending on filter value:
# 1] Run all regressions
# 	 make run-regressions filter=all 
# 2] Run specific regression test
#	 make run-regressions filter=regression-tests/regression-tests/test keep=1
#	 to keep output files
# ------------------------------------------
run-regressions: $(AVR_OBJDIR) $(build-avr)
	@echo -n "[Regression-tests] : Run Regressions\n"
ifeq ($(filter), all)	
	@sh -e $(REGRESSION_ALL_TEST_SCRIPT) 
else
	@sh -e $(REGRESSION_TEST_SCRIPT) -d $(filter) -k $(keep)
endif	
	@echo "\n[Makefile][Regression-Testing] : Tests have been run successfully."

# ----------------------------------------------------
# Rule to run style check rules in sources and headers
# make style-check
# ----------------------------------------------------
style-check:
	@echo -n "[Style-check] : "
	@sh $(STYLE_CHECK_SCRIPT) . $(STYLE_CHECK_RULES)

# ----------------------------------------------------
# Rule to run doxygen and generate warnings for lines
# that not be documented
# make doxygen
# ----------------------------------------------------
doxygen:
	@echo -n "[Doxygen] : "
	@sh $(DOXYGEN_SCRIPT) $(DOXYGEN_CONFIG) $(TREAT_WARN_AS_ERROR)

# ----------------------------------------------------
# Rule clean all generated files through build process
# make clean
# ----------------------------------------------------
clean:
	@find . -name "*.o" -type f -delete
	@rm -rf .build
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf avr
	@rm -rf .build
	@find . -name "*.o" -type f -delete
	@find tests/hardware/ -name "*.elf" -type f -delete