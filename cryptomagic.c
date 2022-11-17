#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

void substring(char* in,char*out, int index, int length){
int i = 0; 
while (i < length){
    out[i] = in[index+i];
    i++;
}
out[length] = '\0';
}


void encrypt(char *fname){
char *pptr = strchr(fname, '.');
int ppos = pptr - fname; 
char newName[ppos+1];
substring(fname, newName, 0, ppos);
strcat(newName, ".crp");

char outChar; 
char end = NULL;
FILE *in = fopen(fname, "r"); 
if (in == NULL){
  puts("Error: Empty File");
}
FILE *out = fopen(newName, "w");
if (out == NULL){
  puts("Error: Empty File");
}
int run = 1; 
while(run == 1);  {
  outChar = fgetc(in); 
  printf("%c", outChar);

  if (outChar == '\0'){
    run = 0; 
  }
  else if (outChar == '\n'){
    fputc('\n', out);
  }
  else if(outChar == '\t'){
    fputc('\t', out);
 
  }
  else {
    outChar = outChar - 16; 
     if (outChar < 32){
     outChar =(outChar - 32) + 144;
     fprintf(out,"%02X",outChar);
    }
  }


}





}



int main (int argc, char *argv[]){ // argc = number of parameters passed, argv = pointer to array of parameters passed 

  if (argc == 1) { // if the program is ran and no switch is passed, execute the code below
    printf("Enter cryptoMagic -E \"File Name\".txt to encript a file\nEnter cryptoMagic -D \"File Name\".crp to decrypt a file");   
  }

  if (argc == 3){ // if the user passes 3 parameters, execute code below
    if (strcmp(argv[1], "-E") == 0){ // if the inputted string is "-E", encrypt the specified file
    encrypt(argv[2]);
    }

    
    else if (strcmp(argv[1], "-D") == 0){ // if the inputted string is "-D", decrypt the specified file
    

   }
  }
}