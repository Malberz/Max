// Linked List Key-Value Program
// Max Albers

// Follows specifications made in https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-kv

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

struct Node {
	int key;
	char *value;
	struct Node *next;
};

struct Node *head = NULL;
struct Node *current = NULL;

// Prints all nodes
void all() {
	struct Node *point = head;
	while (point != NULL) {
		printf("%d,%s\n", point->key, point->value);
		point = point->next;
	}
}

// Places the new value into the linked-list
void put(int key, char *value) {

   for (current = head; current != NULL; current = current->next) {
	   if (current->key == key) {
		   strcpy(current->value, value);
		   return;
	   }
   }

   struct Node *link = (struct Node*) malloc(sizeof(struct Node)); 

   link->key = key;
   link->value = malloc(strlen(value) + 1);
   strcpy(link->value, value);
   link->next = head;

   head = link;
}

// Retrieves one node with the specified key
void get(int key) {

   struct Node *current = head;

   if(head == NULL) {
      printf("%d not found\n", key);
      return;
   }

   while(current->key != key) {

      if(current->next == NULL) {
	 printf("%d not found\n", key);
	 return;
      } else {
         current = current->next;
      }
   }

   printf("%d,%s\n", current->key, current->value);
}

// Deletes node with specified key
void delete(int key) {

   struct Node *current = head;
   struct Node *previous = NULL;
	
   if(head == NULL) {
      printf("%d not found\n", key);
      return;
   }

   while(current->key != key) {

      if(current->next == NULL) {
	  printf("%d not found\n", key);
         return;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if(current == head) {
      head = head->next;
   } else {
      previous->next = current->next;
   }    
}

// Takes values from text file and enters them into the linked-list
void addValues(char *filename) {

	FILE *datafile = fopen(filename, "r");
	char *line = NULL;
	char *value;
	size_t len = 0;
	ssize_t read;

	if (datafile == NULL) {
		return;
	}
	
	int count = 0;
	while ((read = getline(&line, &len, datafile)) != -1) {
		char *token = strtok(line, ",");
		int key = atoi(token);
		value = strtok(NULL, ",");
		value[strlen(value) - 1] = '\0';
		put(key, value);	
	}

	fclose(datafile);
	if (line)
		free(line);
}

// Clears all values in the list
void clear() {
	head = NULL;
	current = NULL;
}


void main(int argc, char *argv[]) {

	char *filename = "dataset.txt";
	if (access(filename, F_OK) != -1) {
		addValues(filename);
	}
	else {
		FILE *newFile;
		newFile = fopen("dataset.txt", "w");
		fclose(newFile);
	}
	
	int i,j,keyVal;
	char *command;
	char *token;
	char *key;
	char *value;
	int comma = 0;
	for (i=1; i<argc; i++) {
		token = strtok(argv[i], ",");
		command = (char*) malloc(sizeof(token) + 1);
		strcpy(command,token);
		char letter = command[0];
		switch(letter) {
			case 'p':
				token = strtok(NULL, ",");
				if (token == NULL) {
					printf("bad command\n");
                                        continue;
				}
				key = (char*) malloc(sizeof(token) + 1);
				strcpy(key, token);
				token = strtok(NULL, ",");
				if (token == NULL) {
				       printf("bad command\n");
                                        continue;
                                }
				value = (char*) malloc(sizeof(token) + 1);
				strcpy(value, token);
				keyVal = atoi(key);
				if (keyVal == 0) {
                                        printf("bad command\n");
                                        continue;
				}
				put(keyVal, value);
				break;
			case 'g':
				token = strtok(NULL, ",");
				if (token == NULL) {
                                        printf("bad command\n");
                                        continue;
                                }
				key = (char*) malloc(sizeof(token) + 1);
                                strcpy(key, token);
				keyVal = atoi(key);
				if (keyVal == 0) {
					printf("bad command\n");
					continue;
				}
				token = strtok(NULL, ",");
				if (token != NULL) {
					printf("bad command\n");
					continue;
				}
				get(keyVal);
				break;
			case 'd':
				token = strtok(NULL, ",");
				if (token == NULL) {
                                        printf("bad command\n");
                                        continue;
                                }
                                key = (char*) malloc(sizeof(token) + 1);
                                strcpy(key, token);
                                keyVal = atoi(key);
				if (keyVal == 0) {
                                        printf("bad command\n");
                                        continue;
				}
				token = strtok(NULL, ",");
                                if (token != NULL) {
                                        printf("bad command\n");
                                        continue;
                                }
                                delete(keyVal);	
				break;
			case 'c':
				clear();
				break;
			case 'a':
				all();
				break;
			default:
				printf("%s\n", "bad command");
				break;
		}
	}
	
	FILE *newFile = fopen("dataset.txt", "w");
	for (current = head; current != NULL; current = current->next) {
		int key = current->key;
		char *value = current->value;
		fprintf(newFile, "%d,%s\n", key, value);
	}
	fclose(newFile);
}

