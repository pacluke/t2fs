#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
/* ************************ */

/* ------------------------ */
#define ERROR -10 //error code
#define SUCCESS 0	//sucess code
/* ------------------------ */
#define TRUE 1
#define FALSE 0
/* ------------------------ */
#define NAMES "Lucas Flores - 00242317\nMatheus Westhelle - 00206688\nRodrigo Madruga - 00180669\n"
#define N_SIZE 85
/* ------------------------ */

/* ************************ */

/* DEFINES DO SUPERBLOCO */
/* ------------------------ */
#define LIB_ID_OFFSET 0
#define LIB_ID 4
/* ------------------------ */
#define LIB_VERSION_OFFSET 4
#define LIB_VERSION 2
/* ------------------------ */
#define SUPER_BLOCK_SIZE_OFFSET 6
#define SUPER_BLOCK_SIZE 2
/* ------------------------ */
#define FREE_BLOCKS_BITMAP_SIZE_OFFSET 8
#define FREE_BLOCKS_BITMAP_SIZE 2
/* ------------------------ */
#define FREE_INODE_BITMAP_SIZE_OFFSET 10
#define FREE_INODE_BITMAP_SIZE 2
/* ------------------------ */
#define INODE_AREA_SIZE_OFFSET 12
#define INODE_AREA_SIZE 2
/* ------------------------ */
#define BLOCK_SIZE_OFFSET 14
#define BLOCK_SIZE 2
/* ------------------------ */
#define DISK_SIZE_OFFSET 16
#define DISK_SIZE 4
/* ------------------------ */

/* ************************ */

/* DEFINES DO I-NODE */
/* ------------------------ */
#define BLOCKS_FILE_SIZE_OFFSET 0
#define BLOCKS_FILE_SIZE 4
/* ------------------------ */
#define BYTES_FILE_SIZE_OFFSET 4
#define BYTES_FILE_SIZE 4
/* ------------------------ */
#define DATA_POINTER_OFFSET 8
#define DATA_POINTER 8
/* ------------------------ */
#define SINGLE_IND_POINTER_OFFSET 16
#define SINGLE_IND_POINTER 4
/* ------------------------ */
#define DOUBLE_IND_POINTER_OFFSET 20
#define DOUBLE_IND_POINTER 4
/* ------------------------ */
#define RESERVED_OFFSET 24
#define RESERVED 8
/* ------------------------ */

/* ************************ */

/* DEFINES DO DIRETÓRIO/ARQUIVO */
/* ------------------------ */
#define TYPE_VALUE_OFFSET 0
#define TYPE_VALUE 1
/* ------------------------ */
#define DIR_NAME_OFFSET 1
#define DIR_NAME 59
/* ------------------------ */
#define I_NODE_NUMBER_OFFSET 60
#define I_NODE_NUMBER 4
/* ------------------------ */

/* ************************ */

/* NÚMERO DE ARQUIVOS */
/* ------------------------ */
#define MAX_RECORDS (64/4)
/* ------------------------ */

/* ************************ */

/* ESTRUTURA DO SUPERBLOCO */
extern struct t2fs_superbloco *SUPERBLOCK;
/* ------------------------ */

/* ESTRUTURA DO BLOCO ATUAL */
extern unsigned char *CURRENT_BLOCK;
/* ------------------------ */

/* I-NODE ATUAL */
extern struct t2fs_inode *CURRENT_I_NODE;
/* ------------------------ */

/* I-NODE RAIZ */
extern struct t2fs_inode *ROOT_I_NODE;
/* ------------------------ */

/* LISTA DE ARQUIVOS (HANDLE) */
extern RECORDS_HANDLE *FILES;
/* ------------------------ */

/* LISTA DE DIRETORIOS (HANDLE) */
extern RECORDS_HANDLE *DIRECTORIES;
/* ------------------------ */

/* CONTROLE DA INICIAÇÃO DAS ESTRUTURAS */
extern int INIT;
/* ------------------------ */

/*************************************
	Inicia o superbloco
*************************************/
int init_superblock();

