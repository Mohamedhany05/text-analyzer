#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analysis.h"
#include "functions.h"

WordFreq words[MAX_WORDS];
int wordCount = 0;

/* Internal counters */
static int totalWords = 0;      /* includes stopwords */
static int toxicWordCount = 0;  /* ALL toxic tokens found */
static int mildCount = 0;
static int moderateCount = 0;
static int severeCount = 0;

/* RESET EVERYTHING */
static void resetWordList(void) {
    wordCount = 0;
    totalWords = 0;
    toxicWordCount = 0;
    mildCount = 0;
    moderateCount = 0;
    severeCount = 0;

    for (int i = 0; i < MAX_WORDS; i++) {
        words[i].word[0] = '\0';
        words[i].count = 0;
        words[i].isToxic = 0;
        words[i].severity = -1;
    }
}

/* CLEAN TOKEN*/
static void cleanToken(char *token) {
    trimNewline(token);
    removePunctuation(token);
    toLowerCase(token);
}

/*INSERT TOKEN INTO TABLE*/
static void insertWord(const char *token) {
    if (!token || token[0] == '\0')
        return;

    totalWords++;

    int sev = getToxicSeverity(token);   /* -1,0,1,2 */
    int isToxic = (sev >= 0);

    if (isToxic) {
        toxicWordCount++;
        if (sev == 0)      mildCount++;
        else if (sev == 1) moderateCount++;
        else if (sev == 2) severeCount++;
    }

    /* stopwords are not tracked in frequency table */
    if (isStopword(token))
        return;

    /* check if already exists */
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(words[i].word, token) == 0) {
            words[i].count++;

            if (isToxic) {
                words[i].isToxic = 1;
                words[i].severity = sev;
            }

            return;
        }
    }

    /* new word */
    if (wordCount < MAX_WORDS) {
        strcpy(words[wordCount].word, token);
        words[wordCount].count = 1;
        words[wordCount].isToxic = isToxic;
        words[wordCount].severity = isToxic ? sev : -1;
        wordCount++;
    }
}

/*CSV SUPPORT*/
static void extractCSVText(const char *line, char *out) {
    int inQuotes = 0;
    int idx = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
            continue;
        }
        if (!inQuotes && c == ',')
            break;

        out[idx++] = c;
    }

    out[idx] = '\0';
}

