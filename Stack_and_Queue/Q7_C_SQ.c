//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct stack
{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int balanced(char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Enter a string:\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(str))
                printf("not balanced!\n");
            else
                printf("balanced!\n");
			break;
		case 0:
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
/*
주어진 소, 중, 대 괄호에 대해 짝이 맞는지 확인하여 짝이 맞다면 balanced를 출력합니다.
스택을 통해서 하나씩 순회하며 짝이 맞는지 확인합니다.
그 이후 짝이 맞으면 수를 1 올리고, 짝이 맞지 않으면 에러를 출력합니다.
*/
/*
Stack stack;
stack.ll.head = NULL;
stack.ll.size = 0;
int i = 0;

while(expression[i]) {
	char exp = expression[i];   // expression 자료형은 char

	// 여는 괄호 스택의 push
	if (exp == '(' || exp =='{' || exp =='[') {
		push(&stack, exp);
	}

	// 닫는 괄호 시, 스택에서 짝이 맞는지 확인후 pop
	else if (exp == ')' || exp == '}' || exp ==']') {
		if (isEmptyStack(&stack))
		return 1;

		char top = peek(&stack);

		if ((exp == ')' && top == '(') || (exp == '}'  && top == '{') || (exp == ']'  && top == '[')) {
			pop(&stack);
		}
		else {
			return 1;
		}
	}
	i++;
}
// 모든 괄호가 정상적으로 짝이 맞으면 스택은 비워 있어야한다. 중복이면 안되므로
return isEmptyStack(&stack) ? 0 : 1;
}
*/


Stack stack;
stack.ll.head = NULL;
stack.ll.size = 0;
int i = 0;

// ASCII코드  () -> 40,41   [] -> 91,93   {} -> 123,125 
while(expression[i])
{
	char exp = expression[i];   
    // expression 자료형은 char로 아스키코드가 담길 것이다.
	// 해당부분에서 현재 읽고 있는 닫힌 괄호.

	if(peek(&stack) == exp -1 || peek(&stack) == exp -2)	
    // ASCII 코드에서 1, 2차이 나는 경우
	// peek(&stack) 부분에서 마지막에 들어간 열린 괄호 검사
	// []일시, 91 == 93 - 2 가 성립되므로 pop
		pop(&stack);

	else     
    // 그외에 경우 처리(push)
		push(&stack,exp);
	
	i += 1;    // 다음 인자 확인
}

if(isEmptyStack(&stack))
	return 0;  // 스택이 비었으면 균형이 잡힘을 출력
else
	return 1;
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;

	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
