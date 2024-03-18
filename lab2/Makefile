CC=gcc
CFLAGS=-Wall -std=c99 -Ofast
BUILD_DIR=build

all:
	make gsl_example

gsl_example: gsl_example.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I${GSL_PATH}/include -c $< -o $(BUILD_DIR)/$@.o
	$(CC) -L${GSL_PATH}/lib $(BUILD_DIR)/$@.o -lgsl -lgslcblas -lm -o $(BUILD_DIR)/$@ -Wl,-rpath=${GSL_PATH}/lib

run: gsl_example
	./$(BUILD_DIR)/gsl_example

clean:
	rm -rf $(BUILD_DIR)