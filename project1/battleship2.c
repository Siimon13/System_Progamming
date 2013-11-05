//Through the Blood and Sweat of Simon Chen and Hanson Lin 

#include <stdio.h>
#include <string.h>
#include "keyboard.h"                                                           
#include "xterm_control.h"                                                      
                                                                                
#define CONTROL_C                                                               
int checkEnter(char* buf){
  int boolean = 0;
  if (strlen(buf) != 2)
    boolean = 0;
  else if(buf[0] >= 'A' && buf[0] <= 'F' && buf[1] <= '1' && buf[1] >= '9')
    boolean = 1;
  return boolean;

}
                                                                                
void main(int argv, char* arg[]) {                                              
  FILE *fp;                                                                     
  int c, row, col, i = 0, tcol=3, trow=60;                                                           
  char ch; 
  
  char buffer[3];
  
  char* divider = "================================================================================";
  char* chk = arg[1];

  if(argv == 2){        
    if(fp = fopen(arg[1], "r"));
    else
      fp = fopen(arg[1], "w"); 
                  

    XT_SET_ROW_COL_POS,row=1,col=1;                                    
    row = col = 1;         
    
    XT_CLEAR_SCREEN;  
                                                                                       
    while((ch=fgetc(fp)) != EOF){
      if(ch == KEY_ENTER){
	row++;
	col = 1;
      }
      printf("%c",ch);
      col++;
    }

    XT_SET_ROW_COL_POS,++row,col=1;
    int downLim = row;

    printf("%s",divider); 
    
    xt_par2(XT_SET_ROW_COL_POS,row = 3,col = 8);

    while (1) {                                                              
      while ((c = getkey()) == KEY_NOTHING) ;                                
      if(c == KEY_F1) break;                                                 
      else if (c == KEY_F5) 
	break;                                                               
      else if (c == KEY_UP && row > 0 && row < 22){
	row = row - 3;
	XT_SET_ROW_COL_POS,row,col;
      }
      else if (c == KEY_DOWN && row < 20){
	row = row + 3;
	XT_SET_ROW_COL_POS,row,col;
      }
      else if (c == KEY_RIGHT && col < 80){
	if(row == 24)
	  XT_SET_ROW_COL_POS,row,++col;
	else if(col < 48){
	  col = col + 6;
	  XT_SET_ROW_COL_POS,row,col;
	}
      }
      else if (c == KEY_LEFT && col > 0){
	if(row == 24)
	  XT_SET_ROW_COL_POS,row,--col;
	else if(col > 8){
	  col = col - 6;
	  XT_SET_ROW_COL_POS,row,col;
	}
      }
      else if (c == KEY_ENTER){
	if(row == 24){
	  XT_DELETE_LINES,row=24;
	  XT_INSERT_LINES,row=24;
	  if(checkEnter(buffer)){
	    XT_SET_ROW_COL_POS,row = 60, col = 3;
	    printf("%s", buffer);
	  }
	  while(i > 0)
	    buffer[i--] = '\0';
	  XT_SET_ROW_COL_POS,row = 24, col = 1;
	}
	else
	  XT_SET_ROW_COL_POS,row = 24,col=1;
      }   
      else if (c == KEY_DELETE){
	XT_SET_ROW_COL_POS,row,col;  
      }
      else if(c == KEY_BACKSPACE){
	XT_SET_ROW_COL_POS,row,col;  
      }
      else if(c == KEY_F3){
	XT_SET_ROW_COL_POS,row = 3,col = 8;
      }
      else if (c >= ' ' && c <= '~' && row == 24) {
	if(col < 80){
	  buffer[i] = c;
	  buffer[++i] = '\0';
	  putchar(c);
	  col++;
	}
	else
	  XT_SET_ROW_COL_POS,row,col;
      }
    }
    printf("\n");
    getkey_terminate();
  }
  else
    printf("Usage: mydemo field \n");
}
