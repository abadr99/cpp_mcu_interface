# ---- STYLE CHECKING 
STYLE_CHECK_PATH   = scripts/style-checking
STYLE_CHECK_SCRIPT = $(STYLE_CHECK_PATH)/style-check.sh
STYLE_CHECK_RULES  = $(STYLE_CHECK_PATH)/rules-scripts

# ---- DOXYGEN OPTIONS
DOXYGEN_SCRIPT = scripts/doxygen/doxygen.sh
TREAT_WARN_AS_ERROR = YES
TREAT_WARN_AS_WARN = NO
DOXYGEN_CONFIG = ./doxygen.cnf

# ---- TESTING 
REGRESSION_TEST_SCRIPT 	   = scripts/testing/run-regressions.sh
REGRESSION_ALL_TEST_SCRIPT = scripts/testing/run-all-regressions.sh
CLEAN_HW_TESTS_SCRIPTS = scripts/testing/clean-hw-tests.sh