# Scrabble

First project for PP

Changelog:

0.3
- creating a randomized pool
- take tiles from pool, if there are remaining, when there are empty in hand
- end of game window, when player has 0 tiles and pool is empty
- exchange chosen tiles
- highlight chosen tiles before action

fixes:
- first letter can be placed only if all needed letters are in player's hand
- border changed to letters and numbers
- function displayAll instead of every thing seperately

0.2
- insert a word instead of letter with check whether player can do it;
  each action is confirmed with enter or cancelled with escape
    * create the word below the board; backspace to delete last letter;
    * position the word within board; arrows move the word and 'o' changes the word orientation
    * confirm to try putting the word; it is placed or error message is shown
- first word must be placed through middle
- rest of words must have at least one letter already on board
- colors indicate correctness while creating or positioning the words
- used tiles dissappear from hand
- check if any of tiles was used to insert a word
- blanks

0.1
- display board with border
- display legend
- move around the board with the cursor
- show player's tilespl
- new game with n key
- insert one letter on the board
