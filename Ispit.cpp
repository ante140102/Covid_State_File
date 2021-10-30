#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Person {
    char firstName[20];
    char lastName[20];
    int covidState;
};

const int NUM_PERSONS_MAX = 30;
const int STATE_MIN = 1;
const int STATE_MAX = 5;
const char inputFile[] = "osobe.txt";

bool readFile(const char* filename, struct Person* persons, int* num_persons) {
    FILE* fptr;
    int i;
    char firstName[20];
    char lastName[20];
    int itemsRead;

    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        return false;
    }

    for (i = 0; i < NUM_PERSONS_MAX; i++) {
        itemsRead = fscanf(fptr, "%s %s", firstName, lastName);
        if (itemsRead == -1) {
            break;
        }

        strcpy(persons[i].firstName, firstName);
        strcpy(persons[i].lastName, lastName);
        persons[i].covidState = rand() % (STATE_MAX + 1 - STATE_MIN) + STATE_MIN;
    }
    *num_persons = i;

    fclose(fptr);
    return true;
}

void printPersons(struct Person* persons, int num_persons) {
    int i;
    for (i = 0; i < num_persons; i++) {
        printf("%s %s %d\n", persons[i].firstName, persons[i].lastName, persons[i].covidState);
    }
}

int main()
{
    struct Person persons[NUM_PERSONS_MAX];
    int num_persons;
    bool valid;

    srand(time(0));
    valid = readFile(inputFile, persons, &num_persons);
    if (!valid) {
        printf("File %s not found.", inputFile);
        return 1;
    }

    printPersons(persons, num_persons);
    return 0;
}