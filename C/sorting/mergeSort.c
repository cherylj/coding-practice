// Author:  Cheryl Jennings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int max(int i1, int i2){
	if (i1 >= i2)
		return(i1);
	return(i2);
}

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

void mergeSort(int *a1, int a1s, int *a2, int a2s, int *result){
	int mid, i, leftSize, rightSize;
	int *left, *right;


	// Take care of the left side
	// If length > 1, recursively sort
	if(a1s > 1){
		mid = a1s / 2;
		left = a1;
		right = a1 + mid;
		leftSize = mid;
		rightSize = a1s - mid;

		mergeSort(left, leftSize, right, rightSize, result);
		copyBuf(a1, result, a1s);
	}	
	// Take care of right side
	// If length > 1, recursively sort
	if(a2s > 1){
		mid = a2s / 2;
		left = a2;
		right = a2 + mid;
		leftSize = mid;
		rightSize = a2s - mid;

		mergeSort(left, leftSize, right, rightSize, result);
		copyBuf(a2, result, a2s);
	}	

	// At this point, the right and left are both sorted.  Merge!
	i = 0;

	while(a1s && a2s){
		if(*a1 <= *a2){
			result[i++] = *a1;
			a1++;
			a1s--;
		}
		else{
			result[i++] = *a2;
			a2++;
			a2s--;
		}
	}

	// Now, at least one of the arrays is empty
	// copy the remaining
	
	while(a1s){
		result[i++] = *a1;
		a1++;
		a1s--;
	}
	while(a2s){
		result[i++] = *a2;
		a2++;
		a2s--;
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


	mergeSort(list, size, NULL, 0, result);

	for(i = 0; i < size; i++)
		printf("%d ", list[i]);

	printf("\n");
	
	return 0;
}
