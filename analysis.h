#ifndef ANALYSIS_H
#define ANALYSIS_H

#define MAX_WORDS 50000
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

void loadFile(const char *filename);
void analyzeText();
void sortWordsByFrequency();
void printStatistics();

#endif
