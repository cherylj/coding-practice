#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void populate(char *fileName, int *list, int *size) {
	int fd, i, length, rc;
	char *buf, *c1, *c2;

	i = 0;

	buf = malloc(4096);
	if (!buf)
		printf("Unable to allocate memory: %d\n", errno);

	fd = open(fileName, O_RDWR);
	if (fd == -1){
		printf("Unable to open file: %s.  Error: %d\n",
			fileName, errno);
		free(buf);
		exit(errno);
	}
	
	length = read(fd, buf, 4096);	

	if(length == -1){
		printf("Error reading file: %d\n", errno);
		free(buf);
		exit(errno);
	}

	c1 = buf;
	while((c1 < (buf + length)) && (i < *size)){
		c2 = c1;
		while(*c2 != ' ' && *c2 != '\0')
			c2++;
		*c2 = '\0';
		list[i++] = atoi(c1);
		c1 = c2+1;
	}		

	*size = i;
	free(buf);

}

void swap(int *list, int idx1, int idx2){
	int tmp;

	tmp = list[idx1];
	list[idx1] = list[idx2];
	list[idx2] = tmp;
}

void bubbleSort(int *list, int size){
	int i;
	
	size--;

	while(size > 0){
		for(i = 0; i < size; i++){
			if(list[i] > list[i + 1])
				swap(list, i, i + 1);
		}

		size--;
	}	
	
}

	
int main(int argc, char *argv[])
{

	int size = 100;
	int list[100];
	int i;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	populate(argv[1], list, &size);

	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");

	bubbleSort(list, size);
	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");
	
	return 0;
}
