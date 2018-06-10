#
# Makefile ESQUELETO
#
# DEVE ter uma regra "all" para geração da biblioteca
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: compile library

compile:
	@echo "*** compilando\n"
	@gcc  -g -c src/t2fs.c -I include -o bin/t2fs.o -Wall
	@gcc  -g -c src/aux2.c -I include -o bin/aux2.o -Wall

library:
	@echo "*** gerando biblioteca\n"
	@ar crs lib/libt2fs.a bin/t2fs.o bin/aux2.o lib/apidisk.o lib/bitmap2.o

clean:
	@echo "*** limpeza de objetos\n"
	@cp lib/apidisk.o bin/
	@cp lib/bitmap2.o bin/
	@rm -rf lib/*
	@cp bin/apidisk.o lib/
	@cp bin/bitmap2.o lib/
	@rm -rf bin/*

test_main:
	@echo ">>> testes <<< \n"
	@echo "*** identify2 *** \n"
	@gcc -g exemplo/identify2_test.c -I include -L lib -lt2fs -o bin/identify2_test -Wall
	@./bin/identify2_test
	@echo "\n*** chdir2 e getcwd2 *** \n"
	@gcc -g exemplo/chdir2_getcwd2_test.c -I include -L lib -lt2fs -o bin/chdir2_getcwd2_test -Wall
	@./bin/chdir2_getcwd2_test
	@echo "\n*** open2, read2, seek2 e close2 *** \n"
	@gcc -g exemplo/handling_files_test.c -I include -L lib -lt2fs -o bin/handling_files_test -Wall
	@./bin/handling_files_test
	@gcc -g exemplo/main.c -I include -L lib -lt2fs -o bin/test_main -Wall
	@./bin/test_main

# com_test:
# 	gcc -g testes/teste.c -I include -L lib -lt2f2 -o testes/teste
# 	./testes/teste

test: compile library test_main

