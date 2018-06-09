# t2fs

Segundo Trabalho da disciplina de Sistemas Operacionais (INF/UFRGS)

| Posição relativa		| Tamanho (bytes)   | Nome 				  		| Valor      |
| --------------------- |:-----------------:| ------------------------- | ---------- |
| 0 					| 4 				| *id* 						| "T2FS" 	 |
| 4 					| 2 				| *version* 				| 0x7E21     |
| 6 					| 2 				| *superBlockSize*  		| 1	 		 |
| 8 					| 2	 				| *freeBlocksBitmapSize* 	| 1 	 	 |
| 10 					| 2	 				| *freeInodeBitmapSize* 	| 1 		 |
| 12 					| 2 				| *inodeAreaSize*  			| 64 		 |
| 14 					| 2 				| *blockSize*  				| 4  		 |
| 16 			     	| 4 				| *diskSize*				| 32768 	 |
| 20 até o final (255)  | - 				| *resevado*				| - 		 | 



Situação atual:

| Função													| Implementada?		| Operacional?				|
| --------------------------------------------------------- |:-----------------:|:-------------------------:|
| `int identify2 (char *name,int size)`						| *SIM*				| *SIM* 					|
| `FILE2 create2 (char *filename)`							| *---*				| *---* 					|
| `int delete2 (char *filename)`							| *---*				| *---* 					|
| `FILE2 open2 (char *filename)`							| *SIM*				| *SIM* 					|
| `int close2 (FILE2 handle)` 								| *SIM*				| *SIM* 					|
| `int read2 (FILE2 handle, char *buffer, int size)`		| *---*				| *---* 					|
| `int write2 (FILE2 handle, char *buffer, int size)`		| *---*				| *---* 					|
| `int truncate2 (FILE2 handle)`							| *---*				| *---* 					|
| `int seek2 (FILE2 handle, unsigned int offset)`			| *SIM*				| *SIM* 					|
| `int mkdir2 (char *pathname)`								| *---*				| *---* 					|
| `int rmdir2 (char *pathname)`								| *---*				| *---* 					|
| `int chdir2(char *pathname)`								| *SIM*				| *SIM* 					|
| `int getcwd2 (char *pathname, int size)`					| *SIM*				| *SIM* 					|
| `DIR2 opendir2 (char *pathname)`							| *SIM*				| *SIM* 					|
| `int readdir2 (DIR2 handle, DIRENT2 *dentry)`				| *SIM*				| *SIM* 					|
| `int closedir2 (DIR2 handle) `							| *SIM*				| *SIM* 					|

