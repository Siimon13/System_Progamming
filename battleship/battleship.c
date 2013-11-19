//Through the Blood and Sweat of Simon Chen and Hanson Lin 

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <string.h>
#include "keyboard.h"                                                          
#include "xterm_control.h"

#define CONTROL_C                                                               
//checks if somehting is hited   
int isHit(char* buf, char* oppL){
  int boolean = 0, tmp = 0;;  
  while(tmp < strlen(oppL)){
    if(oppL[tmp] == buf[0]){
      if(oppL[tmp+1] == buf[1]){
	boolean = 1;
	break;
      }
    }
    tmp = tmp + 2;
  }
  return boolean;
}

//checks if something is used
int checkUsed(char* buf, char* usedL){
  int boolean = 1, tmp = 0;;  
  while(tmp < strlen(usedL)){
    if(usedL[tmp] == buf[0]){
      if(usedL[tmp+1] == buf[1]){
	boolean = 0;
	break;
      }
    }
    tmp = tmp + 2;
  }
  return boolean;
}


//checks if something is used
int checkOL(char* buf, char* OL){
  int boolean = 1, tmp = 0;;  
  while(tmp < strlen(OL)){
    if(OL[tmp] == buf[0]){
      if(OL[tmp+1] == buf[1]){
	boolean = 0;
	break;
      }
    }
    tmp = tmp + 2;
  }
  return boolean;
}



//checks the enter for mistakes
int checkEnter(char* buf,char* usedL,int b){
  int boolean = 0;
  if(strlen(buf) > 2)
    return boolean;
  if(b){
    if(buf[0] == 'u' ||
       buf[0] == 'd' ||
       buf[0] == 'l' ||
       buf[0] == 'r' ||
       buf[0] == 'e')
      boolean = 1;
  }
  else{
    if(buf[0] >= 'A' && buf[0] <= 'H'){
      if(buf[1] >= '1' && buf[1] <= '7')
	boolean = 1;
    }
    int tmp = 0;
    while(tmp < strlen(usedL)){
      if(usedL[tmp] == buf[0]){
	if(usedL[tmp+1] == buf[1]){
	  boolean = 0;
	  break;
	}
      }
      tmp = tmp + 2;
    }
  }
  return boolean;
}     

//RNGer
int RNG(int n){
  srand(time(NULL));
  int randi = rand() % n;
  return randi;
}                                                                       


