/*
 * shelldon interface program

KUSIS ID: 53714 PARTNER NAME: Ege Berk Suzgen
KUSIS ID: 53590 PARTNER NAME: Emir Atisay

 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAX_LINE       80 /* 80 chars per line, per command, should be enough. */


int parseCommand(char inputBuffer[], char *args[],int *background);
char* saflar(char input[]);
void searchInLine(char *inputDir, char *search);
void searchIt(char sr[]);

/* custom calc function */
double calc( char operator, double a, double b) {
   
    double answer = 0;
   
    if( operator == '+'){
        answer = a + b;
    }else if (operator == '-'){
        answer = a - b;
    }else if (operator == '*'){
        answer = a * b;
    }else if (operator == '/'){
        answer = a/b;
    }else{
    printf("Not available operator");
    return 0;
    }
    printf("The result is %f\n", answer);
}

    /* Required method for the redirection operation*/
int isRedirectioned(char inputBuffer[], char *args[], int flag, char *redirprogram[], char redirfile[])
{
    int i=0;
    int booly=0;
    //int len= strlen(inputBuffer);
    //printf("\n%d\n", len);
    while(args[i]!=NULL){
        if((strcmp(args[i],">"))==0){
            booly=1;
            break;
        } else if((strcmp(args[i],">>"))==0){
            booly=1;
            break;
        }
        i++;
    }
    
    return booly;
}

/* History function */

int history(char *hist[], int current)
{

	int listnum = current -1;
	int endten = listnum -10;
	
	if(current>10){
	
	while(listnum != endten){
	
	printf("%4d  %s\n", listnum, hist[listnum]);
	listnum=listnum-1;

	}

	}else{

	for(int i=listnum; i>-1;i--){

	printf("%4d  %s\n", i, hist[i]);

	}

	}  

        return 0;
}


