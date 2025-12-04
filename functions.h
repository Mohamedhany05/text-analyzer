#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#define MAX_STOPWORDS 2000
#define MAX_TOXICWORDS 2000

/* Toxic entry: word + severity */
typedef struct {
    char word[50];
    int severity;   /* 0 = mild, 1 = moderate, 2 = severe */
} ToxicEntry;

/* Stopwords */
int loadStopwords(const char *filename);
int isStopword(const char *word);

/* Toxic words */
int loadToxicWords(const char *filename);
int getToxicSeverity(const char *word);

/* Cleaning helpers */
void removePunctuation(char *s);
void toLowerCase(char *s);
void trimNewline(char *s);

#endif
