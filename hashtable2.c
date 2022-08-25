#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME];
    int age;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i] % TABLE_SIZE);
    }
    
    
    return hash_value;

}

bool init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_table() {

    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t<deleted>\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("Press Enter to continue\n");
    getchar();
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL ||
        hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }
    
    return false;
}

person *hash_table_lookup (char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false;
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE)==0) {
            return hash_table[try];
        }
    }
    return NULL;

}

person *hash_table_delete(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE)==0) {
            person* tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}
char ch;
void menu() {
    system("clear");
    init_hash_table();
    printf("Pick option:\n");
    printf("------------------------\n");
    printf("Print hash table     (1)\n");
    printf("Insert value         (2)\n");
    printf("Delete value         (3)\n");
    printf("Exit                 (4)\n");
    
    int choice;
    scanf("%i", &choice);
    switch(choice) {
        case 1:
            system("clear");
            print_table();
            getchar();
            menu();
            break;
        case 2:
            printf("Type name: ");
            char* temp_name;
            scanf("%s", &temp_name);
            printf("Type age: ");
            int temp_age;
            scanf("%i", &temp_age);
            person temp_person = {.name = &temp_name, .age = &temp_age};
            hash_table_insert(&temp_person);
            printf("Press Enter to continue \n");
            getchar();
            getchar();
            menu();
            break;
        case 3:

            break;
        case 4:
            exit(0);
            break;
    }
}


int main() {
    menu();
    return 0;
}
