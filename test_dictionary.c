#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

void print_list(VNode *head){
	VNode *cur = head;
	while(cur){
		printf("%s ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

int print_anagram(VNode *head, int count){
	if (!head) return count;
	VNode *cur = head->next;
	if (cur){
		printf("Anagram for '%s':\n",head->value);
		count ++;
		while(cur){
			printf("%s\n", cur->value);
			cur = cur->next;
		}
	}
	return count;
}

int cmpfunc( const void *a, const void *b) {
  return *(char*)a - *(char*)b;
}

int main (int argc, char ** argv) {

	//either static or use calloc - to set all bytes initially to 0
	static DNode* dictionary [DEFAULT_HASH_SIZE];

	// DNode* result;
	// set(dictionary, DEFAULT_HASH_SIZE, "pore", "repo");
	// set(dictionary, DEFAULT_HASH_SIZE, "pore", "rope");
	//
	//
	// result = get (dictionary, DEFAULT_HASH_SIZE, "pore");
	// if (result != NULL) {
	// 	printf("Anagrams for 'pore':\n");
	// 	print_list (result->values);
	// }
	// else
	// 	printf ("'pore' not found\n");
	//
	// set(dictionary, DEFAULT_HASH_SIZE, "bore", "robe");
	// result = get (dictionary, DEFAULT_HASH_SIZE, "bore");
	// if (result != NULL) {
	// 	printf("Anagrams for 'bore':\n");
	// 	print_list (result->values);
	// }
	// else
	// 	printf ("'bore' not found\n");

	FILE *fp = fopen("words.txt", "r");
	if(fp == NULL)  {
		printf("Error opening file words.txt\n");
		return 1;
	}
	char buf[20];
	while(fscanf(fp, "%s", buf) != EOF){
		char * key = copystr(buf);
		qsort(key, strlen(key), sizeof(char), cmpfunc);
		// printf("%s:%s\n",key,buf);
		set(dictionary, DEFAULT_HASH_SIZE, key, buf);
		free(key);
	}
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
	//
	// free_dictionary(dictionary, DEFAULT_HASH_SIZE);


	return 0;
}
