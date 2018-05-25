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

// /* ************************ */

// /* DEFINES DO SUPERBLOCO */
// /* ------------------------ */
// #define LIB_ID_OFFSET 0
// #define LIB_ID 4
// /* ------------------------ */
// #define LIB_VERSION_OFFSET 4
// #define LIB_VERSION 2
// /* ------------------------ */
// #define SUPER_BLOCK_SIZE_OFFSET 6
// #define SUPER_BLOCK_SIZE 2
// /* ------------------------ */
// #define FREE_BLOCKS_BITMAP_SIZE_OFFSET 8
// #define FREE_BLOCKS_BITMAP_SIZE 2
// /* ------------------------ */
// #define FREE_INODE_BITMAP_SIZE_OFFSET 10
// #define FREE_INODE_BITMAP_SIZE 2
// /* ------------------------ */
// #define INODE_AREA_SIZE_OFFSET 12
// #define INODE_AREA_SIZE 2
// /* ------------------------ */
// #define BLOCK_SIZE_OFFSET 14
// #define BLOCK_SIZE 2
// /* ------------------------ */
// #define DISK_SIZE_OFFSET 16
// #define DISK_SIZE 4
// /* ------------------------ */

// /* ************************ */

// /* DEFINES DO I-NODE */
// /* ------------------------ */
// #define BLOCKS_FILE_SIZE_OFFSET 0
// #define BLOCKS_FILE_SIZE 4
// /* ------------------------ */
// #define BYTES_FILE_SIZE_OFFSET 4
// #define BYTES_FILE_SIZE 4
// /* ------------------------ */
// #define DATA_POINTER_OFFSET 8
// #define DATA_POINTER 8
// /* ------------------------ */
// #define SINGLE_IND_POINTER_OFFSET 16
// #define SINGLE_IND_POINTER 4
// /* ------------------------ */
// #define DOUBLE_IND_POINTER_OFFSET 20
// #define DOUBLE_IND_POINTER 4
// /* ------------------------ */
// #define RESERVED_OFFSET 24
// #define RESERVED 8
// /* ------------------------ */

// /* ************************ */

// /* DEFINES DO DIRETÓRIO/ARQUIVO */
// /* ------------------------ */
// #define TYPE_VALUE_OFFSET 0
// #define TYPE_VALUE 1
// /* ------------------------ */
// #define DIR_NAME_OFFSET 1
// #define DIR_NAME 59
// /* ------------------------ */
// #define I_NODE_NUMBER_OFFSET 60
// #define I_NODE_NUMBER 4
// /* ------------------------ */

// /* ************************ */

/* ESTRUTURA DO SUPERBLOCO */
struct t2fs_superbloco *SUPERBLOCK;
/* ------------------------ */

/* ESTRUTURA DO BLOCO ATUAL */
unsigned char *CURRENT_BLOCK;
/* ------------------------ */

/* I-NODE ATUAL */
struct t2fs_inode *CURRENT_I_NODE;
/* ------------------------ */

/* I-NODE RAIZ */
struct t2fs_inode *ROOT_I_NODE;
/* ------------------------ */


// int init_superblock(){
// 	SUPERBLOCK = (struct t2fs_superbloco *)malloc(sizeof(struct t2fs_superbloco));	
// 	if(SUPERBLOCK)
// 		return SUCCESS;
// 	return ERROR;
// }

// int init_current_block(){
// 	CURRENT_BLOCK = (unsigned char*)malloc(sizeof(unsigned char)*1024);
// 	if(CURRENT_BLOCK)
// 		return SUCCESS;
// 	return ERROR;
// }

// int init_root_i_node(){
// 	ROOT_I_NODE = (struct t2fs_inode *)malloc(sizeof(struct t2fs_inode));	
// 	if(ROOT_I_NODE)
// 		return SUCCESS;
// 	return ERROR;
// }

// int init_current_i_node(){
// 	CURRENT_I_NODE = (struct t2fs_inode *)malloc(sizeof(struct t2fs_inode));	
// 	if(CURRENT_I_NODE)
// 		return SUCCESS;
// 	return ERROR;
// }

// int load_superblock(){
// 	unsigned char buffer[SECTOR_SIZE];

