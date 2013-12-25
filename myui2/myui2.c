#include "myui2.h"

struct NameValue *nvs = NULL;
int n_nvs = 0;

char input[1000];
int n_input=0;	// number of chars in the input, not including terminating NULL-byte

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

int nitems = 0;
char subject[31];
char body[141];
char errmsg[80] = "";

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
	SearchMenu("message","message",XT_CH_WHITE);
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

// ------------------------------------------------ main --------------------
int main(void) {
	int i, c;
	
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

	while (TRUE) {
		while ((c = getkey()) == KEY_NOTHING) ;
		if (c == KEY_F9)  {
			xt_par0(XT_CLEAR_SCREEN);
			xt_par0(XT_CH_NORMAL);
			xt_par2(XT_SET_ROW_COL_POS,1,1);
			getkey_terminate();
			exit(0);
		}
	}
	
}
