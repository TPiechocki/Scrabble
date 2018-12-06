//
// Created by Tomasz Piechocki on 01/12/2018.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include"save.h"
#include"../conio2.h"

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
    char str[30];   // buffer
    char ch = 0;
    gotoxy(5, 5);
    cputs("Enter the file name. Use letters, numbers or spaces: ");
    gotoxy(5, 6);
    int count = 0;
	while (ch != 0x0d) {    // confirm with enter
	    ch = (char)getch();
	    if (ch == '\b') {   // backspace
            if (count > 0) {
                count--;
                str[count] = '\0';
            }
        }
	    // letters, numbers or space
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '1' && ch <= '9') || ch == ' ') {
            if (count < 29) {
                str[count] = ch;
                str[count + 1] = '\0';
                ++count;
            }
        }
        else if (ch == 0x0d);   // do nothing when enter - confirmation of action
        else {
            error("Invalid character.");
            return NULL;
        }
        gotoxy(5,6);
        clreol();
        for (int i = 0; str[i] != '\0'; ++i) {
            putch(str[i]);
        }
	}
    int length = strlen(str);
    if (length == 0) {      // error when file name is empty
        error("Name can't be empty.");
        return NULL;
    }
	char *fileName = (char *)malloc(sizeof(str[0])*(length + 1));
	if (fileName == NULL) {
	    error("Error while creating a save.");
        return NULL;
	}
    strcpy(fileName, str);
    return fileName;
}

EXTERNC
void saveGame(board_status_t *board, player_t *player, char *dictionary) {
    char *fileName = enterName();       // get name for save
    if(fileName == NULL) {        // if fileName was empty do nothing
        error("You must enter name.");
        return;
    }
    char txt[30];
    _mkdir("saves");        // create directory for saves if it does not exits
    sprintf(txt, "saves\\%s", fileName);        // save in folder saves
    FILE *saveFile = fopen(txt, "w");
    if (saveFile == NULL) {
        error("Can't create save with this name.");
        return;
    }
    fwrite(dictionary, sizeof(dictionary[0]), 50, saveFile);
	fwrite(board, sizeof(*board), 1, saveFile);
	fwrite(player, sizeof(*player), 1, saveFile);
    fclose(saveFile);
    free(fileName);
}

EXTERNC
void loadGame(board_status_t *board, player_t *player, char *dictionary) {
    char *fileName = enterName(); // get name of file
    if(fileName == NULL)        // if fileName was empty do nothing
        return;
    char txt[30];
    sprintf(txt, "saves//%s", fileName);        // save from folder saves
    FILE *saveFile = fopen(txt, "r");
    if (saveFile == NULL)       // check if save with this name exist
        error("This save does not exist.");
    else {          // read only if exist
        fread(dictionary, sizeof(dictionary[0]), 50, saveFile);
        fread(board, sizeof(*board), 1, saveFile);
        fread(player, sizeof(*player), 1, saveFile);
        fclose(saveFile);
    }
    free(fileName);
}
