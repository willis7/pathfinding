#pragma once
#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#define NULL 0

class LinkedQueue
{
private:

	typedef struct nodetag{
		int x, y;
		nodetag *next;
	}node;

	node *head;
	node *current;

public:
	LinkedQueue(void);
	~LinkedQueue(void);

	void addToList(int, int);
	void removeFromList(void);
	bool endOfList(void);

	int getNodeY(void);
	int getNodeX(void);
};
#endif
