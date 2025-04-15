//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll)
{
	/*
	입력된 리스트에서 짝수 값을 모두 리스트 맨뒤로 보내야한다.
	1. 리스트 자체가 NULL인 경우를 예외처리로 리턴.
	2. 리스트 순회하면서 짝수이면 값을 따로 저장한 다음 제거하고 맨뒤에 추가한다.
	3. 다음 인덱스로 넘어가면서 체크, count를 따로 둬서 무한 루프 방지
	*/
	if(ll == NULL || ll->head == NULL){  // 예외처리
		return;
	}

	int index = 0;   // 현재 검사 중인 인덱스
	int count = 0;  // 반복 횟수 지정자
	int size = ll->size;  // 원래 크기 저장

	// 리스트 처음부터 끝까지 순회(무한 루프 방지와 범위 검사를 수행)
	while (count < size && index < size) {
		ListNode *node = findNode(ll, index);   // 현재 index에 해당하는 노드를 가져온다

		if (node == NULL) break;  // 안정성 확보: 노드가 NULL이면 종료
		
		if(node->item % 2 == 0){     // 나머지가 0이면,즉 짝수이면 처리
		int value = node->item;    // 값을 따로 저장해둠 (삭제하면 사라지기 때문)
		removeNode(ll, index);    // 해당 인덱스 제거
		insertNode(ll, ll->size, value);   // 맨뒤 다시 추가, 사이즈 이미 줄였어서 그 자리가 끝이다.
	
	// 삭제했기 때문에 같은 index에서 다시 검사(index 유지)
	} 
	else {
		index++;   // 짝수면 다음 index로 넘어감
	}   
	count++;   // 반복 횟수 증가
    }
}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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
