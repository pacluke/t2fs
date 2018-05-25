#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
#include "../include/aux2.h"

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

int init_superblock(){
	SUPERBLOCK = (struct t2fs_superbloco *)malloc(sizeof(struct t2fs_superbloco));	
	if(SUPERBLOCK)
		return SUCCESS;
	return ERROR;
}

int init_current_block(){
	CURRENT_BLOCK = (unsigned char*)malloc(sizeof(unsigned char)*1024);
	if(CURRENT_BLOCK)
		return SUCCESS;
	return ERROR;
}

int init_root_i_node(){
	ROOT_I_NODE = (struct t2fs_inode *)malloc(sizeof(struct t2fs_inode));	
	if(ROOT_I_NODE)
		return SUCCESS;
	return ERROR;
}

int init_current_i_node(){
	CURRENT_I_NODE = (struct t2fs_inode *)malloc(sizeof(struct t2fs_inode));	
	if(CURRENT_I_NODE)
		return SUCCESS;
	return ERROR;
}

int load_superblock(){
	unsigned char buffer[SECTOR_SIZE];

	if (read_sector(0, buffer) == 0){
		// set id
		memcpy(&(SUPERBLOCK->id), 
			&buffer[LIB_ID_OFFSET], LIB_ID);
		// set version
		memcpy(&(SUPERBLOCK->version),
			&buffer[LIB_VERSION_OFFSET], LIB_VERSION);
		// set superblock size
		memcpy(&(SUPERBLOCK->superblockSize),
			&buffer[SUPER_BLOCK_SIZE_OFFSET], SUPER_BLOCK_SIZE);
		// set free blocks bitmap size
		memcpy(&(SUPERBLOCK->freeBlocksBitmapSize),
			&buffer[FREE_BLOCKS_BITMAP_SIZE_OFFSET], FREE_BLOCKS_BITMAP_SIZE);
		// set free i-node bitmap size
		memcpy(&(SUPERBLOCK->freeInodeBitmapSize),
			&buffer[FREE_INODE_BITMAP_SIZE_OFFSET], FREE_INODE_BITMAP_SIZE);
		// set i-node area size
		memcpy(&(SUPERBLOCK->inodeAreaSize),
			&buffer[INODE_AREA_SIZE_OFFSET], INODE_AREA_SIZE);
		// set block size
		memcpy(&(SUPERBLOCK->blockSize),
			&buffer[BLOCK_SIZE_OFFSET], BLOCK_SIZE);
		// set disk size
		memcpy(&(SUPERBLOCK->diskSize),
			&buffer[DISK_SIZE_OFFSET], DISK_SIZE);
		return SUCCESS;
	}
	return ERROR;
}

int init_all(){
	if((init_root_i_node() + init_current_i_node() + init_current_block() + init_superblock()) == SUCCESS)
		if(load_superblock() == SUCCESS)
			return SUCCESS;
	return ERROR;
}

void print_superblock(){

	printf("LIBRARY ID:\t\t %c%c%c%c\n",
		SUPERBLOCK->id[0],SUPERBLOCK->id[1],SUPERBLOCK->id[2],SUPERBLOCK->id[3]);

	printf("LIBRARY VERSION:\t 0x%X\n",
		SUPERBLOCK->version);

	printf("SUPERBLOCK SIZE:\t (hex) %X \t (dec) %u\n",
		SUPERBLOCK->superblockSize, SUPERBLOCK->superblockSize);

	printf("FREE BLOCKS BITMAP SIZE: (hex) %X \t (dec) %u\n",
		SUPERBLOCK->freeBlocksBitmapSize, SUPERBLOCK->freeBlocksBitmapSize);

	printf("FREE I-NODE BITMAP SIZE: (hex) %X \t (dec) %u\n",
		SUPERBLOCK->freeInodeBitmapSize, SUPERBLOCK->freeInodeBitmapSize);

	printf("I-NODE AREA SIZE:\t (hex) %X \t (dec) %u\n",
		SUPERBLOCK->inodeAreaSize, SUPERBLOCK->inodeAreaSize);

	printf("BLOCK SIZE:\t\t (hex) %X \t (dec) %u\n",
		SUPERBLOCK->blockSize, SUPERBLOCK->blockSize);

	printf("DISK SIZE:\t\t (hex) %X \t (dec) %u BLOCKS or %u SECTORS\n",
		SUPERBLOCK->diskSize, SUPERBLOCK->diskSize, SUPERBLOCK->diskSize*4);

	printf("\n");
}

