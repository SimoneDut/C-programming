#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#define CLICK_VOID -3
#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define MAX_WIDTH 15
#define MAX_HEIGHT 15

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[39m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"
#define ANSI_BACKGROUND_RESET   "\x1b[49m"

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

struct _board_t {
  int ** board;  
  int width;  
  int height;  
  int totalMines;  
};
typedef struct _board_t board_t;

struct _parameters_t {
  int width;  
  int height;
  int numMines;
  int mode;
};
typedef struct _parameters_t parameters_t;

void addRandomMine(board_t * b, int mines) {
  // function revisited by SimoneDut  
  int pos = rand() % ((b->width)*(b->height)-mines);  
  for (int i = 0; i < b->height; i++) {
    for (int j = 0; j < b->width; j++) {
      if (b->board[i][j] != HAS_MINE) { pos--; }
      if (pos < 0) {
	b->board[i][j] = HAS_MINE;
	return;	
      }      
    }    
  }  
}

board_t * makeBoard(int w, int h, int numMines) { 
  board_t * b = malloc(sizeof(*b));
  b->width = w;
  b->height = h;
  b->totalMines = numMines;
  b->board = malloc(h*sizeof(*(b->board)));
  for (int i = 0; i < h; i++) {
    b->board[i] = malloc(w*sizeof(*(b->board[i])));
    for (int j = 0; j < w; j++) {
      b->board[i][j]=UNKNOWN;      
    }    
  }
  srand(time(NULL));  
  for (int k = 0; k < numMines; k++) {
    addRandomMine(b,k);    
  }
  return b;  
}

void printBoard(board_t * b, int moves, int win) {  
  // int win added by SimoneDut
  int found = 0;
  printf("    ");  
  for (int x = 0; x < b->width; x++) {
    if (x/10 == 0) {
      printf(" ");      
    }
    else {      
      printf("%d",x/10);      
    }
  }
  printf("\n    ");  
  for (int x = 0; x < b->width; x++) {    
    printf("%d",x%10);    
  }  
  printf("\n----");
  for (int x = 0; x < b->width; x++) {    
    printf("-");    
  }  
  printf("\n");  
  for (int y = 0; y < b->height; y++) {    
    printf("%2d: ", y %100);    
    for (int x = 0; x < b->width; x++) {      
      if (b->board[y][x] == KNOWN_MINE) {	
	if (win) {	  
	  printf(ANSI_COLOR_CYAN"*"ANSI_COLOR_RESET);	  
	}	
	else {	  
	  printf(ANSI_COLOR_RED"*"ANSI_COLOR_RESET);	  
	}	
	found++;	
      }      
      else if (b->board[y][x] < 0) {
	printf(ANSI_BACKGROUND_GREEN);	
	printf(ANSI_COLOR_BLACK"?"ANSI_COLOR_RESET);	
	printf(ANSI_BACKGROUND_RESET);	
      }      
      else if (b->board[y][x] == 0) {	
	printf(" ");	
      }      
      else {	
	printf("%d", b->board[y][x]);	
      }      
    }    
    printf("\n");    
  }  
  printf("----");  
  for (int x = 0; x < b->width; x++) {    
    printf("-");    
  }  
  printf("\n");
  printf("    ");
  for (int x = 0; x < b->width; x++) {    
    if (x/10 == 0) {      
      printf(" ");      
    }    
    else {      
      printf("%d",x/10);      
    }    
  }  
  printf("\n    ");  
  for (int x = 0; x < b->width; x++) {    
    printf("%d",x%10);    
  }  
  printf("\nFound %d of %d mines\n", found, b->totalMines);
  printf("(You already did %d moves)\n",moves);  
}

int countMines(board_t * b, int x, int y) {  
  int count = 0;  
  for (int i = -1; i <= 1; i++) {    
    for (int j = -1; j <= 1; j++) {      
      int ny = y+i;      
      int nx = x+j;      
      if ((ny>=0)&&(ny<b->height)&&(nx>=0)&&(nx<b->width)) {	
	if ((i!=0)||(j!=0)) {	  
	  if (IS_MINE(b->board[ny][nx])) { count++; }	  
	}	
      }      
    }    
  }  
  return count;  
}



int click (board_t * b, int x, int y) {  
  if (x < 0 || x >= b->width ||      
      y < 0 || y >= b->height) {    
    return CLICK_INVALID;    
  }  
  if (b->board[y][x] == KNOWN_MINE) {    
    return CLICK_KNOWN_MINE;    
  }  
  if (b->board[y][x] == HAS_MINE) {    
    return CLICK_LOSE;    
  }  
  if (b->board[y][x] != UNKNOWN) {    
    return CLICK_VOID;    
  }  
  b->board[y][x] = countMines(b,x,y);  
  return CLICK_CONTINUE;  
}

int checkWin(board_t * b) {  
  for (int i = 0; i < b->height; i++) {    
    for (int j = 0; j < b->width; j++) {      
      if (b->board[i][j]==UNKNOWN) { return 0; }      
    }    
  }  
  return 1;  
}

void freeBoard(board_t * b) {  
  for (int i = 0; i < b->height; i++) {    
    free(b->board[i]);    
  }  
  free(b->board);  
  free(b);  
}

int readInt(char ** linep, size_t * lineszp) {  
  if (getline (linep, lineszp, stdin) == -1) {    
    fprintf (stderr,"End of file from keyboard reading a number.  Quitting\n");    
    exit(EXIT_FAILURE);    
  }
  char * endptr = NULL;  
  long int x = strtol (*linep, &endptr, 10);  
  if (endptr == *linep) {    
    fprintf (stderr,"You did not enter any valid number\n");    
    printf ("Please try again\n");    
    return readInt (linep, lineszp);    
  }  
  if (*endptr != '\n') {    
    fprintf( stderr,	     
	     "Input was not entirely a number (junk at end)\n");    
    printf ("Please try again\n");    
    return readInt (linep, lineszp);
  }  
  if (x > INT_MAX) {    
    fprintf(stderr,"%ld is too big for an int!\n", x);    
    printf("Please try again\n");    
    return readInt(linep, lineszp);    
  }  
  return x;  
}

void doReveal(board_t * b, int x, int y, int revealMines) {  
  for (int dy = -1; dy <=1 ; dy++) {    
    for (int dx = -1; dx <=1 ; dx++) {      
      int nx = x + dx;      
      int ny = y + dy;      
      if (nx >= 0 && nx < b->width &&	  
	  ny >= 0 && ny < b->height) {	
	if (revealMines) {	  
	  assert(b->board[ny][nx] != UNKNOWN);	  
	  if (b->board[ny][nx] == HAS_MINE) {	    
	    b->board[ny][nx] = KNOWN_MINE;	    
	  }	  
	}	
	else  {	  
	  assert(b->board[ny][nx] != HAS_MINE);	  
	  if (b->board[ny][nx] == UNKNOWN) {	    
	    b->board[ny][nx] = countMines(b,nx,ny);	    
	  }	  
	}	
      }      
    }    
  }  
}

int maybeReveal(board_t * b, int x, int y, int mode) {  
  int unknownSquares = 0;  
  int knownMines = 0;  
  for (int dy = -1; dy <=1 ; dy++) {    
    for (int dx = -1; dx <=1 ; dx++) {      
      int nx = x + dx;      
      int ny = y + dy;      
      if (nx >= 0 && nx < b->width &&	  
	  ny >= 0 && ny < b->height) {	
	if (b->board[ny][nx] == UNKNOWN ||	    
	    b->board[ny][nx] == HAS_MINE) {	  
	  unknownSquares++;	  
	}	
	else if(b->board[ny][nx] == KNOWN_MINE) {	  
	  knownMines++;	  
	}	
      }      
    }    
  }  
  assert(knownMines + unknownSquares >= b->board[y][x]);  
  assert(knownMines <= b->board[y][x]);  
  // changes by SimoneDut  
  if (mode == 1) {    
    return 0;    
  }  
  if (mode == 2) {    
    if ((unknownSquares > 0) && (b->board[y][x] == 0)) {      
      doReveal(b,x,y,0);      
      return 1;      
    }    
    return 0;    
  }
  // end of changes  
  if (unknownSquares > 0) {      
    int revealMines = (knownMines + unknownSquares == b->board[y][x]);      
    int allKnown = knownMines == b->board[y][x];      
    if(revealMines || allKnown) {
      assert(!revealMines || !allKnown);
      doReveal(b,x,y, revealMines);	
      return 1;	
    }
  }    
  return 0;      
}

void determineKnownMines(board_t * b, int mode) {  
  // added mode argument by SimoneDut  
  int foundMore = 0;  
  for (int y = 0; y < b->height; y++) {    
    for (int x = 0; x < b->width; x++) {      
      if (b->board[y][x] >= 0) {	
	foundMore = maybeReveal(b,x,y,mode) || foundMore;	
      }      
    }    
  }  
  if (foundMore) {    
    determineKnownMines(b,mode);    
  }  
}

void revealMines(board_t * b) {  
  for (int y = 0; y < b->height; y++) {    
    for (int x = 0; x < b->width; x++) {      
      if (b->board[y][x] == HAS_MINE) {	
	b->board[y][x] = KNOWN_MINE;	
      }      
    }    
  }  
}

void clearscr() {  
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
  system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)  
  system("cls");  
#endif  
}

