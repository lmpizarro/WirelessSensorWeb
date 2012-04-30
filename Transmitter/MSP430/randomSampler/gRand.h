#ifndef GRAND_H_
#define GRAND_H_

//
//http://gushh.net/blog/random-software-delays/
//
 
static unsigned long int rand_next = 1;
 
unsigned long int gRand( void ) {
	rand_next = rand_next * 1103515245 + 12345;
	return (unsigned long int) (rand_next>>16) % 32768;
}


unsigned long int gRandInRange( unsigned long int range ) {
	rand_next = rand_next * 1103515245 + 12345;
	return (unsigned long int)(rand_next>>16) % range;
}

 
void gSRand( unsigned long int seed ) {
	rand_next = seed;
}
 
#define gRandom()		((gRand() & 0x7fff) / ((float)0x7fff)) 	// random in the range [0, 1]
#define gCRandom()		(2.0 * (gRandom() - 0.5)) 			// random in the range [-1, 1]
#define gMax(x,y)		(x > y ? x : y)				// minimum
#define gMin(x,y)		(x < y ? x : y)				// maximum
 
#endif /*GRAND_H_*/
