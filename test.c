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

int main(){

//name changing
    char c[] = "text.txt";
    char *pptr = strchr(c, '.');
    int ppos = pptr - c;
    char newName[ppos + 1];
    substring(c, newName, 0, ppos);
    strcat(newName, ".crp");

//encryption
    char ch;
    FILE *inputfile = fopen(c, "r"); //reads file
    FILE *outputfile = fopen(newName, "w"); //

    int run = 1;
    ch = fgetc(inputfile);

    while (ch != EOF){

        if (ch == '\n'){
            fputc('\n', outputfile);
        }
        else if (ch == '\t'){
            fputs("TT", outputfile);
        }

        else{
            ch = ch - 16;

            if (ch < 32) {
                ch = (ch - 32) + 144;
            }
            
            fprintf(outputfile, "%02X", ch);
        }

        ch = fgetc(inputfile);
    }
}