/*LOAD TXT / CSV FILE*/
void loadFile(const char *filename) {
    resetWordList();

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening %s\n", filename);
        return;
    }

    int isCSV = 0;
    int len = strlen(filename);

    if (len > 4 && strcmp(filename + len - 4, ".csv") == 0)
        isCSV = 1;

    char line[6000];
    char extracted[6000];
    int skipHeader = isCSV;

    while (fgets(line, sizeof(line), file)) {

        if (skipHeader) {
            skipHeader = 0;
            continue;
        }

        if (isCSV) {
            extractCSVText(line, extracted);
            strcpy(line, extracted);
        }

        char *token = strtok(line, " ");
        while (token) {
            cleanToken(token);
            if (token[0] != '\0')
                insertWord(token);

            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    printf("Loaded file: %s\n", filename);
}

/*GENERAL STATS*/
void analyzeText(void) {
    printf("\n--- General Word Statistics ---\n");
    printf("Total words processed (incl. stopwords): %d\n", totalWords);
    printf("Unique non-stopword words: %d\n", wordCount);

    if (totalWords > 0) {
        double lex = (double)wordCount / (double)totalWords;
        printf("Lexical diversity: %.4f\n", lex);
    }
}

/*SORT BY FREQUENCY (DESCENDING)*/
void sortWordsByFrequency(void) {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (words[j].count < words[j + 1].count) {
                WordFreq tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }
    printf("Sorting complete.\n");
}

/*TOP 10 + TOXIC SUMMARY*/
void printStatistics(void) {
    if (wordCount == 0) {
        printf("No dataset loaded.\n");
        return;
    }

    sortWordsByFrequency();

    int limit = (wordCount < 10) ? wordCount : 10;

    printf("\nTop %d Most Frequent Words:\n", limit);
    for (int i = 0; i < limit; i++)
        printf("%s : %d\n", words[i].word, words[i].count);

    printf("\n--- Toxic Word Summary ---\n");
    printf("Total words processed: %d\n", totalWords);
    printf("Toxic words found: %d\n", toxicWordCount);

    if (totalWords > 0) {
        printf("Toxic percentage: %.2f%%\n",
                (double)toxicWordCount * 100.0 / (double)totalWords);
    }

    printf("By severity:\n");
    printf("  Mild     : %d\n", mildCount);
    printf("  Moderate : %d\n", moderateCount);
    printf("  Severe   : %d\n", severeCount);
}

/*TOP N FREQUENT WORDS*/
void printTopNWords(int N) {
    if (wordCount == 0) {
        printf("No dataset loaded.\n");
        return;
    }

    if (N <= 0) {
        printf("N must be positive.\n");
        return;
    }

    sortWordsByFrequency();
    if (N > wordCount) N = wordCount;

    printf("\nTop %d Most Frequent Words:\n", N);
    for (int i = 0; i < N; i++)
        printf("%s : %d\n", words[i].word, words[i].count);
}

/*TOP N TOXIC WORDS*/
void printTopNToxicWords(int N) {
    if (wordCount == 0) {
        printf("No dataset loaded.\n");
        return;
    }

    if (N <= 0) {
        printf("N must be positive.\n");
        return;
    }

    WordFreq tox[MAX_WORDS];
    int tCount = 0;

    for (int i = 0; i < wordCount; i++) {
        if (words[i].isToxic)
            tox[tCount++] = words[i];
    }

    if (tCount == 0) {
        printf("No toxic words found.\n");
        return;
    }

    /* sort toxic subset */
    for (int i = 0; i < tCount - 1; i++) {
        for (int j = 0; j < tCount - i - 1; j++) {
            if (tox[j].count < tox[j + 1].count) {
                WordFreq tmp = tox[j];
                tox[j] = tox[j + 1];
                tox[j + 1] = tmp;
            }
        }
    }

    if (N > tCount) N = tCount;

    printf("\nTop %d Toxic Words:\n", N);

    for (int i = 0; i < N; i++) {
        const char *sev =
            (tox[i].severity == 0) ? "mild" :
            (tox[i].severity == 1) ? "moderate" :
            (tox[i].severity == 2) ? "severe" : "unknown";

        printf("%s : %d (severity: %s)\n",
               tox[i].word, tox[i].count, sev);
    }
}

/*SAVE REPORT*/
void saveReportToFile(const char *filename) {
    if (wordCount == 0) {
        printf("No dataset loaded.\n");
        return;
    }

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Could not write to %s\n", filename);
        return;
    }

    sortWordsByFrequency();

    fprintf(f, "Cyberbullying / Toxic Text Analyzer Report\n");
    fprintf(f, "=========================================\n\n");
    fprintf(f, "Total words processed: %d\n", totalWords);
    fprintf(f, "Unique words: %d\n\n", wordCount);

    int limit = (wordCount < 20) ? wordCount : 20;

    fprintf(f, "Top %d Frequent Words:\n", limit);
    for (int i = 0; i < limit; i++)
        fprintf(f, "%s : %d\n", words[i].word, words[i].count);

    fprintf(f, "\nToxic Summary:\n");
    fprintf(f, "Total toxic: %d\n", toxicWordCount);
    fprintf(f, "Mild: %d\n", mildCount);
    fprintf(f, "Moderate: %d\n", moderateCount);
    fprintf(f, "Severe: %d\n", severeCount);

    fclose(f);
    printf("Report saved to %s\n", filename);
}
