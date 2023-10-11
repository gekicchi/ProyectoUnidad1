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

typedef struct history
{
	char result[10];
	int lives;
	int turns;
	struct history *next;
} History;


int read_file(char *file_name, Guardian **head, Guardian **tail, int min[], int max[]);

// Guardian-related functions
Guardian* create_guardian(char na[], char ty[], int hp, int atk, int def);
void add_guardian(Guardian **head, Guardian **tail, Guardian *add);
Guardian* remove_guardian(Guardian **head, Guardian **tail, int pos);
Guardian* pop_guardian(Guardian **head_stack, Guardian **tail_stack);
Guardian* see_guardian(Guardian *head, int pos);
void print_guardians(Guardian *head);
void free_guardians(Guardian *head);
int get_list_size(Guardian *head);

// History-related functions
History* create_history(char res[], int li, int tu);
void add_history(History **head, History **tail, History *add);
void print_history(History *head);
void free_history(History *head);

// Game-related functions
Guardian* create_card(int min[], int max[]);
void copy_stats(Guardian *deck1, Guardian *deck2, Guardian *copies_head, Guardian *copies_tail);
void shuffle_deck(Guardian **head, Guardian **tail, Guardian **deck_head, Guardian **deck_tail);
void list_to_list(Guardian **deck_head, Guardian **deck_tail, Guardian **hand_head, Guardian **hand_tail, int pos);
int look_by_stats(Guardian *head, int mode);
void attack_guardian(Guardian **defeated_head, Guardian **defeated_tail, Guardian **defender_head, Guardian **defender_tail, Guardian *attacker, int *defender_health, int pos);
void start_fight(Guardian **list_head, Guardian **list_tail, History **history_head, History **history_tail);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Uso: %s <nombre_archivo>.txt\n",argv[0]);
		return 1;
	}
	
	Guardian *list_head = NULL, *list_tail = NULL;
	Guardian *jg_head = NULL, *jg_tail = NULL;
	Guardian *cpu_head = NULL, *cpu_tail = NULL;
	Guardian *newGuardian = malloc(sizeof(Guardian));
	History *history_head = NULL, *history_tail = NULL;
	int minStats[3] = {5000,5000,5000}, maxStats[3] = {0,0,0}, election;
	int error = read_file(argv[1], &list_head, &list_tail, minStats, maxStats);
	
	if (error == 1)
	{
		printf("Error: Separe Datos de Archivo con Comas\n");
		return 2;
	}
	
	do{
		printf("----Menu Provisional----\n");
		printf("[1] Crear Carta\n[2] Ver Guardianes\n[3] Iniciar Pelea\n[4] Ver Historial\n[5] Salir\n");
		printf("Eleccion: ");
		scanf("%d",&election);
		printf("\n");
		
		switch (election)
		{
			case 1:
				newGuardian = create_card(minStats, maxStats);
				add_guardian(&list_head,&list_tail,newGuardian);
				break;
				
			case 2:
				print_guardians(list_head);
				break;
				
			case 3:
				start_fight(&list_head, &list_tail, &history_head, &history_tail);
				break;
			
			case 4:
				print_history(history_head);
				break;
			
			case 5:
				printf("BUH-BYE!\n");
				free_guardians(list_head);
				free_history(history_head);
				break;
		}
		
		printf("\n");
	} while (election != 5);
	return 0;
}

