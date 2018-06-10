#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2fs.h"

int main(int argc, char const *argv[])
{
	char pathname[255];
	char dir[] = "/dir2/dir21";

	if(chdir2(dir) == 0)
		printf("O diretório atual é: %s\n", dir);

	if(getcwd2(pathname, 255) == 0)
		printf("O retorno de getcwd2 foi: %s\n", pathname);

	return 0;
}