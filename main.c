#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("\n Text Editor \n"
           "1. Append text symbols to the end\n"
           "2. Start the new line\n"
           "3. Use files to load/save the information\n"
           "4. Print the current text to console\n"
           "5. Insert the text by line and symbol index\n"
           "6. Search\n"
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
    strcat((*temp).text, input);
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

int main() {
    struct Editor* myEditor = createEditor();
    int command;
    while (1) {
        help();
        if (scanf("%d", &command) != 1 || command > 6) {
            printf("Invalid input. Please choose from the list \n");
        };

        if (command == 1) {
            append(myEditor);
        }
        else if (command == 2) {
            newLine(myEditor);
        }
        else if (command == 4) {
            printAll(myEditor);
        }
        else if (command == 0) {
            break;
        }
        else {
            printf("The command is not implemented\n");
        }
    }
}