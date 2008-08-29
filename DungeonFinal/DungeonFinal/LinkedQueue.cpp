#include "LinkedQueue.h"

LinkedQueue::LinkedQueue(void)
{
	head = new(node);
	current = new(node);
	head->next = NULL;
	current = head;
}

LinkedQueue::~LinkedQueue(void)
{
}
void LinkedQueue::addToList(int i, int j)
{
	node *n;
	n = new (node);
	n->x = i;
	n->y = j;

	current->next = n;
	current = n;
	n->next = NULL;

}
void LinkedQueue::removeFromList(void)
{
	node *ptemp;

	ptemp = head->next;
	head->next = ptemp->next;

	delete(ptemp);
}
bool LinkedQueue::endOfList(void)
{
	if(head->next = NULL)
		return true;
	else 
		return false;
}
int LinkedQueue::getNodeY(void)
{
	return head->next->y;
}
int LinkedQueue::getNodeX(void)
{
	return head->next->x;
}
void LinkedQueue::printList(void)
{
	node* ptemp;
	ptemp = head;

	while(ptemp->next != NULL)
	{
		cout << ptemp->next->x << " X " << ptemp->next->y << " Y " << endl;
		ptemp = ptemp->next;
	}
}