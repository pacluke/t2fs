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

non_destructive_tests:
	@echo ">>> testes <<< \n"
	@echo "*** identify2 *** \n"
	@gcc -g teste/identify2_test.c -I include -L lib -lt2fs -o bin/identify2_test -Wall
	@./bin/identify2_test
	@echo "\n*** chdir2 e getcwd2 *** \n"
	@gcc -g teste/chdir2_getcwd2_test.c -I include -L lib -lt2fs -o bin/chdir2_getcwd2_test -Wall
	@./bin/chdir2_getcwd2_test
	@echo "\n*** open2, read2, seek2 e close2 *** \n"
	@gcc -g teste/handling_files_test.c -I include -L lib -lt2fs -o bin/handling_files_test -Wall
	@./bin/handling_files_test
	@echo "\n*** opendir2, readdir2, e closedir2 *** \n"
	@gcc -g teste/handling_directories.c -I include -L lib -lt2fs -o bin/handling_directories -Wall
	@./bin/handling_directories

destructive_tests:
	@echo "\n*** opendir2, readdir2, closedir2 e rmdir2 *** \n"
	@gcc -g teste/delete_directories_test.c -I include -L lib -lt2fs -o bin/delete_directories_test -Wall
	@./bin/delete_directories_test
	@echo "\n*** opendir2, readdir2, closedir2 e delete2 *** \n"
	@gcc -g teste/delete_files_test.c -I include -L lib -lt2fs -o bin/delete_files_test -Wall
	@./bin/delete_files_test

shell:
	@echo "\n*** shell dado pelo professor *** \n"
	@gcc -g exemplo/main.c -I include -L lib -lt2fs -o bin/test_main -Wall
	@./bin/test_main


test: compile library non_destructive_tests destructive_tests shell

