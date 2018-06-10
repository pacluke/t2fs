#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2fs.h"

int main(int argc, char const *argv[])
{
	char dir[] = "/file3";
	int handle= -1;
	// printf("Esse é o conteúdo de %s:\n", dir);

	handle = open2(dir);

	if (handle >= 0){
		printf("O arquivo %s foi aberto e seu handle é %d.\n", dir, handle);
	}

	char content[255];

	if (read2(handle, content, 255) > 0){
		printf("O arquivo %s de handle %d foi lido e seu conteúdo é:\n", dir, handle);
		printf("%s\n\n\n", content);
	}

	if (seek2(0, 20) == 0){
		printf("O arquivo %s de handle %d tem seu ponteiro em 20 agora.\n", dir, handle);
	}

	char content2[255];

	if (read2(handle, content2, 255) > 0){
		printf("A leitura do arquivo %s de handle %d com ponteiro em 20 é:\n", dir, handle);
		printf("%s\n\n\n", content2);
	}

	if (close2(0) == 0){
		printf("O arquivo %s de handle %d foi fechado.\n", dir, handle);
	}

	return 0;
}