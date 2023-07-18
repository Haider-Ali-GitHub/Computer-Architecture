#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];

  // fgets() reads one line at a time from the input. If you want to get a value from the next line, you have to call fgets() again.
  char* string = fgets(buf, 256, fp);
  int x = atoi(string);
  char* string1 = fgets(buf, 256, fp);
  int z = atoi(string1);

    double c  = sqrt((pow(x, 2)) + (pow(z, 2)));

    if(x > z){
       double b = sqrt((pow(x, 2)) -  (pow(z, 2)));
       if(fmod(b,1) == 0 )
         {
            printf("%d\n",(int)b);
          }
            else if((fmod(c,1)) == 0)
            {
               printf("%d\n",(int)c);
            }
              else{
                    printf("-1\n");
                  }    
    }
    else{ 
      double b = sqrt((pow(z, 2)) - (pow(x, 2)));
         if(fmod(b,1) == 0 )
         {
            printf("%d\n",(int)b);
          }
            else if((fmod(c,1)) == 0)
            {
               printf("%d\n",(int)c);
            }
              else{
                    printf("-1\n");
                  } 
    }
    
  // Printing in C.
  // %d is the format specifier for integer numbers.
  // \n is the newline character

  return EXIT_SUCCESS;

}
