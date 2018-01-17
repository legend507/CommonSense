/*--------------------------------------------------
Explain:
C-style strings
Arrays of type char are special cases.
We use strings frequently, but there is no built-in string type in the language
A C-style string is implemented as an array of type char that ends with a special character, called the "null character".
The null character has ASCII value 0
The null character can be written as a literal in code this way: '\0'
Every string literal (something in double-quotes) implicitly contains the null character at the end
Since character arrays are used to store C-style strings, you can initialize a character array with a string literal (i.e. a string in double quotes), as long as you leave room for the null character in the allocated space.
  char name[7] = "Johnny";
Notice that this would be equivalent to:
  char name[7] = {'J', 'o', 'h', 'n', 'n', 'y', '\0'};
    (or char name[] = "Johnny";        // size is 7)
As for int array, however, the declaration can be
  int list[] = {1, 3, 5, 7, 9};  // size is 5
--------------------------------------------------*/

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
