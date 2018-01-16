#include <stdio.h>

void reverse(char *str) {
    char* end = str;
    char tmp;
    if(str) {
        while(*end) {
            ++ end;
        }
        -- end;
        while(str < end) {
            tmp = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
}

int main() {
    int i;

    // Attention: string[0]='0', string[1]='1', string[2]='2', string[3]='/0'
    // It is WRONG to declared string[3], because one more space is needed to put /0 !!!
    char string[4] = {'0', '1', '2'};

    for(i=0; i<4; i++)
        printf("%c", string[i]);

    reverse(string);

    for(i=0; i<4; i++)
        printf("%c", string[i]);

    return 0;
}
