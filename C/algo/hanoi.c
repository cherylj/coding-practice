/*  This is a recursive solution to the classic Towers of Hanoi problem
 *  https://en.wikipedia.org/wiki/Tower_of_Hanoi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

struct disk {
	int value;
	struct disk* next;
	struct disk* prev;
};

struct disk *towers[3];

int numMoves = 0;

void printTowers(){
	struct disk *t1, *t2, *t3;

	t1 = towers[0];
	t2 = towers[1];
	t3 = towers[2];

	while((t1 != NULL) || (t2 != NULL) || (t3 != NULL)){
		printf("%d	%d	%d\n",
			((t1 != NULL)? t1->value : 0),
			((t2 != NULL)? t2->value : 0),
			((t3 != NULL)? t3->value : 0));
		if(t1 != NULL) t1 = t1->next;
		if(t2 != NULL) t2 = t2->next;
		if(t3 != NULL) t3 = t3->next;
	}
}

void move(int base, int target){
	struct disk *tmpptr;

	assert(towers[base] != NULL);
	assert(towers[target] == NULL || towers[target]->value > towers[base]->value);

	tmpptr = towers[base];
	towers[base] = tmpptr->next;
	if(towers[base])
		towers[base]->prev = NULL;
	tmpptr->next = towers[target];
	if(tmpptr->next)
		(tmpptr->next)->prev = tmpptr;
	towers[target] = tmpptr;

	printTowers();	
	printf("------------------------------\n");

	numMoves++;
	
}

void moveDisks(int base, int target, int spare, struct disk *dp){
	struct disk *tmpptr, *prev;

	if(dp->prev == NULL){
		move(base, target);
		return;
	}

	// Move disks above us, save our previous.
	prev = dp->prev;
	moveDisks(base, spare, target, dp->prev);
	move(base, target);

	// We know the target from our prev disk (spare),
	// that will now be the base.
	moveDisks(spare, target, base, prev);
}	


int main(int argc, char *argv[])
{

	struct disk *tmpptr, *tmpptr2;
	int size, tmp, target, spare;

	if (argc != 2)
	{
		printf("Usage: %s <num disks>\n", argv[0]);
		return 1;
	}

	// allocate disks
	size = atoi(argv[1]);
	if(size <=0 ){
		printf(" Nothing to move!\n");
		return(0);
	}

	towers[0] = malloc(sizeof(struct disk) * size);
	if(!towers[0]){
		printf("Unable to allocate memory: %d\n", errno);
		return(errno);
	}

	// initialize their values
	towers[1] = towers[2] = NULL;
	tmpptr = towers[0];

	for(tmp = 0; tmp < size; tmp++){
		if(tmp == 0)
			tmpptr->prev = NULL;
		else
			tmpptr->prev = tmpptr - 1;

		tmpptr->value = tmp+1;
		tmpptr2 = tmpptr;
		tmpptr2++;

		if(tmp == (size - 1))
			tmpptr->next = NULL;
		else
			tmpptr->next = tmpptr2;

		tmpptr = tmpptr2;
	}

	
	tmpptr = towers[0];
	while(tmpptr->next != NULL)
		tmpptr = tmpptr->next;

	moveDisks(0, 1, 2, tmpptr);

	printf("Number of moves was: %d\n", numMoves);
	return(0);
}
