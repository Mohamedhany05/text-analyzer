#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // for atoi()
#include "functions.h"

/*STOPWORDS*/

static char stopwords[MAX_STOPWORDS][50];
static int stopwordCount = 0;

int loadStopwords(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Warning: could not open %s\n", filename);
        return 0;
    }

    stopwordCount = 0;
    char buf[100];

    while (fgets(buf, sizeof(buf), f) && stopwordCount < MAX_STOPWORDS) {
        trimNewline(buf);
        toLowerCase(buf);
        if (buf[0] == '\0') continue;
        strcpy(stopwords[stopwordCount++], buf);
    }

    fclose(f);
    return stopwordCount;
}

int isStopword(const char *word) {
    for (int i = 0; i < stopwordCount; i++) {
        if (strcmp(stopwords[i], word) == 0)
            return 1;
    }
    return 0;
}

/*TOXIC WORDS*/

static ToxicEntry toxicwords[MAX_TOXICWORDS];
static int toxicCount = 0;

int loadToxicWords(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Warning: could not open %s\n", filename);
        return 0;
    }

    toxicCount = 0;
    char line[200];

    while (fgets(line, sizeof(line), f)) {
        trimNewline(line);
        toLowerCase(line);

        if (line[0] == '\0')
            continue;

        char *token = strtok(line, " \t");
        if (!token) continue;

        char word[50];
        strcpy(word, token);

        token = strtok(NULL, " \t");
        if (!token) continue;

        int sev = atoi(token);

        strcpy(toxicwords[toxicCount].word, word);
        toxicwords[toxicCount].severity = sev;

        toxicCount++;
        if (toxicCount >= MAX_TOXICWORDS)
            break;
    }

    fclose(f);
    return toxicCount;
}

int getToxicSeverity(const char *word) {
    for (int i = 0; i < toxicCount; i++) {
        if (strcmp(toxicwords[i].word, word) == 0)
            return toxicwords[i].severity;
    }
    return -1;
}

/*CLEANING HELPERS*/

void removePunctuation(char *s) {
    int i = 0, j = 0;
    while (s[i] != '\0') {
        if (isalnum((unsigned char)s[i]) || s[i] == '\'' || s[i] == '_')
            s[j++] = s[i];
        i++;
    }
    s[j] = '\0';
}

void toLowerCase(char *s) {
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = (char)tolower((unsigned char)s[i]);
}

void trimNewline(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}
