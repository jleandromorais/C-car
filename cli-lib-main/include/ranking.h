
#ifndef RANKING_H
#define RANKING_H

#define MAX_PLAYERS 100

typedef struct {
    char name[20];
    int score;
} PlayerScore;

void loadScores();
void sortScores();
void showRanking();

#endif
