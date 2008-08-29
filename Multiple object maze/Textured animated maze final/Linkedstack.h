#pragma once
#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#define NULL 0

class Linkedstack
{
private:

	typedef struct nodetag{
		int x, y;
		nodetag *next;
	}node;

	node *head;
	node *current;

public:
	Linkedstack();
	
	void push(int, int);
	void pop(void);
	void resetCurrent(void);
	bool endOfList(void);
	int getNodeY(void);
	int getNodeX(void);

};
#endif