/*************************************
	Inicia o bloco atual
*************************************/
int init_current_block();

/*************************************
	Inicia o inode do diretório raiz
*************************************/
int init_root_i_node();

/*************************************
	Inicia o inode de trabalho
*************************************/
int init_current_i_node();

/*************************************
	Inicia as listas de diretórios
	e arquivos abertos.
*************************************/
int init_records_list();

/*************************************
	Carrega o superbloco
*************************************/
int load_superblock();

/*************************************
	Inicia todas as estruturas
	de dados
*************************************/
int init_all();

/*************************************
	Imprime as impressões do
	superbloco
*************************************/
void print_superblock();

/*************************************
	Recebe o número de um bloco
	em block e carrega esse bloco
	em CURRENT_BLOCK
*************************************/
int load_block(int block);

/*************************************
	Recebe um numero de inode em
	i_node_n e carrega o inode em
	i_node
*************************************/
int get_i_node(int i_node_n, struct t2fs_inode *i_node);

/*************************************
	Imprime na tela o conteúdo de i_node
*************************************/
void print_i_node(struct t2fs_inode *i_node);

/*************************************
	Imprime na tela o conteúdo de record
*************************************/
void print_record(struct t2fs_record *record);

/*************************************
	Lê e imprime na tela os records
	contidos no inode dir
*************************************/
int read_i_node_content(struct t2fs_inode *dir);

/*************************************
	Devolve o primeiro diretório de
	path
*************************************/
char *head_dir(char *path);

/*************************************
	Devolve path sem o priemiro
	diretório
*************************************/
char *tail_dir(char *path);

/*************************************
	Encontra no diretório apontado por
	dir_inode o arquivo de nome filename
*************************************/
struct t2fs_record *find_file(struct t2fs_inode *dir_inode, char* filename);

/*************************************
	Encontra no diretório apontado por
	dir_inode o diretório de nome
	dir_name
*************************************/
struct t2fs_record *find_directory(struct t2fs_inode *dir_inode, char* dir_name);

/*************************************
	Concatena a string1 com a string2
	colocando um '/' entre elas
*************************************/
char *concat_dirs(char *string1, char *string2);

/*************************************
	Devolve o record apontado pelo
	i_node_number procurando a partir do
	inode dir.
*************************************/
struct t2fs_record *get_record_by_inode_number(int i_node_number, struct t2fs_inode *dir);

/*************************************
	Devole o caminho do diretório
	raiz até o diretório apontado
	por work_inode.
*************************************/
char *root_to_current(struct t2fs_inode *work_inode);

/*************************************
	Devole o primeiro bitmap livre no
	bitmap de dados (se data_or_inode = 1)
	ou do bitmap de inodes (se
	data_or_inode = 0)
*************************************/
int get_first_free_bitmap(int data_or_inode);

/*************************************
	Usando a função write_sector
	escreve em um bloco inteiro (4 setores)
	o conteúdo de CURRENT_BLOCK
*************************************/
int write_block(int block);

/*************************************
	Inicia um inode sem informações
*************************************/
int init_new_inode(struct t2fs_inode *new_inode);

/*************************************
	Verifica se o nome em name já existe
	como arquivo ou diretório.
*************************************/
int verify_name(char *name, BYTE dir_or_file, struct t2fs_inode *work_dir);

/*************************************
	Inicia um bloco que não possui 
	nada escrito.
*************************************/
int init_empty_inode_block(int block);

/*************************************
	Cria entradas de diretório para
	colocar em um diretório.
*************************************/
int make_entry(char *filename, struct t2fs_record *father_record, BYTE dir_or_file, int new_inode_number);

/*************************************
	Remove um record (arquivo) de nome
	filename de um diretório.
*************************************/
int remove_file(struct t2fs_inode *dir_inode, char* filename);

/*************************************
	Remove um record (diretorio) de nome
	filename de um diretório.
*************************************/
int remove_directory(struct t2fs_inode *dir_inode, char* dir_name);
