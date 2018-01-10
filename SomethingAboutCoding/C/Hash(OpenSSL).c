
FILE		*fp_input = NULL;			/** << input file pointer > */
/**
 * \brief  open all file
 * \param  argv[]            [IN] argument value array
 * \retval PROG__SUCCESS   :success
 *         PROG_FAILED     :error
 */
static int32_t open_file(char *argv[])
{
	/** << open input file > */
	fp_input = fopen(argv[4], "rb");
	if (NULL == fp_input)
	{
		printf("[ERROR] : failed to open input file.\n");
		return PROG_FAILED;
	}
	
	return PROG_SUCCESS;
}
/**
 * \brief  calculate hash
 * \param  hash    [IN] pointer of hash
 * \retval PROG__SUCCESS   :success
 *         PROG_FAILED     :error
 */
static int32_t calculate_hash( int64_t offset, int64_t size, uint8_t *hash )
{
	int32_t		ret;						/** << method result > */
	SHA256_CTX	sha256_ctx;					/** << SHA256 context > */
	int64_t		remain_size;				/** << remain data size > */
	int32_t		req_size;					/** << process request size > */
	uint8_t		data_buf[PROG_DATA_SIZE];	/** << read data > */
	
	/** ------------------------------------------------------------- */
	/** << calculate temporary hash from inputfile                  > */
	/** ------------------------------------------------------------- */
	/** << initialize sha256 context > */
	ret = SHA256_Init(&sha256_ctx);
	if (1 != ret)
	{
		printf("[ERROR] : failed to SHA256_Init().\n");
		return PROG_FAILED;
	}
	
	/** << update sha256 context > */
	ret = fseeko(fp_input, offset, SEEK_SET);
	if (PROG_SUCCESS != ret)
	{
		printf("[ERROR] : failed to set inputfile fp.\n");
		return PROG_FAILED;
	}
	remain_size = size;
	
	while (remain_size > 0)
	{
		/** << size of proccess > */
		if (PROG_DATA_SIZE <= remain_size)
		{
			req_size = PROG_DATA_SIZE;
		}
		else
		{
			req_size = (int32_t)remain_size;
		}
		
		remain_size -= req_size;
		
		/** << read data > */
		memset(data_buf, 0, PROG_DATA_SIZE);
		ret = fread(data_buf, 1, req_size, fp_input);
		if (req_size != ret)
		{
			printf("[ERROR] : failed to read inputfile. request size = 0x%x, ret = 0x%x\n", req_size, ret);
			return PROG_FAILED;
		}
		
		/** << update sha256 > */
		ret = SHA256_Update(&sha256_ctx, data_buf, req_size);
		if (1 != ret)
		{
			printf("[ERROR] : failed to SHA256_Update().\n");
			return PROG_FAILED;
		}
	}
	
	/** << finalize sha256 contex > */
	ret = SHA256_Final(hash, &sha256_ctx);
	if (1 != ret)
	{
		printf("[ERROR] : failed to SHA256_Final().\n");
		return PROG_FAILED;
	}
	
#if 0 //for debug
	int i;
	for(i = 0; i < 32; i++)
	{
		printf("%02x,", hash[i]);
	}
	printf("\n\n");
#endif
	
	return PROG_SUCCESS;
}