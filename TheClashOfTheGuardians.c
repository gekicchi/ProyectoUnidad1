#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
Guardian* remove_guardian(Guardian **head, Guardian **tail, int pos);
int get_list_size(Guardian *head);
void free_guardians(Guardian *head);
void print_guardians(Guardian *head);
void read_file(char *file_name, Guardian **head, Guardian **tail, int min[], int max[]);
Guardian* create_card(int min[], int max[]);
//void suffle_deck(Guardian **head, Guardian **tail, Guardian **deck_head, Guardian **deck_tail);

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
	Guardian *deck_head = NULL;
	Guardian *deck_tail = NULL;
	int minStats[3] = {5000,5000,5000}, maxStats[3] = {0,0,0};
	read_file(argv[1], &head, &tail, minStats, maxStats);
	
	int election,elim;
	Guardian *newGuardian = malloc(sizeof(Guardian)), *removedGuardian = malloc(sizeof(Guardian));
	
	do{
		printf("----Menu Provisional----\n");
		printf("[1] Crear Carta\n[2] Ver Guardianes\n[3] Probar ELiminar\n[4] Crear Mazo\n[5] Salir\n");
		printf("Eleccion: ");
		scanf("%d",&election);
		
		switch (election)
		{
			case 1:
				newGuardian = create_card(minStats, maxStats);
				add_guardian(&head,&tail,newGuardian);
				break;
				
			case 2:
				print_guardians(head);
				break;
				
			case 3:
				printf("donde: ");
				scanf("%d",&elim);
				removedGuardian =remove_guardian(&head,&tail,elim);
				printf("%s | %s | %d | %d | %d\n",removedGuardian->name,removedGuardian->type,removedGuardian->health,removedGuardian->attack,removedGuardian->defense);
				break;
				
			case 4:
				//shuffle_deck(&head,&tail,&deck_head,&deck_tail);
				print_guardians(deck_head);
				break;
			
			case 5:
				printf("BUH-BYE!\n");
				free_guardians(head);
				break;
		}
	} while (election != 5);
	return 0;
}

// creates guardian structure
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

// adds guardian to list
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

// removes guardian from list
Guardian* remove_guardian(Guardian **head, Guardian **tail, int pos)
{
	Guardian *current = *head;
	Guardian *prev = NULL;
	
	while (current != NULL && pos != 0)
	{
			
		prev = current;
		current = current->next;
		
		pos--;
	}
	
	if (prev != NULL && current->next != NULL) // middle element
	{
		prev->next = current->next;
	}
	else if (current->next == NULL) // end element
	{
		prev->next = NULL;
		*tail = prev;
	}
	else // starting element
	{
		*head = current->next;
	}
	
	current->next = NULL;
	return current;
}

// returns size of selected list
int get_list_size(Guardian* head)
{
	Guardian *current = head;
	int count = 0;
	
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	
	return count;
}

// frees guardian data
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

// prints guardian information
void print_guardians(Guardian *head)
{
	Guardian *current = head;
	int count=0;
	while (current != NULL)
	{
		printf("%d) %s | %s | %d | %d | %d\n",count, current->name, current->type, current->health, current->attack, current->defense);
		current = current->next;
		count++;
	}
}

// reads .txt files separated by commas
void read_file(char *file_name, Guardian **head, Guardian **tail, int min[], int max[])
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
		if (min[0] > health)
			min[0] = health;
		if (max[0] < health)
			max[0] = health;
			
		int attack = atoi(strtok(NULL, ","));
		if (min[1] > attack)
			min[1] = attack;
		if (max[1] < attack)
			max[1] = attack;
		
		int defense = atoi(strtok(NULL, ","));
		if (min[2] > defense)
			min[2] = defense;
		if (max[2] < defense)
			max[2] = defense;
		
		Guardian *new_guardian = create_guardian(name, type, health, attack, defense);
		add_guardian(head, tail, new_guardian);
	}
	
	printf("hp: %d - %d | atk: %d - %d | def: %d - %d\n",min[0],max[0],min[1],max[1],min[2],max[2]);
	
	fclose(file);
}

// lets user create a guardian card
Guardian* create_card(int min[], int max[])
{
	char name[50], type[12];
	int hp, atk, def, election;
	
	printf("Nombre de Guardian: ");
	scanf("%s",&name);
	
	do{
		printf("Tipo de Guardian:\n");
		printf("[1] Mago\t[2] Nigromante\n[3] Bestia\t[4] Vikingo\n");
		printf("Eleccion: ");
		scanf("%d",&election);
	} while (election < 1 || election > 4);
	
	switch (election)
	{
		case 1:
			strcpy(type,"Mago");
			break;
			
		case 2:
			strcpy(type,"Nigromante");
			break;
			
		case 3:
			strcpy(type,"Bestia");
			break;
			
		case 4:
			strcpy(type,"Vikingo");
			break;
	}
	
	do{
		printf("Puntos de Vida de Guardian: ");
		scanf("%d",&hp);
	} while (hp < min[0] || hp > max[0]);
	
	do{
		printf("Puntos de Ataque de Guardian: ");
		scanf("%d",&atk);
	} while (atk < min[1] || atk > max[1]);
	
	do{
		printf("Puntos de Defensa de Guardian: ");
		scanf("%d",&def);
	} while (def < min[2] || def > max[2]);
	
	return create_guardian(name,type, hp, atk, def);
}

// gives 15 random cards to target
/*
void suffle_deck(Guardian **head, Guardian **tail, Guardian **deck_head, Guardian **deck_tail)
{
	srand(time(NULL));
	Guardian *decked_guardian = malloc(sizeof(Guardian));
	int pos,i;
	
	for (i=0; i < 15; i++)
	{
		pos = rand()%(get_list_size(*head));
		decked_guardian = remove_guardian(head,tail,pos);
		add_guardian(deck_head,deck_tail,decked_guardian);
	}
}*/