// reads .txt files separated by commas
int read_file(char *file_name, Guardian **head, Guardian **tail, int min[], int max[])
{
	FILE *file = fopen(file_name, "r");
	char line[100];
	int data_chunk = 0;
	
	while (fgets(line, 100, file) != NULL)
	{
		if (strchr(line, ',') == NULL)
			return 1;
		
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
	
	fclose(file);
	
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
	
	while (pos != 0)
	{
			
		prev = current;
		current = current->next;
		
		pos--;
	}
	
	if (prev == NULL && current->next == NULL) // only element
		*head = NULL;
	else if (prev != NULL && current->next != NULL) // middle element
		prev->next = current->next;
	else if (prev != NULL && current->next == NULL) // end element
	{
		prev->next = NULL;
		*tail = prev;
	}
	else // starting element
		*head = current->next;
	
	current->next = NULL;
	return current;
}

// remove guardian from stack
Guardian* pop_guardian(Guardian **head_stack, Guardian **tail_stack)
{
	if (*head_stack == NULL)
		return NULL;
	else
	{
		Guardian *current = *head_stack;
		Guardian *prev = NULL;
		
		while (current->next != NULL)
		{
			prev = current;
			current = current->next;
		}
		
		if (prev != NULL)
			prev->next = NULL;
			
		*tail_stack = prev;
		
		return current;
	}
}

Guardian* see_guardian(Guardian *head, int pos)
{
	Guardian *current = head;
	
	while (pos != 1)
	{
		current = current->next;
		pos--;
	}
	
	return current;
}

// prints guardian information
void print_guardians(Guardian *head)
{
	Guardian *current = head;
	int count=1;
	while (current != NULL)
	{
		printf("%d) %s\t| %s\t| Vida: %d\t| Ataque: %d\t| Defensa: %d\n",count, current->name, current->type, current->health, current->attack, current->defense);
		current = current->next;
		count++;
	}
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

// creates history structure
History* create_history(char res[], int li, int tu)
{
	History *new_history = malloc(sizeof(History));
	
	strcpy(new_history->result, res);
	new_history->lives = li;
	new_history->turns = tu;
	new_history->next = NULL;
	
	return new_history;
}

// adds history to list
void add_history(History **head, History **tail, History *add)
{
	if (*head == NULL)
		*head = add;
	else
	{
		History *end = *tail;
		end->next = add;
	}
	
	*tail = add;
}

// prints history information
void print_history(History *head)
{
	History *current = head;
	int count=1;
	while (current != NULL)
	{
		printf("---Combate %d---\n",count);
		printf("Resultado: %s\nVida Restante: %d\nTurnos Totales: %d\n",current->result, current->lives, current->turns);
		current = current->next;
		count++;
	}
}

// frees history data
void free_history(History *head)
{
	History *current = head;
	while (current != NULL)
	{
		History *next = current->next;
		free(current);
		current = next;
	}
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
		printf("Puntos de Vida (%d - %d) de Guardian: ",min[0],max[0]);
		scanf("%d",&hp);
	} while (hp < min[0] || hp > max[0]);
	
	do{
		printf("Puntos de Ataque (%d - %d) de Guardian: ",min[1],max[1]);
		scanf("%d",&atk);
	} while (atk < min[1] || atk > max[1]);
	
	do{
		printf("Puntos de Defensa (%d - %d) de Guardian: ",min[2],max[2]);
		scanf("%d",&def);
	} while (def < min[2] || def > max[2]);
	
	return create_guardian(name,type, hp, atk, def);
}

// creates a list of copied guardians from the players decks
void copy_stats(Guardian *deck1, Guardian *deck2, Guardian *copies_head, Guardian *copies_tail)
{
	Guardian *deck1_current = deck1;
	Guardian *deck2_current = deck2;
	Guardian *copy = malloc(sizeof(Guardian));
	
	while (get_list_size(copies_head) < get_list_size(deck1) + get_list_size(deck2))
	{
		strcpy(copy->name,deck1_current->name);
		strcpy(copy->type,deck1_current->type);
		copy->health = deck1_current->health;
		copy->attack = deck1_current->attack;
		copy->defense = deck1_current->defense;
		add_guardian(&copies_head,&copies_tail,copy);
		
		strcpy(copy->name,deck2_current->name);
		strcpy(copy->type,deck2_current->type);
		copy->health = deck2_current->health;
		copy->attack = deck2_current->attack;
		copy->defense = deck2_current->defense;
		add_guardian(&copies_head,&copies_tail,copy);
		
		deck1_current = deck1_current->next;
		deck2_current = deck2_current->next;
	}
}

// gives 15 random cards to target
void shuffle_deck(Guardian **head, Guardian **tail, Guardian **deck_head, Guardian **deck_tail)
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
}

