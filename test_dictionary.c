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


int main (int argc, char ** argv) {

	//either static or use calloc - to set all bytes initially to 0
	static DNode* dictionary [DEFAULT_HASH_SIZE];

	DNode* result;
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "repo");
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "rope");


	result = get (dictionary, DEFAULT_HASH_SIZE, "pore");
	if (result != NULL) {
		printf("Anagrams for 'pore':\n");
		print_list (result->values);
	}
	else
		printf ("'pore' not found\n");

	set(dictionary, DEFAULT_HASH_SIZE, "bore", "robe");
	result = get (dictionary, DEFAULT_HASH_SIZE, "bore");
	if (result != NULL) {
		printf("Anagrams for 'bore':\n");
		print_list (result->values);
	}
	else
		printf ("'bore' not found\n");

	free_dictionary(dictionary, DEFAULT_HASH_SIZE);


	return 0;
}
