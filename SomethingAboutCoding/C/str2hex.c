/**
 * \brief  convert str to hex
 * \param  str         [IN] before value
 * \param  hex         [OUT]after value
 * \retval PROG__SUCCESS   :success
 *         PROG_FAILED     :error
 */
static int32_t convert_str2hex( char *str, uint32_t *hex )
{
	char		*endptr = NULL;						/** << disable string > */
	
	/** << convert > */
	*hex = (uint32_t)strtol(str, &endptr, 16);
	
	if (0 != strlen(endptr))
	{
		printf("[ERROR] : failed to convert version. str=[%s] \n", endptr);
		return PROG_FAILED;
	}
	
	return PROG_SUCCESS;
}

/*  e.g. How to use
		ret = convert_str2hex(ver_byte_str, &ver_byte_number);
		if (PROG_SUCCESS != ret)
		{
			printf("[ERROR] : Input version is bad format.\n");
			return PROG_FAILED;
		}
*/