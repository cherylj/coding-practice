// Author:  Cheryl Jennings

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

void printBuf(int *p, int s) {
	if(s < 1)
		printf("---");

	while(s){
		printf("%d ", *p);
		p++;
		s--;
	}
	printf("\n");
}

void copyBuf(int *dest, int *src, int num){
	int i = 0;
	while(num > 0){
		dest[i] = src[i];
		num--;
		i++;
	}
}	

void selectionSort(int *p, int s){
	int cur = 0, search = 0;
	int tmp, tmpVal;

	if (s <= 1)
		return;

	while(cur < (s-1)){
		tmp = search = cur;
		while(search < s){
			if(p[search] < p[tmp])
				tmp = search;
			search++;
		}
		tmpVal = p[tmp];	
		p[tmp] = p[cur];
		p[cur] = tmpVal;
		cur++;

		printBuf(p, cur);
	}
}

	
int main(int argc, char *argv[])
{

	int size = 100;
	int list[100];
	int result[100];
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

	printf("Starting Size: %d\n", size);


	selectionSort(list, size);

	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");
	
	return 0;
}
