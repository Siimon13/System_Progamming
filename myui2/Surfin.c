#include "myui2.h"
struct NameValue = *nvs = NULL;
int n_nvs = 0;
//-------------------------------------------------Menu----------------------

struct MenuString MS[] = {
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
  {21,1,XT_CH_RED,"Press Ctrl q to quit the program"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,62,XT_CH_WHITE,"Enter Command"}
};

int nMS = sizeof(TS)/sizeof(TS[0]);

struct MenuStringPosition MSP[] = {
  {2,10,70,"message"},
  {4,9,40,"status"},
  {5,21,30,"recordnum"},
  {6,9,30,"author"},
  {7,10,10,"version"},
  {8,20,20,"firstrecord"},
  {9,20,20,"lastrecord"},
  {11,20,20,"location"},
  {23,1,40,"command"}
};
//-------------------------------------------------Add-----------------------

struct AddString AS[] = {
  {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {7,1,XT_CH_WHITE,"Subject:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,62,XT_CH_WHITE,"Enter Subject"}
};

int nAS = sizeof(AS)/sizeof(AS[0]);

struct AddStringPosition ASP[] = {
  {2,10,70,"message"},
  {7,10,31,"subject"},
  {23,1,31,"addsubject"}
};

struct AddStringConfirm ASC[] = {
  {11,1,XT_CH_WHITE, "Status:"},
  {12,1,XT_CH_WHITE, "Author:"},
  {13,1,XT_CH_WHITE, "First record time:"},
  {16,1,XT_CH_WHITE, "Body:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,62,XT_CH_WHITE,"Enter Body"}
};

int nASC = (sizeof(ASC)+sizeof(AS)) / (sizeof(AS[0])+sizeof(ASC[0]));

struct AddStringConfirmPosition ASCP[] = {
  {2,10,70,"message"},
  {7,10,31,"subject"},
  {11,9,40,"status"},
  {12,9,30,"author"},
  {13,20,20,"firstrecord"},
  {16,6,141,"body"},
  {23,1,31,"addsubject"}
};

struct AddStringERROR ASE[] = {
  {11,1,XT_CH_RED, "Status:"},
  {22,1,XT_CH_CYAN,"------------------------------------------------------------------------------"},
  {23,62,XT_CH_WHITE,"Please Enter Again"}
};

int nASE = (sizeof(ASC)+sizeof(ASE))/(sizeof(AS[0])+sizeof(ASE[0]));

struct AddStringERRORPosition ASEP[] = {
  {2,10,70,"message"},
  {7,10,31,"subject"},
  {23,1,31,"addsubject"}  
};

//-------------------------------------------------EDIT----------------------

struct Edit E[] = {
  {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {4,1,XT_CH_WHITE,"Record Number:"},
  {5,1,XT_CH_WHITE,"Location:"},
  {6,1,XT_CH_WHITE,"Last Edit:"},
  {7,1,XT_CH_WHITE,"First Record Time:"},
  {8,1,XT_CH_YELLOW,"Subj: 30 char max, Body: 140 char max. Press up and down to switch."},
  {9,1,XT_CH_YELLOW,"------------------------------------------------------------------------------"},
  {10,1,XT_CH_WHITE,"Subj:"},
  {16,1,XT_CH_WHITE,"Body:"},
  {23,62,XT_CH_YELLOW,"Press Delete to delete, Ctrl s to save changes, F8 to exit the record."}
};

int nE = sizeof(E)/sizeof(E[0]);

struct EditPosition EP[] = {
  {2,10,70,"message"},
  {4,15,10,"recordnum"},
  {5,10,20,"location"},
  {6,12,20,"lastrecord"},
  {7,20,20,"firstrecord"},
  {10,6,31,"subject"},
  {16,6,141,"body"}
};

//-------------------------------------------------Explorer------------------

struct Explorer EXP[] = {
  {1,1,XT_CH_CYAN,"----------------------------------Surfin--------------------------------------"},
  {2,1,XT_CH_WHITE,"Message:"},
  {4,1,XT_CH_WHITE,"Record Number:"},
  {5,1,XT_CH_WHITE,"Current Location:"},
  {6,1,XT_CH_WHITE,"First Record Time:"},
  {7,1,XT_CH_WHITE,"Subject:"},
  {8,1,XT_CH_WHITE,"Body:"},
  {10,1,XT_CH_WHITE,"You can use the arrow keys to navigate the items one by one.Press Enter to edit/enter the item. Alternatively, press F3 to use the search function below.  
When using the search function, use the arrow keys to navigate and edit and press Enter to search. Press F3 to navigate again."},
  {17,1,XT_CH_WHITE,"------------------------------------------------------------------------------"},
  {18,1,XT_CH_WHITE,"Number between:x - y"},
  {19,1,XT_CH_WHITE,"Time between yyyy mm dd - yyyy mm dd"},
  {20,1,XT_CH_WHITE,"Subject Includes: "}
};

int nEXP = sizeof(EXP)/sizeof(EXP[0]);

struct EXPLORERPOSITION EXPP[] = {
  {2,10,70,"message"},
  {4,15,10,"recordnum"},
  {5,10,20,"location"},  
  {6,20,20,"firstrecord"},
  {7,6,31,"subject"},
  {8,6,74,"body"},
  {18,16,1,"lowernum"},
  {18,20,1,"highernum"},
  {19,14,4,"lowyear"},
  {19,19,2,"lowmonth"},
  {19,22,2,"lowday"},
  {19,27,4,"highyear"},
  {19,32,2,"highmonth"},
  {19,35,2,"highday"},
  {20,18,31,"srchsubject"}
};


//-----------------------------------Main---------------------------------------
void main(){



}
