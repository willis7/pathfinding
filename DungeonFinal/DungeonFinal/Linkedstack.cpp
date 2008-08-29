#include "Linkedstack.h"

Linkedstack::Linkedstack()
{
	head = new(node);
	current = new(node);
	head->next = NULL;
	current = head;

}
void Linkedstack::resetCurrent(void)
{
    current = head;
}

void Linkedstack::push(int i, int j)		//simple function to add node to end of list
{
	node *n;				//pointer to new node
	n = new(node);
	n->x = i;
	n->y = j;


	n->next = current->next;
	current->next = n;	
}

void Linkedstack::pop(void)
{
	node *ptemp;
	ptemp=current->next;
	if (current->next !=NULL)				 //can't delete anything after the end of the list!
	{
		current->next=current->next->next;  //current node's next pointer
											//leap frogs current next node
			  								// and therefore points to next but one node
        delete(ptemp);						//free memory associated with leap-frogged node
	}
}
bool Linkedstack::endOfList(void)
{
    if(current->next == NULL)
  	    return true;
    else 
	    return false;
}

int Linkedstack::getNodeX(void)
{
	return current->next->x;
}

int Linkedstack::getNodeY(void)
{

	return current->next->y;
}
void Linkedstack::printList(void)
{
	node* ptemp;
	ptemp = head;

	while(ptemp->next != NULL)
	{
		cout << ptemp->next->x << "X" << ptemp->next->y << "Y" << endl;
		ptemp = ptemp->next;
	}
}


