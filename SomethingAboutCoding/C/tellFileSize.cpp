1.	/* get file size */
	fseek( fp, 0, SEEK_END );
	ulRuleFileSize = ( u_int32 )ftell( fp );
	fseek( fp, 0, SEEK_SET );
	
2.	