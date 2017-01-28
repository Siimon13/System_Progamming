#include <stdio.h> //Allows for use of malloc
#include <stdlib.h>

char GENLINE[] = "================================";

void printWorld(char** world, int row, int col){
  
  for (int r = 0; r < row; ++r){
    printf("%s\n", world[r]);
  }
  
}

void freeWorld(char** world, int rows){

  for (int i=0; i<rows; i++)
    {
      free(world[i]);
    }
  free(world);

}

void initWorld(char** world){
  FILE *fp;
  char line[11];
  int size = sizeof(line) / sizeof(line[0]);

  fp = fopen("life.txt", "r");

  int r = 0;
  while (fgets(line, size, (FILE*)fp) != NULL){
    /* printf("%s", line); */

    if (line[0] != '*' && line[0] != ' ')
      break;

    for (int c = 0; c < size; ++c){
      if (line[c] == '*')
	world[r][c] = line[c];
      else
	world[r][c] = '-';
    }
    ++r;
  }

  while( r < size){
    for (int c = 0; c < size; ++c){
	world[r][c] = '-';
    }
    ++r;
  }

}

int checkAround(char** world, int r, int c, int row, int col){
  char currCell = world[r][c];
  
  int topLeftRowIndex = (r-1) % row;
  int neighs = 0;
  //check top left
  /* printf("%d, %d", (r-1+row) % row, (c-1+col) % col); */
  if (world[(r-1+row)%row][(c-1+col)%col] == '*')
    ++neighs;

  //check top 
  /* printf("%c", world[(r-1+row)%row][(c)%col]); */
  if (world[(r-1+row)%row][c] == '*')
    ++neighs;

  //check top right
  /* printf("%c", world[(r-1+row)%row][(c+1)%col]); */
  if (world[(r-1+row)%row][(c+1)%col] == '*')
    ++neighs;

  /* //check cur left */
  /* printf("%c", world[(r)%row][(c-1+col)%col]); */
  if (world[r][(c-1+col)%col] == '*')
    ++neighs;

  /* //check cur right */
  /* printf("%c", world[(r)%row][(c+1)%col]); */
  if (world[r][(c+1)%col] == '*')
    ++neighs;

  /* //check bot left */
  /* printf("%c", world[(r+1)%row][(c-1+col)%col]); */
  if (world[(r+1)%row][(c-1+col)%col] == '*')
    ++neighs;

  /* //check bot  */
  /* printf("%c", world[(r+1)%row][(c)%col]); */
  if (world[(r+1)%row][c] == '*')
    ++neighs;

  /* //check bot right */
  /* printf("%c", world[(r+1)%row][(c+1)%col]); */
  if (world[(r+1)%row][(c+1)%col] == '*')
    ++neighs;

  
  return neighs;
}  

char** moveState(char** world, int row, int col){

  char** newworld = malloc(row * sizeof *world);
  for (int i = 0; i < col; ++i){
    newworld[i] = malloc(col * sizeof *world[i]);
  }

  int livingneighs = 0;
  for (int r = 0; r < row; ++r){
    for (int c = 0; c < col; ++c){
      livingneighs = checkAround(world, r, c, row, col);
      /* printf("%d", livingneighs); */
      if (livingneighs == 3 || (world[r][c] == '*' && livingneighs == 2))
	newworld[r][c] = '*';
      else
	newworld[r][c] = '-';
    }

  }

  freeWorld(world, row);

  return newworld;
}

int main(int argc, char **argv){

  printf("Arguments: %d \n", argc);
  
  int row = 11;
  int col = 11;
  int limits = 10;

  /* char world[rowlen][collen]; */
  char** world = malloc(row * sizeof *world);
 
  for (int i = 0; i < col; ++i){
    world[i] = malloc(col * sizeof *world[i]);
  }

  int generation = 0;

  initWorld(world);

  while(generation != limits){
    printf("Generation %d:\n", generation++);
    printWorld(world, row, col);
    world = moveState(world, row, col);
    printf("%s\n",GENLINE);
  }

  freeWorld(world, row);
}
