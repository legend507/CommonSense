/*
�����w��ϊ������o�͂𕶎���Ɋi�[���܂�

�y�����z
#include <stdio.h>
int sprintf(char *str, const char *format,  �D�D�D ); 
�y�����z
char *str�@�F�@�ϊ������o�͂��i�[���镶����B
const char *format�@�F�@�����w�蕶����B�@�ڂ�����printf�֐����Q�Ƃ̂��ƁB
�D�D�D�@�F�@�ό����B���̈����������w��ɏ]���ϊ����܂��B�����w�蕶����͂��̈����Ɠ����K�v�ł��B

�y�߂�l�z
�������@�F�@str�Ɋi�[�����������i�Ō��'\0'�͏����j
���s���@�F�@EOF
�y�g�p��z
// step1: put char array into str, 
// step2: use puts(str); to output what's in str
*/
#include        <stdio.h>

int     main(void)
{
        int             i;
        char    str[100];
        char    str1[] = "������";
        char    str2[] = "�A��";
        char    str3[] = "����y";

        for (i=1; i<=10; i++) {
                /* ���[�v�񐔂𕶎���Ɋi�[ */
                sprintf(str,"���[�v�񐔁F%2d",i);
                puts(str);
        }

        sprintf(str,"%s��%s������%s��",str1,str2,str3);
        puts(str);

        return 0;
}
/*
�y���s���ʁz
���[�v�񐔁F 1
���[�v�񐔁F 2
���[�v�񐔁F 3
���[�v�񐔁F 4
���[�v�񐔁F 5
���[�v�񐔁F 6
���[�v�񐔁F 7
���[�v�񐔁F 8
���[�v�񐔁F 9
���[�v�񐔁F10
������̘A�������Ă���y��
*/
