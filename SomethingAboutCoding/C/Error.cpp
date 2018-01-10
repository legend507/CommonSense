/*
	this file contains some useful coding references
*/

#include <stdint.h>

/* Error Code (base code) */
#define SEC_SUCCESS                 (0x00000000)    /* Successful completion */
#define SEC_ERROR_GENERIC           (0x7FFF0001)    /* General error */
#define SEC_ERROR_BAD_FORMAT        (0x7FFF1002)    /* Bad format */
#define SEC_ERROR_BAD_PARAMETERS    (0x7FFF1003)    /* Bad parameters */
#define SEC_ERROR_BAD_STATE         (0x7FFF1004)    /* Bad state */
#define SEC_ERROR_NOT_SUPPORTED     (0x7FFF1005)    /* Operation not supported */
#define SEC_ERROR_OUT_OF_MEMORY     (0x7FFF1006)    /* Memory shortage */
#define SEC_ERROR_SHORT_BUFFER      (0x7FFF1007)    /* Buffer capacity shortage */
#define SEC_ERROR_SIGNATURE_INVALID (0x7FFF1008)    /* Signature verify error */
#define SEC_ERROR_MAC_INVALID       (0x7FFF1009)    /* MAC authentication error */
#define SEC_ERROR_CHAP_INVALID      (0x7FFF100A)    /* CHAP authentication error */
#define SEC_ERROR_STORAGE_NO_SPACE  (0x7FFF100B)    /* Storage capacity shortage */
#define SEC_ERROR_ITEM_NOT_FOUND    (0x7FFF100C)    /* File is not founded */
#define SEC_ERROR_STORAGE_CORRUPTED (0x7FFF100D)    /* Storage access error */
#define SEC_ERROR_SYSTEM            (0x7FFF100E)    /* System error */
#define SEC_ERROR_DETECTED          (0x7FFF1081)    /* Detect illegal operation */
#define SEC_ERROR_TEE               (0x7FFF1082)    /* TEE API error */
#define SEC_ERROR_CONTINUE          (0x7FFF1083)    /* Error occured but continue process */

#define ERRORTABLESIZE

static const int32_t error_table[ERRORTABLESIZE][2] = {
	{ SEC_SUCCESS,				1  },
	{ SEC_ERROR_CONTINUE,		11 }

};