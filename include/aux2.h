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
#define NAMES "Lucas Flores 00242317\nMatheus Westhelle 00206688\nRodrigo Madruga 00180669\n"
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
extern struct t2fs_record RECORDS[255];
/* ------------------------ */

int init_superblock();
int init_current_block();
int init_root_i_node();
int init_current_i_node();
int init_records_list();
int load_superblock();
int init_all();
void print_superblock();
int load_block(int block);
int get_i_node(int i_node_n, struct t2fs_inode *i_node);
void print_i_node(struct t2fs_inode *i_node);
void print_record(struct t2fs_record *record);
int read_i_node_content(struct t2fs_inode *dir);
char *head_dir(char *path);