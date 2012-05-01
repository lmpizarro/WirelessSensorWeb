//
//  credits http://www.pjrc.com/teensy/usb_serial.html
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>


#define BAUDRATE B57600

// To compile on Ubuntu or Mac OS X with xcode:
//   gcc -O3 -Wall -o serial_listen serial_listen.c

const char *begin_string="10 second speed test begins";
const char *end_string="done!\r\n";
#define END_LEN 7

struct timeval time1;

int errorMensaje (unsigned char countChars){
  printf ("error de mensaje\n"); 
  return (1);
}

void procMensaje (unsigned char countChars, char *bufRecepc){
    struct tm *newtime;
    time_t ltime;
    struct timeval time2, deltaTime;
    float  dtime, usec;
 
    /* Get the time in seconds */
    time(&ltime);
    /* Convert it to the structure tm */
    newtime = localtime(&ltime);
    
    usec = 1000000.0; 
    gettimeofday(&time2, NULL); 
    deltaTime.tv_sec = time2.tv_sec - time1.tv_sec;
    deltaTime.tv_usec = time2.tv_usec - time1.tv_usec;
    dtime = (float)time2.tv_sec + (float)time2.tv_usec/usec - (float)time1.tv_sec - (float)time1.tv_usec/usec;
    
    time1.tv_sec  = time2.tv_sec;
    time1.tv_usec  = time2.tv_usec;
    
   // imprimir Delta

  printf("%d/%d/%d-%d:%d:%d ",  newtime->tm_year+1900, 
                                   newtime->tm_mon+1, 
                                   newtime->tm_mday, 
                                   newtime->tm_hour,  
                                   newtime->tm_min, 
                                   newtime->tm_sec); 

       //%s       bufRecepc
  int i = 1;
  while (1){
    if (bufRecepc[i]!='!'){
     printf ("%c", bufRecepc[i]);
     i = i + 1;
    } else {
      break;
    }
  }



  printf ("  %d %d\n", deltaTime.tv_sec, deltaTime.tv_usec );
  
}

int main(int argc, char **argv)
{
	char buf[64], bufRecepc[32];
	int port,k;
	int n, sum=0, mciclos = 0, i;
	struct termios settings;
        char countChars;

	if (argc < 2) {
		fprintf(stderr, "Usage:   serial_listen <port>\n");
		fprintf(stderr, "Example: serial_listen /dev/ttyACM0\n");
		return 1;
	}

	// Open the serial port
	port = open(argv[1], O_RDONLY);
	if (port < 0) {
		fprintf(stderr, "Unable to open %s\n", argv[1]);
		return 1;
	}

	// Configure the port
	tcgetattr(port, &settings);
	///cfmakeraw(&settings);
        cfsetispeed(&settings, BAUDRATE);
        cfsetospeed(&settings, BAUDRATE);
	tcsetattr(port, TCSANOW, &settings);
        gettimeofday(&time1, NULL);
	// Read data until we get a see the end string or get an error
	printf("Reading from %s\n", argv[1]);
        countChars = 0;
	while (1) {
                sleep(2);
		n = read(port, buf, 64);
                if (n>0){ // Hay datos en el buffer
                   for (k=0; k < n; k++){
                       if (buf[k] == ':'){
                          countChars = 0;
                          bufRecepc[countChars] = buf[k];
                          countChars = countChars + 1;
                       } else {
                          // fin de mensaje 0x0A, anterior 0x0D
                          if (buf[k]!= '!'){
                            bufRecepc[countChars] = buf[k];
                            countChars = countChars + 1;
                          }else {
                             countChars = countChars + 1;
                             bufRecepc[countChars] = buf[k];
                             if (countChars != 12) {
                               errorMensaje(countChars);
                             } else {
                               procMensaje (countChars, bufRecepc);
                             }
                          }
                       }
                   }  //  cierra el for
                }else { // no hay datos en el buffer
                  mciclos = mciclos + 1;
                  if (mciclos > 50)
                    printf ("Bus sin actividad: \n");
                  mciclos = 0;
                }
	} // fin del while (1)

	close(port);
	printf("Total bytes read: %d\n", sum);
	return 0;
}
