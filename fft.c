#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <sndfile.h>
 
typedef int complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	double PI = atan2(1, 1) * 4;
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 		
 		int i;
		for (i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	int i;
	for (i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, cplx buf[]) {
	printf("%s", s);
	int i;
	for (i = 0; i < 8; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}
 
int main(){

	SNDFILE *sf;
    SF_INFO info;
    int num_channels;
    int num, num_items;
    int *buf;
    int f,sr,c;
    int i,j;
    FILE *out;
    
    /* Open the WAV file. */
    info.format = 0;
    sf = sf_open("A440.wav",SFM_READ,&info);
    if (sf == NULL)
        {
        printf("Failed to open the file.\n");
        exit(-1);
        }
    /* Print some of the info, and figure out how much data to read. */
    f = info.frames;
    sr = info.samplerate;
    c = info.channels;
    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
    num_items = f*c;
    printf("num_items=%d\n",num_items);
    /* Allocate space for the data to be read, then read it. */
    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(sf,buf,num_items);
    sf_close(sf);
    printf("Read %d items\n",num);

    cplx signal_in[num_items];

    for (i = 0; i < num; i += c){
	    for (j = 0; j < c; ++j){
	    	signal_in[i+j] = buf[i+j];
	    }
    }
	//cplx buf1[] = {1, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0};
	show("Data: ", signal_in);
	fft(signal_in, 8);
	show("\nFFT : ", signal_in);
	printf("\n\n%d\n\n", 3/2);
 
	return 0;
}