void main(int argv, char* arg[]) {                                              
  FILE *fp;                                                                     
  //Int for stuff, i = index, startgame is for setting pieces, gameover, hit, destoryed for game over condition, ol, l = list counters, i and oi playercoord indexes
  int c, row, col, i = 0,tcol = 60, trow = 3,l = 0,startgame = 1, gameover = 0, pi = 0, oi = 0, boolean = 1, hit = 0, destoryed = 0, ol = 0;                                       
  //The reader
  char ch;
 
  //The everything buffer
  char buffer[3];

  //Tmp holder for looping tankers and w/e
  char tmp[3];

  //List of points you hit
  char list[98];

  //List of opponent's points they've hit already
  char Olist[98];

  //Initizalized list for coordinates
  char playercoord[20], oppcoord[20];
  playercoord[0] = '\0';
  oppcoord[0] = '\0';
  
  //Infinite loop catcher
  int checker = 0;

  
  /*Failed random opponent maker
    while (i < 3 && checker < 10){
    checker++;
    char buf[2];
    int tmp = 0;
    srand(time(NULL));
    int randi = rand() % 8;
    buf[0] = 'B' + randi;
    srand(time(NULL));
    randi = rand() % 7;
    buf[0] = '2' + randi;
    while(tmp < strlen(oppcoord)){
    if(oppcoord[tmp] == buf[0]){
    if(oppcoord[tmp+1] == buf[1]){
    boolean = 0;
    break;
    }
    }
    tmp = tmp + 2;
    }
    if(boolean){
    if(i == 0){
    randi = rand() % 2;
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1];
    oppcoord[oi] = '\0';
    i++;
    if (randi == 0){
    oppcoord[oi++] = buf[0]++;
    oppcoord[oi++] = buf[1];
    oppcoord[oi] = '\0';
    i++;
    }
    else{
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1]++;
    oppcoord[oi] = '\0';
    i++;
    }
    }
    else if(i == 1){
    randi = rand() % 2;
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1];
    oppcoord[oi] = '\0';
    i++;
    if (randi == 0){
    int c = 0;
    while(c < 2){
    buf[0]++;
    if(checkUsed(buf,oppcoord)){
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1];
    oppcoord[oi] = '\0';
    c++;
    }
    else{
    buf[0]-=2;
    }
    }
    }
    }
    else{
    while(1){
    int c = 0;
    randi = rand() % 4;
    if(randi == 0){
    buffer[0] = 'A';
    buffer[1] = '1';
    while(c < 4){
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1]++;
    oppcoord[oi] = '\0';
    c++;
    }
    if(c <= 4){
    i++;
    break;
    }
    }
    else if(randi == 1){
    buffer[0] = 'A';
    buffer[1] = '7';
    while(c < 4){
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1]++;
    oppcoord[oi] = '\0';
    c++;
    }
    if(c <= 4){
    i++;
    break;
    }
    }
    else if(randi == 2){
    buffer[0] = 'H';
    buffer[1] = '1';
    while(c < 4){
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1]++;
    oppcoord[oi] = '\0';
    c++;
    }
    if(c <= 4){
    i++;
    break;
    }
    }
    else{
    buffer[0] = 'H';
    buffer[1] = '7';
    while(c < 4){
    oppcoord[oi++] = buf[0];
    oppcoord[oi++] = buf[1]++;
    oppcoord[oi] = '\0';
    c++;
    }
    if(c <= 4){
    i++;
    break;
    }
    }
    }
    }
    }
    }
  */

  //Coordinates of enemy ships
  int rando = rand() % 10;
  if (rando == 0){
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '5';
    oppcoord[oi] = '\0';
  }
  else if(rando == 1){
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'B';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '6';
    oppcoord[oi] = '\0';
  }
  else if (rando == 2){
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'B';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '1';
    oppcoord[oi] = '\0';
  }
  else if(rando == 3){
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'B';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '7';
    oppcoord[oi] = '\0';
  }
  else if(rando == 4){
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '7';
    oppcoord[oi] = '\0';
  }
  else if(rando == 6){
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'G';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '5';
    oppcoord[oi] = '\0';
  }
  else if(rando == 7){
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'B';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'C';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'H';
    oppcoord[oi++] = '3';
    oppcoord[oi] = '\0';
  }
  else if(rando == 8){
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'F';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '6';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '7';
    oppcoord[oi] = '\0';
  }
  else{
    oppcoord[oi++] = 'E';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '7';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'D';
    oppcoord[oi++] = '5';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '1';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '2';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '3';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '4';
    oppcoord[oi++] = 'A';
    oppcoord[oi++] = '5';
    oppcoord[oi] = '\0';
  }
  boolean = 0;
  i = 0;
  
  char* divider = "======================================================================";
  
  char* chk = arg[1];

  if(argv == 1){        
    if(fp = fopen("field", "r"));
    else
      fp = fopen(arg[1], "w"); 
                  

    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);                                    
    row = col = 1;         
    
    xt_par0(XT_CLEAR_SCREEN);  

    xt_par2(XT_SET_ROW_COL_POS,row=24,col=1);
    printf("Press Enter to Begin");
    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);    
                                                       
    while((ch=fgetc(fp)) != EOF){
      if(ch == KEY_ENTER){
	row++;
	col = 1;
      }
      printf("%c",ch);
      col++;
    }

    xt_par2(XT_SET_ROW_COL_POS,++row,col=1);
    int downLim = row;

    printf("%s",divider); 
    
    xt_par2(XT_SET_ROW_COL_POS,row = 3,col = 8);

    while (1) {                                                              
      while ((c = getkey()) == KEY_NOTHING) ;                                
      if(c == KEY_F1) break;                                                 
      else if (c == KEY_F5) 
	break;             
      else if (gameover){
	printf("Game over! \n");
	break;
      }
      else if(checker >=10){
	break;
      }
      else if (hit >= 10){
	printf("Game over! \n");
	break;
      }
      else if(c == KEY_F4){
	//Supposed to print out coords of enemies
	xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
	printf("%c",oppcoord[0]);
	xt_par2(XT_SET_ROW_COL_POS,row = 3,col=8);
      }
      else if(c == KEY_BACKSPACE){
	if(col > 1 && row == 24){
	  buffer[--i] = '\0';
	  xt_par2(XT_SET_ROW_COL_POS,row,--col);
	  putchar(' ');
	  col++;
	  xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
	else{
	  buffer[i] = '\0';
	  putchar(' ');
	  col++;
	  xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
      }
      else if (c == KEY_UP && row > 0 && row < 22){
	row = row - 3;
	xt_par2(XT_SET_ROW_COL_POS,row,col);
      }
      else if (c == KEY_DOWN && row < 20){
	row = row + 3;
	xt_par2(XT_SET_ROW_COL_POS,row,col);
      }
      else if (c == KEY_RIGHT && col < 80){
	if(row == 24)
	  xt_par2(XT_SET_ROW_COL_POS,row,++col);
	else if(row < 48){
	  col = col + 6;
	  xt_par2(XT_SET_ROW_COL_POS,row,col);
	}
      }
      else if (c == KEY_LEFT && col > 0){
	if(row == 24)
	  xt_par2(XT_SET_ROW_COL_POS,row,--col);
	else if(col > 8){
	  col = col - 6;
	  xt_par2(XT_SET_ROW_COL_POS,row,col);
	}
      }
      else if (c == KEY_ENTER){
	if(row == 24){
	  xt_par1(XT_DELETE_LINES,row=24);
	  xt_par1(XT_INSERT_LINES,row=24);
	  if(checkEnter(buffer,list,boolean)){
	    if(!boolean){
	      list[l++] = buffer[0];
	      list[l++] = buffer[1];
	      list[l] = '\0';
	    }
	    //Starts game, sets coordinates
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
	    if(!boolean && startgame){
	      if(strlen(playercoord)+2 <= 4)
		printf("Please enter coords for a destoryers(2x1)");
	      else if(strlen(playercoord)+2 >= 4 && strlen(playercoord)+2 < 10)		  
		printf("Please enter coords for a carriers(3x1)");
	      else if(strlen(playercoord)+2 >= 10 && strlen(playercoord)+2 < 20)
		printf("Please enter coords for a tankers(5x1)");
	      else
		printf("Please Enter a Coord.          ");
	    }
	    else{
	      printf("Please pick direction,u,r.d,l");
	    }
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	    if(startgame){
	      if(strlen(playercoord) + 2 >= 20){
		startgame = 0;
		while(l >= 0){
		  buffer[l--] = '\0';
		}
		l = 0;
	      }
	      else if(strlen(playercoord) < 4){
		if(!boolean){
		  //sets up coordinates
		  playercoord[pi++] = buffer[0];
		  playercoord[pi++] = buffer[1];
		  tmp[0] = buffer[0];
		  tmp[1] = buffer[1];
		  playercoord[pi] = '\0';
		  col = 6*(buffer[0] - 'A') + 8;
		  row = 3*(buffer[1] - '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('D');
		  xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
		  boolean = 1;
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		  printf("Please pick direction,u,r,d,l                ");
		}
		else{
		  if(buffer[0] == 'u'){
		    //puts something up to the start if nothing is there,everything repeats for tanker and carrier(u(p),d(own),l(eft),r(ight)
		    tmp[1]--;
		    if(tmp[1] >= '1' && checkUsed(tmp,list)){
		      playercoord[pi++] = tmp[0];
		      playercoord[pi++] = tmp[1];
		      list[l++] = tmp[0];
		      list[l++] = tmp[1];
		      list[l] = '\0';
		      playercoord[pi] = '\0';
		      col = 6*(tmp[0] - 'A') + 8;
		      row = 3*(tmp[1] - '1') + 3;
		      xt_par2(XT_SET_ROW_COL_POS,row,col);
		      putchar('D');
		      tmp[0] = '\0';
		      tmp[1] = '\0';
		      boolean = 0;
		      printf("Please enter coords for a carriers(3x1) ");
		    }
		    else{
		      //Error catcher
		      tmp[1]++;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }
		  else if(buffer[0] == 'r'){
		    tmp[0]++;
		    if(tmp[1] <= 'H' && checkUsed(tmp,list)){
		      playercoord[pi++] = tmp[0];
		      playercoord[pi++] = tmp[1];
		      list[l++] = tmp[0];
		      list[l++] = tmp[1];
		      list[l] = '\0';
		      playercoord[pi] = '\0';
		      col = 6*(tmp[0] - 'A') + 8;
		      row = 3*(tmp[1] - '1') + 3;
		      xt_par2(XT_SET_ROW_COL_POS,row,col);
		      putchar('D');
		      tmp[0] = '\0';
		      tmp[1] = '\0';
		      boolean = 0;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Please enter coords for a carriers(3x1) ");
		    }
		    else{
		      tmp[0]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    } 
		   
		  }  
		  else if(buffer[0] == 'd'){
		    tmp[1]++;
		    if(tmp[1] <= '7' && checkUsed(tmp,list)){
		      playercoord[pi++] = tmp[0];
		      playercoord[pi++] = tmp[1];
		      list[l++] = tmp[0];
		      list[l++] = tmp[1];
		      list[l] = '\0';
		      playercoord[pi] = '\0';
		      col = 6*(tmp[0] - 'A') + 8;
		      row = 3*(tmp[1] - '1') + 3;
		      xt_par2(XT_SET_ROW_COL_POS,row,col);
		      putchar('D');
		      tmp[0] = '\0';
		      tmp[1] = '\0';
		      boolean = 0;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Please enter coords for a carriers(3x1) ");
		    }
		    else{
		      tmp[1]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'l'){
		    tmp[0]--;
		    if(tmp[0] >= 'A' && checkUsed(tmp,list)){
		      playercoord[pi++] = tmp[0];
		      playercoord[pi++] = tmp[1];
		      list[l++] = tmp[0];
		      list[l++] = tmp[1];
		      list[l] = '\0';
		      playercoord[pi] = '\0';
		      col = 6*(tmp[0] - 'A') + 8;
		      row = 3*(tmp[1] - '1') + 3;
		      xt_par2(XT_SET_ROW_COL_POS,row,col);
		      putchar('D');
		      tmp[0] = '\0';
		      tmp[1] = '\0';
		      boolean = 0;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Please enter coords for a carriers(3x1)");
		    }
		    else{
		      tmp[0]++;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'e'){
		    //terminates the process and restarts the coordinates
		    playercoord[--pi] = '\0';
		    playercoord[--pi] = '\0';
		    list[l--] = '\0';
		    list[l--] = '\0';
		    col = 6*(tmp[0] - 'A') + 8;
		    row = 3*(tmp[1] - '1') + 3;
		    xt_par2(XT_SET_ROW_COL_POS,row,col);
		    putchar(' ');
		    xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
		    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		    printf("Please enter another coord to start.");
		    boolean = 0;
		  }  
		}
	      }
	      else if(strlen(playercoord) >= 4 && strlen(playercoord) < 10){
		if(!boolean){
		  playercoord[pi++] = buffer[0];
		  playercoord[pi++] = buffer[1];
		  tmp[0] = buffer[0];
		  tmp[1] = buffer[1];
		  playercoord[pi] = '\0';
		  col = 6*(buffer[0] - 'A') + 8;
		  row = 3*(buffer[1] - '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('C');
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		  boolean = 1;
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		  printf("Please pick direction,u,r,d,l                ");
		}
		else{
		  if(buffer[0] == 'u'){
		    tmp[1]--;
		    int counter = 0;
		    if(tmp[1] >= '1' && checkUsed(tmp,list)){
		      while (counter < 2){
			if(tmp[1] >= '1' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  list[l]= '\0';
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('C');
			  boolean = 0;
			  tmp[1]--;
			  counter++;
			}
			else{
			  tmp[1]++;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter coords for a tankers(5x1)");
		      }
		      if(counter != 2 && counter > 0){
			playercoord[--pi] = '\0';
			playercoord[--pi] = '\0';
			list[--l] = '\0';
			list[--l] = '\0';
			col = 6*(tmp[0] - 'A') + 8;
			row = 3*(tmp[1] - '1') + 3;
			xt_par2(XT_SET_ROW_COL_POS,row,col);
			putchar(' ');
			xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter another direction.");
			counter--;
			tmp[1]++;
			boolean = 1;
		      }
		    }
		    else{
		      tmp[1]++;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  } 
		  else if(buffer[0] == 'r'){
		    int counter = 0;
		    tmp[0]++;
		    if(tmp[0] <= 'H' && checkUsed(tmp,list)){
		      while (counter < 2){
			if(tmp[0] <= 'H' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  list[l]= '\0';
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('C');
			  boolean = 0;
			  tmp[0]++;
			  counter++;
			}
			else{
			  tmp[0]--;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter coords for a tankers(5x1)");
		      }
		      if(counter != 2 && counter > 0){
			playercoord[--pi] = '\0';
			playercoord[--pi] = '\0';
			list[--l] = '\0';
			list[--l] = '\0';
			col = 6*(tmp[0] - 'A') + 8;
			row = 3*(tmp[1] - '1') + 3;
			xt_par2(XT_SET_ROW_COL_POS,row,col);
			putchar(' ');
			xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter another direction.");
			counter--;
			tmp[0]--;
			boolean = 1;
		      }
		    }
		    else{
		      tmp[0]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  } 
		  else if(buffer[0] == 'd'){
		    int counter = 0;
		    tmp[1]++;
		    if(tmp[1] <= '7' && checkUsed(tmp,list)){
		      while (counter < 2){
			if(tmp[1] <= '7' && checkUsed(tmp,list)){
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  list[l]= '\0';
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('C');
			  boolean = 0;
			  tmp[1]++;
			  counter++;
			  
			}
			else{
			  tmp[1]--;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter coords for a tankers(5x1)");
		      }
		      if(counter != 2 && counter > 0){
			playercoord[--pi] = '\0';
			playercoord[--pi] = '\0';
			list[--l] = '\0';
			list[--l] = '\0';
			col = 6*(tmp[0] - 'A') + 8;
			row = 3*(tmp[1] - '1') + 3;
			xt_par2(XT_SET_ROW_COL_POS,row,col);
			putchar(' ');
			xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter another direction.");
			counter--;
			tmp[1]--;
			boolean = 1;
		      }
		    }
		    else{
		      tmp[1]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'l'){
		    int counter = 0;
		    tmp[0]--;
		    if(tmp[0] >= 'A' && checkUsed(tmp,list)){
		      while (counter < 2){
			if(tmp[0] >= 'A' && checkUsed(tmp,list)){
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  list[l]= '\0';
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('C');
			  boolean = 0;
			  tmp[0]--;
			  counter++;
			}
			else{
			  tmp[0]++;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter coords for a tankers(5x1)");
		      }
		      if(counter != 2 && counter > 0){
			playercoord[--pi] = '\0';
			playercoord[--pi] = '\0';
			list[--l] = '\0';
			list[--l] = '\0';
			col = 6*(tmp[0] - 'A') + 8;
			row = 3*(tmp[1] - '1') + 3;
			xt_par2(XT_SET_ROW_COL_POS,row,col);
			putchar(' ');
			xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Please enter another direction.");
			counter--;
			tmp[0]++;
			boolean = 1;
		      }
		    }
		    else{
		      tmp[1]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'e'){
		    playercoord[--pi] = '\0';
		    playercoord[--pi] = '\0';
		    list[--l] = '\0';
		    list[--l] = '\0';
		    col = 6*(tmp[0] - 'A') + 8;
		    row = 3*(tmp[1] - '1') + 3;
		    xt_par2(XT_SET_ROW_COL_POS,row,col);
		    putchar(' ');
		    xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
		    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		    printf("Please enter another coord to start.");
		    boolean = 0;
		  }  
		}
	      }
	      else if(strlen(playercoord) >= 10 && strlen(playercoord) < 20){
		if(!boolean){
		  playercoord[pi++] = buffer[0];
		  playercoord[pi++] = buffer[1];
		  tmp[0] = buffer[0];
		  tmp[1] = buffer[1];
		  playercoord[pi] = '\0';
		  col = 6*(buffer[0] - 'A') + 8;
		  row = 3*(buffer[1] - '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('T');
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		  boolean = 1;
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		  printf("Please pick direction,u,r,d,l                ");
		}
		else{
		  if(buffer[0] == 'u'){
		    tmp[1]--;
		    int counter = 0;
		    if(tmp[1] >= '1' && checkUsed(tmp,list)){
		      while (counter < 4){
			if(tmp[1] >= '1' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('T');
			  boolean = 0;
			  tmp[1]--;
			  counter++;
			}
			else{
			  tmp[1]++;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Enter a coord.                      ");
		      }
		      if(counter != 4){
			while(counter > 0){
			  playercoord[--pi] = '\0';
			  playercoord[--pi] = '\0';
			  list[--l] = '\0';
			  list[--l] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar(' ');
			  xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			  printf("Please enter another direction.");
			  counter--;
			  tmp[1]++;
			  boolean = 1;
			}
		      }
		    }
		    else{
		      tmp[1]++;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  } 
		  else if(buffer[0] == 'r'){
		    int counter = 0;
		    tmp[0]++;
		    if(tmp[0] <= 'H' && checkUsed(tmp,list)){
		      while (counter < 4){
			if(tmp[0] <= 'H' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('T');
			  boolean = 0;
			  tmp[0]++;
			  counter++;
			}
			else{
			  tmp[0]--;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Enter a coord.                      ");
		      }
		      if(counter != 4){
			while(counter > 0){
			  playercoord[--pi] = '\0';
			  playercoord[--pi] = '\0';
			  list[--l] = '\0';
			  list[--l] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar(' ');
			  xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			  printf("Please enter another direction.");
			  counter--;
			  tmp[0]--;
			  boolean = 1;
			}
		      }
		    }
		    else{
		      tmp[0]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  } 
		  else if(buffer[0] == 'd'){
		    int counter = 0;
		    tmp[1]++;
		    if(tmp[1] <= '7' && checkUsed(tmp,list)){
		      while (counter < 4){
			if(tmp[1] <= '7' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('T');
			  boolean = 0;
			  tmp[1]++;
			  counter++;
			}
			else{
			  tmp[1]--;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Enter a coord.                      ");
		      }
		      if(counter != 4){
			while(counter > 0){
			  playercoord[--pi] = '\0';
			  playercoord[--pi] = '\0';
			  list[--l] = '\0';
			  list[--l] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar(' ');
			  xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			  printf("Please enter another direction.");
			  counter--;
			  tmp[1]--;
			  boolean = 1;
			}
		      }
		    }
		    else{
		      tmp[1]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'l'){
		    int counter = 0;
		    tmp[0]--;
		    if(tmp[0] >= 'A' && checkUsed(tmp,list)){
		      while (counter < 4){
			if(tmp[0] >= 'A' && checkUsed(tmp,list)){
			  playercoord[pi++] = tmp[0];
			  playercoord[pi++] = tmp[1];
			  list[l++] = tmp[0];
			  list[l++] = tmp[1];
			  playercoord[pi] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar('T');
			  boolean = 0;
			  tmp[0]--;
			  counter++;
			}
			else{
			  tmp[0]++;
			  list[l--] = '\0';
			  list[l--] = '\0';
			  break;
			}
			xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			printf("Enter a coord.                      ");
		      }
		      if(counter != 4){
			while(counter > 0){
			  playercoord[--pi] = '\0';
			  playercoord[--pi] = '\0';
			  list[l--] = '\0';
			  list[l--] = '\0';
			  col = 6*(tmp[0] - 'A') + 8;
			  row = 3*(tmp[1] - '1') + 3;
			  xt_par2(XT_SET_ROW_COL_POS,row,col);
			  putchar(' ');
			  xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
			  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
			  printf("Please enter another direction.");
			  counter--;
			  tmp[0]++;
			  boolean = 1;
			}
		      }
		    }
		    else{
		      tmp[1]--;
		      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		      printf("Pick another direction, or use e to cancel");
		    }
		  }  
		  else if(buffer[0] == 'e'){
		    playercoord[--pi] = '\0';
		    playercoord[--pi] = '\0';
		    list[l--] = '\0';
		    list[l--] = '\0';
		    col = 6*(tmp[0] - 'A') + 8;
		    row = 3*(tmp[1] - '1') + 3;
		    xt_par2(XT_SET_ROW_COL_POS,row,col);
		    putchar(' ');
		    xt_par2(XT_SET_ROW_COL_POS,row = 23,col=1);
		    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		    printf("Please enter another coord to start.");
		    boolean = 0;
		  }  
		}
	      }
	      else{
		//turns game to false if playercoord is at 20 length
		startgame = 0;
		while(l >= 0){
		  buffer[l--] = '\0';
		}
		l = 0;
	      }
	    }
	    else{
	      //Game process
	      boolean = 0;
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=25);
	      printf("Enter the coords to hit                ");
	      xt_par2(XT_SET_ROW_COL_POS,trow++,tcol);
	      if(isHit(buffer,oppcoord)){
		printf("%s-H", buffer);
		hit++;
	      }
	      else
		printf("%s", buffer);
	      list[l++] = buffer[0];
	      list[l++] = buffer[1];
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	      list[l] = '\0';
	      //Enemy code
	      srand (time(NULL));
	      buffer[0] = 'A' + RNG(8);
	      buffer[1] = '1' + RNG(7);
	      while(!checkUsed(buffer,Olist)){
		buffer[0] = 'A' + RNG(8);
		buffer[1] = '1' + RNG(7);
	      }
	      Olist[ol++] = buffer[0];
	      Olist[ol++] = buffer[1];
	      Olist[ol] = '\0';
	      col = 6*(buffer[0] - 'A') + 8;
	      row = 3*(buffer[1] - '1') + 3;
	      xt_par2(XT_SET_ROW_COL_POS,row,col);
	      xt_par2(XT_CH_BLUE,row,col);
	      putchar('X');
	      xt_par2(XT_CH_WHITE,row,col);
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=60);
	      if(isHit(buffer,playercoord)){
		printf("You were hit at %s", buffer);
		destoryed++;
	      }
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	    }
	  }
	  else{
	    //If user enters wrong data
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
	    if(boolean)
	      printf("Please enter a direction(u,r,d,l)");
	    else
	      printf("Please enter a correct and unused coord");
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  }
	  if (trow > 22){
	    //restarts tries
	    trow = 3;
	    tcol = tcol + 5;
	  }
	  while(i >= 0){
	    //cleans buffer
	    buffer[i] = '\0';
	    i--;
	  }
	  i = 0;
	  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  if(destoryed >= 10){
	    gameover = 1;
	  }
	}
	else{
	  //If you pressed enter into F3
	  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  xt_par1(XT_DELETE_LINES,row=24);
	  xt_par1(XT_INSERT_LINES,row=24);
	  if(strlen(playercoord) < 4 && !boolean){
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=25);
	    printf("Please enter coords for a destoryers(2x1)");
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  }
	}
      }   
      else if (c == KEY_DELETE){
	xt_par2(XT_SET_ROW_COL_POS,row,col);  
      }
      else if(c == KEY_BACKSPACE){
	xt_par2(XT_SET_ROW_COL_POS,row,col);  
      }
      else if(c == KEY_F3){
	xt_par2(XT_SET_ROW_COL_POS,row = 3,col = 8);
      }
      else if (c >= ' ' && c <= '~' && row == 24) {
	if (col < 80){
	  buffer[i] = c;
	  buffer[++i] = '\0';
	  putchar(c);
	  col++;
	}
	else
	  xt_par2(XT_SET_ROW_COL_POS,row,col);
      }
    }
    printf("\n");
    getkey_terminate();
    if(checker >= 10)
      printf("Please Start again \n");
    else if(hit >= 10)
      printf("You win!");
    else if(gameover)
      printf("You lose! \n");
  }
  else
    printf("Usage: battleship \n");      
      
}
