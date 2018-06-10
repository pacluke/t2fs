#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2fs.h"

int main(int argc, char const *argv[])
{	
	printf("\n*** ATENÇÃO *** \nO TESTE A SEGUIR É DESTRUTIVO, OU SEJA\nO ARQUIVO file3 SERÁ REMOVIDO DO DISCO\nCASO ESTE TESTE JÁ TENHA OCORRIDO\nO ARQUIVO file3 NÃO EXISTE MAIS NO DISCO.\n");

	printf("Pressione enter para continuar...\n");
	getchar();

	char dir[] = "/file3";
	char dir_root[] = "/";
	int handle= -1;

	handle = opendir2(dir_root);

	if (handle >= 0){
		printf("O diretório %s foi aberto e seu handle é %d.\n", dir_root, handle);
	}

	printf("Conteúdo do diretório %s de handle %d:\n", dir_root, handle);

    DIRENT2 dentry;
    while ( readdir2(handle, &dentry) == 0 ) {
        printf ("%c %8u %s\n", (dentry.fileType==0x02?'d':'-'), dentry.fileSize, dentry.name);
    }

	if (closedir2(0) == 0){
		printf("O diretório %s de handle %d foi fechado.\n", dir_root, handle);
	}

	if (delete2(dir) == 0){
		printf("O arquivo %s foi removido.\n", dir);
	}

	handle = opendir2(dir_root);

	if (handle >= 0){
		printf("O diretório %s foi aberto e seu handle é %d.\n", dir_root, handle);
	}

	printf("Conteúdo do diretório %s de handle %d:\n", dir_root, handle);

    while ( readdir2(handle, &dentry) == 0 ) {
        printf ("%c %8u %s\n", (dentry.fileType==0x02?'d':'-'), dentry.fileSize, dentry.name);
    }

	if (closedir2(0) == 0){
		printf("O diretório %s de handle %d foi fechado.\n", dir_root, handle);
	}

	return 0;
}