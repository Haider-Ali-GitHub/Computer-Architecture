#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min ( size_t x, size_t y ) {
    return x<y ? x : y;
}

size_t levenshtein_recursive ( char* source, char* target ) {

    // printf( "source=%s\n", source );
    // printf( "target=%s\n", target );

    // if (strlen(source)==0) return strlen(target);
    // else if (strlen(target)==0) return strlen(source);
    // else if (source[0]==target[0]) return levenshtein_recursive (source+1, target+1);
    // else {
    //     size_t ins = levenshtein_recursive (source+1, target  );
    //     size_t del = levenshtein_recursive (source,   target+1);
    //     size_t sub = levenshtein_recursive (source+1, target+1);
    //     return 1 + min( min(ins,del), sub ); } 

//   size_t sourcelength = strlen(source);

//   size_t targetlength = strlen(target);

//   size_t twoD[sourcelength + 1][targetlength + 1];

//   for (size_t i = 0; i <= sourcelength; i++) {
//     twoD[i][0] = i;
//   }

//   for (size_t j = 0; j <= targetlength; j++) {
//     twoD[0][j] = j;
//   }

//     for(int i = 0; i <= sourcelength; i++){
//         for(int j = 0; j <= targetlength + 1; j++)
//         {
//             if(source[i][0] = 0)
//             {

//             }
//         }
//     }
  size_t sourcelength = strlen(source);
  size_t targetlength = strlen(target);

  size_t minD[sourcelength + 1][targetlength + 1];

  for (size_t i = 0; i <= sourcelength; i++) {
    minD[i][0] = i;
  }

  for (size_t j = 0; j <= targetlength; j++) {
    minD[0][j] = j;
  }

  for (size_t i = 1; i <= sourcelength; i++) {
    for (size_t j = 1; j <= targetlength; j++) {
      if (source[i - 1] == target[j - 1]) {
        minD[i][j] = minD[i - 1][j - 1];
      } else {
        minD[i][j] = 1 + min(min(minD[i - 1][j], minD[i][j - 1]), minD[i - 1][j - 1]);
      }
    }
  }
  return minD[sourcelength][targetlength];

}

int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];
    

    fscanf (inputFile, "%s\n%s", source, target);

    printf("%ld\n", levenshtein_recursive ( source, target ));

    return EXIT_SUCCESS;

}
