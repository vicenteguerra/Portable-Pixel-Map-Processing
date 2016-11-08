#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  FILE* inputFile;
  FILE* outputFile;

  char buffer[255];
  int magicNumberFlag = 0;
  int magicNumber = 0;
  int sizeFlag = 0;
  char size[10];
  int maximum, maximumFlag = 0;
  int colorLine = 0;
  int plusColor = 0;

  inputFile = fopen("lena_color.pnm", "r");

  outputFile = fopen("lena_gray.pgm", "w");
  fprintf(outputFile, "P2\n");

  while(fgets(buffer, 255, (FILE*) inputFile)) {
      if(strncmp(buffer, "#",1)){ // Exclude comments
        if(!magicNumberFlag){ // GET MagicNumber
          magicNumber = atoi(&buffer[1]);
          magicNumberFlag = 1;
        }else if(!sizeFlag){ // GET Size (Width Height)
            strcpy(size, buffer);
            fprintf(outputFile, "%s\n", size);
            sizeFlag = 1;
          }else if(!maximumFlag){ // GET Maximun Value for each colour
            maximum = atoi(buffer);
            fprintf(outputFile, "%i\n", maximum);
            maximumFlag = 1;
          }else{  // Get Colours
            if(colorLine == 2){
              fprintf(outputFile, "%i\n", plusColor/3);
              plusColor = 0;
              colorLine = 0;
            }else{
              plusColor = plusColor + atoi(buffer);
              colorLine++;
            }
          }
      }
  }
  printf("%i \n", magicNumber);
  printf("%s", size);
  printf("%i", maximum);
  fclose(inputFile);
  fclose(outputFile);

  return 0;
}
