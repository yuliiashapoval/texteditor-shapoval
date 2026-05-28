#include <stdio.h>
#include <stdlib.h>

void help() {
    printf("\n Text Editor \n"
           "1. Append text symbols to the end\n"
           "2. Start the new line\n"
           "3. Use files to load the information\n"
           "4. Use files to save the information\n"
           "5. Print the current text to console\n"
           "6. Insert the text by line and symbol index\n"
           "7. Search\n"
           "0. Exit\n"
           "Choose the command: ");
}

struct LineNode {
    char* text;
    struct LineNode* next;
};

struct Editor {
    struct LineNode* head;
};

struct Editor* createEditor() {
    struct Editor* ed = malloc(sizeof(struct Editor));
    (*ed).head = NULL;
    return ed;
}

void newLine(struct Editor* ed) {
    struct LineNode* newNode = malloc(sizeof(struct LineNode));
    (*newNode).text = malloc(1024* sizeof(char));
    (*newNode).text[0] = '\0';
    (*newNode).next = NULL;

    if ((*ed).head == NULL) {
        (*ed).head = newNode;
    }
    else {
        struct LineNode* temp = (*ed).head;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        (*temp).next = newNode;
    }
    printf("new line had been added\n");
}

void append(struct Editor* ed) {
    char input[256];
    printf("enter your text: ");
    scanf(" %[^\n]", input);

    if ((*ed).head == NULL) {
        newLine(ed);
    }

    struct LineNode* temp = (*ed).head;
    while ((*temp).next != NULL) {
        temp = (*temp).next;
    }
    int i = 0;
    while ((*temp).text[i] != '\0') {
        i++;
    }
    int j = 0;
    while (input[j] != '\0') {
        (*temp).text[i] = input[j];
        i++;
        j++;
    }
    (*temp).text[i] = '\0';
}

void printAll(struct Editor* ed) {
    struct LineNode* current = (*ed).head;
    if (current == NULL) {
        printf("editor is empty");
        return;
    }

    printf("\n Current text: ");
    while (current != NULL) {
        printf("%s\n", (*current).text);
        current = (*current).next;
    }
}

void saveToFile(struct Editor* ed) {
    char filename[256];
    printf("enter the filename for savings: ");
    scanf(" %s", filename);

    FILE* file;
    file = fopen(filename, "w");

    if (file != NULL) {
        struct LineNode* current = (*ed).head;
        if (current == NULL) {
            printf("nothing to save");
        }
        else {
            while (current != NULL) {
                fputs((*current).text, file);
                fputs("\n", file);
                current = (*current).next;
            }

            fclose(file);
            printf("saved successfully\n");
        }
    }
    else {
        printf("error opening file");
    }
}

void loadFromFile(struct Editor* ed) {
    char filename[256];
    printf("enter the filename for load: ");
    scanf(" %s", filename);

    FILE* file;
    char mystring[1024];

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening the file\n");
    }
    else {
        while (fgets(mystring, 1024, file) != NULL) {
            int i = 0;
            while (mystring[i] != '\0') {
                if (mystring[i] == '\n') {
                    mystring[i] = '\0';
                    break;
                }
                i++;
            }

            newLine(ed);

            struct LineNode* temp = (*ed).head;
            while ((*temp).next != NULL) temp = (*temp).next;
            int k = 0;
            while (mystring[k] != '\0') {
                (*temp).text[k] =mystring[k];
                k++;
            }
            (*temp).text[k] = '\0';
        }
        fclose(file);
        printf("loaded successfully");
    }
}

void search(struct Editor* ed) {
    char target[256];
    printf("enter text to search: ");
    scanf(" %[^\n]", target);

    struct LineNode* current = (*ed).head;
    int lineNumber = 0;
    int foundany = 0;

    while (current != NULL) {
        char* text = (*current).text;

        for (int a = 0; text[a] != '\0'; a++) {
            int b = 0;

            while (target[b] != '\0' && text[a + b] != '\0' && text[a + b] == target[b]) {
                b++;
            }
            if (target[b] == '\0') {
                printf("found in line %d: %s \n", lineNumber, text);
                foundany = 1;
                break;
            }
        }
        current = (*current).next;
        lineNumber++;
    }
    if (foundany == 0) {
        printf("non found\n");
    }
}

void insertByIndex(struct Editor* ed) {
    int linei, chari;
    char textToInsert[256];

    printf("enter line and symbol index: ");
    scanf("%d %d", &linei, &chari);
    printf("enter text to insert: ");
    scanf(" %[^\n]", textToInsert);

    struct LineNode* current = (*ed).head;
    for (int i = 0; i < linei && current != NULL; i++) {
        current = (*current).next;
    }

    if (current != NULL) {
        char oldtext[1024];
        int len = 0;
        while ((*current).text[len] != '\0') {
            oldtext[len] = (*current).text[len];
            len++;
        }
        oldtext[len] = '\0';

        int result = 0;
        for (int i = 0; i < chari && oldtext[i] != '\0'; i++) {
            (*current).text[result++] = oldtext[i];
        }

        for (int i = 0; textToInsert[i] != '\0'; i++) {
            (*current).text[result++] = textToInsert[i];
        }

        for (int i = chari; oldtext[i] != '\0'; i++) {
            (*current).text[result++] = oldtext[i];
        }

        (*current).text[result] = '\0';
        printf("inserted successfully");
    }
    else {
        printf("line non found");
    }
}

int main() {
    struct Editor* myEditor = createEditor();
    int command;
    while (1) {
        help();
        if (scanf("%d", &command) != 1 || command > 7) {
            printf("Invalid input. Please choose from the list \n");
            while (getchar() != '\n');
            continue;
        };

        while (getchar() != '\n');

        if (command == 1) {
            append(myEditor);
        }
        else if (command == 2) {
            newLine(myEditor);
        }
        else if (command == 3) {
            loadFromFile(myEditor);
        }
        else if (command == 4) {
            saveToFile(myEditor);
        }
        else if (command == 5) {
            printAll(myEditor);
        }
        else if (command == 6) {
            insertByIndex(myEditor);
        }
        else if (command == 7) {
            search(myEditor);
        }
        else if (command == 0) {
            break;
        }
        else {
            printf("The command is not implemented\n");
        }
    }
}