#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNSET		-2
#define ERROR		-1
#define NO_EXIT		 0
#define EXIT		 1
#define BRUTE_FORCE	 2
#define DISPLAY_HASH	 3
#define UNRAVEL_HASH	 4

char letters[] = "acdegilmnoprstuw";
char word[32];
long long int hash_input = 945924806726376;
bool verbose = false;

bool is_hash_valid(long long int h) {
 if (h <= 7) return false;
 return true;
}

int check_args(int argc,char *argv[]) {
 if (argc <= 1) return 0;
 int mode = UNSET;
 for (int i = 1; i < argc; i++) {
  if (strcmp(argv[i],"--brute-force") == 0) {
   if (mode != UNSET) goto LABERR;
   mode = BRUTE_FORCE;
   if (argc >= i+2) {
    long long int n = atoll(argv[++i]);
    if (n > 0) hash_input = n;
   } else {
    scanf("%lld",&hash_input);
   }
   continue;
  }
  if (strcmp(argv[i],"--display-hash") == 0) {
   if (mode != UNSET) goto LABERR;
   mode = DISPLAY_HASH;
   if (argc > i+1) {
    strcpy(word,argv[++i]);
    continue;
   } else {
    scanf("%s",word);
   }
   continue;
  }
  if (strcmp(argv[i],"--unravel-hash") == 0) {
   if (mode != UNSET) goto LABERR;
   mode = UNRAVEL_HASH;
   if (argc > i+1) {
    long long int n = atoll(argv[++i]);
    if (n > 0) hash_input = n;
   } else {
    scanf("%lld",&hash_input);
   }
   continue;
  }
  if (strcmp(argv[i],"--verbose") == 0 || strcmp(argv[i],"-v") == 0) {
   verbose = true;
   continue;
  }
  printf("Invalid command: %s\n",argv[i]);
  return ERROR;
 }
 return mode;

 LABERR: {
  printf("Error: Only one mode may be specified.\n");
  return ERROR;
 }
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

int check(char word[], int pos) {
 for (int i = 0; i < strlen(letters); i++) {
  word[pos] = letters[i];
  if (hash(word) == hash_input) {
   return EXIT;
  }
  if (pos > 0)
   if (check(word,pos-1) == EXIT) return EXIT;
 }
 return NO_EXIT;
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
   if (hash_input <= 7) {
    printf("Error: Invalid hash\n");
    return ERROR;
   }
   if (verbose) {
    printf("Brute-forcing a result. This might take a while.\n");
   }
   char str[] = "aaaaaaaaa";
   check(str,strlen(str)-1);
   if (verbose) {
    printf("The magic word is: %s\n",word);
   } else {
    printf("%s\n",word);
   }
   return 0;
  }
  case DISPLAY_HASH: {
   if (verbose) {
    printf("The hash for '%s' is: %lld\n",word,hash(word));
   } else {
    printf("%lld\n",hash(word));
   }
   return 0;
  }
  case UNRAVEL_HASH: {
   if (!is_hash_valid(hash_input)) {
    printf("Error: Invalid hash\n");
    return ERROR;
   }
   unravel(hash_input);
   if (verbose) {
    printf("The magic word is: %s\n",word);
   } else {
    printf("%s\n",word);
   }
   return 0;
  }
  case ERROR: {
   return ERROR;
  }
  default: {
   printf("Specify a command: --brute-force, --display-hash WORD, or "
          "--unravel-hash\n");
   return ERROR;
  }
 }
 return 0;
}

