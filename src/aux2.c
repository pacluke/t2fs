#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include "../include/bitmap2.h"
#include "../include/aux2.h"

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

int init_records_list(){

	FILES = malloc(sizeof(RECORDS_HANDLE) * 10);
	DIRECTORIES = malloc(sizeof(RECORDS_HANDLE) * 10);

	for (int i = 0; i < 10; ++i)
	{
		FILES[i].record_info = malloc(sizeof(struct t2fs_record));
		FILES[i].record_info->TypeVal = TYPEVAL_INVALIDO;
		FILES[i].record_info->inodeNumber = -1;
		strcpy(FILES[i].record_info->name, "indef");
		FILES[i].seek_pointer = 0;

		DIRECTORIES[i].record_info = malloc(sizeof(struct t2fs_record));
		DIRECTORIES[i].record_info->TypeVal = TYPEVAL_INVALIDO;
		DIRECTORIES[i].record_info->inodeNumber = -1;
		strcpy(DIRECTORIES[i].record_info->name, "indef");
		DIRECTORIES[i].seek_pointer = -1;
	}

	return SUCCESS;
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

	if(read_sector(sectors, buffer) == SUCCESS)
		memcpy(&CURRENT_BLOCK[0], &buffer, SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+1, buffer) == SUCCESS)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*1], &buffer,SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+2, buffer) == SUCCESS)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*2], &buffer,SECTOR_SIZE);
	else 
		return ERROR;

	if(read_sector (sectors+3, buffer) == SUCCESS)
		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*3], &buffer,SECTOR_SIZE);
	else 
		return ERROR;

	return SUCCESS;
}

