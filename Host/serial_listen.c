#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define BAUDRATE B9600

// To compile on Ubuntu or Mac OS X with xcode:
//   gcc -O3 -Wall -o serial_listen serial_listen.c

const char *begin_string="10 second speed test begins";
const char *end_string="done!\r\n";
#define END_LEN 7

int main(int argc, char **argv)
{
	char buf[64];
	int port,k;
	int n, sum=0, mciclos = 0;
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
        cfsetispeed(&settings, B9600);
        cfsetospeed(&settings, B9600);
	tcsetattr(port, TCSANOW, &settings);

	// Read data until we get a see the end string or get an error
	printf("Reading from %s\n", argv[1]);
        countChars = 0;
	while (1) {
                sleep(2);
		n = read(port, buf, 64);
                if (n>0){ // Hay datos en el buffer
                   printf ("<-- %d -->   ",n);
                   for (k=0; k < n; k++){
                       if (buf[k] == ':'){
                          countChars = 0;
                          printf ("Comienzo\n");
                       } else {
                               // fin de mensaje 0x0A, anterior 0x0D
                                if (buf[k]!= 0x0A){
                                  countChars = countChars + 1;
                                }else{
                                     if (countChars != 20)
                                        printf("Error mensaje \n");
                                     else
                                        printf ("fin %d \n", countChars);
                                   countChars = 0;
                                }
                       }
                                   
                       printf ("%c",buf[k]);
                   }
                }else { // no hay datos en el buffer
                  mciclos = mciclos + 1;
                  if (mciclos > 50)
                    printf ("Bus sin actividad: \n");
                }
	}

	close(port);
	printf("Total bytes read: %d\n", sum);
	return 0;
}


