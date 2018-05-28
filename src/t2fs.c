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

/* NÚMERO DE ARQUIVOS */
/* ------------------------ */
#define MAX_RECORDS (64/4)
/* ------------------------ */

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

/* LISTA DE ARQUIVOS (HANDLE) */
RECORDS_HANDLE *FILES;
/* ------------------------ */

/* LISTA DE DIRETORIOS (HANDLE) */
RECORDS_HANDLE *DIRECTORIES;
/* ------------------------ */


void debug_main(){

	printf("\n");
	if (init_all() == SUCCESS)
		printf("[init_all] Estruturas de dados iniciadas com sucesso e superbloco carregado.\n");
	printf("\n\n..:: INFO SOBRE O SUEPRBLOCO ::..\n\n");
	print_superblock();
	printf("\n");
	init_records_list();

	// if (load_block(3) == SUCCESS)
	// 	printf("[load_block] Carregamento do bloco 3 realizado com sucesso.\n\n");

	if (get_i_node(0, ROOT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node raiz é o 0 do bloco 3.\n\n");

	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o nodo raiz.\n\n");


	// printf("[read_i_node_content] Esse é o conteúdo do i-node raíz: \n\n");

	// read_i_node_content(CURRENT_I_NODE);

	

	// char pathname01[200] = "/dir0/dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/dir9/dir10/dir11/dir12/dir13/dir14/file";
	// char pathname02[59] = "dir1/dir2/dir3/dir4/file";

	// char *hd01 = head_dir(pathname01);
	// char *hd02 = head_dir(pathname02);
	// char *tl01 = tail_dir(pathname01);
	// char *tl02 = tail_dir(pathname02);

	// printf("PATH01\n HEAD: %s, TAIL: %s\n", hd01, tl01);
	// printf("PATH02\n HEAD: %s, TAIL: %s\n", hd02, tl02);

	// printf("%s\n", pathname01);
	// char *hd01 = tail_dir(pathname01);
	// printf("%s\n", hd01);
	// while (hd01 != NULL){
	// 	printf("tail: %s\n", hd01);
	// 	printf("head: %s\n", head_dir(hd01));
	// 	printf("--\n");
	// 	hd01 = tail_dir(hd01);
	// }

	struct t2fs_record *aux = malloc(sizeof(struct t2fs_record));

	char filename[59] = "/file3";
	aux = find_file(CURRENT_I_NODE, filename);
	printf("INODE NUMBER OF FILE3: %d\n\n", aux->inodeNumber);
	print_record(aux);

	// read_i_node_content(CURRENT_I_NODE);

	// print_i_node(CURRENT_I_NODE);

	// int file111_inode_number;

	// if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
	// 	printf("[get_i_node] I-node de trabalho é o nodo raiz.\n\n");
	// file111_inode_number = find_file(CURRENT_I_NODE, filename111, aux);
	// printf("INODE NUMBER OF file221: %d\n\n", file111_inode_number);
	// print_record(aux);

	char filenamedir1[59] = "/dir2/dir21";

	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o nodo raiz.\n\n");

	aux = find_directory(CURRENT_I_NODE, filenamedir1);
	printf("INODE NUMBER OF dir21: %d\n\n", aux->inodeNumber);
	print_record(aux);

	// init_records_list();

	// int inode_value = 1;

	// while(inode_value >= 0){
	// 	printf("INODE: ");
	// 	scanf("%d", &inode_value);
	// 	if (get_i_node(inode_value, CURRENT_I_NODE) == SUCCESS)
	// 		printf("[get_i_node] I-node de trabalho é o node %d.\n\n", inode_value);
	// 	read_i_node_content(CURRENT_I_NODE);
	// }

	/*
	******************************************************
		Testes OPEN2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>OPEN2<<<<<<<<]\n");

	char filename111[59] = "/dir2/dir21/file211";
	char filename112[59] = "dir21/file211";
	char filename113[59] = "file3";

	printf("[open2] tentando abrir %s\n", filename111);
	int file_handle = open2(filename111);
	printf("HANDLE: %d\n", file_handle);
	print_record(FILES[file_handle].record_info);

	if (get_i_node(4, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 4.\n\n");

	printf("[open2] tentando abrir %s\n", filename112);
	file_handle = open2(filename112);
	printf("HANDLE: %d\n", file_handle);
	print_record(FILES[file_handle].record_info);

	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 5.\n\n");

	printf("[open2] tentando abrir %s\n", filename113);
	file_handle = open2(filename113);
	printf("HANDLE: %d\n", file_handle);
	print_record(FILES[file_handle].record_info);

	/*
	******************************************************
		Testes OPENDIR2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>OPENDIR2<<<<<<<<]\n");

	char path111[59] = "/dir2/dir21/";
	char path112[59] = "dir21";
	// char path113[59] = "/file3";

	printf("[opendir2] tentando abrir %s\n", path111);
	int dir_handle = opendir2(path111);
	printf("HANDLE: %d\n", dir_handle);
	print_record(DIRECTORIES[dir_handle].record_info);

	if (get_i_node(4, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 4.\n\n");
		// read_i_node_content(CURRENT_I_NODE);	

	printf("[opendir2] tentando abrir %s\n", path112);
	dir_handle = opendir2(path112);
	printf("HANDLE: %d\n", dir_handle);
	print_record(DIRECTORIES[dir_handle].record_info);


	/*
	******************************************************
		Testes CLOSE2
	******************************************************
	*/
	
	printf("\n\n\n[>>>>>>>CLOSE2<<<<<<<<]\n");

	if (close2(0) == SUCCESS){
		print_record(FILES[0].record_info);
	}
	if (close2(1) == SUCCESS){
		print_record(FILES[1].record_info);
	}
	if (close2(2) == SUCCESS){
		print_record(FILES[2].record_info);
	}

		/*
	******************************************************
		Testes CLOSEDIR2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>CLOSEDIR2<<<<<<<<]\n");

	if (closedir2(0) == SUCCESS){
		print_record(DIRECTORIES[0].record_info);
	}
	if (closedir2(1) == SUCCESS){
		print_record(DIRECTORIES[1].record_info);
	}
	if (closedir2(2) == SUCCESS){
		print_record(DIRECTORIES[2].record_info);
	}

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

	struct t2fs_inode *work_directory;
	struct t2fs_record *file_record = malloc(sizeof(struct t2fs_record));
	int handle = -10;

	if (filename[0] == '/'){
		work_directory = ROOT_I_NODE;
	}
	else {
		work_directory = CURRENT_I_NODE;
	}

	file_record = find_file(work_directory, filename);
	// printf("file_record->inodeNumber = %d\n", file_record->inodeNumber);

	if (file_record->inodeNumber != ERROR){
		for (int i = 0; i < 10; ++i){
			if (FILES[i].record_info->TypeVal == TYPEVAL_REGULAR &&
				FILES[i].record_info->inodeNumber == file_record->inodeNumber){
				FILES[i].seek_pointer = 0;
				handle = i;
				return handle;
			}
			else if (handle == -10 && 
				FILES[i].record_info->TypeVal == TYPEVAL_INVALIDO){
				handle = i;
			}
		}

		if (handle >= 0){
			FILES[handle].record_info = file_record;
			return handle;
		}

		else {
			printf("ERRO: Maximo de arquivos abertos atingido.\n");
			return ERROR;
		}
	}

	else{
		printf("ERRO: Arquivo não encontrado.\n");
		return ERROR;
	}
}


/*-----------------------------------------------------------------------------
Função:	Fecha o arquivo identificado pelo parâmetro "handle".

Entra:	handle -> identificador do arquivo a ser fechado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int close2 (FILE2 handle){

	if (FILES[handle].record_info->TypeVal == TYPEVAL_REGULAR){
		FILES[handle].record_info->TypeVal = TYPEVAL_INVALIDO;
		FILES[handle].record_info->inodeNumber = -1;
		strcpy(FILES[handle].record_info->name, "indef");
		FILES[handle].seek_pointer = 0;
		return SUCCESS;
	}

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

	struct t2fs_inode *work_directory;
	struct t2fs_record *file_record = malloc(sizeof(struct t2fs_record));
	int handle = -10;

	if (pathname[0] == '/'){
		work_directory = ROOT_I_NODE;
	}
	else {
		work_directory = CURRENT_I_NODE;
	}

	// printf("wooow\n");
	file_record = find_directory(work_directory, pathname);
	// printf("file_record->inodeNumber = %d\n", file_record->inodeNumber);

	if (file_record->inodeNumber != ERROR){
		for (int i = 0; i < 10; ++i){
			if (DIRECTORIES[i].record_info->TypeVal == TYPEVAL_DIRETORIO &&
				DIRECTORIES[i].record_info->inodeNumber == file_record->inodeNumber){
				handle = i;

				return handle;
			}
			else if (handle == -10 && 
				DIRECTORIES[i].record_info->TypeVal == TYPEVAL_INVALIDO){
				handle = i;
			}
		}

		if (handle >= 0){
			DIRECTORIES[handle].record_info = file_record;
			return handle;
		}

		else {
			printf("ERRO: Maximo de diretórios abertos atingido.\n");
			return ERROR;
		}
	}

	else{
		printf("ERRO: Diretório não encontrado.\n");
		return ERROR;
	}

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

	if (DIRECTORIES[handle].record_info->TypeVal == TYPEVAL_DIRETORIO){
		DIRECTORIES[handle].record_info->TypeVal = TYPEVAL_INVALIDO;
		DIRECTORIES[handle].record_info->inodeNumber = -1;
		strcpy(DIRECTORIES[handle].record_info->name, "indef");
		DIRECTORIES[handle].seek_pointer = 0;
		return SUCCESS;
	}

	return ERROR;
}










