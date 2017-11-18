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

void quickSort(int *start, int *end){
	int pivot;
	int tmp;
	int *s, *e;

	s = start;
	e = end;

	// do nothing if we're less than 2 elements
	if ((end - start) < 1)
		return;

	// pick a pivot
	pivot = start[(rand() % (end - start))];
	printf("Pivot is: %d\n", pivot);

	while(1){
		while(*start < pivot)
			start++;
		while(*end > pivot)
			end--;

		if(start != end){
			tmp = *start;
			*start = *end;
			*end = tmp;	
		}	
		else
			break;
	}

	// recursively sort the remaining pieces
	// start with the left
	quickSort(s, start-1);
	quickSort(end+1, e);
}

int binSearch(int *list, int size, int k){

	int midpoint;

	printf("Binary Search: %lx, %d, %d\n", (unsigned long)list,
		size, k);

	if(!list || size <=0)
		return -1;

	if(size == 1){
		if(list[0] == k)
			return k;
		return -1;
	}

	// find midpoint, and compare to k
	midpoint = size / 2;

	if(k <= list[midpoint - 1]){
		return(binSearch(list, midpoint, k));
	}

	return(binSearch(&list[midpoint], size - (midpoint), k));
}

	
int main(int argc, char *argv[])
{

	int size = 100;
	int list[100];
	int i;

	if (argc != 3)
	{
		printf("Usage: %s <filename> <search key>\n", argv[0]);
		return 1;
	}

	populate(argv[1], list, &size);

	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");

	quickSort(list, (list + (size - 1)));
	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");

	i = binSearch(list, size, atoi(argv[2]));
	printf("binSearch returned: %d\n", i);
	
	return 0;
}