int get_i_node(int i_node_n, struct t2fs_inode *i_node){

	int position = i_node_n*(32);
	int inode_block = (SUPERBLOCK->superblockSize + SUPERBLOCK->freeBlocksBitmapSize + SUPERBLOCK->freeInodeBitmapSize);

	if (load_block(inode_block) == SUCCESS){
		if(i_node){
			memcpy(&(i_node->blocksFileSize),
				&CURRENT_BLOCK[position+BLOCKS_FILE_SIZE_OFFSET], BLOCKS_FILE_SIZE);

			memcpy(&(i_node->bytesFileSize),
				&CURRENT_BLOCK[position+BYTES_FILE_SIZE_OFFSET], BYTES_FILE_SIZE);

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

	if(dir->blocksFileSize > 0){
		if (load_block(dir->dataPtr[0]) == SUCCESS){
			for(int i = 0; i < MAX_RECORDS; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
					print_record(record);
				}
			}
		}
		return SUCCESS;
	}
	if(dir->blocksFileSize > 1){
		if (load_block(dir->dataPtr[1]) == SUCCESS){
			if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
				for(int i = 0; i < MAX_RECORDS; i++) {
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

char *head_dir(char *path){
	char *path_copy = malloc(sizeof(char)*strlen(path));
	char *result;

	strcpy(path_copy, path);
	result = strtok(path_copy, "/");

	return result;
}

char *tail_dir(char *path){
	char *head;
	head = head_dir(path);

	if ((strlen(path)-1 == strlen(head)) || (strlen(path) == strlen(head))){
		return NULL;
	}

	int head_size = strlen(head);
	int tail_size = strlen(path) - head_size+1;

	if ((path[0] == '/')){
		head_size+=1;
		// tail_size-=1;
	}
	if ((path[strlen(path)-1] == '/')){
		head_size+=1;
		// tail_size-=1;
		// printf("aaaaaa\n");
	}

	char *tail = malloc(sizeof(char)*tail_size);

	int tail_count = 0;

	for (int i = head_size; i < strlen(path); ++i)
	{
		tail[tail_count] = path[i];
		tail_count++;
	}

	tail[tail_count] = '\0';
	return tail;
}


struct t2fs_record *find_file(struct t2fs_inode *dir_inode, char* filename){

	struct t2fs_record *file;
	char *name = head_dir(filename);

	// printf("\n\n\n\n\n\n\n");
	// printf("%s\n", name);
	// read_i_node_content(dir_inode);

	file = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

	if(dir_inode->blocksFileSize > 0){
		if (load_block(dir_inode->dataPtr[0]) == SUCCESS){
			for (int i = 0; i < MAX_RECORDS; ++i){
				memcpy(file, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(file->TypeVal == TYPEVAL_REGULAR && ((strcmp(name, file->name) == SUCCESS))){
					return file;
				}
				else if (file->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, file->name) == SUCCESS)){
					char *tail = tail_dir(filename);
					if (tail != NULL){
						struct t2fs_inode *next_inode;
						next_inode = (struct t2fs_inode *) malloc(sizeof(struct t2fs_inode));
						if (get_i_node(file->inodeNumber, next_inode) == SUCCESS){
							return find_file(next_inode, tail_dir(filename));
						}
					}
				}
			}
		}
		else {
			return NULL;
		}
	}
	if(dir_inode->blocksFileSize > 1){
		if (load_block(dir_inode->dataPtr[1]) == SUCCESS){
			for (int i = 0; i < MAX_RECORDS; ++i){
				memcpy(file, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(file->TypeVal == TYPEVAL_REGULAR && ((strcmp(name, file->name) == SUCCESS))){
					return file;
				}
				else if (file->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, file->name) == SUCCESS)){
					char *tail = tail_dir(filename);
					if (tail != NULL){
						struct t2fs_inode *next_inode;
						next_inode = (struct t2fs_inode *) malloc(sizeof(struct t2fs_inode));
						if (get_i_node(file->inodeNumber, next_inode) == SUCCESS){
							return find_file(next_inode, tail_dir(filename));
						}
					}
				}
			}
		}
		else {
			return NULL;
		}
	}

	if(dir_inode->blocksFileSize > 2){
		printf("TODO >>> INDIRECT READING\n");
	}

	if(dir_inode->blocksFileSize > SUPERBLOCK->blockSize+2){
		printf("TODO >>> DOUBLE INDIRECT READING\n");
	}

	return NULL;
}

struct t2fs_record *find_directory(struct t2fs_inode *dir_inode, char* dir_name){

	struct t2fs_record *directory;
	char *name = head_dir(dir_name);

	// printf("\n\n\n\n\n\n\n");
	// printf("%s\n", name);
	// printf("%s\n", tail_dir(dir_name));
	// read_i_node_content(dir_inode);

	directory = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

	if(dir_inode->blocksFileSize > 0){
		if (load_block(dir_inode->dataPtr[0]) == SUCCESS){
			for (int i = 0; i < MAX_RECORDS; ++i){
				memcpy(directory, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));

				// printf("???1 %d\n", directory->TypeVal == TYPEVAL_DIRETORIO);
				// printf("???2 %d\n", (strcmp(name, directory->name) == SUCCESS));
				// printf("???3 %d\n", (tail_dir(dir_name) == NULL));

				if(directory->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, directory->name) == SUCCESS) && (tail_dir(dir_name) == NULL)){
					// printf("eita\n");
					return directory;
				}


				else if (directory->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, directory->name) == SUCCESS)){
					char *tail = tail_dir(dir_name);
					if (tail != NULL){
						struct t2fs_inode *next_inode;
						next_inode = (struct t2fs_inode *) malloc(sizeof(struct t2fs_inode));
						if (get_i_node(directory->inodeNumber, next_inode) == SUCCESS){
							return find_directory(next_inode, tail_dir(dir_name));
						}
					}
				}
			}
		}

		else {
			return NULL;
		}
	}

	if(dir_inode->blocksFileSize > 1){
		if (load_block(dir_inode->dataPtr[1]) == SUCCESS){
			for (int i = 0; i < MAX_RECORDS; ++i){
				memcpy(directory, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));

				// printf("???1 %d\n", directory->TypeVal == TYPEVAL_DIRETORIO);
				// printf("???2 %d\n", (strcmp(name, directory->name) == SUCCESS));
				// printf("???3 %d\n", (tail_dir(dir_name) == NULL));

				if(directory->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, directory->name) == SUCCESS) && (tail_dir(dir_name) == NULL)){
					// printf("eita\n");
					return directory;
				}


				else if (directory->TypeVal == TYPEVAL_DIRETORIO && (strcmp(name, directory->name) == SUCCESS)){
					char *tail = tail_dir(dir_name);
					if (tail != NULL){
						struct t2fs_inode *next_inode;
						next_inode = (struct t2fs_inode *) malloc(sizeof(struct t2fs_inode));
						if (get_i_node(directory->inodeNumber, next_inode) == SUCCESS){
							return find_directory(next_inode, tail_dir(dir_name));
						}
					}
				}
			}
		}

		else {
			return NULL;
		}
	}

	if(dir_inode->blocksFileSize > 2){
		printf("TODO >>> INDIRECT READING\n");
	}

	if(dir_inode->blocksFileSize > SUPERBLOCK->blockSize+2){
		printf("TODO >>> DOUBLE INDIRECT READING\n");
	}

	return NULL;
}

char *concat_dirs(char *dir1, char *dir2){

	return strcat(strcat(dir1, "/"), dir2);
}


struct t2fs_record *get_record_by_inode_number(int i_node_number, struct t2fs_inode *dir){
	struct t2fs_record *record;
	record = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

	if(dir->blocksFileSize > 0){
		if (load_block(dir->dataPtr[0]) == SUCCESS){
			for(int i = 0; i < MAX_RECORDS; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if((record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO) && 
					(strcmp(record->name, "..") != SUCCESS) && (strcmp(record->name, ".") != SUCCESS) &&
					(record->inodeNumber == i_node_number)){
					// print_record(record);
					return record;
				}
			}
		}
	}
	
