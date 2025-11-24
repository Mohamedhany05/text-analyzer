#include <stdio.h>
#include "ui.h"
#include "analysis.h"
#include "functions.h"

void showMenu() {
    int choice;
    char filename[256];

    while (1) {
        printf("\n--- TEXT ANALYZER MENU ---\n");
        printf("1. Load dataset\n");
        printf("2. Analyze\n");
        printf("3. Sort by frequency\n");
        printf("4. Show statistics\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter file name (inside Datasets/): ");
                fgets(filename, sizeof(filename), stdin);
                trimNewline(filename);

                char fullpath[300];
                sprintf(fullpath, "Datasets/%s", filename);

                loadFile(fullpath);
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

            default:
                printf("Invalid choice.\n");
        }
    }
}
