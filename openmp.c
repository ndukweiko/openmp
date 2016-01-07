#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char* argv[])
{

  int niter = 1000000;//number of iterations per FOR loop
  double x,y;//x,y value for the random coordinate
  int i;//loop counter
  int count=0;//Count holds all the number of how many good coordinates
  double z;//Used to check if x^2+y^2<=1
  double pi;//holds approx value of pi
  
#pragma omp parallel private(x, y, z, i) reduction(+:count)
 {
    srand((int)time(NULL) ^ omp_get_thread_num());//Give random() a seed value
    for (i=0; i<niter; ++i)//main loop
      {
	x = (double)drand48();//gets a random x coordinate
	y = (double)drand48();//gets a random y coordinate
	z = ((x*x)+(y*y));//Checks to see if number is inside unit circle
	if (z<=1)
	  {
	    ++count;//if it is, consider it a valid random point
	  }
      }
  
  pi = 4.0 * ((double)count/(double)(niter));
 }
  printf("Pi: %f\n", pi);
  return 0;
}
