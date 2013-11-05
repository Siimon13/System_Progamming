//Through the Blood and Sweat of Simon Chen and Hanson Lin 

#include <stdio.h>
#include <string.h>
#include "keyboard.h"                                                           
#include "xterm_control.h"                                                                                                                                
#define CONTROL_C                                                               
   
int checkEnter(char* buf,char* usedL){
  int boolean = 0;
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
  return boolean;
}                                                                               
int checkCorrectCords(char* cord, char* input){
  int boolean = 0;
  if((cord[0] + 1) == input[0] || (cord[0] - 1) == input[0] || cord[0] == input[0]){
    if((cord[1] + 1) == input[1] || (cord[0] - 1) == input[1])
      boolean = 1;
  }
  return boolean; 
}

void main(int argv, char* arg[]) {                                              
  FILE *fp;                                                                     
  int c, row, col, i = 0,tcol = 60, trow = 3,l = 0,startgame = 1, gameover = 0, pi = 0, oi = 0;                                                           
  char ch;
 
  char buffer[3];

  char tmp[3];
  tmp[2] = '\0';
  char catcher[3];
  catcher[2] = '\0';

  char list[98];

  char playercoord[20], oppcoord[20];
  playercoord[0] = '\0';
  oppcoord[0] = '\0';
  
  char* divider = "=======================================================================";
  
  char* chk = arg[1];

  if(argv == 2){        
    if(fp = fopen(arg[1], "r"));
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
	  if(checkEnter(buffer,list)){
	    list[l++] = buffer[0];
	    list[l++] = buffer[1];
	    list[l] = '\0';
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
	    if(strlen(playercoord)+2 <= 4)
	      printf("Please enter coords for a destoryers(2x1");
	    else if(strlen(playercoord)+2 >= 4 && strlen(playercoord)+2 < 10)
	      printf("Please enter coords for a carriers(3x1)");
	    else if(strlen(playercoord)+2 >= 10 && strlen(playercoord)+2 < 20)
	      printf("Please enter coords for a tankers(5x1)");
	    else
	      printf("Please Enter a Coord.");
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=75);
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	    if(startgame){
	      if(strlen(playercoord) == 0){
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
	      }
	      if(strlen(playercoord) < 4){
		if(checkCorrectCords(tmp,buffer)){
		  playercoord[pi++] = buffer[0];
		  playercoord[pi++] = buffer[1];
		  playercoord[pi] = '\0';
		  col = 6*(buffer[0] - 'A') + 8;
		  row = 3*(buffer[1] - '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('D');
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		}
		else{
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		  printf("Please enter a correct and unused coord!!!!");
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		  list[--l] = '\0';
		  list[--l] = '\0';
		}
	      }
	      else if(strlen(playercoord) == 4){
		playercoord[pi++] = buffer[0];
		playercoord[pi++] = buffer[1];
		playercoord[pi] = '\0';
		tmp[0] = buffer[0];
		tmp[1] = buffer[0];
		col = 6*(catcher[0] - 'A') + 8;
		row = 3*(catcher[1] - '1') + 3;
		xt_par2(XT_SET_ROW_COL_POS,row,col);
		putchar('C');
		xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	      }
	      else if(strlen(playercoord) >= 4 && strlen(playercoord) < 10){
		if(checkCorrectCords(tmp,buffer)){
		  playercoord[pi++] = buffer[0];
		  playercoord[pi++] = buffer[1];
		  playercoord[pi] = '\0';
		  int colinc = buffer[0] - tmp[0];
		  int rowinc = buffer[1] - tmp[1];
		  col = 6*(buffer[0] - 'A') + 8;
		  row = 3*(buffer[1] - '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('C');
		  col = 6*(buffer[0] + colinc - 'A') + 8;
		  row = 3*(buffer[1] + rowinc- '1') + 3;
		  xt_par2(XT_SET_ROW_COL_POS,row,col);
		  putchar('C');
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		}
		else{
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
		  printf("Please enter a correct and unused coord!!!!");
		  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		  l-=2;
		}
	      }
	      else if(strlen(playercoord) >= 10 && strlen(playercoord) < 20){
		playercoord[pi++] = buffer[0];
		playercoord[pi++] = buffer[1];
		playercoord[pi] = '\0';
		col = 6*(catcher[0] - 'A') + 8;
		row = 3*(catcher[1] - '1') + 3;
		xt_par2(XT_SET_ROW_COL_POS,row,col);
		putchar('T');
		xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
		xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	      }
	      else{
		startgame = 0;
		while(l >= 0){
		  buffer[l--] = '\0';
		}
		l = 0;
	      }
	    }
	    else{
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=25);
	      printf("Enter the coords to hit");
	      xt_par2(XT_SET_ROW_COL_POS,trow++,tcol);
	      printf("%s", buffer);
	      list[l++] = buffer[0];
	      list[l++] = buffer[1];
	      xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	      list[l] = '\0';
	    }
	  }
	  else{
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=30);
	    printf("Please enter a correct and unused coord");
	    xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  }
	  if (trow > 22){
	    trow = 3;
	    tcol = tcol + 3;
	  }
	  while(i >= 0){
	    buffer[i] = '\0';
	    i--;
	  }
	  i = 0;
	  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	}
	else{
	  xt_par2(XT_SET_ROW_COL_POS,row = 24,col=1);
	  xt_par1(XT_DELETE_LINES,row=24);
	  xt_par1(XT_INSERT_LINES,row=24);
	  if(strlen(playercoord) < 4){
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
	  catcher[i%2] = c;
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
  }
  else
    printf("Usage: mydemo field \n");
}
