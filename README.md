# Scrabble

First project for Basics of Programming

To append custom dicitonary add in console after program name "-d name-of-file".
Every word in dictionary is stored in a new line. End line symbol is in Windows style (CRLF).
Other line endings will probably cause an uncaught error, because of different char between the words.

Changelog:

1.0.1

fixes:
- player could choose empty tiles to exchange
- player couldn't exchange letters

1.0
- read a dictionary from a file
- clear space allocated before closing program(fixed)
- user can specify dictionary name in command line call "-d name_of_file"
- check if all words created by move are in dictionary
- loading the save try to load the same dictionary with which it was saved
- count points for all new words

fixes:
- display on end with scores
- player can skip his move(as long as this is one player game it will cause end of game)
- check if word can placed just after creating the word
- 50 point bonus if player used all tiles
- exchange error, when player wants to exchange more than left in a pool
- letter used with blank while creating word had no color
- on save or load backspace handling
- crash when too long save name
- board coordinates with letter and number(earlier two letters)

0.5
- save and load state of the game
- user can specify save name

0.4
- colored places for bonuses
- every letter is connected with it's points value
- letter points below a tile
- count points including  all bonuses

fixes:
- 'f' key fixes problems with colours and cursor after resizing the console
- tiles from exchange are taken in order not randmoly

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
