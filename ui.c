#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "analysis.h"
#include "functions.h"

void reloadDictionaries(void) {
    int stop = loadStopwords("stopwords.txt");
    int tox  = loadToxicWords("toxicwords.txt");

    printf("Dictionaries reloaded (%d stopwords, %d toxic words).\n", stop, tox);
}

void runMenu(void) {
    int choice = 0;
    char fileName[260];
    char fullPath[512];
    int N;

    int stopCount = loadStopwords("stopwords.txt");
    int toxCount  = loadToxicWords("toxicwords.txt");

    printf("Loaded %d stopwords.\n", stopCount);
    printf("Loaded %d toxic words.\n", toxCount);

    while (1) {
        printf("\n--- TEXT ANALYZER MENU ---\n");
        printf("1. Load dataset\n");
        printf("2. Analyze\n");
        printf("3. Sort words by frequency\n");
        printf("4. Show statistics\n");
        printf("5. Exit\n");
        printf("6. Show top N frequent words\n");
        printf("7. Show top N toxic words\n");
        printf("8. Save analysis report to file\n");
        printf("9. Reload dictionaries\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter file name (inside Datasets/): ");
                scanf("%s", fileName);
                snprintf(fullPath, sizeof(fullPath), "Datasets/%s", fileName);
                loadFile(fullPath);
                break;

            case 2:
                analyzeText();
                break;

            case 3:
                sortWordsByFrequency();
                break;

            case 4:
                printStatistics();
                break;

            case 5:
                return;

            case 6:
                printf("Top how many? ");
                scanf("%d", &N);
                printTopNWords(N);
                break;

            case 7:
                printf("Top how many toxic? ");
                scanf("%d", &N);
                printTopNToxicWords(N);
                break;

            case 8:
                saveReportToFile("analysis_report.txt");
                break;

            case 9:
                reloadDictionaries();
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
}
