#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define ERROR		-1
#define EXIT		 1
#define BRUTE_FORCE	 2
#define DISPLAY_HASH	 3
#define UNRAVEL_HASH	 4

char letters[] = "acdegilmnoprstuw";
char word[32];
long long int hash_input = 945924806726376;

int check_args(int argc,char *argv[]) {
 if (argc <= 1) return 0;
 if (strcmp(argv[1],"--brute-force") == 0) {
  if (argc >= 3) {
   long long int n = atoll(argv[2]);
   if (n > 0) hash_input = n;
  }
  return BRUTE_FORCE;
 }
 if (strcmp(argv[1],"--display-hash") == 0) {
  if (argc >= 3) {
   strcpy(word,argv[2]);
   return DISPLAY_HASH;
  }
  printf("Missing required word to translate.\n");
  return ERROR;
 }
 if (strcmp(argv[1],"--unravel-hash") == 0) {
  if (argc >= 3) {
   long long int n = atoll(argv[2]);
   if (n > 0) hash_input = n;
  }
  return UNRAVEL_HASH;
 }
 return ERROR;
}

long long int hash(char *s) {
 long long int h = 7;
 char str[2];
 for (int i = 0; i < strlen(s); i++) {
  str[0] = s[i];
  str[1] = '\0';
  h = (h * 37 + strcspn(letters,str));
 }
 return h;
}

bool check(char word[], int pos) {
 for (int i = 0; i < strlen(letters); i++) {
  word[pos] = letters[i];
  if (hash(word) == 945924806726376) {
   printf("The magic word is: %s\n",word);
   return EXIT;
  }
  if (pos > 0)
   if (check(word,pos-1) == EXIT) return true;
 }
 return false;
}

int unravel(long long int h) {
 char tmp[32];
 int i;
 for (i = 0; h > 37; i++) {
  tmp[i] = letters[h % 37];
  h /= 37;
 }
 int j = --i;
 for (; i >= 0; i--) {
  word[j-i] = tmp[i];
 }
 word[j+1] = '\0';
 return 0;
}

int main(int argc, char *argv[]) {
 switch (check_args(argc,argv)) {
  case BRUTE_FORCE: {
   printf("Brute-forcing a result. This might take a while.\n");
   char str[] = "aaaaaaaaa";
   check(str,strlen(str)-1);
   return 0;
  }
  case DISPLAY_HASH: {
   printf("The hash for '%s' is: %lld\n",word,hash(word));
   return 0;
  }
  case UNRAVEL_HASH: {
   unravel(hash_input);
   printf("%s\n",word);
   return 0;
  }
  default: {
   printf("Specify a command: --brute-force, --display-hash WORD, or "
          "--unravel-hash\n");
   return ERROR;
  }
 }
 return 0;
}

