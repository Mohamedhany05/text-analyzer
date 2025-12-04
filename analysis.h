#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "functions.h"

#define MAX_WORDS 50000

typedef struct {
    char word[50];
    int count;
    int isToxic;
    int severity;   /* -1 = non-toxic, 0/1/2 = levels */
} WordFreq;

extern WordFreq words[MAX_WORDS];
extern int wordCount;

void loadFile(const char *filename);
void analyzeText(void);
void sortWordsByFrequency(void);
void printStatistics(void);

void printTopNWords(int N);
void printTopNToxicWords(int N);

void saveReportToFile(const char *filename);

/* OPTION A: reload dictionaries */
void reloadDictionaries(void);

#endif
