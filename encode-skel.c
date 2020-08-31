#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Program developed for NWEN243, Victoria University of Wellington
   Author: Kris Bubendorfer (c) 2015.
   Uses a modified caeser I & II

   Compile:  gcc -o encode encode.c

   // Make a file with a plain aplhabet in it:

   % cat > test
   ABCDEFGHIJKLMNOPQRSTUVWXYZ
   ^D

   // test it - this should be the correct result when encoding.

   % cat test | encode "i came, i saw"
   key: HJKLNOPQRTUVICAMESWXYZBDFG - 26
   HJKLNOPQRTUVICAMESWXYZBDFG

 */

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

char* fixkey(char* s){
  int i, j;
  char plain[26]; // assume key < length of alphabet, local array on stack, will go away!

  for(i = 0, j = 0; i < strlen(s); i++){
    if(isalpha(s[i])){

            int duplicate = 0;
            for(int k =0;k<i;k++) {
                    if(upcase(s[i])==plain[k]) {
                            duplicate = 1;
                    }
            }
            if(duplicate ==0) {
                plain[j++] = upcase(s[i]);
        }
    }
  }
  plain[j] = '\0';
  //printf("format is: '%s' key", plain);
  s=(char *)malloc(strlen(plain)*sizeof(char));
  return strcpy(s,plain);
}

void buildtable (char* key, char* encode){
        // This function needs to build an array of mappings in the 'encode' array from plaintext characters
        // to encypered characters.  The encode array will be indexed by the plaintext char.  To
        // make this a useful 0-26 index for the array, 'A' will be stubtracted from it (yes you
        // can do this in C).  You can see this in the main(){} below.  The values in the array
        // will be the cipher value, in the example at the top A -> H, B -> J, etc.

        // You are implementing a Caesar 1 & 2 combo Cypher as given in handout.
        // Your code here:

        // probably need to declare some stuff here!

  int offset = strlen(key);
  char temp[26];
  char *newKey = fixkey(key); // fix the key, i.e., uppercase and remove whitespace and punctuation
  // the simplest way to do this is to do exactly the same as you did when creating the
  // encode table, and then look up the encode table to get the translations, and build the
  // decode table from this.  This isn't the most efficient approach, but it will get the
  // job done unless you want to be fancy.
  int keyLength = strlen(newKey);
  printf("%s\n",newKey);
  int pos = offset-1;
  for(int i =0;i<keyLength;i++) {
          if(pos >25) {
                  pos = 0;
          }
          temp[pos] = newKey[i];
          pos++;
  }
  printf("%s\n",temp );
  char c = newKey[keyLength-1];
  for(int i =0;i<26;i++){
          if(c++ >= 'Z') {
                  c = 'A';
          }
          if(pos>25) {
                  pos =0;
          }
          if(strchr(newKey,c) == NULL) {
                  temp[pos] = c;
                  pos++;
          }
  }
  strcpy(encode,temp);
}

int main(int argc, char **argv){
  // format will be: 'program' key {encode|decode}
  // We'll be using stdin and stdout for files to encode and decode.

  // first allocate some space for our translation table.

  char* encode = (char*)malloc(sizeof(char)*26);
  char ch;

  argc = 2;

  if(argc != 2){
    printf("format is: '%s' key", argv[0]);
    exit(1);
  }
  // Build translation tables, and ensure key is upcased and alpha chars only.
  argv[1] = "ABCDEFGHIJKLMNOPQRSTUVWXY";
  buildtable(argv[1], encode);

  // write the key to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", encode, strlen(encode));

  // the following code does the translations.  Characters are read
  // one-by-one from stdin, translated and written to stdout.

  ch = fgetc(stdin);
  while (!feof(stdin)) {
    if(isalpha(ch)){        // only encrypt alpha chars
      ch = upcase(ch);      // make it uppercase
      fputc(encode[ch-'A'], stdout);
    }else
      fputc(ch, stdout);
    ch = fgetc(stdin);      // get next char from stdin
  }
}
