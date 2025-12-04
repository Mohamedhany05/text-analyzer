# Cyberbullying Text Analyzer  
### COMP1028 Programming Coursework  
### Group Name: Nashafy  

**Group Members**
- Youssef Mahran — 20683692  
- Mohamed Hany Abdelaziz — 20679455  
- Ali Ibrahim Al Komey — 20794457  
- Nageh Mohamed Sameh — 20686405  

##  Overview

The **Cyberbullying Text Analyzer** is a C-based command-line program that processes text datasets to detect toxic or harmful language. It identifies toxic words, categorizes them into severity levels, filters stopwords, computes word frequencies, and generates detailed statistical reports.

The program supports:
- `.txt` and `.csv` input files  
- Stopword removal  
- Toxicity detection with severity classification (0 = mild, 1 = moderate, 2 = severe)  
- Sorting & Top-N analysis  
- Report generation  
- Dictionary reloading without restarting the program  


##  Folder Structure

Text Analyzer/
│   main.c
│   ui.c
│   analysis.c
│   functions.c
│   functions.h
│   analysis.h
│   README.md
│   analyzer.exe
│
├── Datasets/
│     tweets.txt
│     cyberbullying_tweets.csv
│
├── stopwords.txt
└── toxicwords.txt

##  How to Compile (Windows Command Prompt)

Run this command inside the project folder:

```bash
gcc -std=c11 -Wall -Wextra -o analyzer.exe main.c ui.c analysis.c functions.c

If successful, `analyzer.exe` will be created.


## ▶ How to Run

```bash
analyzer.exe


##  Program Menu

- TEXT ANALYZER MENU -
1. Load dataset
2. Analyze
3. Sort words by frequency
4. Show statistics
5. Exit
6. Show top N frequent words
7. Show top N toxic words
8. Save analysis report to file
9. Reload dictionaries


##  Required Files

Ensure the following files exist in the main folder:

stopwords.txt
toxicwords.txt

Place datasets inside:

/Datasets/

When loading a dataset, enter only the filename:

tweets.txt
cyberbullying_tweets.csv

##  Sample Output

Loaded 127 stopwords.
Loaded 20 toxic words.

Top 10 Most Frequent Words:
school : 8722
fuck : 5797
dumb : 5335

--- Toxic Word Summary ---
Toxic words found: 25751
Mild: 8941
Moderate: 4126
Severe: 12684

##  Features

###  Text Processing
- Lowercasing  
- Punctuation removal  
- Tokenization via `strtok`  
- CSV first-column extraction  

###  Toxicity Detection  
Reads toxic words from `toxicwords.txt`:

Example format:

idiot 0
stupid 0
bitch 1
fuck 2
```

Severity:
- **0 — Mild**
- **1 — Moderate**
- **2 — Severe**

###  Analysis Features  
- Word frequency table  
- Top N frequent words  
- Top N toxic words  
- Toxic distribution summary  
- Lexical diversity calculation  
- Report saving  

###  Live Dictionary Reloading  
Reloads:
- stopwords.txt  
- toxicwords.txt  

without restarting the program.

---


COMP1028 — Cyberbullying Text Analyzer  
