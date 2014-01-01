#include "myui2.h"
#define MATCH -32
extern struct NameValue *nvs;
extern int n_nvs;

extern char input[1000];
extern int n_input;
extern int n_edit;
extern int e;
extern int emax;
extern int Exp[999];

extern int nitems;
extern char subject[31];
extern char body[141];
extern char errmsg[80];


// ----------------------------------------- ReadMystoreFromChild ---------------------------
int ReadMystoreFromChild(char *argv1, char *argv2, char *argv3, char *argv4) {
  int pid, mypipe[2], i;
  char *newargv[7];
	
  if (nvs != NULL) {
    free(nvs);
    nvs = NULL;
  }
  n_nvs = 0;
  n_input = 0;
	
  // turn off special keyboard handling
  getkey_terminate();
	
  // create the pipe
  if (pipe(mypipe) == -1) {
    strcpy(errmsg,"Problem in creating the pipe");
    return 0;
  }
	
  pid = fork();
	
  if (pid == -1) {
    strcpy(errmsg, "Error in forking");
    return 0;
  }
  if (pid == 0) {  // child
    close(mypipe[0]);  // Don't need to read from the pipe
    dup2(mypipe[1],STDOUT_FILENO);  // connect the "write-end" of the pipe to child's STDOUT
		
    for (i = 2; i < 7; ++i) newargv[i] = NULL;
    newargv[0] = newargv[1] = "./mystore";
    newargv[2] = argv1;
    newargv[3] = argv2;
    newargv[4] = argv3;
    newargv[5] = argv4;
    newargv[6] = NULL;
		
    execvp(newargv[0],newargv+1);
    exit(0);
  }
  else if (pid > 0) {
    char *s = input;
    int c, i, n;
    close(mypipe[1]);  // Don't need to write to the pipe
		
    // read the data into the input array
    FILE *fpin;
    if ((fpin = fdopen(mypipe[0],"r")) == NULL) {
      printf("ERROR: Cannot read from mypipe[0]\n");
      exit(1);
    }
    for (n_input = 0; n_input < sizeof(input)-1; ++n_input) {
      if ((c = getc(fpin)) == EOF) break;
      *s++ = c;
    }
    input[n_input] = '\0';
    fclose(fpin);
		
    wait(NULL);  // wait for child to finish
    close(mypipe[0]);
  }
	
  return n_input;
}
//----------------------------------------------Checks for same name---------
int CheckMystore(){
  int i = nitems;
  char n[3];
  while(i){
    sprintf(n,"%d",i);
    ReadMystoreFromChild("display",n,NULL,NULL);
    ParseInput(input,n_input);
    if (strcmp(nvs[3].value,subject) == MATCH) return FALSE;
    i--;
  }
  return TRUE;
}

//----------------------------------------------Adds to My Store-------------
int AddMystore(){
  int  pid;
  int status;
  char* argv[6];

  argv[0] = "./mystore";
  argv[1] = "add";
  argv[2] = subject;
  argv[3] = body;
  argv[4] = NULL;
  argv[5] = NULL;

  if ((pid = fork()) < 0) {    
    strcpy(errmsg,"Failed forking");
    exit(1);
  }
  else if (pid == 0) {         
    if (execvp(*argv, argv) < 0) {     
      strcpy(errmsg,"Something went wrong");
      exit(1);
    }
  }
  else {                                 
    wait(NULL);       
  }
  wait(NULL);
  return TRUE;
}

//-----------------------------------------------Edit My Store---------------
int EditMystore(int num){
  int pid;
  int status;
  char* argv[6];
  char n[3];
  sprintf(n,"%d",num);

  argv[0] = "./mystore";
  argv[1] = "edit";
  argv[2] = n;
  argv[3] = subject;
  argv[4] = body;
  argv[5] = NULL;

  if ((pid = fork()) < 0) {    
    strcpy(errmsg,"Failed forking");
    exit(1);
  }
  else if (pid == 0) {         
    if (execvp(*argv, argv) < 0) {     
      strcpy(errmsg,"Something went wrong");
      exit(1);
    }
  }
  else {                                 
    wait(NULL);       
  }
  wait(NULL);
  return TRUE;
}

