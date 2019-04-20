#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int print_anagram(VNode *head, int count){
	if (!head) return count;
	VNode *cur = head->next;
	if (cur){
		printf("Anagram for '%s':\n",head->value);
		count ++;
		while(cur){
			printf("%s ", cur->value);
			cur = cur->next;
		}
    printf("\n");
	}
	return count;
}

int cmpfunc( const void *a, const void *b) {
  return *(char*)a - *(char*)b;
}

int main (int argc, char ** argv) {
	static DNode* dictionary [DEFAULT_HASH_SIZE];

  FILE * fp;

  if (argc > 1){
    fp = fopen(argv[1], "r");
  	if(fp == NULL)  {
  		printf("Error opening file words.txt\n");
  		return 1;
  	}
  } else{
    printf("No file given, default to opening file \'words.txt\'\nTo use other file, pass file name as argument: \'./anagram_search <filename>\'\n\n");
    fp = fopen("words.txt", "r");
  	if(fp == NULL)  {
  		printf("Error opening file words.txt\n");
  		return 1;
  	}
  }


	char buf[30];
	while(fscanf(fp, "%s", buf) != EOF){
		char * key = copystr(buf);
		qsort(key, strlen(key), sizeof(char), cmpfunc);
		// printf("%s:%s\n",key,buf);
		set(dictionary, DEFAULT_HASH_SIZE, key, buf);
		free(key);
	}
  fclose(fp);
	int count = 0;
	for (int i = 0; i < DEFAULT_HASH_SIZE; i++){
		if (dictionary [i]!=NULL){
			// printf("Anagrams for %s\n",(dictionary[i])->key);
			// print_list((dictionary[i])->values);
			for (DNode *np = dictionary[i]; np !=NULL; np = np->next){
				count = print_anagram(np->values, count);
			}
		}
	}
	printf("Total number of anagram is %d\n", count);

	//Personal test
	// DNode *result;
	// result = get (dictionary, DEFAULT_HASH_SIZE, "how");
	// if (result != NULL) {
	// 	printf("Anagrams for 'how':\n");
	// 	print_list (result->values);
	// }
	// else
	// 	printf ("'how' not found\n");

	free_dictionary(dictionary, DEFAULT_HASH_SIZE);


	return 0;
}
