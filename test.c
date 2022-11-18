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
int faceValue(char symbol)
{
    if (symbol < 65){
        return symbol - '0';

    }
    else {
	    switch(symbol)
	    {
		 case 'A': return 10;
		 case 'B': return 11;
		 case 'C': return 12;
		 case 'D': return 13;
		 case 'E': return 14;
		 case 'F': return 15;
		default:
		{
		 return -1;
		}
	    }
    }
}
int main(){

//name changing
    char c[] = "text.crp";
    char *pptr = strchr(c, '.');
    int ppos = pptr - c;
    char newName[ppos + 1];
    substring(c, newName, 0, ppos);
    strcat(newName, ".txt");

//encryption
    char ch;
    char ch2;
    FILE *inputfile = fopen(c, "r"); //reads file
    FILE *outputfile = fopen(newName, "w"); //

    int run = 1;
    ch = fgetc(inputfile);
    ch2 = fgetc(inputfile);
    char outChar;



    while (ch != EOF)
    {
        if (ch == '0' && ch2){
            fputc('\n', outputfile); //converts new line character
            ch = ch2; 
            ch2 = fgetc(inputfile);
            
        }

        else if (ch == 'T'&& ch2 == 'T'){
            fputs("TT", outputfile); //converts tab character
            ch = fgetc(inputfile); 
            ch2 = fgetc(inputfile);
        }
        else if (ch == '8'&&ch2 == '0'){
            fputc(' ', outputfile);
            ch = fgetc(inputfile); 
            ch2 = fgetc(inputfile);
        }
        
        else {
          outChar = (faceValue(ch)*16) + faceValue(ch2);
          outChar += 16; 

          if (outChar > 127) {
            outChar= (outChar - 144) + 32;
            
          }
          ch = fgetc(inputfile); 
          ch2 = fgetc(inputfile);
          putc(outChar, outputfile);
        }
          



    }

    fclose(inputfile);
    fclose(outputfile);
}