// 	if (read_sector(0, buffer) == 0){
// 		// set id
// 		memcpy(&(SUPERBLOCK->id), 
// 			&buffer[LIB_ID_OFFSET], LIB_ID);
// 		// set version
// 		memcpy(&(SUPERBLOCK->version),
// 			&buffer[LIB_VERSION_OFFSET], LIB_VERSION);
// 		// set superblock size
// 		memcpy(&(SUPERBLOCK->superblockSize),
// 			&buffer[SUPER_BLOCK_SIZE_OFFSET], SUPER_BLOCK_SIZE);
// 		// set free blocks bitmap size
// 		memcpy(&(SUPERBLOCK->freeBlocksBitmapSize),
// 			&buffer[FREE_BLOCKS_BITMAP_SIZE_OFFSET], FREE_BLOCKS_BITMAP_SIZE);
// 		// set free i-node bitmap size
// 		memcpy(&(SUPERBLOCK->freeInodeBitmapSize),
// 			&buffer[FREE_INODE_BITMAP_SIZE_OFFSET], FREE_INODE_BITMAP_SIZE);
// 		// set i-node area size
// 		memcpy(&(SUPERBLOCK->inodeAreaSize),
// 			&buffer[INODE_AREA_SIZE_OFFSET], INODE_AREA_SIZE);
// 		// set block size
// 		memcpy(&(SUPERBLOCK->blockSize),
// 			&buffer[BLOCK_SIZE_OFFSET], BLOCK_SIZE);
// 		// set disk size
// 		memcpy(&(SUPERBLOCK->diskSize),
// 			&buffer[DISK_SIZE_OFFSET], DISK_SIZE);
// 		return SUCCESS;
// 	}
// 	return ERROR;
// }

// int init_all(){
// 	if((init_root_i_node() + init_current_i_node() + init_current_block() + init_superblock()) == SUCCESS)
// 		if(load_superblock() == SUCCESS)
// 			return SUCCESS;
// 	return ERROR;
// }

// void print_superblock(){

// 	printf("LIBRARY ID:\t\t %c%c%c%c\n",
// 		SUPERBLOCK->id[0],SUPERBLOCK->id[1],SUPERBLOCK->id[2],SUPERBLOCK->id[3]);

// 	printf("LIBRARY VERSION:\t 0x%X\n",
// 		SUPERBLOCK->version);

// 	printf("SUPERBLOCK SIZE:\t (hex) %X \t (dec) %u\n",
// 		SUPERBLOCK->superblockSize, SUPERBLOCK->superblockSize);

// 	printf("FREE BLOCKS BITMAP SIZE: (hex) %X \t (dec) %u\n",
// 		SUPERBLOCK->freeBlocksBitmapSize, SUPERBLOCK->freeBlocksBitmapSize);

// 	printf("FREE I-NODE BITMAP SIZE: (hex) %X \t (dec) %u\n",
// 		SUPERBLOCK->freeInodeBitmapSize, SUPERBLOCK->freeInodeBitmapSize);

// 	printf("I-NODE AREA SIZE:\t (hex) %X \t (dec) %u\n",
// 		SUPERBLOCK->inodeAreaSize, SUPERBLOCK->inodeAreaSize);

// 	printf("BLOCK SIZE:\t\t (hex) %X \t (dec) %u\n",
// 		SUPERBLOCK->blockSize, SUPERBLOCK->blockSize);

// 	printf("DISK SIZE:\t\t (hex) %X \t (dec) %u BLOCKS or %u SECTORS\n",
// 		SUPERBLOCK->diskSize, SUPERBLOCK->diskSize, SUPERBLOCK->diskSize*4);

// 	printf("\n");
// }

// int load_block(int block){

// 	unsigned char buffer[SECTOR_SIZE];
// 	int sectors = (block * SUPERBLOCK->blockSize);

// 	if(read_sector(sectors, buffer) == 0)
// 		memcpy(&CURRENT_BLOCK[0], &buffer[0], SECTOR_SIZE);
// 	else 
// 		return ERROR;

// 	if(read_sector (sectors+1, buffer) == 0)
// 		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*1], &buffer[0],SECTOR_SIZE);
// 	else 
// 		return ERROR;

// 	if(read_sector (sectors+2, buffer) == 0)
// 		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*2], &buffer[0],SECTOR_SIZE);
// 	else 
// 		return ERROR;

// 	if(read_sector (sectors+3, buffer) == 0)
// 		memcpy(&CURRENT_BLOCK[SECTOR_SIZE*3], &buffer[0],SECTOR_SIZE);
// 	else 
// 		return ERROR;

// 	return SUCCESS;
// }

// int get_i_node(int i_node_n, struct t2fs_inode *i_node){