int playTurn(board_t * b, char ** linep, size_t * lineszp, int * movesp, int mode, int gameOver) {  
  // added moves, mode and gameOver by SimoneDut  
  clearscr();  
  printf("Current board:\n");  
  printBoard(b,*movesp,0);
  switch (gameOver) {    
  case -1:    
    printf("That is not a valid square, please try again\n");
    break;    
  case -2:    
    printf("You already know there is a mine there!\n");    
    break;    
  case -3:    
    printf("You already freed that cell!\n");    
    break;
  default:    
    printf("\n");    
    break;    
  }  
  printf("x coordinate:\n");
  int x = readInt(linep, lineszp);  
  printf("y coordinate:\n");  
  int y = readInt(linep, lineszp);  
  int result = click(b,x,y);  
  if (result == CLICK_INVALID) {    
    return -1;    
  }  
  else if (result == CLICK_KNOWN_MINE) {    
    return -2;    
  }  
  else if (result == CLICK_VOID) {    
    return -3;    
  }  
  (*movesp)++;
  determineKnownMines(b,mode);  
  if(checkWin(b)) {    
    revealMines(b);    
    clearscr();    
    printf("Current board:\n");    
    printBoard(b,*movesp,1);    
    printf("\n");    
    printf(ANSI_COLOR_CYAN"CONGRATULATIONS!!! You win!\n"ANSI_COLOR_RESET);    
    return 1;    
  }  
  else if (result == CLICK_LOSE) {    
    revealMines(b);    
    clearscr();    
    printf("Current board:\n");    
    printBoard(b,*movesp,0);    
    printf("\n");    
    printf(ANSI_COLOR_RED"OH NO, THAT SQUARE HAD A MINE!!! You lose!\n"ANSI_COLOR_RESET);    
    return 1;    
  }  
  return 0;  
}