//------------------------------------------------SearchMyStore For Name-----
int SearchMystore(char* name){
  int i = nitems;
  char n[3];
  while(i){
    sprintf(n,"%d",i);
    ReadMystoreFromChild("display",n,NULL,NULL);
    ParseInput(input,n_input);
    if (strcmp(nvs[3].value,name) == 0){ 
      n_edit = i;
      return i;
    }
    i--;
  }
  return FALSE;
}

//---------------------------------------------Creates the Array for Search--
int SearchArrayMystore(char* date1, char* date2, char* subj, char* lownum, char* highnum){
  fillint(Exp,999);
  e = 1;
  emax = 0;
  int i = nitems;
  char n[3];
  int l = atoi(lownum);
  int h = atoi(highnum);
  while(i > 0){
    sprintf(n,"%d",i);
    ReadMystoreFromChild("display",n,NULL,NULL);
    ParseInput(input,n_input);
    if ((i >= l || (lownum[0] == ' ' && lownum[1] == ' ')) //Checks recordnum
	&& (i <= h || (highnum[0] == ' ' && highnum[1] == ' '))
	&& (subj[0] == ' ' || subjSearch(subj))
	&& dateSearch(date1,date2)
	){
      Exp[e] = i;
      e++;
      emax++;
    }
    i--;
  }
  xt_par2(XT_SET_ROW_COL_POS,23,1);
  e = 1;
  return TRUE;
}

//===================================================Helpers for SearchArryMystore
int subjSearch(char* subj){
  int z = 0;
    while(z < 29){
      if (subj[0] == nvs[3].value[z]){
	if(checkPattern(subj,z))
	printf("Something");
	return TRUE;
      }
      z++;
    }
  return FALSE;
}

  //Helper for subjSearch
int checkPattern(char* subj, int i){
  int j = 1;
  while( j < strlen(subj) - 2){
    if (subj[j++] != nvs[3].value[++i]) return FALSE;
  }
  return TRUE;
}


int dateSearch(char* date1, char* date2){
  char date[11];
  fill(date, 11);
  int i = 0;
  while (i < 10){
    date[i] = nvs[2].value[i]; 
    i++;
  }
  i = 0;
  if ((strcmp(date,date1) >= 0 || date1[0] == ' ') //Checks date
      && (strcmp(date,date2) <= 0 || date2[0] == ' '))
    return TRUE;
  return FALSE;
}
    //-----------------------------------------------Delete My store-------------
int DeleteMystore(int num){
  int pid;
  int status;
  char* argv[6];
  char n[3];
  sprintf(n,"%d",num);

  argv[0] = "./mystore";
  argv[1] = "delete";
  argv[2] = n;
  argv[3] = NULL;
  argv[4] = NULL;
  argv[5] = NULL;

  if ((pid = fork()) < 0) {    
    strcpy(errmsg,"Failed forking");
    exit(1);
  }
  else if (pid == 0) {         
    if (execvp(*argv, argv) < 0) {     
      strcpy(errmsg,"Something went wrong");
      exit(1);
    }
  }
  else {                                 
    wait(NULL);       
  }
  wait(NULL);
  return TRUE;
}

    // ----------------------------------------------- ParseInput -----------------------------
    int ParseInput(char *in, int n_in) {
      int num_nvs, i_nvs;
      char *p;
	
      if (nvs != NULL) free(nvs);
      nvs = NULL;
      n_nvs = 0;
	
      if (n_in < 7)
	return 0;
	
      for (num_nvs = 0, p = in; *p; ++p) {
	if (*p == '|') ++num_nvs;
      }
      num_nvs /= 2;
	
      if ((nvs = calloc(num_nvs, sizeof(struct NameValue))) == NULL)
	return 0;
	
      for (i_nvs = 0, p = in; i_nvs < num_nvs; ++i_nvs) {
	// until record
	while (*p++ != '|')
	  ;
	// start of name
	nvs[i_nvs].name = p;
	while (*p != ':')
	  p++;
	*p++ = '\0';
	// name finished, looking for value...
	while (*p == ' ')
	  p++;
	nvs[i_nvs].value = p;
	while (*p != '|')
	  p++;
	*p = '\0';
	// value finished
      }
      n_nvs = num_nvs;
      return n_nvs;
    }