int load_block(int block){

	unsigned char buffer[SECTOR_SIZE];
	int sectors = (block * SUPERBLOCK->blockSize);

	if(read_sector(sectors, buffer) == 0)
		memcpy(&CURRENT_BLOCK[0], &buffer[0], SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+1, buffer) == 0)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*1], &buffer[0],SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+2, buffer) == 0)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*2], &buffer[0],SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+3, buffer) == 0)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*3], &buffer[0],SECTOR_SIZE);
	else 
		return ERROR;

	return SUCCESS;
}

int get_i_node(int i_node_n, struct t2fs_inode *i_node){

	int position = i_node_n*(SUPERBLOCK->inodeAreaSize);

	if(i_node){
		memcpy(&(i_node->blocksFileSize),
			&CURRENT_BLOCK[position+BLOCKS_FILE_SIZE_OFFSET], BLOCKS_FILE_SIZE);

		memcpy(&(i_node->bytesFileSize),
			&CURRENT_BLOCK[position+BYTES_FILE_SIZE_OFFSET], 	BYTES_FILE_SIZE);

		memcpy(&(i_node->dataPtr[0]),
			&CURRENT_BLOCK[position+(DATA_POINTER_OFFSET)], (DATA_POINTER/2));

		memcpy(&(i_node->dataPtr[1]),
			&CURRENT_BLOCK[position+(DATA_POINTER_OFFSET+4)], (DATA_POINTER/2));

		memcpy(&(i_node->singleIndPtr),
			&CURRENT_BLOCK[position+SINGLE_IND_POINTER_OFFSET], SINGLE_IND_POINTER);

		memcpy(&(i_node->doubleIndPtr),
			&CURRENT_BLOCK[position+DOUBLE_IND_POINTER_OFFSET], DOUBLE_IND_POINTER);

		memcpy(&(i_node->reservado),
			&CURRENT_BLOCK[position+RESERVED_OFFSET], RESERVED);

		return SUCCESS;
	}

	return ERROR;
}

void print_i_node(struct t2fs_inode *i_node){
	printf("BLOCKS FILE SIZE\t %u\n", i_node->blocksFileSize);
	printf("BYTES FILE SIZE:\t %u\n", i_node->bytesFileSize);
	printf("1ST DATA POINTER:\t %u\n", i_node->dataPtr[0]);
	printf("2ND DATA POINTER:\t %u\n", i_node->dataPtr[1]);
	printf("SINGLE INDIRECT POINTER: %u\n", i_node->singleIndPtr);
	printf("DOUBLE INDIRECT POINTER: %u\n", i_node->doubleIndPtr);
	printf("\n");
}


void print_record(struct t2fs_record *record){
	printf("TYPE VALUE: \t0x0%X (0x01 FILE, 0x02 DIR)\n" ,record->TypeVal);
	printf("NAME: \t\t%s\n", record->name);
	printf("I-NODE NUMBER:  %d\n", record->inodeNumber);
	printf("\n");
}


int read_i_node_content(struct t2fs_inode *dir){
	struct t2fs_record *record;
	record = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

	if(CURRENT_I_NODE->blocksFileSize > 0){
		if (load_block(dir->dataPtr[0]) == SUCCESS){
			for(int i = 0; i < 16; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
					print_record(record);
				}
			}
		}
		return SUCCESS;
	}
	if(CURRENT_I_NODE->blocksFileSize > 1){
		if (load_block(dir->dataPtr[1]) == SUCCESS){
			if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
				for(int i = 0; i < 16; i++) {
					memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
					print_record(record);
				}
			}
		}
		return SUCCESS;
	}
	if(dir->blocksFileSize > 2){
		printf("TODO >>> INDIRECT READING\n");
		return SUCCESS;
	}
	return ERROR;
}