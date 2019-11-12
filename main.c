#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main() {
	unsigned char BITS = sizeof(int);
	
	//create array of random numbers
	int rand[10];
	int random = open("/dev/random", O_RDONLY | O_TRUNC);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}
	int i;
	for (i=0; i < 10; i++) {
		read(random, &rand[i], BITS);
		printf("random %d: %d\n", i, rand[i]);
		if (errno) {
			printf("Error: %s\n", strerror(errno));
			return errno;
		}
	}
	close(random);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}

	//write array to file
	printf("Writing array to file...\n");
	random = open("randfile", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}
	write(random, rand, BITS * 10);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}
	close(random);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}

	//read array from file
	printf("Reading array from file...\n");
	random = open("randfile", O_RDONLY);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}
	int data[10];
	read(random, data, BITS * 10);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}
	close(random);
	if (errno) {
		printf("Error: %s\n", strerror(errno));
		return errno;
	}

	//print results of read
	printf("Result verification:\n");
	for (i=0; i < 10; i++) {
		printf("random %d: %d\n", i, data[i]);
	}

	return 0;
}
