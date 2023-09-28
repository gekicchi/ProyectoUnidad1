#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct guardian
{
	char name[50];
	char type[12];
	int health;
	int attack;
	int defense;
	struct guardian *next;
} Guardian;

Guardian* create_guardian(char na[], char ty[], int hp, int atk, int def);
void add_guardian(Guardian **head, Guardian **tail, Guardian *add);
void free_guardians(Guardian *head);
void print_guardians(Guardian *head);
void read_file(char *file_name, Guardian **head, Guardian **tail);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s guardians.txt",argv[0]);
		return 1;
	}	
	// find way to validate when file data is not separated by ","
	
	Guardian *head = NULL;
	Guardian *tail = NULL;
	read_file(argv[1], &head, &tail);
	print_guardians(head);
	
	return 0;
}

Guardian* create_guardian(char na[], char ty[], int hp, int atk, int def)
{
	Guardian *new_guardian = (Guardian*)malloc(sizeof(Guardian));
	
	strcpy(new_guardian->name, na);
	strcpy(new_guardian->type, ty);
	new_guardian->health = hp;
	new_guardian->attack = atk;
	new_guardian->defense = def;
	new_guardian->next = NULL;
	
	return new_guardian;
}

void add_guardian(Guardian **head, Guardian **tail, Guardian *add)
{
	if (*head == NULL)
		*head = add;
	else
	{
		Guardian *end = *tail;
		end->next = add;
	}
	
	*tail = add;
}

void free_guardians(Guardian *head)
{
	Guardian *current = head;
	while (current != NULL)
	{
		Guardian *next = current->next;
		free(current);
		current = next;
	}
}

void print_guardians(Guardian *head)
{
	Guardian *current = head;
	while (current != NULL)
	{
		printf("%s | %s | %d | %d | %d\n",current->name, current->type, current->health, current->attack, current->defense);
		current = current->next;
	}
}

void read_file(char *file_name, Guardian **head, Guardian **tail)
{
	FILE *file = fopen(file_name, "r");
	char line[100];
	
	while (fgets(line, 100, file) != NULL)
	{
		char *token;
		token = strtok(line, ",");
		char name[50];
		strcpy(name, token);
		token = strtok(NULL, ",");
		char type[11];
		strcpy(type, token);
		int health = atoi(strtok(NULL, ","));
		int attack = atoi(strtok(NULL, ","));
		int defense = atoi(strtok(NULL, ","));
		
		Guardian *new_guardian = create_guardian(name, type, health, attack, defense);
		add_guardian(head, tail, new_guardian);
	}
	
	fclose(file);
}

