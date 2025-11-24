#include <stdio.h>
#include <string.h>
#include "analysis.h"
#include "functions.h"

static WordFreq words[MAX_WORDS];
static int wordCount = 0;

void loadFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        trimNewline(line);
        toLowerCase(line);
        removePunctuation(line);

        char *token = strtok(line, " ");
        while (token) {
            int found = 0;

            for (int i = 0; i < wordCount; i++) {
                if (strcmp(words[i].word, token) == 0) {
                    words[i].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && wordCount < MAX_WORDS) {
                strcpy(words[wordCount].word, token);
                words[wordCount].count = 1;
                wordCount++;
            }

            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    printf("Loaded file: %s\n", filename);
}

void analyzeText() {
    printf("\nTotal unique words: %d\n", wordCount);
}

void sortWordsByFrequency() {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (words[j].count < words[j + 1].count) {
                WordFreq temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

void printStatistics() {
    printf("\nTop 10 words:\n");
    for (int i = 0; i < 10 && i < wordCount; i++) {
        printf("%s : %d\n", words[i].word, words[i].count);
    }
}
