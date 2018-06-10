#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2fs.h"

int main(int argc, char const *argv[])
{
	char group[255];

	if(identify2(group, 255) == 0)
		printf("Developed by: \n%s\n", group);

	return 0;
}