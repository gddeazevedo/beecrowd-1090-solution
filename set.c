#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Authors:
    * Gabriel Dias, gabriel.dias@aluno.cefet-rj.br
    * Gustavo Kanji, gustaavokanji@gmail.com
    * Nícolas Henriques, nicolas.bhenriques@gmail.com
*/

#define ONE "um"
#define TWO "dois"
#define THREE "tres"
#define CIRCLE 'c'
#define TRIANGLE 't'
#define SQUARE 'q'
#define LENGTH 3


struct node {
    int data;
    struct node* next;
};

typedef struct node Node;

typedef struct {
    Node* head;
    Node* tail;
} LinkedList;


int map_card_number_to_index(char* card_number);
int map_card_form_to_index(char* card_form);
int get_total_sets(int card_deck[LENGTH][LENGTH]);
bool does_card_deck_have_all_cards(int card_deck[LENGTH][LENGTH]);
void count_sets_on_rows(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_cols(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_main_diagonal(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_secondary_diagonal(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_same_index(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_different_indexes(int card_deck[LENGTH][LENGTH], int* total_sets);
void count_sets_on_remainders(int card_deck[LENGTH][LENGTH], int* total_sets);
void append(LinkedList* list, int data);
void print_list(LinkedList* list);


int main() {
    int total_of_cards = 0;
    LinkedList* results = (LinkedList*) malloc(sizeof(LinkedList));

    while (true) {
        scanf("%d", &total_of_cards);

        if (total_of_cards < 3 || total_of_cards > 3 * 10 * 10 * 10 * 10) {
            break;
        }

        int card_deck[LENGTH][LENGTH] = { 
            { 0, 0, 0 },  // circles
            { 0, 0, 0 }, // triangles
            { 0, 0, 0 } // squares
        };

        char card_number[5];
        char card_form[11];

        for (int i = 0; i < total_of_cards; i++) {
            scanf("%s %s", card_number, card_form);
            int card_number_index = map_card_number_to_index(card_number);
            int card_form_index = map_card_form_to_index(card_form);
            card_deck[card_form_index][card_number_index]++;
        }

        int total_sets = get_total_sets(card_deck);
        append(results, total_sets);
    }

    print_list(results);
    free(results);

    return 0;
}

int get_total_sets(int card_deck[LENGTH][LENGTH]) {
    int total_sets = 0;
    bool card_deck_had_all_cards = does_card_deck_have_all_cards(card_deck);

    count_sets_on_rows(card_deck, &total_sets);
    count_sets_on_cols(card_deck, &total_sets);
    count_sets_on_main_diagonal(card_deck, &total_sets);
    count_sets_on_secondary_diagonal(card_deck, &total_sets);
    count_sets_on_same_index(card_deck, &total_sets);
    count_sets_on_different_indexes(card_deck, &total_sets);


    if (card_deck_had_all_cards) {
        count_sets_on_remainders(card_deck, &total_sets);
    }

    return total_sets;
}

void count_sets_on_rows(int card_deck[LENGTH][LENGTH], int* total_sets) {
    for (int shape = 0; shape < LENGTH; shape++) {
        while (card_deck[shape][0] > 0 && card_deck[shape][1] > 0 && card_deck[shape][2] > 0) {
            *total_sets += 1;
            card_deck[shape][0]--;
            card_deck[shape][1]--;
            card_deck[shape][2]--;
        }
    }
}

void count_sets_on_cols(int card_deck[LENGTH][LENGTH], int* total_sets) {
    for (int number = 0; number < LENGTH; number++) {
        while (card_deck[0][number] > 0 && card_deck[1][number] > 0 && card_deck[2][number] > 0) {
            *total_sets += 1;
            card_deck[0][number]--;
            card_deck[1][number]--;
            card_deck[2][number]--;
        }
    }
}

void count_sets_on_main_diagonal(int card_deck[LENGTH][LENGTH], int* total_sets) {
    while (card_deck[0][0] > 0 && card_deck[1][1] > 0 && card_deck[2][2] > 0) {
        *total_sets += 1;
        card_deck[0][0]--;
        card_deck[1][1]--;
        card_deck[2][2]--;
    }
}

void count_sets_on_secondary_diagonal(int card_deck[LENGTH][LENGTH], int* total_sets) {
    while (card_deck[0][2] > 0 && card_deck[1][1] > 0 && card_deck[2][0] > 0) {
        *total_sets += 1;
        card_deck[0][2]--;
        card_deck[1][1]--;
        card_deck[2][0]--;
    }
}

void count_sets_on_same_index(int card_deck[LENGTH][LENGTH], int* total_sets) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (card_deck[i][j] >= 3) {
                *total_sets += card_deck[i][j] / 3;
                card_deck[i][j] %= 3;
            }
        }
    }
}

void count_sets_on_different_indexes(int card_deck[LENGTH][LENGTH], int* total_sets) {
    while (card_deck[0][0] > 0 && card_deck[1][2] > 0 && card_deck[2][1] > 0) {
        *total_sets += 1;
        card_deck[0][0]--;
        card_deck[1][2]--;
        card_deck[2][1]--;
    }

    while (card_deck[0][2] > 0 && card_deck[1][0] > 0 && card_deck[2][1] > 0) {
        *total_sets += 1;
        card_deck[0][2]--;
        card_deck[1][0]--;
        card_deck[2][1]--;
    }

    while (card_deck[0][1] > 0 && card_deck[1][0] > 0 && card_deck[2][2] > 0) {
        *total_sets += 1;
        card_deck[0][1]--;
        card_deck[1][0]--;
        card_deck[2][2]--;
    }

    while (card_deck[0][1] > 0 && card_deck[1][2] > 0 && card_deck[2][0] > 0) {
        *total_sets += 1;
        card_deck[0][1]--;
        card_deck[1][2]--;
        card_deck[2][0]--;
    }
}

void count_sets_on_remainders(int card_deck[LENGTH][LENGTH], int* total_sets) {
    int remainder = 0;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            remainder += card_deck[i][j];
        }
    }

    if (remainder > 3 && remainder < 6) {
        *total_sets += 1;
    } else if (remainder == 6){
        /*
            0 0 2
            1 1 0
            0 0 2
        */
        if (card_deck[0][2] > 0 && card_deck[1][0] > 0 && card_deck[1][1] > 0 && card_deck[2][2] > 0) {
            *total_sets += 2;
        } else if (card_deck[0][0] > 0 && card_deck[1][1] > 0 && card_deck[1][2] > 0 && card_deck[2][0] > 0) {
            *total_sets += 2;
        } else if (card_deck[0][1] > 0 && card_deck[1][0] > 0 && card_deck[1][2] > 0 && card_deck[2][1] > 0) {
            *total_sets += 2;
        } 

        /*
            0 0 2
            0 2 0
            0 0 2
        */
        else {
            *total_sets += 1;
        }
    } else if (remainder > 6 && remainder < 9) {
        *total_sets += 2;
    }
}

bool does_card_deck_have_all_cards(int card_deck[LENGTH][LENGTH]) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (card_deck[i][j] == 0)
                return false;
        }
    }

    return true;
}

int map_card_number_to_index(char* card_number) {
    if (strcmp(card_number, ONE) == 0) {
        return 0;
    }
    if (strcmp(card_number, TWO) == 0) {
        return 1;
    }
    if (strcmp(card_number, THREE) == 0) {
        return 2;
    }
}

int map_card_form_to_index(char* card_form) {
    if (card_form[0] == CIRCLE) {
        return 0;
    }
    if (card_form[0] == TRIANGLE) {
        return 1;
    }
    if (card_form[0] == SQUARE) {
        return 2;
    }
}

void append(LinkedList* list, int data) {
    if (list->head == NULL) {
        list->head = (Node*) malloc(sizeof(Node));
        list->head->data = data;
        list->tail = list->head;
    } else {
        list->tail->next = (Node*) malloc(sizeof(Node));
        list->tail = list->tail->next;
        list->tail->data = data;
    }
}

void print_list(LinkedList* list) {
    Node* aux = list->head;

    while (aux != NULL) {
        printf("%d\n", aux->data);
        aux = aux->next;
    }
}
