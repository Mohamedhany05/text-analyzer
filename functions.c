#include <ctype.h>
#include <string.h>
#include "functions.h"

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void removePunctuation(char *str) {
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (isalnum((unsigned char)str[i]) || str[i] == ' ')
            str[j++] = str[i];
    }
    str[j] = '\0';
}

char* trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
    return str;
}
