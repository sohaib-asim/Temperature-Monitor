#include <stdio.h>
#include <wiringPi.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void tempMonitor(char *serialNum, int verbose);

int main(int argc, char *argv[]){
  wiringPiSetup () ;
  char *device = "28-031841890cff";
   int verbose = 0;
 /* process the arguments */
 argc--; argv++;
 
 while(argc > 0){
	 printf("%d %s\n", argc, argv[0]);
	 
	 if(!strcmp("-v", argv[0])) {
	 	verbose = 1;
 	 } 
	 
	 else if(!strcmp("-d", argv[0])) {
	 	if(argc == 0)
	 		printf("argc == 0");
		 	argc--; argv++;
			device = argv[0];
 		} else {
		printf("no args");
	 }

	 argc--; argv++;
 }
 
 tempMonitor(device, verbose);
 return 0;
}


tempMonitor(char *serialNum, int verbose){

  FILE *fd;
  int n;
  char buf[1001];
  char temperature[6];
  char path[1000] = "/sys/bus/w1/devices/";
  strcat(path, serialNum);
  strcat(path, "/w1_slave");


  float max,temp;
  float prevTemp;
  prevTemp = temp;
  float min;
  min = 0.00;

  /*IF NO SERIAL NUM RETURN ERROR*/
  if(serialNum == NULL)
  {
    perror("Error, sensor argument missing");
    (void) exit(1);
  }
  char maximum[500];
  char minimum[500];
  char current[500];
  
    /*IF temperature SENSOR NOT FOUND, THEN THROW ERROR */
    fd = fopen(path, "r");
    if(fd == (FILE *)NULL){
      perror("Error, sensor not found\n");
      exit(1);
    }

    n = fread(buf,sizeof(char),1000,fd);
    if(n==0)
    {
      perror("read failed");
      exit(1);
    }


    buf[n] = '\0';
	
	 if(verbose == 1)
	 {
        printf("verbose: %s ",buf);
	 }


    strncpy(temperature, strstr(buf, "t=") + 2, 5);
    temperature[n]='\0';

    temp = (float)atof(temperature);
	fprintf(stdout, "%.f\n", temp);


}
