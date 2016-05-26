//addFront

DequeNode *newPtr = new DequeNode;
newPtr->item = obj;
newPtr->next = front;
newPtr->prev = NULL;

if (isEmpty())
back = newPtr;
else
front->prev = newPtr;

front = newPtr;


//removeBack

Object backItem = getBack()l

DequeNode *old = back;
if (front == back)
front = back = NULL;
else {
	back = back->prev;
	back->next = NULL;
}

delete old;
return backItem;

