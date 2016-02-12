#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

////////////////////////
// Generates a random double on the range [-bound,bound]
// Meant to be an analog of random.uniform()
double rand_uni_double(double bound){
	double x = ((double)rand()/(double)RAND_MAX);
	double out = (x * 2.0 * bound) - bound;
	return out;
}

////////////////////////
// Sums up all the elements of an array of doubles
// Meant to be an analog of sum()
double sum(double *x,int size){
	double total = 0.;
	for(int i = 0; i < size; i++){
		total = total + x[i];
	}
	return total;
}

////////////////////////
// Generates an array of 'size' doubles on the range [-bound,bound]
double * generate_random_list(int size, double bound){
	double *out;
	out = (double *)malloc(sizeof(double)*size);
	for(int i=0; i<size; i++){
		out[i]=rand_uni_double(bound);
	}
	return out;
}

////////////////////////
// Updates locations according to corresponding velocity by one time-step
void update_coords(double *x,double *y,double *z,
	double *vx,double *vy,double *vz,uint64_t size){
	uint64_t i = 0;

	__asm__ __volatile__ (
		"coordloop:"
		"movss (%1,%0,8), %%xmm0;"
		"movss (%4,%0,8), %%xmm1;"
		"addss %%xmm1, %%xmm0;"
		"movss %%xmm0, (%1,%0,8);"
		"movss (%2,%0,8), %%xmm0;"
		"movss (%5,%0,8), %%xmm1;"
		"addss %%xmm1, %%xmm0;"
		"movss %%xmm0, (%2,%0,8);"
		"movss (%3,%0,8), %%xmm0;"
		"movss (%6,%0,8), %%xmm1;"
		"addss %%xmm1, %%xmm0;"
		"movss %%xmm0, (%3,%0,8);"
		"inc %0;"
		"cmpq %0, %7;"
		"jg coordloop"
		: 
		: "r" (i), "r" (x),  "r" (y), "r" (z), 
		"r" (vx), "r" (vy), "r" (vz), "r" (size)
		: "memory", "cc" 
		);
}

//////////////////////// Main:
int main(int argc, char *argv[]){
	int size, iters;
	double *x, *y, *z, *vx, *vy, *vz;

	if( argc != 3 ) {
    	printf("Required arguments: vector_length(N) and iterations_num(M)");
    	return 0;
	}

	if (argc == 3) {
		size = atoi( argv[1] );
		iters = atoi( argv[2] );
	}

	srand(size);
	x = generate_random_list(size, 1000.);
	y = generate_random_list(size, 1000.);
	z = generate_random_list(size, 1000.);
	vx = generate_random_list(size, 1.);
	vy = generate_random_list(size, 1.);
	vz = generate_random_list(size, 1.);



	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i = 0;i<iters;i++){
		update_coords(x,y,z,vx,vy,vz,size);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double diff = 1000000000. * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	diff = diff / (1000.*size * iters);
	

	printf("Mean time per coordinate: %f us\n", diff);



	double chksum = sum(x,size) + sum(y,size) + sum(z,size);
	printf("Final checksum is: %f \n",chksum);
	return 0;
	}