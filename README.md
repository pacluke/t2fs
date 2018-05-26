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
