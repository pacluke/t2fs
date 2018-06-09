	struct t2fs_record *record;
	record = (struct t2fs_record *) malloc(sizeof(struct t2fs_record));

	if(CURRENT_I_NODE->blocksFileSize > 0){
		if (load_block(CURRENT_I_NODE->dataPtr[0]) == SUCCESS){
			for(int i = 0; i < MAX_RECORDS; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
					print_record(record);
				}
			}
		}
		return SUCCESS;
	}
	if(CURRENT_I_NODE->blocksFileSize > 1){
		if (load_block(CURRENT_I_NODE->dataPtr[1]) == SUCCESS){
			for(int i = 0; i < MAX_RECORDS; i++) {
				memcpy(record, &CURRENT_BLOCK[i*64], sizeof(struct t2fs_record));
				if(record->TypeVal == TYPEVAL_REGULAR || record->TypeVal == TYPEVAL_DIRETORIO){
					print_record(record);
				}
			}
		}
		return SUCCESS;
	}