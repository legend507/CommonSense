#include <stdio.h>
#include <stdlib.h>


#define MYLOG(zone, func, fmt, ...)		do{printf("%s() L%04d ZONE%03d: ", (const char*)__func__, __LINE__, zone); printf((fmt), ## __VA_ARGS__); printf("\n");} while(0)
#define LOG(func, ...)					do{printf("%s() LINE%04d: ", (const char*)__func__, __LINE__); printf("%05s", ## __VA_ARGS__);printf("\n");}while(0);

#define	RELLOG_ASCII( blkid, fmt, ... ) \
	do{ \
		printf("[CHEN]\n"); \
		printf( "%s() L%04d: ", (const char*)__func__, __LINE__); \
		printf( "log=" ); \
		printf( (const char*)(fmt), ## __VA_ARGS__ ); \
		printf( ", ucLogWriteNum=%d", ucLogWriteNum ); \
		printf( ", (ulWriteTime=%08X)", ulWriteTime ); \
		printf( ", (ulRestTime=%08X)", ulRestTime ); \
		printf( "\n" ); \
	} while( 0 )

int main() {
	MYLOG(0, __func__, "%04u", 250);
	MYLOG(1, __func__, "%05s", "shit");
	MYLOG(2, __func__, "%06u", 122, 222);
	//main() L0009 ZONE000: 0250
	//main() L0010 ZONE001:  shit

	

	return 0;

}