// interchanges guardians from one list to another
void list_to_list(Guardian **deck_head, Guardian **deck_tail, Guardian **hand_head, Guardian **hand_tail, int pos)
{
	Guardian *popped_guardian = malloc(sizeof(Guardian));
	if (pos == -1)
		popped_guardian = pop_guardian(deck_head,deck_tail);
	else
		popped_guardian = remove_guardian(deck_head,deck_tail,pos);
		
	add_guardian(hand_head,hand_tail,popped_guardian);
}

// searches a guardian by comparing stats
int look_by_stats(Guardian *head, int mode)
{
	Guardian *current = head;
	int less_health = 5000, most_attack = 0, pos = 1, pos_selected = pos;
	
	switch (mode)
	{
		case 1: // less health
			while (current != NULL)
			{
				if (current->health < less_health)
				{
					less_health = current->health;
					pos_selected = pos;
				}
					
				pos++;
				current = current->next;
			}
			break;
			
		case 2: // most attack
			while (current != NULL)
			{
				if (current->attack > most_attack)
				{
					most_attack = current->attack;
					pos_selected = pos;
				}
				
				pos++;
				current = current->next;
			}
			break;
		
	}
	
	return pos_selected;
}

// attacks guardian and sends it to the defeated list if its health reaches zero
void attack_guardian(Guardian **defeated_head, Guardian **defeated_tail, Guardian **defender_head, Guardian **defender_tail, Guardian *attacker, int *defender_health, int pos)
{
	Guardian *defender = *defender_head;
	int defender_pos = pos;
	while (pos != 1)
	{
		defender = defender->next;
		defender_pos--;
	}
	
	int damage = attacker->attack - defender->defense;
	if (damage <= 0)
		damage = 1;
		
	defender->health -= damage;
	printf("%s Ataca a %s por %d Puntos de Vida\n", attacker->name, defender->name, damage);
	
	if (defender->health <= 0)
	{
		printf("%s ya no Puede Combatir\n", defender->name);
		list_to_list(defender_head,defender_tail,defeated_head,defeated_tail,pos-1);
		printf("lesgooo\n");
		*defender_health = *defender_health-1;
	}
}