void setCustomSize(parameters_t * param, int w, int h, int n) {  
  // created by SimoneDut  
  param->width = w;  
  param->height = h;  
  param->numMines = n;  
}

void setStandardSize(parameters_t * param, char boardSize) {  
  // created by SimoneDut  
  switch (boardSize) {    
  case 'S':    
  case 's':    
    setCustomSize(param,5,5,5);    
    break;    
  case 'M':    
  case 'm':    
    setCustomSize(param,10,10,20);    
    break;    
  case 'B':    
  case 'b':    
    setCustomSize(param,15,15,45);    
    break;    
  default:    
    exit(EXIT_FAILURE);    
  }  
}

int checkValidSize(parameters_t * param) {  
  // created by SimoneDut  
  if (param->width <= 0 || param->height <= 0 || param->numMines <= 0) {    
    fprintf(stderr,"Width, height, and numMines must all be positive ints\n\n");    
    return 0;    
  }  
  if (param->width > MAX_WIDTH || param->height > MAX_HEIGHT) {    
    fprintf(stderr,"The maximum dimension is (width %d x height %d)\n\n",MAX_WIDTH,MAX_HEIGHT);    
    return 0;    
  }
  if (param->numMines > param->width*param->height) {    
    fprintf(stderr,"Too many mines, with these dimensions cannot be more than %d\n\n",param->width*param->height);    
    return 0;    
  }  
  return 1;  
}