// 	int position = i_node_n*(SUPERBLOCK->inodeAreaSize);

// 	if(i_node){
// 		memcpy(&(i_node->blocksFileSize),
// 			&CURRENT_BLOCK[position+BLOCKS_FILE_SIZE_OFFSET], BLOCKS_FILE_SIZE);

// 		memcpy(&(i_node->bytesFileSize),
// 			&CURRENT_BLOCK[position+BYTES_FILE_SIZE_OFFSET], 	BYTES_FILE_SIZE);

// 		memcpy(&(i_node->dataPtr[0]),
// 			&CURRENT_BLOCK[position+(DATA_POINTER_OFFSET)], (DATA_POINTER/2));

// 		memcpy(&(i_node->dataPtr[1]),
// 			&CURRENT_BLOCK[position+(DATA_POINTER_OFFSET+4)], (DATA_POINTER/2));

// 		memcpy(&(i_node->singleIndPtr),
// 			&CURRENT_BLOCK[position+SINGLE_IND_POINTER_OFFSET], SINGLE_IND_POINTER);

// 		memcpy(&(i_node->doubleIndPtr),
// 			&CURRENT_BLOCK[position+DOUBLE_IND_POINTER_OFFSET], DOUBLE_IND_POINTER);

// 		memcpy(&(i_node->reservado),
// 			&CURRENT_BLOCK[position+RESERVED_OFFSET], RESERVED);

// 		return SUCCESS;
// 	}

// 	return ERROR;
// }

// void print_i_node(struct t2fs_inode *i_node){
// 	printf("BLOCKS FILE SIZE\t %u\n", i_node->blocksFileSize);
// 	printf("BYTES FILE SIZE:\t %u\n", i_node->bytesFileSize);
// 	printf("1ST DATA POINTER:\t %u\n", i_node->dataPtr[0]);
// 	printf("2ND DATA POINTER:\t %u\n", i_node->dataPtr[1]);
// 	printf("SINGLE INDIRECT POINTER: %u\n", i_node->singleIndPtr);
// 	printf("DOUBLE INDIRECT POINTER: %u\n", i_node->doubleIndPtr);
// 	printf("\n");
// }


// void print_record(struct t2fs_record *record){
// 	printf("TYPE VALUE: \t0x0%X (0x01 FILE, 0x02 DIR)\n" ,record->TypeVal);
// 	printf("NAME: \t\t%s\n", record->name);
// 	printf("I-NODE NUMBER:  %d\n", record->inodeNumber);
// 	printf("\n");
// }


// int read_i_node_content(struct t2fs_inode *dir){
// 	struct t2fs_record *record;
// 	record = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

// 	if(CURRENT_I_NODE->blocksFileSize > 0){
// 		if (load_block(dir->dataPtr[0]) == SUCCESS){
// 			for(int i = 0; i < 16; i++) {
// 				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
// 				if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
// 					print_record(record);
// 				}
// 			}
// 		}
// 		return SUCCESS;
// 	}
// 	if(CURRENT_I_NODE->blocksFileSize > 1){
// 		if (load_block(dir->dataPtr[1]) == SUCCESS){
// 			if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
// 				for(int i = 0; i < 16; i++) {
// 					memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
// 					print_record(record);
// 				}
// 			}
// 		}
// 		return SUCCESS;
// 	}
// 	if(dir->blocksFileSize > 2){
// 		printf("TODO >>> INDIRECT READING\n");
// 		return SUCCESS;
// 	}
// 	return ERROR;
// }



