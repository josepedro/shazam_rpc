struct Buffer {
	float *buffer;
	int size;
};
program PROG {
	version VERSAO {
		string get_music_information(Buffer) = 1;
	} = 100;
} = 55555555;

