#include <stdio.h>

void help() {
    printf("\n Text Editor \n"
           "1. Append text symbols to the endAppend text symbols to the end\n"
           "2. Start the new line\n"
           "3. Use files to load/save the information\n"
           "4. Print the current text to console\n"
           "5. Insert the text by line and symbol index\n"
           "6. Search\n"
           "0. Exit\n"
           "Choose the command: ");
}

int main() {
    int command;
    while (1) {
        help();
        if (scanf("%d", &command) != 1 || command > 6) {
            printf("Invalid input. Please choose from the list \n");
        };

        if (command == 0) {
            break;
        }
        else {
            printf("The command is not implemented\n");
        }
    }
}