/* Project Name: Cryptomagic
*  Group members: Shane Ramphal, Kush Shastri
*  Description: This command line utility will encrypt a user inputed txt file and produce a .crp file. It will also do the opposite 
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// substring function for file name changing
void substring(char *in, char *out, int index, int length) {
  int i = 0;
  //copies file from the specifed index to the specified length of chaarcters 
  while (i < length) {
    out[i] = in[index + i]; 
    i++;
  }
  out[length] = '\0'; //all string end with "\0"
}

//changes the file type for the output file
char fileType(char fname, char newType){
  char *pptr = strchr(fname, '.'); // find the position of the period
  int ppos = pptr - fname;
  char newName[strlen(fname)]; //makes a new file name with the same size as the input file
  substring(fname, newName, 0, ppos); //copies the old name to the new name up to the period 
  strcat(newName, newType); //appends the new file type to the end of the file name
  return newName; //returns the new file name 
}

//gets the "face value" of the inputted character, used for decryption 
int faceValue(char symbol) {
  if (symbol < 65){ //if the symbol is not a letter, find the face value by subtracting '0'
    return symbol - '0';
  }
  else { //if the character is a letter, execute code below to find face value 
    switch (symbol) {
    case 'A':
      return 10;
    case 'B':
      return 11;
    case 'C':
      return 12;
    case 'D':
      return 13;
    case 'E':
      return 14;
    case 'F':
      return 15;
    default: 
      return -1;
    }
  }
}

// encryption function
void encrypt(char *fname) {

  char newName = fileType(fname, ".crp"); //makes a new file name with a .crp extension
  FILE *in = fopen(fname, "r"); //open the inputed file for reading 
  if (in == NULL) {
    puts("Error: Empty File");
  }
  FILE *out = fopen(newName, "w"); //open the output file for writing
  if (out == NULL){
    puts("Error: Empty File");
  }

  // encryption
  unsigned int outChar;//holds value of the character to be outputed 
  outChar = fgetc(in); // print character by character

  while (outChar != EOF) { // while the end of file has not been reached, run the loop
    if (outChar == '\n') {
      fputc('\n', out); // converts new line character
    }
    else if (outChar == '\t') {
      fputs("TT", out); // converts tab character
    }
    else { //encryption method outlined in assignment doc
      outChar = outChar - 16;
      if (outChar < 32)
      {
        outChar = (outChar - 32) + 144; // if the outchar value<32, perform operation
      }
      fprintf(out, "%02X", outChar); // print to the file
    }

    outChar = fgetc(in); // print character by character
  }
  //close both files and remove the original txt file 
  fclose(in);
  fclose(out);
  remove(fname);
}

//decryption function
void decrypt(char *fname) {

  char newName = fileType(fname, ".txt"); // converts file type   
  
  FILE *in = fopen(fname, "r");//opens .crp file for reading  
  FILE *out = fopen(newName, "w"); //opens new .txt file for writing

  char ch = fgetc(in); //holds first character in hex value 
  char ch2 = fgetc(in); //holds second character in hex value
  unsigned int outChar;

  while (ch != EOF) {
    if (ch == '\n') {// converts CR character
      fputc('\n', out); 
      ch = ch2;
      ch2 = fgetc(in);
    }
    else if (ch == 'T' && ch2 == 'T') {// converts tab character
      fputc('\t', out); 
      ch = fgetc(in);
      ch2 = fgetc(in);
    }
    else{ // if the character is not a CR or a tab, run decyption outlined in assignment doc
      outChar = (faceValue(ch) * 16) + faceValue(ch2);
      outChar += 16;

      if (outChar > 127){
        outChar = (outChar - 144) + 32;
      }
      ch = fgetc(in);
      ch2 = fgetc(in);
      putc(outChar, out);
    }
  }
//closes both files and removes the original .crp file
  fclose(in);
  fclose(out);
  remove(fname);
}

int main(int argc, char *argv[]) { // argc = number of parameters passed, argv = pointer to array of parameters passed

  if (strcmp(argv[1], "-E") == 0) { // if the inputted string is "-E", encrypt the specified file
      encrypt(argv[2]);
    }
  else if (strcmp(argv[1], "-D") == 0) { // if the inputted string is "-D", decrypt the specified file
    decrypt(argv[2]);
    }
  else // if the program is ran and no switch is passed, print the menu
    printf("Enter cryptoMagic -E \"File Name\".txt to encript a file\nEnter cryptoMagic -D \"File Name\".crp to decrypt a file");

return 0; 
}