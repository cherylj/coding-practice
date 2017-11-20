// Author:  Cheryl Jennings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define HASHMASK 0xF
#define HASHVAL(x) (x & HASHMASK)
#define NUMBUCKETS 16
#define DEPTH 100

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
	printf("length: %d\n", length);

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

void printHtab(int array[NUMBUCKETS][DEPTH]){
	int i, j;

	if(!array)
		return;

	for(i = 0; i < NUMBUCKETS; i++){
		printf("Bucket %d:", i);
		for(j = 0; ((j < DEPTH) && (array[i][j] != 0)); j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}
}

void insert(int array[NUMBUCKETS][DEPTH], int idx1, int idx2, int val){
	
	int tmp1, tmp2;

	printf("Calling insert! %d\n", val);

	if(array[idx1][idx2] == 0){
		array[idx1][idx2] = val;
		return;
	}
		
	tmp1 = array[idx1][idx2];
	array[idx1][idx2] = val;
	idx2++;

	while((idx2 < DEPTH) && (array[idx1][idx2]) != 0){
		tmp2 = array[idx1][idx2];
		array[idx1][idx2] = tmp1;
		tmp1 = tmp2;
	}
}

int insertElement(int array[NUMBUCKETS][DEPTH], int val){
	int idx1, idx2;
	int end;

	printf("Inserting value: %d\n", val);

	idx1 = HASHVAL(val);
	printf("HASHVAL is: %d\n", idx1);

	for(idx2 = 0; ((idx2 < DEPTH) && (array[idx1][idx2] != 0)); idx2++){
		if(val < array[idx1][idx2])
			break;
	}

	if(idx2 == DEPTH)
		return(ENOSPC);

	insert(array, idx1, idx2, val);

	return(0);
}

	
int main(int argc, char *argv[])
{
	int size=100, i, rc;
	int list[100];
	int htab[NUMBUCKETS][DEPTH];

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	for(i = 0; i < NUMBUCKETS; i++)
		memset(htab[i], 0, DEPTH);

	populate(argv[1], list, &size);

	for(i = 0; i < size; i++){
		rc = insertElement(htab, list[i]);
		if(rc)
			printf("Failure inserting element: %d\n", list[i]);
	}

	printHtab(htab);

	return 0;
}
