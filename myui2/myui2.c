#include "myui2.h"
#define WHITE XT_CH_WHITE
#define RED XT_CH_RED
#define YELLOW XT_CH_YELLOW

struct NameValue *nvs = NULL;
int n_nvs = 0, n_edit = 0;
int isMenu, isAdd, isAddC, isAddE, isExp, isEdit, isSearch;
int Exp[999];
int e = 0;
int emax = 0;


char input[1000];
int n_input=0;	// number of chars in the input, not including terminating NULL-byte

int nitems = 0;
char subject[33];
char body[141];
char buffer[30];
char command[5];
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

char* SearchMenu(char *prompt, char *name, char *color) {
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
  return value;
}

void DisplayMenu(void) {
	ReadMystoreFromChild("stat",NULL,NULL,NULL);
	ParseInput(input,n_input);
	SearchMenu("status","status",XT_CH_WHITE);
	nitems = atoi(SearchMenu("nitems","nitems",XT_CH_WHITE));
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
  /*Useless Function
  ReadMystoreFromChild("display","3",NULL,NULL);
  ParseInput(input,n_input);
  */
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
  {10,1,XT_CH_WHITE, "Record Number:"},
  {11,1,XT_CH_WHITE, "Status:"},
  {12,1,XT_CH_WHITE, "Author:"},
  {13,1,XT_CH_WHITE, "Time:"},
  {16,1,XT_CH_WHITE, "Body:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,52,XT_CH_WHITE,"Enter Body(Max 140 chars)"}
};
int nASC = sizeof(ASC)/sizeof(ASC[0]);

struct StringPosition ASCP[] = {
  {7,10,31,"subject"},
  {10,16,3,"recordnum"},
  {11,9,40,"status"},
  {12,9,30,"author"},
  {13,6,20,"time"},
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
  char n[3];
  sprintf(n,"%d",nitems);
  ReadMystoreFromChild("display",n,NULL,NULL);
  ParseInput(input,n_input);
  xt_par2(XT_SET_ROW_COL_POS,7,10);
  printf("%s",subject);
  SearchAddC("recordnum","item",XT_CH_WHITE);
  SearchAddC("status","status",XT_CH_WHITE);
  SearchAddC("author","author",XT_CH_WHITE);
  SearchAddC("time","time",XT_CH_WHITE);

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

//===================================================EDIT===================
struct TemplateString ES[] = {
  {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {4,1,XT_CH_WHITE,"Record Number:"},
  {5,1,XT_CH_WHITE,"Location:"},
  {6,1,XT_CH_WHITE,"Last Edit:"},
  {8,1,XT_CH_YELLOW,"Subj: 30 char max, Body: 140 char max. Press up and down to switch."},
  {9,1,XT_CH_YELLOW,"------------------------------------------------------------------------------"},
  {10,1,XT_CH_WHITE,"Subj:"},
  {11,1,XT_CH_WHITE,"Body:"},
  {13,1,XT_CH_WHITE,"Edit Subj:"},
  {16,1,XT_CH_WHITE,"Edit Body:"},
  {23,1,XT_CH_YELLOW,"Press Delete to delete, F3 to save changes, F7 to exit the record."}
};
int nES = sizeof(ES)/sizeof(ES[0]);

struct StringPosition ESP[] = {
  {2,10,70,"message"},
  {4,15,10,"recordnum"},
  {5,10,20,"location"},
  {6,12,20,"lastrecord"},
  {10,6,31,"subject"},
  {11,6,141,"body"}
};
int nESP = sizeof(ESP)/sizeof(ESP[0]);

void SearchEdit(char *prompt, char *name, char *color) {
  int loc, col, i, j;
  int instring = TRUE;
  char *value;
	
  // search for location
  loc = FindEditStringPosition(prompt);
  col = ESP[loc].col;
	
  // search for value
  value = "";
  for (j = 0; j < n_nvs; ++j) {
    if (strcmp(nvs[j].name,name) == 0) {
      value = nvs[j].value;
      break;
    }
  }
	
  DisplayAt(ESP[loc].row,ESP[loc].col,XT_CH_WHITE,ESP[loc].length,value);
}

void DisplayEdit(void) {
  char n[3];
  sprintf(n,"%d",n_edit);
  ReadMystoreFromChild("display",n,NULL,NULL);
  ParseInput(input,n_input);
  SearchEdit("recordnum","item",XT_CH_WHITE);
  SearchEdit("status","status",XT_CH_WHITE);
  SearchEdit("author","author",XT_CH_WHITE);
  SearchEdit("lastrecord","time",XT_CH_WHITE);
  SearchEdit("subject","subject",XT_CH_CYAN);
  SearchEdit("body","body",XT_CH_CYAN);
}


int FindEditStringPosition(char *prompt) {
  int i;
	
  for (i = 0; i < nESP; ++i) {
    if (strcmp(prompt,ESP[i].name) == 0)
      return i;
  }
  return 0;
}
//==================================================End Edit================


//==================================================EXPLORER================
struct TemplateString EXS[] = {
  {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {4,1,XT_CH_WHITE,"Record Number:"},
  {5,1,XT_CH_WHITE,"First Record Time:"},
  {6,1,XT_CH_WHITE,"Author:"},
  {7,1,XT_CH_WHITE,"Subject:"},
  {8,1,XT_CH_WHITE,"Body:"},
  {10,1,XT_CH_WHITE,"You can use the arrow keys to navigate the items one by one.Press Enter to edit/enter the item. Alternatively, press F3 to use the search function below."},
    {12,1,XT_CH_WHITE,"When using the search function, use the arrow keys to navigate and edit and press Enter to search. Press F3 to navigate again."},
  {17,1,XT_CH_WHITE,"------------------------------------------------------------------------------"},
  {18,1,XT_CH_WHITE,"Record Number between:x - y"},
  {19,1,XT_CH_WHITE,"Time between yyyy mm dd - yyyy mm dd"},
  {20,1,XT_CH_WHITE,"Subject Includes: "}
};
int nEXS = sizeof(EXS)/sizeof(EXS[0]);

struct StringPosition EXSP[] = {
  {4,15,10,"recordnum"},
  {6,10,20,"author"},
  {5,21,20,"lastrecord"},
  {7,9,31,"subject"},
  {8,6,141,"body"}
};
int nEXSP = sizeof(EXSP)/sizeof(EXSP[0]);

void SearchEXP(char *prompt, char *name, char *color) {
  int loc, col, i, j;
  int instring = TRUE;
  char *value;
	
  // search for location
  loc = FindEXPStringPosition(prompt);
  col = EXSP[loc].col;
	
  // search for value
  value = "";
  for (j = 0; j < n_nvs; ++j) {
    if (strcmp(nvs[j].name,name) == 0) {
      value = nvs[j].value;
      break;
    }
  }
	
  DisplayAt(EXSP[loc].row,EXSP[loc].col,XT_CH_WHITE,EXSP[loc].length,value);
}

void DisplayEXP(void) {
  char n[3];
  n_edit = Exp[e];
  sprintf(n,"%d",n_edit);
  ReadMystoreFromChild("display",n,NULL,NULL);
  ParseInput(input,n_input);
  SearchEXP("recordnum","item",XT_CH_WHITE);
  SearchEXP("author","author",XT_CH_WHITE);
  SearchEXP("lastrecord","time",XT_CH_WHITE);
  SearchEXP("subject","subject",XT_CH_CYAN);
  SearchEXP("body","body",XT_CH_CYAN);
}


int FindEXPStringPosition(char *prompt) {
  int i;
	
  for (i = 0; i < nEXSP; ++i) {
    if (strcmp(prompt,EXSP[i].name) == 0)
      return i;
  }
  return 0;
}
//==================================================End Explorer============

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

void fillint(int *s, int n) {
	while (n--) *s++=0;
	*s=0;
}

//-------------------------------------Helper--------------------------------
void turnOff(){
  isMenu = 0;
  isAdd = 0;
  isEdit = 0;
  isExp = 0;
  isAddC = 0;
  isAddE = 0;
}

//Fills explorer array
void fillExp(){
  fillint(Exp, 999);
  int i = 1;
  while (i <= nitems) Exp[i] = i++;
  e = 1;
  emax = nitems;
}

//clears a certain place
void clear(int r,int c){
  if(c <= 0)c = 1;
  xt_par2(XT_SET_ROW_COL_POS,r,c);
  while(c++ <= 80){
    putchar(' ');
  }
}

//prints the message in designated color
void message(char* msg,char* color){
  clear(2,10);
  xt_par0(color);
  xt_par2(XT_SET_ROW_COL_POS,2,10);
  strcpy(errmsg,msg);
  printf("%s",errmsg);
  xt_par2(XT_SET_ROW_COL_POS,23,1);
  xt_par0(WHITE);
}

//prints the command line
void pcommand(char* command,int c){
  xt_par2(XT_SET_ROW_COL_POS,23,c);
  printf("%s",command);
  xt_par2(XT_SET_ROW_COL_POS,23,1);
}

// ------------------------------------------------ main --------------------

int main(void) {
  int i, c;
  int row = 0;
  int subsize,bdysize,buffersize = 0 ,commandsize = 0;

  //Search Functions
  char date1[11];
  char date2[11];
  char subj[31];
  char lownum[3];
  char highnum[3];
  int erow;
  int ecol;
  int sze;

  fill(date1, 11);
  fill(date2, 11);
  fill(subj, 30);
  fill(lownum, 3);
  fill(highnum, 3);

  date1[4] = '-';
  date1[7] = '-';  
  date2[4] = '-';
  date2[7] = '-';

  n_edit = 1;
  fill(subject,30);
  fill(body,140);
  fill(buffer,30);
  fill(command,5);
  xt_par0(XT_CLEAR_SCREEN);
  isMenu = 1;
  // display Menu
  for (i = 0; i < nMS; ++i) {
    xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
    xt_par0(XT_CH_DEFAULT);
    xt_par0(MS[i].color);
    printf("%s",MS[i].string);
  }
  DisplayMenu();
  xt_par2(XT_SET_ROW_COL_POS,23,1);
  message("Welcome!",WHITE);
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
      subsize = 0;
      bdysize = 0;
      fill(subject,30);
      fill(body,140);
      //display AddScreen
      xt_par0(XT_CLEAR_SCREEN);
      for (i = 0; i < nAS; ++i) {
	xt_par2(XT_SET_ROW_COL_POS,AS[i].row,AS[i].col);
	xt_par0(XT_CH_DEFAULT);
	xt_par0(AS[i].color);
	printf("%s",AS[i].string);
      }
      message("Input Subject",WHITE);
      DisplayAdd();
      xt_par2(XT_SET_ROW_COL_POS,23,1);
    }
    else if (c == KEY_F7 && !isMenu){
      turnOff();
      isMenu = 1;
      clear(23,-1);
      subsize = 0;
      bdysize = 0;
      fill(subject,30);
      fill(body,140);
      //display MenuScreen
      xt_par0(XT_CLEAR_SCREEN);
      for (i = 0; i < nMS; ++i) {
	xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
	xt_par0(XT_CH_DEFAULT);
	xt_par0(MS[i].color);
	printf("%s",MS[i].string);
      }
      message("Enter Command",WHITE);
      DisplayMenu();
      xt_par2(XT_SET_ROW_COL_POS,23,1);
    }
    else if(c == KEY_DELETE){//Deletes the file in edit
      if(isEdit){
	DeleteMystore(n_edit);
	nitems--;
	turnOff();
	isMenu = 1;
	clear(23,-1);
	subsize = 0;
	bdysize = 0;
	fill(subject,30);
	fill(body,140);
	//display MenuScreen
	xt_par0(XT_CLEAR_SCREEN);
	for (i = 0; i < nMS; ++i) {
	  xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
	  xt_par0(XT_CH_DEFAULT);
	  xt_par0(MS[i].color);
	  printf("%s",MS[i].string);
	}
	message("Record Deleted. Enter Command",WHITE);
	DisplayMenu();
	xt_par2(XT_SET_ROW_COL_POS,23,1);  
      }
    }
    else if(c == KEY_F3){//Saves the Edit
      if (isEdit){
	EditMystore(n_edit);
	turnOff();
	isMenu = 1;
	clear(23,-1);
	subsize = 0;
	bdysize = 0;
	buffersize = 0;
	commandsize = 0;
	fill(buffer,30);
	fill(command,5);
	fill(subject,30);
	fill(body,140);
	//display MenuScreen
	xt_par0(XT_CLEAR_SCREEN);
	for (i = 0; i < nMS; ++i) {
	  xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
	  xt_par0(XT_CH_DEFAULT);
	  xt_par0(MS[i].color);
	  printf("%s",MS[i].string);
	}
	message("Edits saved. Enter Command",WHITE);
	DisplayMenu();
	xt_par2(XT_SET_ROW_COL_POS,23,1);  
      }
      if (isExp){//Goes to Search mode
	if(!row){
	  row = 1;
	  clear(2,9);
	  message("Type in the search parameters",WHITE);
	  isSearch = 1;
	  erow = 18;
	  ecol = 23;
	  subsize = 0;
	  xt_par2(XT_SET_ROW_COL_POS,18,23);
	}
	else{//Gets out of Search mode
	  xt_par2(XT_SET_ROW_COL_POS,23,1); 
	  clear(2,9);
	  message("Use arrow keys to scroll through items.",WHITE);
	  row = 0;
	  isSearch = 0;
	}
      }
    }
    else if(c == KEY_BACKSPACE){
      if(isAdd && subsize > 0){
	putchar('\b');
	putchar(' ');
	putchar('\b');
	if(subsize > 0) subject[subsize--] = ' ';
      }
      else if(isAddC && bdysize > 0){
	if(bdysize == 80) xt_par2(XT_SET_ROW_COL_POS,16,80);
	putchar('\b'); 
	putchar(' ');
	putchar('\b');
	body[bdysize--] = ' ';
      }
      else if(isEdit){
	if(row == 0){
	  putchar('\b');
	  putchar(' ');
	  putchar('\b');
	  if(subsize > 0) subject[subsize--] = ' ';
	}
	else if(bdysize > 0){
	  putchar('\b'); 
	  putchar(' ');
	  putchar('\b');
	  body[bdysize--] = ' ';
	}
      }
      else if(isMenu){
	putchar('\b'); 
	putchar(' ');
	putchar('\b');
      }
    }
    else if(c == KEY_F2){
      printf("%c", subj[0]);
    }
    else if(c == KEY_F6 && isMenu){
      n_edit = 1;
      turnOff();
      sze = 0;
      isExp = 1;
      row = 0;
      clear(23,-1);
      subsize = 0;
      bdysize = 0;
      isSearch = 0;
      buffersize = 0;
      commandsize = 0;
      fill(buffer,30);
      fill(command,5);
      fill(subject,30);
      fill(body,140);
      fill(date1, 11);
      fill(date2, 11);
      fill(subj, 30);
      fill(lownum, 3);
      fill(highnum, 3);
      date1[4] = '-';
      date1[7] = '-';  
      date2[4] = '-';
      date2[7] = '-';
      //display ExplorerScreen
      xt_par0(XT_CLEAR_SCREEN);
      for (i = 0; i < nEXS; ++i) {
	xt_par2(XT_SET_ROW_COL_POS,EXS[i].row,EXS[i].col);
	xt_par0(XT_CH_DEFAULT);
	xt_par0(EXS[i].color);
	printf("%s",EXS[i].string);
      }
      message("Use up and down to scroll through the items.",WHITE);
      fillExp();
      DisplayEXP();
      xt_par2(XT_SET_ROW_COL_POS,23,1);  
    }
    else if(c == KEY_UP){
      if(row && isEdit){
	xt_par2(XT_SET_ROW_COL_POS,13,12);
	row = 0;
      }
      else if(isSearch && isExp){
	if (erow == 19){
	  erow = 18;
	  ecol = 23;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	}
	else if(erow == 20){
	  erow = 19;
	  ecol = 14;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	}
      }
      else if(isExp){
	if(++e > emax || Exp[e] == 0){
	  e = 1;
	}
	DisplayEXP();
	xt_par2(XT_SET_ROW_COL_POS,23,1); 
      }
    }
    else if(c == KEY_DOWN){
      if(!row && isEdit){ 
	xt_par2(XT_SET_ROW_COL_POS,17,1);
	row = 1;
      }
      else if(isSearch && isExp){
	if (erow == 18){
	  erow = 19;
	  ecol = 14;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	}
	else if(erow == 19){
	  erow = 20;
	  ecol = 18;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	}
      }
      else if(isExp){
	if(--e < 1){
	  e = emax;
	}
	DisplayEXP();
	xt_par2(XT_SET_ROW_COL_POS,23,1); 
      }
    }
    else if(c == KEY_RIGHT && isExp){
      if(isSearch && erow == 18){
	if(ecol < 27){
	  ecol++;
	  if (ecol == 25) ecol++;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol); 
	}
      }
    }
    else if(c == KEY_LEFT && isExp){
      if(isSearch && erow == 18){
	if(ecol > 23){
	  ecol--;
	  if(ecol == 25)ecol--;
	  xt_par2(XT_SET_ROW_COL_POS,erow,ecol); 
	}
      }
    }
    else if( c == KEY_ENTER){
      if(isAdd){
	if(CheckMystore()){//Checks to see if same file name
	  turnOff();
	  subsize = 0;
	  bdysize = 0;
	  isAddC = 1;
	  AddMystore();
	  //Displays Confirm Screen
	  clear(23,-1);
	  for (i = 0; i < nASC; ++i) {
	    xt_par2(XT_SET_ROW_COL_POS,ASC[i].row,ASC[i].col);
	    xt_par0(XT_CH_DEFAULT);
	    xt_par0(ASC[i].color);
	    printf("%s",ASC[i].string);
	  }
	  nitems++;
	  message("Subject Added to MyStore. Input Body",WHITE);
	  DisplayAddC();
	  xt_par2(XT_SET_ROW_COL_POS,17,1);
	}
	else{
	  clear(23,-1);
	  clear(7,10);
	  message("Same Subject Found in My Store, Rename.",RED);
	  fill(subject,30);
	  subsize = 0;
	  pcommand("Enter Subject(Max 30 chars)", 53);
	}
      }  
      else if(isAddC){//Puts the Body into the file
	printf("here");
	EditMystore(nitems);
	fill(subject,30);
	fill(body,140);
	subsize = 0;
	bdysize = 0;
	turnOff();
	isMenu = 1;
	xt_par0(XT_CLEAR_SCREEN);		
	// display Menu
	for (i = 0; i < nMS; ++i) {
	  xt_par2(XT_SET_ROW_COL_POS,MS[i].row,MS[i].col);
	  xt_par0(XT_CH_DEFAULT);
	  xt_par0(MS[i].color);
	  printf("%s",MS[i].string);
	}
	DisplayMenu();
	message("Item Added.",YELLOW);
	xt_par2(XT_SET_ROW_COL_POS,23,1);
      }
      else if(isMenu){//Opens the edit part
	if(strcmp(command,"open ") == 0 && SearchMystore(buffer)){
	  fill(buffer,30);
	  fill(command,5);
	  commandsize = 0;
	  buffersize = 0;
	  turnOff();
	  isEdit = 1;
	  row = 0;
	  xt_par0(XT_CLEAR_SCREEN);		
	  // display Edit
	  for (i = 0; i < nES; ++i) {
	    xt_par2(XT_SET_ROW_COL_POS,ES[i].row,ES[i].col);
	    xt_par0(XT_CH_DEFAULT);
	    xt_par0(ES[i].color);
	    printf("%s",ES[i].string);
	  }
	  DisplayEdit();
	  message("Edit",WHITE);
	  xt_par2(XT_SET_ROW_COL_POS,13,12);
	  //Sets subject and body
	  char n[3];
	  sprintf(n,"%d",n_edit);
	  ReadMystoreFromChild("display",n,NULL,NULL);
	  ParseInput(input,n_input);
	  sprintf(subject,"%s",nvs[3].value);
	  sprintf(body,"%s",nvs[4].value);
	  subsize = 0;
	  bdysize = 0;
	}
	else if(strcmp(command,"open ") != 0){
	  fill(buffer,30);
	  fill(command,5);
	  commandsize = 0;
	  buffersize = 0;
	  clear(23,1);
	  pcommand("Wrong command", 65);
	}
	else{
	  fill(buffer,30);
	  fill(command,5);
	  commandsize = 0;
	  buffersize = 0;
	  clear(23,1);
	  pcommand("No file with that name", 57);
	}
      }
      else if(isExp && !isSearch){//opens the edit page
	fill(buffer,30);
	fill(command,5);
	commandsize = 0;
	buffersize = 0;
	turnOff();
	isEdit = 1;
	row = 0;
	xt_par0(XT_CLEAR_SCREEN);		
	// display Edit
	for (i = 0; i < nES; ++i) {
	  xt_par2(XT_SET_ROW_COL_POS,ES[i].row,ES[i].col);
	  xt_par0(XT_CH_DEFAULT);
	  xt_par0(ES[i].color);
	  printf("%s",ES[i].string);
	}
	DisplayEdit();
	message("Edit",WHITE);
	xt_par2(XT_SET_ROW_COL_POS,13,12);
	//Sets subject and body
	char n[3];
	sprintf(n,"%d",n_edit);
	ReadMystoreFromChild("display",n,NULL,NULL);
	ParseInput(input,n_input);
	sprintf(subject,"%s",nvs[3].value);
	sprintf(body,"%s",nvs[4].value);
	subsize = 0;
	bdysize = 0;
      }
      else if(isSearch){
	SearchArrayMystore(date1, date2, subj, lownum, highnum);
	clear(2,9);
	message("Search Complete. Use arrow keys to scroll through results.",YELLOW);
	if (emax == 0){
	  clear(2,9);
	  message("No Searches Found! Returned to Original Items.",RED);
	  fillExp();
	}
	erow = 0;
	ecol = 0;
	isSearch = 0;
	DisplayEXP();
	xt_par2(XT_SET_ROW_COL_POS,23,1);
      }
    }
    else if(c >= ' ' && c <= '~'){
      if(isAdd && subsize < 30){
	subject[subsize++]= c;
	putchar(c);
      }
      else if(isAddC && bdysize < 140){
	body[bdysize++] = c;
	if(bdysize == 81) xt_par2(XT_SET_ROW_COL_POS,18,1);
	putchar(c);
      }
      else if(commandsize < 5 && isMenu){
	command[commandsize++] = c;
	putchar(c);
      }
      else if(buffersize < 30 && isMenu){
	buffer[buffersize++] = c;
	putchar(c);
      }
      else if(isEdit && row == 0 && subsize < 30){
	subject[subsize++] = c;
	putchar(c);
      }
      else if(isEdit && row == 1 && bdysize < 140){
	body[bdysize++] = c;
	if(bdysize == 81) xt_par2(XT_SET_ROW_COL_POS,18,1);
	putchar(c);
      }
      else if(isExp && erow == 18 && isSearch){//record Number Search
	if ( c >= '1' && c <= '9'){
	  if(ecol == 23){
	    putchar(c);
	    lownum[0] = c;
	    ecol = 24;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if(ecol = 24){
	    putchar(c);
	    highnum[1] = c;
	    ecol = 26;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if(ecol = 26){
	    putchar(c);
	    highnum[0] = c;
	    ecol = 27;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if(ecol = 27){
	    putchar(c);
	    highnum[1] = c;
	    ecol = 28;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	}
      }
      else if(isExp && erow == 19 && isSearch){//Date Search
	if ( c >= '0' && c <= '9'){
	  if (ecol == 14){
	    putchar(c);
	    date1[0] = c;
	    ecol = 15;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 15){
	    putchar(c);
	    date1[1] = c;
	    ecol = 16;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 16){
	    putchar(c);
	    date1[2] = c;
	    ecol = 17;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 17){
	    putchar(c);
	    date1[3] = c;
	    ecol = 19;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 19){
	    putchar(c);
	    date1[5] = c;
	    ecol = 20;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 20){
	    putchar(c);
	    date1[6] = c;
	    ecol = 22;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 22){
	    putchar(c);
	    date1[8] = c;
	    ecol = 23;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 23){
	    putchar(c);
	    date1[9] = c;
	    ecol = 27;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 27){
	    putchar(c);
	    date2[0] = c;
	    ecol = 28;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 28){
	    putchar(c);
	    date2[1] = c;
	    ecol = 29;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 29){
	    putchar(c);
	    date2[2] = c;
	    ecol = 30;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 30){
	    putchar(c);
	    date2[3] = c;
	    ecol = 32;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 32){
	    putchar(c);
	    date2[5] = c;
	    ecol = 33;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 33){
	    putchar(c);
	    date2[6] = c;
	    ecol = 35;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 35){
	    putchar(c);
	    date2[8] = c;
	    ecol = 36;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	  else if (ecol == 36){
	    putchar(c);
	    date2[9] = c;
	    xt_par2(XT_SET_ROW_COL_POS,erow,ecol);
	  }
	}
      }
      else if(isExp && erow == 20 && isSearch){
	if (sze < 30){
	  subj[sze++] = c;
	  putchar(c);
	}
      }
    }
  }
	
}
