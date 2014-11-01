#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <sndfile.h>
 
typedef struct _buffer{
    float *buffer;
    int size;
} Buffer;

Buffer *get_music_buffer(char *name_file){
    SF_INFO info;
    SNDFILE *sf;
    sf = sf_open(name_file,SFM_READ,&info);
    if (sf == NULL){
        printf("Failed to open the file.\n");
        exit(-1);
    }
    Buffer *buffer = malloc(sizeof(Buffer));
    buffer->size = info.frames*info.channels;
    buffer->buffer = (float *) malloc(buffer->size*sizeof(float));
    sf_read_float(sf,buffer->buffer,buffer->size);
    sf_close(sf);
    return buffer;
}

float calculate_mean(Buffer *buffer){
    //Calculating the mean array
    int i;
    float sum = 0;
    for (i = 0; i < buffer->size; ++i){
        sum = sum + buffer->buffer[i];
      //printf("\n%f\n",sum);
    }
    sum = sum/buffer->size;
    //printf("%f\n", sum);
    return sum;
}

float calculate_covariance(Buffer *bufferX, Buffer *bufferY){
    float meanX  = calculate_mean(bufferX);
    float meanY  = calculate_mean(bufferY);
    int i;
    float covariance = 0;
    for (i = 0; i < bufferX->size; ++i){
        covariance = covariance + (bufferX->buffer[i] - meanX)*(bufferY->buffer[i] - meanY);
    }
    //printf("\n%f\n", covariance);
    return covariance;
}

float calculate_correlation_pearson(Buffer *bufferX, Buffer *bufferY){
    float standart_deviationX = sqrt(calculate_covariance(bufferX, bufferX));
    //printf("\n%f\n", standart_deviationX);
    float standart_deviationY = sqrt(calculate_covariance(bufferY, bufferY));
    //printf("\n%f\n", standart_deviationY);
    float correlation = calculate_covariance(bufferX, bufferY);
    float normalization_part = standart_deviationX*standart_deviationY;
    correlation = correlation/normalization_part;
    //printf("\ncorrelation: %f\n", correlation);
    return correlation;
}

void get_music_information(Buffer *buffer){
    Buffer *music_1 = (Buffer *) get_music_buffer("i_can_see.wav");
    Buffer *music_2 = (Buffer *) get_music_buffer("oh_darling.wav");
    Buffer *music_3 = (Buffer *) get_music_buffer("smoke_on_the_water.wav");
    float correlation_1 = calculate_correlation_pearson(buffer, music_1);
    correlation_1 = sqrt(correlation_1*correlation_1);
    float correlation_2 = calculate_correlation_pearson(buffer, music_2);
    correlation_2 = sqrt(correlation_2*correlation_2);
    float correlation_3 = calculate_correlation_pearson(buffer, music_3);
    correlation_3 = sqrt(correlation_3*correlation_3);

    printf("\n%f\n", correlation_1);
    printf("\n%f\n", correlation_2);
    printf("\n%f\n", correlation_3);

}

int main(int argc, char *argv[]){

    char *music_to_know = argv[1];

    Buffer *buffer = get_music_buffer(music_to_know);
    /*printf("\n%d\n", buffer->size);
    int i;
    for (i = 0; i < buffer->size; ++i)
    {
        printf("%f\n", buffer->buffer[i]);
    }*/
    get_music_information(buffer);
/*
	SNDFILE *sf;
    SF_INFO info;
    int num_channels;
    int num, num_items;
    int *buf;
    int f,sr,c;
    int i,j;
    FILE *out;
    
    info.format = 0;
    sf = sf_open("A440.wav",SFM_READ,&info);
    if (sf == NULL)
        {
        printf("Failed to open the file.\n");
        exit(-1);
        }
    f = info.frames;
    sr = info.samplerate;
    c = info.channels;
    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
    num_items = f*c;
    printf("num_items=%d\n",num_items);
    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(sf,buf,num_items);
    sf_close(sf);
    printf("Read %d items\n",num);

    //float buffer[num_items];
    Buffer *buffer = (Buffer *) malloc(sizeof(Buffer));
    buffer->buffer = (float *) malloc(num_items*sizeof(float));
    buffer->size = num_items;
    //printf("\n%d\n",sizeof(buffer)/sizeof(int));
    int max = 0;
    for (i = 0; i < num; i += c){
        for (j = 0; j < c; ++j){
            buffer->buffer[i+j] = (float) buf[i+j]/1000000000;
            //printf("\n%f\n",buffer[i+j]);
            if (buf[i+j] > max){
                max = buf[i+j];
                //printf("\n%f\n",buffer[i+j]);
            }
        }
    }
    printf("asdasdasdasd: %d\n",buffer->size);
    get_music_buffer("A440.wav");

    //get_music_information(buffer, num_items);

  */ 
 
	return 0;
}