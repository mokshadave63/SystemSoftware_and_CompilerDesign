#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SYMBOLS 10
#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 100

char nonTerminals[MAX_SYMBOLS];
char terminals[MAX_SYMBOLS];
char productions[MAX_PRODUCTIONS][MAX_LENGTH];
int productionCount = 0;

char firstSets[MAX_SYMBOLS][MAX_LENGTH];
char followSets[MAX_SYMBOLS][MAX_LENGTH];

bool isTerminal(char symbol) {
    return !isupper(symbol);
}

void addToSet(char *set, char symbol) {
    if (!strchr(set, symbol)) {
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}


void computeFirstSets() {
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < productionCount; i++) {
            char nonTerminal = productions[i][0];
            char *firstSet = firstSets[nonTerminal - 'A'];
            char *rule = productions[i] + 3; // Skip the "A -> "

            for (int j = 0; rule[j] != '\0'; j++) {
                if (isTerminal(rule[j])) {
                    if (!strchr(firstSet, rule[j])) {
                        addToSet(firstSet, rule[j]);
                        changed = true;
                    }
                    break;
                } else {
                    char *nextFirstSet = firstSets[rule[j] - 'A'];
                    for (int k = 0; nextFirstSet[k] != '\0'; k++) {
                        if (nextFirstSet[k] != 'e' && !strchr(firstSet, nextFirstSet[k])) {
                            addToSet(firstSet, nextFirstSet[k]);
                            changed = true;
                        }
                    }
                    if (!strchr(nextFirstSet, 'e')) break;
                    if (rule[j + 1] == '\0') {
                        if (!strchr(firstSet, 'e')) {
                            addToSet(firstSet, 'e');
                            changed = true;
                        }
                    }
                }
            }
        }
    } while (changed);
}

// Compute FOLLOW set
void computeFollowSets() {
    addToSet(followSets[0], '$');  // FOLLOW(S) includes $

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < productionCount; i++) {
            char *rule = productions[i] + 3;
            char nonTerminal = productions[i][0];
            char *followSet = followSets[nonTerminal - 'A'];

            for (int j = 0; rule[j] != '\0'; j++) {
                if (isupper(rule[j])) {
                    char *currentFollowSet = followSets[rule[j] - 'A'];

                    if (rule[j + 1] != '\0') {
                        if (isTerminal(rule[j + 1])) {
                            if (!strchr(currentFollowSet, rule[j + 1])) {
                                addToSet(currentFollowSet, rule[j + 1]);
                                changed = true;
                            }
                        } else {
                            char *nextFirstSet = firstSets[rule[j + 1] - 'A'];
                            for (int k = 0; nextFirstSet[k] != '\0'; k++) {
                                if (nextFirstSet[k] != 'e' && !strchr(currentFollowSet, nextFirstSet[k])) {
                                    addToSet(currentFollowSet, nextFirstSet[k]);
                                    changed = true;
                                }
                            }
                            if (strchr(nextFirstSet, 'e')) {
                                for (int k = 0; followSet[k] != '\0'; k++) {
                                    if (!strchr(currentFollowSet, followSet[k])) {
                                        addToSet(currentFollowSet, followSet[k]);
                                        changed = true;
                                    }
                                }
                            }
                        }
                    } else {
                        for (int k = 0; followSet[k] != '\0'; k++) {
                            if (!strchr(currentFollowSet, followSet[k])) {
                                addToSet(currentFollowSet, followSet[k]);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &productionCount);

    for (int i = 0; i < productionCount; i++) {
        printf("Enter production %d (e.g., A->aB): ", i + 1);
        scanf("%s", productions[i]);
        if (!strchr(nonTerminals, productions[i][0])) {
            strncat(nonTerminals, &productions[i][0], 1);
        }
        for (int j = 3; productions[i][j] != '\0'; j++) {
            if (isTerminal(productions[i][j]) && !strchr(terminals, productions[i][j])) {
                strncat(terminals, &productions[i][j], 1);
            }
        }
    }

    computeFirstSets();
    computeFollowSets();

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < strlen(nonTerminals); i++) {
        printf("FIRST(%c) = { %s }\n", nonTerminals[i], firstSets[nonTerminals[i] - 'A']);
    }

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < strlen(nonTerminals); i++) {
        printf("FOLLOW(%c) = { %s }\n", nonTerminals[i], followSets[nonTerminals[i] - 'A']);
    }

    return 0;
}
