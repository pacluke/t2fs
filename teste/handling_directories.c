#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2fs.h"

int main(int argc, char const *argv[])
{
	char dir[] = "/dir2";
	int handle= -1;

	handle = opendir2(dir);

	if (handle >= 0){
		printf("O diretório %s foi aberto e seu handle é %d.\n", dir, handle);
	}

	printf("Conteúdo do diretório %s de handle %d:\n", dir, handle);

    DIRENT2 dentry;
    while ( readdir2(handle, &dentry) == 0 ) {
        printf ("%c %8u %s\n", (dentry.fileType==0x02?'d':'-'), dentry.fileSize, dentry.name);
    }

	if (closedir2(0) == 0){
		printf("O diretório %s de handle %d foi fechado.\n", dir, handle);
	}

	return 0;
}