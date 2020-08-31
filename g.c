#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TEXT_SIZE 1000000  // Note, the longer the text the more likely you will get a good 'decode' from the start.
#define ALEN 26         // Number of chars in ENGLISH alphabet
#define CHFREQ "ETAONRISHDLFCMUGYPWBVKJXQZ" // Characters in order of appearance in English documents.
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/* Program developed for NWEN243, Victoria University of Wellington
   Author: Kris Bubendorfer, this extended version (c) 2015
   LAB: 2
   This program applies a basic frequency analysis on a cyphertext.  It has been extened over the 2014 version to
   solve polyalphabetic cyphers - by brute force.  In this case, it applies the frequency analysis for different
   numbers of n keys (polyalphabetic Caeser).  Obviously it will need a cypher of about n times
   the typical length for a monoalphabetic cypher.
   Program is used like this:
   Compile:  gcc -o crack crack.c
   Test file (ctext): JWRLS, XSSH PZK JH HES BJFV, UZU (this is not a realistic length piece of cypher text)
   crack n
   Argument:
   n number of keys to try
   ---
   % cat ctext | crack 1
   ALICE, MEET YOU AT THE PARK, BOB   <-- of course it won't be this correct.  Don't worry about that for the -d option.
   AMFDE, UEET LNH AT TIE RASC, ONO   <-- this is what it really looks like, a larger sample is better, this is short.
 */

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

int main(int argc, char **argv){

  // first allocate some space for our input text (we will read from stdin).
  char* text = (char*)malloc(sizeof(char)*TEXT_SIZE+1);
  char ch;
  int n, i;

  if(argc > 1 && (n = atoi(argv[1])) > 0); else{ fprintf(stderr,"Malformed argument, use: crack [n], n > 0\n"); exit(-1);} // get the command line argument n

  // Now read TEXT_SIZE or feof worth of characters (whichever is smaller) and convert to uppercase as we do it.
  // Added: changed to count frequencies as we read it in

  for(i = 0, ch = fgetc(stdin); i < TEXT_SIZE && !feof(stdin); i++, ch = fgetc(stdin)){
    text[i] = (ch = (isalpha(ch)?upcase(ch):ch));
  }
  text[i] = '\0'; // terminate th                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              e string properly.

  /* At this point we have two things,
   *   1. The input cyphertext in "text"
   *   2. The maximum number of keys to try (n) - we'll be trying 1..n keys.
   *
   * What you need to do is as follows:
   *   1. create a for-loop that will check key lengths from 1..n
   *   2. for each i <= n, spit the cypher text into i sub-texts.  For i = 1, 1 subtext, for i = 2, 2 subtexts, of alternating characters etc.
   *   3. for each subtext:
   *          a. count the occurance of each letter
   *          b. then map this onto the CHFREQ, to create a map between the sub-text and english
   *          c. apply the new map to the subtext
   *   4. merge the subtexts
   *   5. output the 'possibly' partially decoded text to stdout.  This will only look OK if i was the correct number of keys
   *
   * what you need to output (sample will be provided) - exactly:
   * i maps -> stderr
   * i 'possible' translations
   *
   * You would be wise to make seperate functions that perform various sub-tasks, and test them incrementally.  Any other approach will likely
   * make your brain revolt.  This isn't a long program, mine is 160 lines, with comments (and written in a very verbose style) - if yours is
   * getting too long, double check you're on the right track.
   *
   */

  // Your code here...
//   for(int keys = 1; keys <= n; keys++){
//   for(int k = 0; k < TEXT_SIZE; ++k){
//
//               printf("%c", text[k]);
//         }
//   }
char subCyphertexts[n][TEXT_SIZE + 1];
char decodedText[TEXT_SIZE];
for(int i = 0; i < TEXT_SIZE; ++i){
    decodedText[i] = '\0'; //initialise the decode char array.
}
for(int i = 0; i < n; ++i){
    for(int j = 0; j < TEXT_SIZE; ++j){
        subCyphertexts[i][j] = '\0'; //initialise the array of subtexts.
    }
}
//--------------------------------------splitting start---------------------------------------------------------------//
  for(int i = 1; i <= n ; ++i){ // checks key lengths from 1..n.

    for(int j = 0; j < i; ++j){ // split the text into i subtexts.
        for(int k = 0; k < TEXT_SIZE; ++k){
            //if(text[j + n * k] == '\0') break;
            //printf("%c", text[j + n * k + 1]);
            if(j + i * k > TEXT_SIZE) break;
            subCyphertexts[j][k] = text[j + i * k] ;
        }
    }
//      for(int j = 0; j < n; ++j){ // split the text into i subtexts.
//           for(int k = 0; k < TEXT_SIZE; ++k){
//                if(subCyphertexts[j][k] == '\0') break;
//               printf("%c", subCyphertexts[j][k]);
//         }
//     }

//           for(int k = 0; k < TEXT_SIZE; ++k){
//
//               printf("%c", text[k]);
//         }
//
//--------------------------------------splitting end---------------------------------------------------------------//
int subTextLength = 0;
     for(int j = 0; j < i; ++j){ // split the text into i subtexts.
          for(int k = 0; k < TEXT_SIZE; ++k){
            if(subCyphertexts[j][k] == '\0') break;
            subTextLength++;
        }
    }
//--------------------------------------decoding start---------------------------------------------------------------//
 int frequencies[26]; // array of letter frequencies.
    // counts the frequency of the letters in the text.
    for(int i = 0; i < 26; i++) {
        frequencies[i] = 0;   //Initialise the frequency table.
    }

    for(int r= 0; r < i; r++) {
        for(int c = 0; c < subTextLength; c++){
        if(isalpha(subCyphertexts[r][c])){
            frequencies[subCyphertexts[r][c] - 65] += 1;
            //printf(" %d %c", subCyphertexts[r][c] - 65, subCyphertexts[r][c]);
            }
    }
    }

//      for(int i = 0 ; i < 26; i++)
//          printf("%d %c",frequencies[i], i+65 );
//        printf("\n");

    // array of letter occurances using the macro.
    char occurances[] = CHFREQ;
    char result[TEXT_SIZE];
    for(int i = 0; i < TEXT_SIZE; ++i){
        result[i] = '\0'; //initialise the result array.
    }


    char newFrequencies[26];
    int index = 0;
    int max = -9999;
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            if(frequencies[j] > max){
                max = frequencies[j];
                index = j;
            }
        }
        max = -9999;
        frequencies[index] = -9999; // set this to negative and start looking for the next letter that has highest occurance.
        newFrequencies[i] = index + 65;
    }



    for(int j = 0; j < i; ++j){
        for(int k = 0; k < subTextLength; k++){
            if(isalpha(subCyphertexts[j][k])){
                for(int a = 0; a < 26; a++){
                    if(newFrequencies[a] == subCyphertexts[j][k]){
                         subCyphertexts[j][k] = occurances[a]; //map it onto the CHFREQ.
                         break;
                    }
                }
            }
            result[i * k + j] = subCyphertexts[j][k]; // if it is not letter put it into result directly.
        }
    }
    printf("%s\n", result);
  }
//--------------------------------------decoding end---------------------------------------------------------------//

  return 0;
}