int main(void)
{
  char inputBuffer[MAX_LINE];             /* buffer to hold the command entered */
  int background;                         /* equals 1 if a command is followed by '&' */
  char *args[MAX_LINE/2 + 1];            /* command line (of 80) has max of 40 arguments */
  pid_t child;                    /* process id of the child process */
  int status;                   /* result from execv system call*/
  int shouldrun = 1;
  FILE *cronptr;
  int argctr=0;
  char *hist[100];
  char cmdcheck[200];
  int current =0;


char *redirprogram[MAX_LINE/2 + 1];  //rediraction program
  char *redirfile; //rediction output file
  int flag; //redirection method specifie
    /* calc  icin gerekli parametreler */
    double operand1, operand2= 0;
    char operator;


   
  int i, upper;
       
  while (shouldrun){                    /* Program terminates normally inside setup */
    background = 0;
       
    shouldrun = parseCommand(inputBuffer,args,&background);       /* get next command */
       
    if (strncmp(inputBuffer, "exit", 4) == 0)
      shouldrun = 0;     /* Exiting from shelldon*/


     int indicator=isRedirectioned(inputBuffer,args, flag,redirprogram,redirfile);
    if (shouldrun) {
      if(inputBuffer[0] != '!'){

        hist[current] = strdup(inputBuffer);
                current = (current + 1);
      }

   
    child=fork();
    if ( child < 0){
    fprintf(stderr, "Failed to Fork :(");
    return 1;
    }
    else if (child == 0) {



    if (strcmp(inputBuffer, "history") == 0)
    {
                        history(hist, current);






                            /* ----------------------------Functions with !------------------------------------- */

    }else if (inputBuffer[0] == '!')
    {

            if (inputBuffer[1]== '!') {
        
                if(current ==0){

                printf("The last command entered by the user : %s \n", hist[9]);
                system(hist[9]);

                }else{   

                printf("The last command entered by the user : %s \n", hist[current-1]);
                system(hist[current-1]);
                }   
            }else{        
                char nthcmd = inputBuffer[1];
                int x = nthcmd - '0';
                
                printf("The last %c 'th command entered by the user :%s \n", nthcmd,hist[x]);
                system(hist[x]);
                }
            
}else if (strcmp(inputBuffer, "calc") == 0)		/* starting of the calculator */
{
                           


        

        
     
        printf("Please enter the operator = ");
        scanf("%c", &operator);
        printf("Please enter the first operand = ");
        scanf("%lf",&operand1);
        printf("Please enter the second operator = ");
        scanf("%lf",&operand2);
    calc(operator, operand1,operand2);

}else if (strcmp(inputBuffer,"oldestchild")==0){


char oldestchildinput[100]= "sudo insmod oldestchild processID=";


strcat(oldestchildinput, args[1]);

printf("OLDU MU SIMDI %s \n",oldestchildinput);

system("sudo make");
system(oldestchildinput);




}else  if (strcmp(inputBuffer, "birdakika") == 0)
{
       


                /* starting of the birdakika function */

       
                  shouldrun = 0;    

    cronptr = fopen("crontabFile", "a+");
          if(cronptr == NULL){
              printf("Error while opening file\n!");
              exit(1);
          }

          argctr=0;
          while(args[argctr] != NULL){
              argctr++;
          }     

          if(argctr != 3) {
            printf("Please use proper number of commands for function: birdakika \"time\" \"song's name\"\n");
          }else{



        /* starting of the parsing part */
    char hour[10];
    char minute[10];
    int ctr=0;
    char tempArray[100];
   
    strcpy(tempArray,args[1]);   
    for(int i=0;i<sizeof(args[1]);i++){
        if(tempArray[i]== '.') ctr=i;
    }
       
    if(ctr==1){

    char hourt[]= {tempArray[0],NULL};
    strcpy(hour,hourt);

    }else{

    char hourt[]= {tempArray[0], tempArray[1],NULL};
    strcpy(hour,hourt);
    }
    char minutet[]={tempArray[ctr+1],tempArray[ctr+2],NULL};
    strcpy(minute,minutet);

        /* ending of the parsing part */

	char buff[100];
        getcwd( buff, sizeof(buff) );

    char crontabInput[220] = "echo \"";
    char third[100]=" * * * mpg321 ";
												
    strcat(crontabInput, minute);
    strcat(crontabInput, " ");
    strcat(crontabInput, hour);
    strcat(crontabInput, " ");
   
    execv("crontab", "crontabFile");        
        //system("crontab -l >> crontabFile");
        strcat(crontabInput, third);
	strcat(crontabInput, buff);
	strcat(crontabInput, "/");
        strcat(crontabInput, args[2]);

            strcat(crontabInput, "\"");

            strcat(crontabInput, " >> crontabFile");

    //execv("crontab",crontabInput);
            system(crontabInput);
    //execv("crontab", "crontabFile");
            system("crontab crontabFile");
            system("rm crontabFile");


        /* pkill part */
        char kill[220] = "echo \"";
        int nextminuteone = minute[1] - '0';
        int nextminuteten = minute[0] - '0';
        int lanet = (nextminuteten*10) + nextminuteone;


        lanet= lanet +1;
           
        char result[50];
            sprintf(result, "%d", lanet);

        strcat(kill, result);   
        strcat(kill, " ");
        strcat(kill, hour);
       
        strcat(kill, " ");
        char pkillstr[100]=" * * * pkill mpg321";

        strcat(kill, pkillstr);
        strcat(kill, "\"");
            strcat(kill, " >> crontabFile");
       
       
        system("crontab -l >> crontabFile");
        system(kill);
        system("crontab crontabFile");
          }

      fclose(cronptr);

}else if(indicator)
{

        

            int lll=0;
            while(args[lll]!=NULL){
                    if((strcmp(args[lll],">"))== 0){
                        flag=0;
                     break;
                    }
                    if((strcmp(args[lll],">>"))== 0){
                        flag=1;
                     break;
                    }
                redirprogram[lll] = malloc(sizeof(args[lll]));
                redirprogram[lll] = args[lll];
                lll++;
            }
            redirprogram[lll] = NULL;
            
            redirfile=args[lll+1];
            int file;
            if(flag){
                file = open(redirfile, O_CREAT | O_APPEND | O_WRONLY, 0600);
                dup2(file, STDOUT_FILENO);
            } else {
                file = open(redirfile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
                dup2(file, STDOUT_FILENO);
            }
            
           
           
          close(file);
          execvp(redirprogram[0], redirprogram);
          
         //  execvp(args[0], args);
        }

else if(strcmp(inputBuffer, "codesearch") == 0)
{
            /*getting the current directory
            char buff[FILENAME_MAX];
            getcwd( buff, FILENAME_MAX );
            printf("Current working dir: %s\n", buff);
            */

           //char *search;
           //char *direct; 
           if((strcmp(args[1],"-r"))== 0)
           {
             //printf("%s\n",search);
             //  printf("%s",args[2]);
               printf("Can not implemented\n");
          } else
          {
          char search[20];
          int k=0;
          while(args[1][k+2]!=NULL)
          {
            search[k]=args[1][k+1];
            k++;
          }
          search[k]='\0';
          
          //printf("\n%s\n",args[1]);
          //printf("\n%s\n",search);
          //printf("\n%c\n",search[3]);
          //printf("\n%c\n",search[4]);
          //printf("\n%c\n",search[5]);

          
                if (args[2] == NULL){
                  //printf("destur");
                  searchIt(search);
                  
                } else if ((strcmp(args[2],"-f"))== 0)
                {
                                if(args[3] == NULL){
                                  printf("no source given");
                                  exit(0);
                                }
                                searchInLine(args[3],search);

                    }
                }
}

else
{
    /* ending of the birdakika function */
    char str[50]="which ";
    strcat(str,inputBuffer);
    strcat(str," > directoryFile.txt");
    system(str);
    char c[1000];
    FILE *fptr;
    if ((fptr = fopen("directoryFile.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);
    execv(c, args);
    fclose(fptr);
   
}
    
    exit(0);
    }
    else{
    if(!background){
 wait(NULL);   
}
}
      /*
    After reading user input, the steps are
    (1) Fork a child process using fork()
    (2) the child process will invoke execv()
    (3) if command included &, parent will invoke wait()
       */
    }
  }
  return 0;
}

/**
 * The parseCommand function below will not return any value, but it will just: read
 * in the next command line; separate it into distinct arguments (using blanks as
 * delimiters), and set the args array entries to point to the beginning of what
 * will become null-terminated, C-style strings.
 */
void searchIt(char sr[]){
                      int csi=0;
                      char* cs[20];
                      pid_t child2;
                      child2=fork();
                            if ( child2 < 0){
                              fprintf(stderr, "Failed to Fork :(");
                              return 1;
                            }
                            else if (child2 == 0){
                                int file1;
                                char lsoutput[1000] = "output";
                                file1= open(lsoutput,O_CREAT | O_TRUNC | O_WRONLY,0600);
                                dup2(file1, STDOUT_FILENO);
                                system("ls");
                                close(file1);
                                wait(NULL);
                              
                            }
                            else{
                                wait(NULL);
                                char buff[FILENAME_MAX];
                                getcwd( buff, FILENAME_MAX );
                                strcat(buff,"/");

                                size_t len = 0;
                                ssize_t read;
                                FILE *filePointer;
                                char *line;
                                filePointer = fopen("output", "r");
                                    if (filePointer == NULL)
                                        exit(EXIT_FAILURE);
                                    while ((read = getline(&line, &len, filePointer)) != -1) {
                                      // search for specific word
                                        if(strstr(line, ".c") != NULL){
                                          //printf("%s", line);
                                          int k=0;
                                          k=strlen(line);
                                          line[k-1]=NULL;
                                          //printf("%s",buff);
                                          //char* x;
                                          //strcpy(x,buff);
                                          //strcat(x,line);
                                          //printf("%s",x);
                                          //searchInLine(x,search);
                                          searchInLine(line,sr);
                                          
                                          //cs[csi]=line;
                                          // printf("%s",search2);
                                          //fputs(filePointer2,line);
                                          //csi++;
                                        }
                                    }
                                    
                                fclose(filePointer);
                                remove("output");
                                
                            }
}
void searchRecursive(char *search)
{   
  

}
void searchInLine(char *inputDir, char *search){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNo=0;
  /*
  char* sh="shelldon.c";


  printf("\n%s\n",inputDir);
  printf("\n%s\n",sh);
  int c= strcmp(inputDir,sh);
  printf("\n%d\n",c);
  printf("\n%d\n",c);


  int len2=strlen(inputDir);
  int len3=strlen(sh);
  printf("\ninputDir lenght: %d\n",len2);
  printf("\nshelldon.c lenght: %d\n",len3);

  int jk=0;
  while(inputDir[jk]!=NULL){
      if(sh[jk]!=inputDir[jk]){
        printf("%c",sh[jk]);
        printf("%c",inputDir[jk]);

      }
      jk++;
  }
  */
    fp = fopen(inputDir, "r");
    if (fp == NULL){
        printf("file could not open\n");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
    //search for specific word
        if(strstr(line, search) != NULL){
            //char linem[20];
            //strcpy(linem,line);
            //linem= saflar(line);
            printf("%d : %s -> %s", lineNo, inputDir, line);
        }
        lineNo++;
    }
    fclose(fp);
}
char* saflar(char input[]){
  char* fill;
  int c = 0, d = 0;
  while (input[c] != '\0') {
      if (input[c] == ' ') {
         int temp = c + 1;
         if (input[temp] != '\0') {
            while (input[temp] == ' ' && input[temp] != '\0') {
               if (input[temp] == ' ') {
                  c++;
               }  
               temp++;
            }
         }
      }
      fill[d] = input[c];
      c++;
      d++;
   }
   return fill;
}
int parseCommand(char inputBuffer[], char *args[],int *background)
{
    int length,        /* # of characters in the command line */
      i,        /* loop index for accessing inputBuffer array */
      start,        /* index where beginning of next command parameter is */
      ct,            /* index of where to place the next parameter into args[] */
      command_number;    /* index of requested command number */
   
    ct = 0;
   
    /* read what the user enters on the command line */
    do {
      printf("shelldon>");
      fflush(stdout);
      length = read(STDIN_FILENO,inputBuffer,MAX_LINE);
    }
    while (inputBuffer[0] == '\n'); /* swallow newline characters */
   
    /**
     *  0 is the system predefined file descriptor for stdin (standard input),
     *  which is the user's screen in this case. inputBuffer by itself is the
     *  same as &inputBuffer[0], i.e. the starting address of where to store
     *  the command that is read, and length holds the number of characters
     *  read in. inputBuffer is not a null terminated C-string.
     */   
    start = -1;
    if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */
   
    /**
     * the <control><d> signal interrupted the read system call
     * if the process is in the read() system call, read returns -1
     * However, if this occurs, errno is set to EINTR. We can check this  value
     * and disregard the -1 value
     */

    if ( (length < 0) && (errno != EINTR) ) {
      perror("error reading the command");
      exit(-1);           /* terminate with error code of -1 */
    }
   
    /**
     * Parse the contents of inputBuffer
     */
   
    for (i=0;i<length;i++) {
      /* examine every character in the inputBuffer */
     
      switch (inputBuffer[i]){
      case ' ':
      case '\t' :               /* argument separators */
    if(start != -1){
      args[ct] = &inputBuffer[start];    /* set up pointer */
      ct++;
    }
    inputBuffer[i] = '\0'; /* add a null char; make a C string */
    start = -1;
    break;
   
      case '\n':                 /* should be the final char examined */
    if (start != -1){
      args[ct] = &inputBuffer[start];    
      ct++;
    }
    inputBuffer[i] = '\0';
    args[ct] = NULL; /* no more arguments to this command */
    break;
   
      default :             /* some other character */
    if (start == -1)
      start = i;
    if (inputBuffer[i] == '&') {
      *background  = 1;
      inputBuffer[i-1] = '\0';
    }
      } /* end of switch */
    }    /* end of for */
   
    /**
     * If we get &, don't enter it in the args array
     */
   
    if (*background)
      args[--ct] = NULL;
   
    args[ct] = NULL; /* just in case the input line was > 80 */
   
    return 1;
   
} /* end of parseCommand routine */
