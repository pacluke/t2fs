#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
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

int init_superblock();
int init_current_block();
int init_root_i_node();
int init_current_i_node();
int load_superblock();
int init_all();
void print_superblock();
int load_block(int block);
int get_i_node(int i_node_n, struct t2fs_inode *i_node);
void print_i_node(struct t2fs_inode *i_node);
void print_record(struct t2fs_record *record);
int read_i_node_content(struct t2fs_inode *dir);