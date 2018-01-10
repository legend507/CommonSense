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
 * \brief  close all file
 * \param  None
 * \retval PROG__SUCCESS   :success
 *         PROG_FAILED     :error
 */
static int32_t close_file( void )
{
	int32_t		ret;						/** << method result > */
	int32_t		result = PROG_SUCCESS;		/** << return value > */
	
	/** << close inputfile > */
	if (NULL != fp_input)
	{
		ret = fclose(fp_input);
		if (PROG_SUCCESS != ret)
		{
			printf("[ERROR] : failed to close inputfile.\n");
			result = PROG_FAILED;
		}
	}
	
	/** << close keyfile > */
	if (NULL != fp_key)
	{
		ret = fclose(fp_key);
		if (PROG_SUCCESS != ret)
		{
			printf("[ERROR] : failed to close keyfile.\n");
			result = PROG_FAILED;
		}
	}
	
	/** << close revokeinfofile > */
	if (NULL != fp_revoke)
	{
		ret = fclose(fp_revoke);
		if (PROG_SUCCESS != ret)
		{
			printf("[ERROR] : failed to close revokeinfofile.\n");
			result = PROG_FAILED;
		}
	}
	
	/** << close outputfile > */
	if (NULL != fp_output)
	{
		ret = fclose(fp_output);
		if (PROG_SUCCESS != ret)
		{
			printf("[ERROR] : failed to close outputfile.\n");
			result = PROG_FAILED;
		}
	}
	
	return result;
}