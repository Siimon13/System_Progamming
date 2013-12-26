#include "myui2.h"

struct NameValue *nvs = NULL;
int n_nvs = 0;
int isMenu, isAdd, isExp, isEdit;

char input[1000];
int n_input=0;	// number of chars in the input, not including terminating NULL-byte

int nitems = 0;
char subject[31];
char body[141];
char errmsg[80] = "";

//======================================================================MENU
struct TemplateString MS[] = {
 {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {4,1,XT_CH_YELLOW,"Status:"},
  {5,1,XT_CH_WHITE,"Number of records:"},
  {6,1,XT_CH_WHITE,"Author:"},
  {7,1,XT_CH_WHITE,"Version:"},
  {8,1,XT_CH_WHITE,"First record time:"},
  {9,1,XT_CH_WHITE,"Last  record time:"},
  {11,1,XT_CH_YELLOW,"Current Location:"},
  {12,1,XT_CH_WHITE,"Number of records at "},
  {14,1,XT_CH_WHITE,"Press F5 to add something to this location"},
  {16,1,XT_CH_WHITE,"Press F6 to view everything at this location"},
  {18,1,XT_CH_WHITE,"Enter \"open filename\" to have a record be opened"},
  {21,1,XT_CH_RED,"Press F9 to quit the program"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,62,XT_CH_WHITE,"Enter Command"}
};
int nMS = sizeof(MS)/sizeof(MS[0]);

struct StringPosition MSP[] = {
  {2,10,70,"message"},
  {4,9,40,"status"},
  {5,21,30,"nitems"},
  {6,9,30,"author"},
  {7,10,10,"version"},
  {8,20,20,"firstrecord"},
  {9,20,20,"lastrecord"},
  {11,20,20,"location"},
  {23,1,40,"command"}
};
int nMSP = sizeof(MSP)/sizeof(MSP[0]);

void SearchMenu(char *prompt, char *name, char *color) {
	int loc, col, i, j;
	int instring = TRUE;
	char *value;
	
	// search for location
	loc = FindMenuStringPosition(prompt);
	col = MSP[loc].col;
	
	// search for value
	value = "";
	for (j = 0; j < n_nvs; ++j) {
		if (strcmp(nvs[j].name,name) == 0) {
			value = nvs[j].value;
			break;
		}
	}
	
	DisplayAt(MSP[loc].row,MSP[loc].col,XT_CH_WHITE,MSP[loc].length,value);
}

void DisplayMenu(void) {
	ReadMystoreFromChild("stat",NULL,NULL,NULL);
	ParseInput(input,n_input);
	SearchMenu("status","status",XT_CH_WHITE);
	SearchMenu("nitems","nitems",XT_CH_WHITE);
	SearchMenu("author","author",XT_CH_WHITE);
	SearchMenu("version","version",XT_CH_WHITE);
	SearchMenu("firstrecord","first-time",XT_CH_WHITE);
	SearchMenu("lastrecord","last-time",XT_CH_WHITE);
	SearchMenu("location","Home",XT_CH_WHITE);
}


int FindMenuStringPosition(char *prompt) {
	int i;
	
	for (i = 0; i < nMSP; ++i) {
		if (strcmp(prompt,MSP[i].name) == 0)
			return i;
	}
	return 0;
}

//====================================End Menu==============================

//====================================ADD===================================
struct TemplateString AS[] = {
    {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {7,1,XT_CH_WHITE,"Subject:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,54,XT_CH_WHITE,"Enter Subject(Max 30 chars)"}
};
int nAS = sizeof(AS)/sizeof(AS[0]);

struct StringPosition ASP[] = {
  {2,10,70,"message"},
  {7,10,31,"subject"},
  {23,1,31,"addsubject"}
};
int nASP = sizeof(ASP)/sizeof(ASP[0]);

void SearchAdd(char *prompt, char *name, char *color) {
	int loc, col, i, j;
	int instring = TRUE;
	char *value;
	
	// search for location
	loc = FindAddStringPosition(prompt);
	col = ASP[loc].col;
	
	// search for value
	value = "";
	for (j = 0; j < n_nvs; ++j) {
		if (strcmp(nvs[j].name,name) == 0) {
			value = nvs[j].value;
			break;
		}
	}
	
	DisplayAt(ASP[loc].row,ASP[loc].col,XT_CH_WHITE,ASP[loc].length,value);
}

void DisplayAdd(void) {
	ReadMystoreFromChild("stat",NULL,NULL,NULL);
	ParseInput(input,n_input);
	SearchAdd("subject","subject",XT_CH_WHITE);
	SearchAdd("addsubject","addsubject",XT_CH_WHITE);
}


int FindAddStringPosition(char *prompt) {
	int i;
	
	for (i = 0; i < nASP; ++i) {
		if (strcmp(prompt,ASP[i].name) == 0)
			return i;
	}
	return 0;
}

//---------------------------------------------------Add Confirm------------
struct TemplateString ASC[] = {
  {11,1,XT_CH_WHITE, "Status:"},
  {12,1,XT_CH_WHITE, "Author:"},
  {13,1,XT_CH_WHITE, "First record time:"},
  {16,1,XT_CH_WHITE, "Body:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,52,XT_CH_WHITE,"Enter Body(Max 140 chars)"}
};
int nASC = sizeof(ASC)/sizeof(ASC[0]);

struct StringPosition ASCP[] = {
  {7,10,31,"subject"},
  {11,9,40,"status"},
  {12,9,30,"author"},
  {13,20,20,"firstrecord"},
  {16,6,141,"body"},
  {23,1,31,"addbody"}
};
int nASCP = sizeof(ASCP)/sizeof(ASCP[0]);

void SearchAddC(char *prompt, char *name, char *color) {
	int loc, col, i, j;
	int instring = TRUE;
	char *value;
	
	// search for location
	loc = FindAddCStringPosition(prompt);
	col = ASCP[loc].col;
	
	// search for value
	value = "";
	for (j = 0; j < n_nvs; ++j) {
		if (strcmp(nvs[j].name,name) == 0) {
			value = nvs[j].value;
			break;
		}
	}
	
	DisplayAt(ASCP[loc].row,ASCP[loc].col,XT_CH_WHITE,ASCP[loc].length,value);
}

void DisplayAddC(void) {
	ReadMystoreFromChild("stat",NULL,NULL,NULL);
	ParseInput(input,n_input);
	SearchAddC("subject","subject",XT_CH_WHITE);
	SearchAddC("status","status",XT_CH_WHITE);
	SearchAddC("author","author",XT_CH_WHITE);
	SearchAddC("firstrecord","first-time",XT_CH_WHITE);

}


int FindAddCStringPosition(char *prompt) {
	int i;
	
	for (i = 0; i < nASCP; ++i) {
		if (strcmp(prompt,ASCP[i].name) == 0)
			return i;
	}
	return 0;
}

//===================================================End ADD================

// ------------------------------------- DisplayAt -------------------------
void DisplayAt(int row, int col, char *color, int maxlength, char *value) {
	int i, instring = TRUE;
	
	xt_par2(XT_SET_ROW_COL_POS,row,col);
	xt_par0(color);
	for (i = 0; i < maxlength; ++i) {
		if (value[i] == '\0') 
			instring = FALSE;
		printf("%c",instring?value[i]:' ');
		if (++col == 80) {
			xt_par2(XT_SET_ROW_COL_POS,row+1,1);
			col = 1;
		}
	}
	fflush(stdout);
}


// ------------------------------------ fill --------------------------------
void fill(char *s, int n) {
	while (n--) *s++=' ';
	*s='\0';
}
//-------------------------------------Helper--------------------------------
void turnOff(){
  isMenu = 0;
  isAdd = 0;
  isEdit = 0;
  isExp = 0;
}


void clear(int r,int c){
  if(c <= 0)c = 1;
  xt_par2(XT_SET_ROW_COL_POS,r,c);
  while(c++ <= 80){
    putchar(' ');
  }
}

void message(char* msg){
  clear(2,10);
  xt_par2(XT_SET_ROW_COL_POS,2,10);
  strcpy(errmsg,msg);
  printf("%s",errmsg);
  xt_par2(XT_SET_ROW_COL_POS,23,1);
}
// ------------------------------------------------ main --------------------

int main(void) {
  int i, c,subsize,bdysize;
  fill(subject,30);
  fill(body,140);
	
  xt_par0(XT_CLEAR_SCREEN);
	
	
  // display Menu
  for (i = 0; i < nMS; ++i) {
    xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
    xt_par0(XT_CH_DEFAULT);
    xt_par0(MS[i].color);
    printf("%s",MS[i].string);
  }
  DisplayMenu();
  xt_par2(XT_SET_ROW_COL_POS,23,1);
  message("Welcome!");
  while (TRUE) {
    while ((c = getkey()) == KEY_NOTHING) ;
    if (c == KEY_F9)  {
      xt_par0(XT_CLEAR_SCREEN);
      xt_par0(XT_CH_NORMAL);
      xt_par2(XT_SET_ROW_COL_POS,1,1);
      getkey_terminate();
      exit(0);
    }
    else if (c == KEY_F5 && !isAdd){
      turnOff();
      isAdd = 1;
      clear(23,-1);
      //display AddScreen
      xt_par0(XT_CLEAR_SCREEN);
      for (i = 0; i < nAS; ++i) {
	xt_par2(XT_SET_ROW_COL_POS,AS[i].row,AS[i].col);
	xt_par0(XT_CH_DEFAULT);
	xt_par0(AS[i].color);
	printf("%s",AS[i].string);
      }
      message("Input Subject");
      DisplayAdd();
      xt_par2(XT_SET_ROW_COL_POS,23,1);
    }
    else if(c == KEY_BACKSPACE){
      if(isAdd){
      putchar('\b');
      putchar(' ');
      putchar('\b');
      subject[subsize--] = ' ';
      }
    }
    else if(c == KEY_F2){
      printf("%s",subject);
    }
    else if( c == KEY_ENTER){
      if(isAdd && CheckMystore(subject)){
	//Displays Confirm Screen
	clear(23,-1);
	for (i = 0; i < nASC; ++i) {
	  xt_par2(XT_SET_ROW_COL_POS,ASC[i].row,ASC[i].col);
	  xt_par0(XT_CH_DEFAULT);
	  xt_par0(ASC[i].color);
	  printf("%s",ASC[i].string);
	}
	message("Input Body");
	DisplayAddC();
	xt_par2(XT_SET_ROW_COL_POS,17,1);
      } 
    }
    else if(c >= ' ' && c <= '~'){
      if(isAdd && subsize <= 30){
	subject[subsize++]= c;
	putchar(c);
      }
    }
  }
	
}

