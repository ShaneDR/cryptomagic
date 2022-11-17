#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void substring(char *in, char *out, int index, int length)
{
    int i = 0;
    while (i < length)
    {
        out[i] = in[index + i];
        i++;
    }
    out[length] = '\0';
}
int main()
{
    char c[] = "text.txt";
    char *pptr = strchr(c, '.');
    int ppos = pptr - c;
    char newName[ppos + 1];
    substring(c, newName, 0, ppos);
    strcat(newName, ".crp");

    char ch;
    FILE *in = fopen(c, "r");
    FILE *out = fopen(newName, "w+");

    int run = 1;
    ch = fgetc(in);
    while (ch != EOF)
    {
        if (ch == '\n')
        {
            fputc('\n', out);
        }
        else if (ch == '\t')
        {
            fputs("TT", out);
        }
        else
        {
            ch = ch - 16;
            if (ch < 32)
            { 
                ch = (ch - 32) + 144;
            }
            fprintf(out, "%02X", (int)(*(unsigned char*)(&ch)));
        }
        ch = fgetc(in);

    }
    printf("\nworked");
}
