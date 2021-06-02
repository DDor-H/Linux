#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node node_t;
struct node {
	char* name;
	node_t* next;
};

node_t* create_node(char* dname) {
	node_t* pnode = (node_t*)malloc(sizeof(node_t));
	assert(pnode != NULL);
	pnode->name = (char*)malloc(strlen(dname) + 1);
	assert(pnode->name != NULL);
	memset(pnode->name, 0x00, strlen(dname) + 1);
	strcpy(pnode->name, dname);
	pnode->next = NULL;
	return pnode;
}

void insert_list(node_t** head, char* dname) {
	if ( head == NULL ) return;

	node_t* new_node = create_node(dname);
	if (*head == NULL) 
		*head = new_node;
	else {
		// strcasecmp忽略大小写比较
   		if ( strcasecmp( (*head)->name, new_node->name ) > 0 ) {
			new_node->next = *head;
			*head = new_node;
			return;	
		}

		node_t* cur = *head;
		node_t* next = (*head)->next;
		while ( next != NULL ) {
			if ( strcasecmp( next->name, new_node->name ) > 0 ) {
				break;
			}
			cur = next;
			next = cur->next;
		}
		new_node->next = next;
		cur->next = new_node;
	}
}


int main( void ) {
	node_t* head = NULL;

	struct dirent* pdirent = NULL;
	DIR* pdir = opendir(".");
	
	while ( (pdirent = readdir(pdir)) != NULL ) {
		if ( pdirent->d_name[0] == '.' )
			continue;
		insert_list(&head, pdirent->d_name);
		// printf("%s ", pdirent->d_name);
	}
	node_t* cur = head;
	while (cur != NULL) {
		printf("%s  ", cur->name);
		head = cur->next;
		free(cur->name);
		free(cur);
		cur = head;
	}
	printf("\n");
	return 0;
}
