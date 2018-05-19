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
	gcc  -g -c src/t2fs.c -I include -o bin/t2fs.o -Wall

library:
	ar crs lib/libt2fs.a bin/t2fs.o lib/apidisk.o lib/bitmap2.o

clean:
	cp lib/apidisk.o bin/
	cp lib/bitmap2.o bin/
	rm -rf lib/*
	cp bin/apidisk.o lib/
	cp bin/bitmap2.o lib/
	rm -rf bin/*

com_test:
	gcc -g testes/teste.c -I include -L lib -lt2f2 -o testes/teste
	./testes/teste

test: compile library com_test clean

