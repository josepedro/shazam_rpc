struct Buffer{
	int size;
	float buffer[44100];
};

program PROG {
	version VERSAO {
		string get_music_information(Buffer *) = 1;
	} = 100;
} = 55555555;