	if(dir->blocksFileSize > 1){
		if (load_block(dir->dataPtr[1]) == SUCCESS){
			for(int i = 0; i < MAX_RECORDS; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if((record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO) && 
					(strcmp(record->name, "..") != SUCCESS) && (strcmp(record->name, ".") != SUCCESS) &&
					(record->inodeNumber == i_node_number)){
					// print_record(record);
					return record;
				}
			}
		}
	}
	if(dir->blocksFileSize > 2){
		printf("TODO >>> INDIRECT READING\n");
		return SUCCESS;
	}

	return NULL;
}

char *root_to_current(struct t2fs_inode *work_inode){

	struct t2fs_record *father_record = malloc(sizeof(struct t2fs_record));
	struct t2fs_record *self_record = malloc(sizeof(struct t2fs_record));
	struct t2fs_record *aux = malloc(sizeof(struct t2fs_record));

	struct t2fs_inode *father_inode = malloc(sizeof(struct t2fs_inode));
	struct t2fs_inode *self_inode = malloc(sizeof(struct t2fs_inode));

	if (father_record && self_record && aux && father_inode && self_inode)
	{

		int father_inode_number = -1;
		int self_inode_number = -1;

		char *father = "..";
		char *self = ".";

		char *full_path = ""; // = "";
		// printf("FULL PATH: %s\n", full_path);

		father_record = find_directory(work_inode, father);

		if (father_record == NULL){
			return NULL;
		}

		father_inode_number = father_record->inodeNumber;
		// printf("FATHER\n");
		// print_record(father_record);

		self_record = find_directory(work_inode, self);

		if (self_record == NULL){
			return NULL;
		}

		self_inode_number = self_record->inodeNumber;
		// printf("SELF\n");
		// print_record(self_record);

		while(self_inode_number != 0){
			if ((get_i_node(father_inode_number, father_inode) == ERROR) ||
			(get_i_node(self_inode_number, self_inode) == ERROR)) {
				return NULL;
			}

			// printf("SELF w/ NAME\n");

			aux = get_record_by_inode_number(self_inode_number, father_inode);

			if (aux == NULL) {
				return NULL;
			}

			// printf("%s\n", aux->name);
			// printf("ADDING: %s\n", aux->name);
			full_path = concat_dirs(aux->name, full_path);
			// printf("FULL PATH: %s\n", full_path);

			father_record = find_directory(father_inode, father);

			if (father_record == NULL){
				return NULL;
			}

			father_inode_number = father_record->inodeNumber;
			// printf("FATHER\n");
			// print_record(father_record);

			self_record = find_directory(father_inode, self);

			if (self_record == NULL){
				return NULL;
			}

			self_inode_number = self_record->inodeNumber;
			// printf("SELF\n");
			// print_record(self_record);
		}

		char *temp = malloc(sizeof(char)*(strlen(full_path) + 2));
		strcat(temp, "/");
		strcat(temp, full_path);
		// printf("FULL PATH: %s\n", temp);
		return temp;
	}

	return NULL;
}

int get_first_free_bitmap(int data_or_inode){

	int first_free = 0;

	while(getBitmap2(data_or_inode, first_free) == 1){
		first_free++;
	}

	return first_free;

}

int write_block(int block){

	unsigned char buffer[SECTOR_SIZE];
	int sectors = (block * SUPERBLOCK->blockSize);

	memcpy(&buffer, &CURRENT_BLOCK[0], SECTOR_SIZE);
	if(write_sector(sectors, buffer) != SUCCESS){
		return ERROR;
	}
	
	memcpy(&buffer, &CURRENT_BLOCK[SECTOR_SIZE*1], SECTOR_SIZE);
	if(write_sector(sectors+1, buffer) != SUCCESS){
		return ERROR;
	}
	
	memcpy(&buffer, &CURRENT_BLOCK[SECTOR_SIZE*2], SECTOR_SIZE);
	if(write_sector(sectors+2, buffer) != SUCCESS){
		return ERROR;
	}

	memcpy(&buffer, &CURRENT_BLOCK[SECTOR_SIZE*3], SECTOR_SIZE);
	if(write_sector(sectors+3, buffer) != SUCCESS){
		return ERROR;
	}

	return SUCCESS;
}

int init_new_inode(struct t2fs_inode *new_inode){

	new_inode->blocksFileSize = 0;
	new_inode->bytesFileSize = 0;
	new_inode->dataPtr[0] = INVALID_PTR;
	new_inode->dataPtr[1] = INVALID_PTR;
	new_inode->singleIndPtr = INVALID_PTR;
	new_inode->doubleIndPtr = INVALID_PTR;

	return SUCCESS;
}


int verify_name(char *name, int dir_or_file){

	if (dir_or_file == TYPEVAL_DIRETORIO){
		
	}

	else if(dir_or_file == TYPEVAL_REGULAR){

	}

	return SUCCESS;
}