void debug_main(){

	printf("\n");
	if (init_all() == SUCCESS)
		printf("[init_all] Estruturas de dados iniciadas com sucesso e superbloco carregado.\n");
	printf("\n\n..:: INFO SOBRE O SUEPRBLOCO ::..\n\n");
	print_superblock();
	printf("\n");

	if (load_block(3) == SUCCESS)
		printf("[load_block] Carregamento do bloco 3 realizado com sucesso.\n\n");

	if (get_i_node(0, ROOT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node raiz é o 0 do bloco 3.\n\n");
	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o nodo raiz.\n\n");

	printf("[read_i_node_content] Esse é o conteúdo do i-node raíz: \n\n");

	read_i_node_content(CURRENT_I_NODE);
}

/*-----------------------------------------------------------------------------
Função: Usada para identificar os desenvolvedores do T2FS.
	Essa função copia um string de identificação para o ponteiro indicado por "name".
	Essa cópia não pode exceder o tamanho do buffer, informado pelo parâmetro "size".
	O string deve ser formado apenas por caracteres ASCII (Valores entre 0x20 e 0x7A) e terminado por ‘\0’.
	O string deve conter o nome e número do cartão dos participantes do grupo.

Entra:	name -> buffer onde colocar o string de identificação.
	size -> tamanho do buffer "name" (número máximo de bytes a serem copiados).

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int identify2 (char *name, int size){

  if(size < N_SIZE)
    return ERROR;

  int i = 0;
  while ((name[i] = NAMES[i]) != '\0')
  {
    i++;
  }
  return SUCCESS;

}


/*-----------------------------------------------------------------------------
Função: Criar um novo arquivo.
	O nome desse novo arquivo é aquele informado pelo parâmetro "filename".
	O contador de posição do arquivo (current pointer) deve ser colocado na posição zero.
	Caso já exista um arquivo ou diretório com o mesmo nome, a função deverá retornar um erro de criação.
	A função deve retornar o identificador (handle) do arquivo.
	Esse handle será usado em chamadas posteriores do sistema de arquivo para fins de manipulação do arquivo criado.

Entra:	filename -> nome do arquivo a ser criado.

Saída:	Se a operação foi realizada com sucesso, a função retorna o handle do arquivo (número positivo).
	Em caso de erro, deve ser retornado um valor negativo.
-----------------------------------------------------------------------------*/
FILE2 create2 (char *filename){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Apagar um arquivo do disco.
	O nome do arquivo a ser apagado é aquele informado pelo parâmetro "filename".

Entra:	filename -> nome do arquivo a ser apagado.

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int delete2 (char *filename){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Abre um arquivo existente no disco.
	O nome desse novo arquivo é aquele informado pelo parâmetro "filename".
	Ao abrir um arquivo, o contador de posição do arquivo (current pointer) deve ser colocado na posição zero.
	A função deve retornar o identificador (handle) do arquivo.
	Esse handle será usado em chamadas posteriores do sistema de arquivo para fins de manipulação do arquivo criado.
	Todos os arquivos abertos por esta chamada são abertos em leitura e em escrita.
	O ponto em que a leitura, ou escrita, será realizada é fornecido pelo valor current_pointer (ver função seek2).

Entra:	filename -> nome do arquivo a ser apagado.

Saída:	Se a operação foi realizada com sucesso, a função retorna o handle do arquivo (número positivo)
	Em caso de erro, deve ser retornado um valor negativo
-----------------------------------------------------------------------------*/
FILE2 open2 (char *filename){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Fecha o arquivo identificado pelo parâmetro "handle".

Entra:	handle -> identificador do arquivo a ser fechado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int close2 (FILE2 handle){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Realiza a leitura de "size" bytes do arquivo identificado por "handle".
	Os bytes lidos são colocados na área apontada por "buffer".
	Após a leitura, o contador de posição (current pointer) deve ser ajustado para o byte seguinte ao último lido.

Entra:	handle -> identificador do arquivo a ser lido
	buffer -> buffer onde colocar os bytes lidos do arquivo
	size -> número de bytes a serem lidos

Saída:	Se a operação foi realizada com sucesso, a função retorna o número de bytes lidos.
	Se o valor retornado for menor do que "size", então o contador de posição atingiu o final do arquivo.
	Em caso de erro, será retornado um valor negativo.
-----------------------------------------------------------------------------*/
int read2 (FILE2 handle, char *buffer, int size){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Realiza a escrita de "size" bytes no arquivo identificado por "handle".
	Os bytes a serem escritos estão na área apontada por "buffer".
	Após a escrita, o contador de posição (current pointer) deve ser ajustado para o byte seguinte ao último escrito.

Entra:	handle -> identificador do arquivo a ser escrito
	buffer -> buffer de onde pegar os bytes a serem escritos no arquivo
	size -> número de bytes a serem escritos

Saída:	Se a operação foi realizada com sucesso, a função retorna o número de bytes efetivamente escritos.
	Em caso de erro, será retornado um valor negativo.
-----------------------------------------------------------------------------*/
int write2 (FILE2 handle, char *buffer, int size){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Função usada para truncar um arquivo.
	Remove do arquivo todos os bytes a partir da posição atual do contador de posição (CP)
	Todos os bytes a partir da posição CP (inclusive) serão removidos do arquivo.
	Após a operação, o arquivo deverá contar com CP bytes e o ponteiro estará no final do arquivo

Entra:	handle -> identificador do arquivo a ser truncado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int truncate2 (FILE2 handle){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Reposiciona o contador de posições (current pointer) do arquivo identificado por "handle".
	A nova posição é determinada pelo parâmetro "offset".
	O parâmetro "offset" corresponde ao deslocamento, em bytes, contados a partir do início do arquivo.
	Se o valor de "offset" for "-1", o current_pointer deverá ser posicionado no byte seguinte ao final do arquivo,
		Isso é útil para permitir que novos dados sejam adicionados no final de um arquivo já existente.

Entra:	handle -> identificador do arquivo a ser escrito
	offset -> deslocamento, em bytes, onde posicionar o "current pointer".

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int seek2 (FILE2 handle, DWORD offset){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Criar um novo diretório.
	O caminho desse novo diretório é aquele informado pelo parâmetro "pathname".
		O caminho pode ser ser absoluto ou relativo.
	São considerados erros de criação quaisquer situações em que o diretório não possa ser criado.
		Isso inclui a existência de um arquivo ou diretório com o mesmo "pathname".

Entra:	pathname -> caminho do diretório a ser criado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int mkdir2 (char *pathname){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Apagar um subdiretório do disco.
	O caminho do diretório a ser apagado é aquele informado pelo parâmetro "pathname".
	São considerados erros quaisquer situações que impeçam a operação.
		Isso inclui:
			(a) o diretório a ser removido não está vazio;
			(b) "pathname" não existente;
			(c) algum dos componentes do "pathname" não existe (caminho inválido);
			(d) o "pathname" indicado não é um arquivo;

Entra:	pathname -> caminho do diretório a ser criado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int rmdir2 (char *pathname){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Altera o diretório atual de trabalho (working directory).
		O caminho desse diretório é informado no parâmetro "pathname".
		São considerados erros:
			(a) qualquer situação que impeça a realização da operação
			(b) não existência do "pathname" informado.

Entra:	pathname -> caminho do novo diretório de trabalho.

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
		Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int chdir2 (char *pathname){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Informa o diretório atual de trabalho.
		O "pathname" do diretório de trabalho deve ser copiado para o buffer indicado por "pathname".
			Essa cópia não pode exceder o tamanho do buffer, informado pelo parâmetro "size".
		São considerados erros:
			(a) quaisquer situações que impeçam a realização da operação
			(b) espaço insuficiente no buffer "pathname", cujo tamanho está informado por "size".

Entra:	pathname -> buffer para onde copiar o pathname do diretório de trabalho
		size -> tamanho do buffer pathname

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
		Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int getcwd2 (char *pathname, int size){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Abre um diretório existente no disco.
	O caminho desse diretório é aquele informado pelo parâmetro "pathname".
	Se a operação foi realizada com sucesso, a função:
		(a) deve retornar o identificador (handle) do diretório
		(b) deve posicionar o ponteiro de entradas (current entry) na primeira posição válida do diretório "pathname".
	O handle retornado será usado em chamadas posteriores do sistema de arquivo para fins de manipulação do diretório.

Entra:	pathname -> caminho do diretório a ser aberto

Saída:	Se a operação foi realizada com sucesso, a função retorna o identificador do diretório (handle).
	Em caso de erro, será retornado um valor negativo.
-----------------------------------------------------------------------------*/
DIR2 opendir2 (char *pathname){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Realiza a leitura das entradas do diretório identificado por "handle".
	A cada chamada da função é lida a entrada seguinte do diretório representado pelo identificador "handle".
	Algumas das informações dessas entradas devem ser colocadas no parâmetro "dentry".
	Após realizada a leitura de uma entrada, o ponteiro de entradas (current entry) 
	deve ser ajustado para a próxima entrada válida, seguinte à última lida.
	São considerados erros:
		(a) qualquer situação que impeça a realização da operação
		(b) término das entradas válidas do diretório identificado por "handle".

Entra:	handle -> identificador do diretório cujas entradas deseja-se ler.
	dentry -> estrutura de dados onde a função coloca as informações da entrada lida.

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero ( e "dentry" não será válido)
-----------------------------------------------------------------------------*/
int readdir2 (DIR2 handle, DIRENT2 *dentry){


	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Fecha o diretório identificado pelo parâmetro "handle".

Entra:	handle -> identificador do diretório que se deseja fechar (encerrar a operação).

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int closedir2 (DIR2 handle){


	return ERROR;
}










