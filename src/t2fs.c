#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* CONTROLE DA INICIAÇÃO DAS ESTRUTURAS */
int INIT = 0;
/* ------------------------ */

void debug_main(){

	printf("\n");
	if (init_all() == SUCCESS)
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

	init_records_list();

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
		Testes IDENTIFY2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>IDENTIFY2<<<<<<<<]\n");
	printf("[>>>>>>>IDENTIFY2<<<<<<<<]\n");
	printf("[>>>>>>>IDENTIFY2<<<<<<<<]\n");
	printf("\n\n\n");

	char namesssss[255];

	identify2(namesssss, 255);

	printf("GRUPO: \n%s\n", namesssss);


	/*
	******************************************************
		Testes OPEN2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>OPEN2<<<<<<<<]\n");
	printf("[>>>>>>>OPEN2<<<<<<<<]\n");
	printf("[>>>>>>>OPEN2<<<<<<<<]\n");
	printf("\n\n\n");

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
	printf("[>>>>>>>OPENDIR2<<<<<<<<]\n");
	printf("[>>>>>>>OPENDIR2<<<<<<<<]\n");
	printf("\n\n\n");

	char path111[59] = "/dir1/dir11/";
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
	printf("[>>>>>>>CLOSE2<<<<<<<<]\n");
	printf("[>>>>>>>CLOSE2<<<<<<<<]\n");
	printf("\n\n\n");

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
	printf("[>>>>>>>CLOSEDIR2<<<<<<<<]\n");
	printf("[>>>>>>>CLOSEDIR2<<<<<<<<]\n");
	printf("\n\n\n");

	if (closedir2(0) == SUCCESS){
		print_record(DIRECTORIES[0].record_info);
	}
	if (closedir2(1) == SUCCESS){
		print_record(DIRECTORIES[1].record_info);
	}
	if (closedir2(2) == SUCCESS){
		print_record(DIRECTORIES[2].record_info);
	}

	/*
	******************************************************
		Testes CHDIR2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>CHDIR2<<<<<<<<]\n");
	printf("[>>>>>>>CHDIR2<<<<<<<<]\n");
	printf("[>>>>>>>CHDIR2<<<<<<<<]\n");
	printf("\n\n\n");

	char dir2[59] = "dir2";

	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 0 (raiz).\n\n");

	if (chdir2(dir2) == SUCCESS){
		printf("CHDIR2 -> %s\n", dir2);
		read_i_node_content(CURRENT_I_NODE);
	}

	char dir2_2[59] = "/dir2/dir21";

	if (get_i_node(5, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 5.\n\n");

	if (chdir2(dir2_2) == SUCCESS){
		printf("CHDIR2 -> %s\n", dir2_2);
		read_i_node_content(CURRENT_I_NODE);
	}

	char dir_root[59] = "/";

	if (chdir2(dir_root) == SUCCESS){
		printf("CHDIR2 -> %s\n", dir_root);
		read_i_node_content(CURRENT_I_NODE);
	}

		
	/********************************************************/


	if (get_i_node(5, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 5.\n\n");

	read_i_node_content(CURRENT_I_NODE);

	printf("\n\n\n[>>>>>>>ROOT TO CURRENT<<<<<<<<]\n");

	char *full_path = root_to_current(CURRENT_I_NODE);

	printf("FULL PATH OF dir21: %s\n\n\n", full_path);

	/********************************************************/

	// printf("\n\n\n[>>>>>>>GET RECORD BY INODE NUMBER<<<<<<<<]\n");

	// struct t2fs_record *auxrecord = get_record_by_inode_number(ROOT_I_NODE, 1);

	// print_record(auxrecord);

	/*
	******************************************************
		Testes GETCWD2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>GETCWD2<<<<<<<<]\n");
	printf("[>>>>>>>GETCWD2<<<<<<<<]\n");
	printf("[>>>>>>>GETCWD2<<<<<<<<]\n");
	printf("\n\n\n");

	char churros[1024];

	if (getcwd2(churros, 1024) == SUCCESS)
	{
		printf("O RESULTADO DE GETCWD2 FOI: %s\n", churros);
	}

	if (get_i_node(0, CURRENT_I_NODE))
		printf("[get_i_node] I-node de trabalho é o i-node 0.\n\n");

	if (getcwd2(churros, 1024) == SUCCESS)
	{
		printf("O RESULTADO DE GETCWD2 FOI: %s\n", churros);
	}

	/*
	******************************************************
		Testes SEEK2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>SEEK2<<<<<<<<]\n");
	printf("[>>>>>>>SEEK2<<<<<<<<]\n");
	printf("[>>>>>>>SEEK2<<<<<<<<]\n");
	printf("\n\n\n");


	if (get_i_node(4, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 4.\n\n");

	printf("[open2] tentando abrir %s\n", filename112);
	file_handle = open2(filename112);
	printf("HANDLE: %d\n", file_handle);
	print_record(FILES[file_handle].record_info);

	printf("[seek2] Offset agora vai ser 43.\n");

	if (seek2(file_handle, 43) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	if (seek2(file_handle, 0) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	if (seek2(file_handle, -1) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	printf(".:Erro proposital:.\n");
	if (seek2(file_handle, 1242) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	printf("\n\n\n");

	if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 5.\n\n");

	printf("[open2] tentando abrir %s\n", filename113);
	file_handle = open2(filename113);
	printf("HANDLE: %d\n", file_handle);
	print_record(FILES[file_handle].record_info);

	printf("[seek2] Offset agora vai ser 17.\n");

	if (seek2(file_handle, 17) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	if (seek2(file_handle, 0) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	if (seek2(file_handle, -1) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	printf(".:Erro proposital:.\n");
	if (seek2(file_handle, 1242) == SUCCESS){
		printf("Offset do %s agora é %d\n", FILES[file_handle].record_info->name, FILES[file_handle].seek_pointer);
	}

	printf("\n\n\n");


	printf("first free bitmap for inode: %d \n", get_first_free_bitmap(0));
	printf("first free bitmap for data: %d \n", get_first_free_bitmap(1));

	char dir_test_ok[] = "dir2";
	char file_test_ok[] = "file3";

	if (verify_name(dir_test_ok, TYPEVAL_DIRETORIO, ROOT_I_NODE) == SUCCESS){
		printf("VERIFICOU QUE EXISTE %s\n", dir_test_ok);
	}

	if (verify_name(file_test_ok, TYPEVAL_REGULAR, ROOT_I_NODE) == SUCCESS){
		printf("VERIFICOU QUE EXISTE %s\n", file_test_ok);
	}


	if (get_i_node(5, CURRENT_I_NODE) == SUCCESS)
		printf("[get_i_node] I-node de trabalho é o i-node 5.\n\n");


	char dir_test_fail[] = "dir2";
	char file_test_fail[] = "file3";


	if (verify_name(dir_test_fail, TYPEVAL_DIRETORIO, CURRENT_I_NODE) == ERROR){
		printf("VERIFICOU QUE não EXISTE %s\n", dir_test_fail);
	}

	if (verify_name(file_test_fail, TYPEVAL_REGULAR, CURRENT_I_NODE) == ERROR){
		printf("VERIFICOU QUE não EXISTE %s\n", file_test_fail);
	}


	/*
	******************************************************
		Testes MKDIR2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>MKDIR2<<<<<<<<]\n");
	printf("[>>>>>>>MKDIR2<<<<<<<<]\n");
	printf("[>>>>>>>MKDIR2<<<<<<<<]\n");
	printf("\n\n\n");

	// if (get_i_node(0, CURRENT_I_NODE) == SUCCESS)
	// 	printf("[get_i_node] I-node de trabalho é o i-node 0.\n\n");

	// char eita_giovana[] = "/dir2/churrascao";
	// // char eita_cuzaum[] = "/miau";

	// mkdir2(eita_giovana);
	// // mkdir2(eita_cuzaum);

	// read_i_node_content(ROOT_I_NODE);

	/*
	******************************************************
		Testes READDIR2
	******************************************************
	*/

	printf("\n\n\n[>>>>>>>READDIR2<<<<<<<<]\n");
	printf("[>>>>>>>READDIR2<<<<<<<<]\n");
	printf("[>>>>>>>READDIR2<<<<<<<<]\n");
	printf("\n\n\n");

	opendir2("/");

    DIRENT2 dentry;
    while ( readdir2(0, &dentry) == SUCCESS ) {
        printf ("%c %8u %s\n", (dentry.fileType==0x02?'d':'-'), dentry.fileSize, dentry.name);
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

	if (init_all() != SUCCESS){
		return ERROR;
	}


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

	if (init_all() != SUCCESS){
		return ERROR;
	}

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

	if (init_all() != SUCCESS){
		return ERROR;
	}


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

	if (file_record != NULL){
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	if (handle > 9 || handle < 0 || FILES[handle].record_info->inodeNumber == -1){
		printf("ERROR: Handle inválido.\n");
		return ERROR;
	}

	struct t2fs_record *current_i_node_cpy = malloc(sizeof(struct t2fs_record));
	char father [] = "..";
	current_i_node_cpy = find_directory(CURRENT_I_NODE, father);


	struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));
	if (get_i_node(FILES[handle].record_info->inodeNumber, aux_inode) == SUCCESS){

		if (aux_inode->bytesFileSize == 0){
			get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
			return SUCCESS;
		}

		int b_ctr = 0; // controle do buffer
		int f_ctr = 0; // controle dos bytes do arquivo

		if (aux_inode->dataPtr[0] != INVALID_PTR){

			if(b_ctr < 1024){
				f_ctr = FILES[handle].seek_pointer % 1024;
			}

			if ((b_ctr < (aux_inode->bytesFileSize - FILES[handle].seek_pointer)) && (b_ctr < size)){
				if (load_block(aux_inode->dataPtr[0]) == SUCCESS){
					while((b_ctr < size) &&
						(b_ctr < (aux_inode->bytesFileSize - FILES[handle].seek_pointer)) &&
						(f_ctr < 1024)){

						buffer[b_ctr] = CURRENT_BLOCK[f_ctr];

						b_ctr++;
						f_ctr++;
					}
				}
			}
			
		}

		if (aux_inode->dataPtr[1] != INVALID_PTR){
			if(b_ctr < 1024){
				f_ctr = FILES[handle].seek_pointer % 1024;
			}

			if ((b_ctr < (aux_inode->bytesFileSize - FILES[handle].seek_pointer)) && (b_ctr < size)){
				if (load_block(aux_inode->dataPtr[1]) == SUCCESS){
					while((b_ctr < size) &&
						(b_ctr < (aux_inode->bytesFileSize - FILES[handle].seek_pointer)) &&
						(f_ctr < 1024)){

						buffer[b_ctr] = CURRENT_BLOCK[f_ctr];
					
						b_ctr++;
						f_ctr++;
					}
				}
			}			
		}

		get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
		return b_ctr;
	}

	get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

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

	if (init_all() != SUCCESS){
		return ERROR;
	}

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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	if (handle < 0 || handle > 10){
		printf("ERROR: Handle inválido.\n");
		return ERROR;
	}

	if (FILES[handle].record_info->TypeVal == TYPEVAL_INVALIDO){
		printf("ERROR: Arquivo inválido.\n");
		return ERROR;
	}

	struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));

	if (get_i_node(FILES[handle].record_info->inodeNumber, aux_inode) == SUCCESS){
		if (offset == -1){
			FILES[handle].seek_pointer = aux_inode->bytesFileSize + 1;
			return SUCCESS;
		}

		else if(offset > aux_inode->bytesFileSize){
			printf("ERROR: Offset inválido.\n");
			return ERROR;
		}

		FILES[handle].seek_pointer = offset;
		return SUCCESS;
	}

	printf("ERROR: Erro na leitura do i-node.\n");
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	// struct t2fs_inode *work_directory = malloc(sizeof(struct t2fs_inode));

	// if (pathname[0] == '/'){
	// 	if (get_i_node(0, work_directory) != SUCCESS){
	// 		printf("ERROR: Erro ao carregar o diretório raiz.\n");
	// 		return ERROR;
	// 	}
	// }

	// else {
	// 	work_directory = CURRENT_I_NODE;
	// }

	// if (verify_name(pathname, TYPEVAL_DIRETORIO, work_directory) == SUCCESS){
	// 	printf("ERROR: Diretório já existe.\n");
	// 	return ERROR;
	// }

	// int free_inode = get_first_free_bitmap(BITMAP_INODE);

	// if (free_inode < 0){
	// 	printf("ERROR: Erro ao encontrar um espaço vazio no bitmap.\n");
	// 	return ERROR;
	// }

	// int i_node_block = ((SUPERBLOCK->superblockSize + SUPERBLOCK->freeBlocksBitmapSize + SUPERBLOCK->freeInodeBitmapSize)
	// 					+ ((int)(free_inode/32)));

	// if(load_block(i_node_block) != SUCCESS){
	// 	printf("ERROR: Erro na leitura do bloco do inode livre.\n");
	// 	return ERROR;
	// }

	// // setBitmap2(BITMAP_INODE, free_inode, 1);

	// struct t2fs_inode *new_inode = malloc(sizeof(struct t2fs_inode));

	// init_new_inode(new_inode);

	// // print_i_node(new_inode);

	// // printf("ue\n");

	// char *filename = pathname;
	// char *temp = tail_dir(pathname);

	// // printf("%s, %d\n", temp, strlen(temp));

	// // printf("ue\n");
	// while(temp != NULL && strlen(temp) != 0){
	// 	filename = tail_dir(filename);
	// 	temp = tail_dir(temp);
	// }

	// // printf("ue\n");
	// filename = head_dir(filename); // nome do novo diretório

	// char *father_path = malloc(sizeof(char) * strlen(pathname));

	// int father_size = strlen(pathname) - strlen(filename);

	// if (pathname[strlen(pathname)-1] == '/'){
	// 	father_size -= 1;
	// }

	// if (pathname[0] == '/'){
	// 	father_size -= 1;
	// }

	// // printf("FATHER SIZE: %d\n", father_size);

	// struct t2fs_record *father_record = malloc(sizeof(struct t2fs_record));

	// if (father_size > 0){
	// 	strncpy(father_path, pathname, father_size);

	// 	father_record = find_directory(work_directory, father_path);

	// 	if (father_record == NULL){
	// 		printf("ERROR: Erro ao encontrar o diretório pai. \n");
	// 		return ERROR;
	// 	}

	// 	print_record(father_record);

	// 	// printf("eita\n");
	// 	get_i_node(father_record->inodeNumber, work_directory);

	// }

	// // struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));
	// // get_i_node(free_inode, new_inode);

	// char self[] = ".";
	// // char father[] = "..";

	// father_record = find_directory(work_directory, self);
	// print_record(father_record);

	// get_i_node(free_inode, new_inode);

	// init_new_inode(new_inode);

	// int current_block_index = sizeof(struct t2fs_inode) * (free_inode % (1024/sizeof(struct t2fs_inode)));

	// memcpy(&CURRENT_BLOCK[current_block_index], new_inode, sizeof(struct t2fs_inode));

	// write_block(3 + (int)(free_inode/(1024/sizeof(struct t2fs_inode))));

	// printf("AFTER MEMCPY:\n");
	// read_i_node_content(new_inode);

	// descobrir numero do i-node do pai
	// current_i_node deve ser o pai
	// no current tem que add info sobre o novo diretório

	//*******************************************
	// no filho tem que add self (.) e pai (..)
	//*******************************************


	// printf("%s %d\n", filename, free_inode);
	// printf("FATHER PATH: %s, FULL PATH: %s\n", father_path, pathname);



	// printf("HEAD: %s, TAIL: %s\n", head_dir(pathname), tail_dir(pathname));



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

	if (init_all() != SUCCESS){
		return ERROR;
	}

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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	struct t2fs_inode *work_directory = malloc(sizeof(struct t2fs_inode));
	struct t2fs_record *file_record = malloc(sizeof(struct t2fs_record));
	struct t2fs_inode *work_inode = malloc(sizeof(struct t2fs_inode));

	char root[] = "/";

	if (strcmp(pathname, root) == SUCCESS){
		if (get_i_node(file_record->inodeNumber, CURRENT_I_NODE) == SUCCESS){
			return SUCCESS;
		}
		else {
			printf("ERROR: Erro na leitura do i-node.\n");
			return ERROR;
		}
	}

	if (pathname[0] == '/'){
		work_directory = ROOT_I_NODE;
	}
	else {
		work_directory = CURRENT_I_NODE;
	}

	file_record = find_directory(work_directory, pathname);

	if (file_record != NULL){

		if (get_i_node(file_record->inodeNumber, work_inode) == SUCCESS){
			// read_i_node_content(work_inode);
			get_i_node(file_record->inodeNumber, CURRENT_I_NODE);
			// read_i_node_content(CURRENT_I_NODE);
			return SUCCESS;
		}

		printf("ERROR: Erro na leitura do i-node.\n");
		return ERROR;
	}


	printf("ERROR: Diretório não encontrado.\n");
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	char root[] = "/";

	if (CURRENT_I_NODE == ROOT_I_NODE){
		if (strlen(root) > size){
			printf("ERROR: Espaço insuficiente no buffer pathname.\n");
			return ERROR;
		}

		strcpy(pathname, root);
		return SUCCESS;
	}

	char *temp_path = root_to_current(CURRENT_I_NODE);

	if (strlen(temp_path) > size){
		printf("ERROR: Espaço insuficiente no buffer pathname.\n");
		return ERROR;
	}

	strcpy(pathname, temp_path);

	return SUCCESS;
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	struct t2fs_record *current_i_node_cpy = malloc(sizeof(struct t2fs_record));

	// printf(" INODE::::::..... %d\n", current_i_node_cpy->inodeNumber);

	char self [] = ".";

	current_i_node_cpy = find_directory(CURRENT_I_NODE, self);

	struct t2fs_inode *work_directory;
	struct t2fs_record *file_record = malloc(sizeof(struct t2fs_record));
	int handle = -10;

	if (pathname[0] == '/'){
		work_directory = ROOT_I_NODE;
	}
	else {
		work_directory = CURRENT_I_NODE;
	}

	char root[] = "/";

	if(strcmp(root, pathname) == SUCCESS){

		file_record->TypeVal = TYPEVAL_DIRETORIO;
		file_record->inodeNumber = 0;
		strcpy(file_record->name, root);
	}

	else {
		file_record = find_directory(work_directory, pathname);
	}

	if (file_record != NULL){
		for (int i = 0; i < 10; ++i){
			if (DIRECTORIES[i].record_info->TypeVal == TYPEVAL_DIRETORIO &&
				DIRECTORIES[i].record_info->inodeNumber == file_record->inodeNumber){
				handle = i;

				get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
				// printf("OPDIR> INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
				return handle;
			}
			else if (handle == -10 && 
				DIRECTORIES[i].record_info->TypeVal == TYPEVAL_INVALIDO){
				handle = i;
				get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
				// printf("OPDIR> INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
			}
		}

		if (handle >= 0){
			DIRECTORIES[handle].record_info = file_record;
			get_i_node(DIRECTORIES[handle].record_info->inodeNumber, CURRENT_I_NODE);
			// printf("OPDIR> INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
			return handle;
		}

		else {
			get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
			// printf(" OPDIR>INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
			printf("ERRO: Maximo de diretórios abertos atingido.\n");
			return ERROR;
		}
	}

	else{
		get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
		// printf("OPDIR> INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
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

	if (init_all() != SUCCESS){
		return ERROR;
	}

	if (handle > 9 || handle < 0 || DIRECTORIES[handle].record_info->inodeNumber == -1){
		printf("ERROR: Handle inválido.\n");
		return ERROR;
	}

	struct t2fs_record *current_i_node_cpy = malloc(sizeof(struct t2fs_record));

	// printf(" INODE::::::..... %d\n", current_i_node_cpy->inodeNumber);

	char father [] = "..";

	current_i_node_cpy = find_directory(CURRENT_I_NODE, father);

	// printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);


	struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));

	if (get_i_node(DIRECTORIES[handle].record_info->inodeNumber, aux_inode) == SUCCESS){

		struct t2fs_record *aux_record;
		aux_record = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

		if(aux_inode->blocksFileSize > 0){
			if (load_block(aux_inode->dataPtr[0]) == SUCCESS){
				int i = DIRECTORIES[handle].seek_pointer;
				if (i < 16) {
					memcpy(aux_record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
					if(aux_record->TypeVal == TYPEVAL_REGULAR || aux_record->TypeVal == TYPEVAL_DIRETORIO){
						struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));
						if (get_i_node(aux_record->inodeNumber, aux_inode) == SUCCESS){
							strcpy(dentry->name, aux_record->name);
							dentry->fileType = aux_record->TypeVal;
							dentry->fileSize = aux_inode->bytesFileSize;
						}
						DIRECTORIES[handle].seek_pointer++;

						get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
						// printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
						return SUCCESS;
					}

					else {
						get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
						// printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
						return ERROR;
					}
				}
			}
		}

		if(aux_inode->blocksFileSize > 1){
			if (load_block(aux_inode->dataPtr[1]) == SUCCESS){
				int i = DIRECTORIES[handle].seek_pointer;
				if (i < 32) {
					memcpy(aux_record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
					if(aux_record->TypeVal == TYPEVAL_REGULAR || aux_record->TypeVal == TYPEVAL_DIRETORIO){
						struct t2fs_inode *aux_inode = malloc(sizeof(struct t2fs_inode));
						if (get_i_node(aux_record->inodeNumber, aux_inode) == SUCCESS){
							strcpy(dentry->name, aux_record->name);
							dentry->fileType = aux_record->TypeVal;
							dentry->fileSize = aux_inode->bytesFileSize;
						}
						DIRECTORIES[handle].seek_pointer++;

						get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
						// printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
						return SUCCESS;
					}
					else {

						get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
						// printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
						return ERROR;
					}
				}
			}
		}

		get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
		printf("INODE NUM: %d\n", current_i_node_cpy->inodeNumber);
		return ERROR;
	}

	get_i_node(current_i_node_cpy->inodeNumber, CURRENT_I_NODE);
	printf("ERROR: Erro na leitura do inode do diretório.\n");
	return ERROR;
}


/*-----------------------------------------------------------------------------
Função:	Fecha o diretório identificado pelo parâmetro "handle".

Entra:	handle -> identificador do diretório que se deseja fechar (encerrar a operação).

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int closedir2 (DIR2 handle){

	if (init_all() != SUCCESS){
		return ERROR;
	}

	if (DIRECTORIES[handle].record_info->TypeVal == TYPEVAL_DIRETORIO){
		DIRECTORIES[handle].record_info->TypeVal = TYPEVAL_INVALIDO;
		DIRECTORIES[handle].record_info->inodeNumber = -1;
		strcpy(DIRECTORIES[handle].record_info->name, "indef");
		DIRECTORIES[handle].seek_pointer = 0;
		return SUCCESS;
	}

	return ERROR;
}