void setGameMode(parameters_t * param, char gameMode) {
  switch (gameMode) {
  case '1':    
    param->mode = 1;    
    break;    
  case '2':    
    param->mode = 2;    
    break;    
  case '3':    
    param->mode = 3;    
    break;    
  default:    
    exit(EXIT_FAILURE);    
  }  
}

parameters_t * initParam(int argc, char ** argv) {  
  // created by SimoneDut  
  parameters_t * ans = malloc(sizeof(*ans));  
  int initSuccess = 0;  
  char * line = NULL;  
  size_t linesz = 0;  
  if (argc > 1) {    
    if (argc != 4) {      
      fprintf(stderr,"Wrong usage: to customize the parameters you should run the program with the following format 'minesweeper width height numMines'.\n\n");
    }    
    else {      
      do {	
	printf("Do you want to use your custom parameters? ('Y'/'y' for yes, any other character for no)\n");	
      } while(getline(&line, &linesz, stdin) == -1);      
      printf("\n");      
      switch (line[0]) {	
      case 'Y':	
      case 'y':
	setCustomSize(ans,atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));	
	initSuccess = checkValidSize(ans);	
	break;	
      default:	
	initSuccess = 0;	
	break;	
      }      
    }    
  }  
  if (initSuccess == 0) {    
    printf("Playing with the standard configuration\n\n");    
    do {      
      printf("Which board do you want? ('S'/'s' for small, 'M'/'m' for medium, 'B'/'b' for big, any other character to quit)\n");      
    } while(getline(&line, &linesz, stdin) == -1);    
    setStandardSize(ans,line[0]);    
    printf("\n");    
  }  
  do {    
    printf("Which game mode you want? ('1' for one move at a time, '2' for automatic free areas clearing, '3' for automatic obvious moves, any other character to quit)\n");    
  } while(getline(&line, &linesz, stdin) == -1);  
  setGameMode(ans,line[0]);
  return ans;
}

void welcomeScreen() {  
  // created by SimoneDut  
  char * line = NULL;  
  size_t linesz = 0;  
  printf("\n\n");  
  printf("                                        WELCOME TO THE ");  
  printf(ANSI_COLOR_RED"M");  
  printf(ANSI_COLOR_MAGENTA"I");  
  printf(ANSI_COLOR_CYAN"N");  
  printf(ANSI_COLOR_GREEN"E");  
  printf(ANSI_COLOR_YELLOW"S");  
  printf(ANSI_COLOR_RED"W");  
  printf(ANSI_COLOR_MAGENTA"E");  
  printf(ANSI_COLOR_CYAN"E");  
  printf(ANSI_COLOR_GREEN"P");  
  printf(ANSI_COLOR_YELLOW"E");  
  printf(ANSI_COLOR_RED"R");  
  printf(ANSI_COLOR_RESET);  
  printf(" GAME!");  
  printf("\n\n");  
  printf("          - The purpose of this game is to completely free the board while avoiding hitting the mines\n");  
  printf("          - Too free the board you will need to enter each time the x (horizontal) and y (vertical) coordinates of the cell you want to free\n");  
  printf("          - But be careful! If you hit a mine the game will end\n");
  printf("\n");  
  printf("Press enter to continue\n");  
  do {}  
  while(getline(&line, &linesz, stdin) == -1);  
}

int main(int argc, char ** argv) {  
  // changes by SimoneDut

  int width;  
  int height;  
  int numMines;  
  int mode;
    
  char * line = NULL;  
  size_t linesz = 0;
  
  clearscr();  
  welcomeScreen();  
  clearscr();
    
  parameters_t * param = initParam(argc, argv);
  width = param->width;  
  height = param->height;  
  numMines = param->numMines;  
  mode = param->mode;  
  free(param);
  
  do {    
    board_t * b = makeBoard (width, height, numMines);    
    int gameOver = 0;    
    int moves = 0;    
    while (gameOver<=0) {      
      gameOver = playTurn(b, &line, &linesz, &moves, mode, gameOver);      
    }
    freeBoard(b);
    do {      
      printf("Do you want to play again? (enter 'Y'/'y' for yes, any other character to quit)\n");      
    } while(getline(&line, &linesz, stdin) == -1);    
  } while(line[0] == 'Y' || line[0] == 'y');  
  free(line);  
  return EXIT_SUCCESS;  
}
