#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Variables used in most of the other modules.

char items[30][100][100];
char augmented_grammar[100][100], terminals[10], nonterminals[10];
int no_of_productions = 0, no_of_states = 0, no_of_items[30], no_of_terminals = 0, no_of_nonterminals = 0;

char FIRST[2][10][10];
char FOLLOW[10][10];


// Variables used only in this module.

int state_index = 0, goto_state_index = 0, closure_item_index = 0;

int check(char c) {
    int i;

    for(i = 0; i < no_of_terminals; i++)
        if(terminals[i] == c)
            return 1;

    return 0;
}

void generate_terminals() {
    int i, j;
    int index = 0;

    for(i = 0; i < no_of_productions; i++) {
        for(j = 0; augmented_grammar[i][j] != '>'; j++);
        j++;

        for(; augmented_grammar[i][j] != '\0'; j++) {
            if(augmented_grammar[i][j] < 65 || augmented_grammar[i][j] > 90) {
                if(!check(augmented_grammar[i][j])) {
                    terminals[index] = augmented_grammar[i][j];
                    no_of_terminals++;
                    index++;
                }
            }
        }
    }

    terminals[index] = '$';
    no_of_terminals++;
    index++;
    terminals[index] = '\0';
}

int check2(char c, int index) {
    int i;

    for(i = 0; i < index; i++)
        if(nonterminals[i] == c)
            return 1;

    return 0;
}

void generate_nonterminals() {
    int i, index = 0;

    for(i = 0; i < no_of_productions; i++)
        if(!check2(augmented_grammar[i][0], index)) {
            nonterminals[index] = augmented_grammar[i][0];
            index++;
        }

    no_of_nonterminals = index;
    nonterminals[index] = '\0';
}

void initialize_items() {
    generate_terminals();
    generate_nonterminals();

    int i;

    for(i = 0; i < 30; i++)
        no_of_items[i] = 0;
}

void generate_item(char *s, char *t) {
    int i;

    for(i = 0; i < 3; i++)
        t[i] = s[i];

    t[i] = '.';

    if(s[i] != '@')
        for(; i < strlen(s); i++)
            t[i+1] = s[i];

    t[i+1] = '\0';
}

int item_found(char *s) {
    int i;

    for(i = 0; i < closure_item_index; i++) {
        if(!strcmp(s, items[state_index][i]))
            return 1;
    }

    return 0;
}

int isterminal(char s) {
    int i;

    for(i = 0; i < no_of_terminals; i++)
        if(s == terminals[i])
            return 1;

    return 0;
}

void closure(char *s) {
    int i, j;

    for(i = 0; s[i] != '.'; i++);

    i++;

    if(!isterminal(s[i])) {
        for(j = 0; j < no_of_productions; j++)
            if(augmented_grammar[j][0] == s[i]) {
                generate_item(augmented_grammar[j], items[state_index][closure_item_index]);
                closure_item_index++;

                if(!item_found(items[state_index][closure_item_index-1]))
                    closure(items[state_index][closure_item_index-1]);
            }
    }
}

void Goto1(char *I, char X, char *J) {
    int i, j, k;

    for(i = 0; I[i] != '.'; i++)
        J[i] = I[i];

    J[i] = I[i+1];
    J[i+1] = '.';

    if(I[i+2] != '@') {
        for(j = i+2; I[j] != '\0'; j++)
            J[j] = I[j];

        J[j] = '\0';
    } else
        J[i+2] = '\0';

    for(k = 0; k < strlen(J); k++)
        if(J[k] == X)
            break;

    if(k != strlen(J))
        closure_item_index = 0;
    else
        strcpy(J, "");
}

int state_found(char *s) {
    int i;

    for(i = 0; i < state_index; i++)
        if(!strcmp(s, items[i][0]))
            return 1;

    return 0;
}

int transition_item_found(char *s, char *t) {
    int i;

    for(i = 0; i < state_index; i++)
        if(!strcmp(s, items[i][0])) {
            if(!strcmp(t, items[i][no_of_items[i]-1]))
                return 1;
        }

    return 0;
}

void compute_closure_goto() {
    int i, j, k;
    char temp1[100], temp2[100], temp3[100], transition_item[100];

    strcpy(items[0][0], augmented_grammar[0]);
    no_of_items[0]++;

    closure_item_index++;

    closure(items[0][0]);

    no_of_states++;

    while(state_index < no_of_states) {
        for(i = 0; i < no_of_items[state_index]; i++) {
            for(j = 0; items[state_index][i][j] != '.'; j++);

            if(items[state_index][i][j+1] != '\0') {
                Goto1(items[state_index][i], items[state_index][i][j+1], transition_item);

                if(strlen(transition_item) != 0) {
                    if(!state_found(transition_item)) {
                        strcpy(items[state_index+1][0], transition_item);
                        no_of_items[state_index+1]++;
                        closure_item_index = 0;

                        closure(items[state_index+1][0]);

                        no_of_states++;
                    } else {
                        if(!transition_item_found(transition_item, items[state_index+1][0])) {
                            for(k = 0; k < no_of_states; k++)
                                if(!strcmp(transition_item, items[k][0]))
                                    break;

                            strcpy(items[state_index+1][0], items[k][0]);
                            no_of_items[state_index+1]++;
                        }
                    }

                    strcpy(temp1, "");
                    strcpy(temp2, "");
                    strcpy(temp3, "");

                    for(k = 0; k < i; k++) {
                        if(!strcmp(transition_item, items[state_index][k])) {
                            strcpy(temp1, items[state_index][k]);
                            break;
                        }
                    }

                    for(k = i+1; k < no_of_items[state_index]; k++) {
                        strcpy(temp2, items[state_index][k]);
                        strcpy(items[state_index][k-1], temp2);
                    }

                    for(k = 0; k < no_of_items[state_index+1]; k++) {
                        strcpy(temp3, items[state_index+1][k]);
                        strcpy(items[state_index+1][k+1], temp3);
                    }

                    strcpy(items[state_index+1][no_of_items[state_index+1]-1], temp1);
                    no_of_items[state_index]--;
                }
            }
        }

        state_index++;
    }
}

void display_items() {
    int i, j;

    for(i = 0; i < no_of_states; i++) {
        printf("I%d:\n", i);

        for(j = 0; j < no_of_items[i]; j++)
            printf("%s\n", items[i][j]);

        printf("\n");
    }
}

int main() {
    int i;

    printf("Enter the number of productions: ");
    scanf("%d", &no_of_productions);

    printf("Enter the productions (in the form A->alpha):\n");
    for(i = 0; i < no_of_productions; i++)
        scanf("%s", augmented_grammar[i]);

    initialize_items();
    compute_closure_goto();
    display_items();

    return 0;
}