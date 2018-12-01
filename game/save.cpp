//
// Created by Tomasz Piechocki on 01/12/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"save.h"
#include"../conio2.h"
#include"direct.h"

#ifdef __GNUC__
#include<stdlib.h>
#endif

#ifdef __cplusplus
#define EXTERNC    extern "C"
#else
#define EXTERNC
#endif

// function which returns save file name provided by the user
char *enterName() {
    clrscr();
    char str[30];
    char ch = 0;
    gotoxy(5, 5);
    cputs("Enter the file name: ");
    gotoxy(5, 6);
    int i;
	ch = (char)getche();
    for (i = 0; ch != 0x0d ; ++i) {
        str[i] = ch;
		ch = (char)getche();
    }
    str[i] = '\0';
    int length = strlen(str);
	char *fileName = (char *)malloc(sizeof(str[0])*(length + 1));
	if (fileName == NULL) {
	    error("Error while creating a save.");
        return NULL;
	}
    strcpy(fileName, str);
    return fileName;
}

EXTERNC
void saveGame(board_status_t *board, player_t *player) {
    char *fileName = enterName();       // get name for save
    char txt[30];
    _mkdir("saves");        // create directory for saves if it does not exits
    sprintf(txt, "saves\\%s", fileName);        // save in folder saves
    FILE *saveFile = fopen(txt, "w");
	fwrite(board, sizeof(*board), 1, saveFile);
	fwrite(player, sizeof(*player), 1, saveFile);
    fclose(saveFile);
}

EXTERNC
void loadGame(board_status_t *board, player_t *player) {
    char *fileName = enterName(); // get name of file
    char txt[30];
    sprintf(txt, "saves//%s", fileName);        // save from folder saves
    FILE *saveFile = fopen(txt, "r");
    if (saveFile == NULL)
        error("This save does not exist.");
    else {
        fread(board, sizeof(*board), 1, saveFile);
        fread(player, sizeof(*player), 1, saveFile);
        fclose(saveFile);
    }
}