// the fight proper
void start_fight(Guardian **list_head, Guardian **list_tail, History **history_head, History **history_tail)
{
	srand(time(NULL));
	Guardian *copies_head = NULL, *copies_tail = NULL, *copy = malloc(sizeof(Guardian));
	Guardian *jg_head = NULL, *jg_tail = NULL,*jg_hand = NULL, *jg_end = NULL, *jg_arena = NULL, *jg_arena_end = NULL;
	Guardian *cpu_head = NULL, *cpu_tail = NULL, *cpu_hand = NULL, *cpu_end = NULL, *cpu_arena = NULL, *cpu_arena_end = NULL;
	Guardian *attacker = NULL, *defeated_head = NULL, *defeated_tail = NULL;
	History *history = malloc(sizeof(History));
	int jg_lives = 5, cpu_lives = 5;
	int turn = 1, player_election, cpu_election, to_arena, to_attack, to_defend;
	
	shuffle_deck(list_head,list_tail,&jg_head,&jg_tail);
	shuffle_deck(list_head,list_tail,&cpu_head,&cpu_tail);
	printf("HIIIII!!!!\n");
	/*
	copy_stats(jg_head, cpu_head, copies_head, copies_tail);
	print_guardians(copies_head);
	*/
	while(get_list_size(jg_hand) < 3 && get_list_size(cpu_hand) < 3)
	{
		list_to_list(&jg_head,&jg_tail,&jg_hand,&jg_end,-1);
		list_to_list(&cpu_head,&cpu_tail,&cpu_hand,&cpu_end,-1);
	}
	
	do{
		printf("------Turno %d------\n",turn);
		printf("--Cartas En Campo--\n");
		printf("Jugador (%d Vidas):\n",jg_lives);
		print_guardians(jg_arena);
		printf("CPU (%d Vidas):\n",cpu_lives);
		print_guardians(cpu_arena);
		printf("\n");
		
		// player turn
		if (cpu_arena != NULL && jg_arena != NULL)
		{
			printf("[1] Bajar Carta\n[2] Atacar\nEleccion: ");
			scanf("%d",&player_election);
			printf("\n");
		}
		else
			player_election = 1;	
		
		switch(player_election)
		{	
			case 1: // hand to arena
				printf("---Elige Guardian a Bajar---\n");
				print_guardians(jg_hand);
				printf("Eleccion: ");
				scanf("%d",&to_arena);
				list_to_list(&jg_hand,&jg_end,&jg_arena,&jg_arena_end,to_arena-1);
				break;
				
			case 2: // attack
				printf("---Elige Guardian con Quien Atacar---\n");
				print_guardians(jg_arena);
				printf("Eleccion: ");
				scanf("%d",&to_attack);
				attacker = see_guardian(jg_arena, to_attack);
				
				printf("---Elige Guardian al Que Atacar---\n");
				print_guardians(cpu_arena);
				printf("Eleccion: ");
				scanf("%d",&to_defend);
				
				attack_guardian(&defeated_head,&defeated_tail, &cpu_arena, &cpu_arena_end, attacker, &cpu_lives, to_defend);
				break;
		}
		printf("\n");
		// cpu turn
		if (cpu_lives > 0)
		{
			if (cpu_arena != NULL && jg_arena != NULL)
			{
				if (rand()%10 < 3)
					cpu_election = 1;
				else
					cpu_election = 2;
			}
			else
				cpu_election = 1;
			
			switch(cpu_election)
			{
				case 1: // hand to arena
					printf("Rival Baja Guardian al Campo\n");
					to_arena = rand()%get_list_size(cpu_hand);
					list_to_list(&cpu_hand,&cpu_end,&cpu_arena,&cpu_arena_end,to_arena-1);
					break;
					
				case 2: // attack
					printf("Rival Ataca\n");
					to_attack = look_by_stats(cpu_arena, 2);
					printf("numero atacante\n");
					attacker = see_guardian(cpu_arena, to_attack);
					printf("atacante conseguido\n");
					
					to_defend = look_by_stats(jg_arena, 1);
					printf("numero defensor\n");
					attack_guardian(&defeated_head,&defeated_tail, &jg_arena, &jg_arena_end, attacker, &jg_lives, to_defend);
					break;
			}
		}
		printf("\n");
		
		if (turn < 13)
		{
			printf("Recogiendo Carta...\n");
			list_to_list(&jg_head,&jg_tail,&jg_hand,&jg_end,-1);
			list_to_list(&cpu_head,&cpu_tail,&cpu_hand,&cpu_end,-1);
		}
		turn++;
		printf("\n\n");
	} while (jg_lives > 0 && cpu_lives > 0);
	
	if (jg_lives == 0 && cpu_lives == 0)
		history = create_history("Empate", jg_lives, turn);
	else if (cpu_lives == 0)
		history = create_history("Victoria", jg_lives, turn);
	else
		history = create_history("Derrota", jg_lives, turn);
		
	printf("---Resultado Combate---\n");
	printf("Resultado: %s\nVida Restante: %d\nTurnos Totales: %d\n",history->result, history->lives, history->turns);
	
	add_history(history_head, history_tail, history);
	
	while (get_list_size(copies_head) > 0)
		list_to_list(&copies_head,&copies_tail, list_head,list_tail,-1);
}
