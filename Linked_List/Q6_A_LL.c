//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    /*
	리스트에서 가장 큰 요소가 앞에 위치해서 출력하면 된다.
	입력 받은 리스트에서 max인 값을 뽑아서 맨 앞으로 보내기 위해
	temp에 저장하고 나머지 값을 차례대로 입력하여 출력하면 될 것 같다.
	헤드를 순회하면서 제일 높은 값을 추출해야 좋을 것 같다.
	GPT한테 물어보니 연결만 바꿔주면 된다고 한다.
	*/

	if(ptrHead == NULL || *ptrHead == NULL || (*ptrHead)->next == NULL){    // 만약에 빈 리스트이거나 노드 1개일때 처리
		return 0;
	}

	ListNode *maxNode = *ptrHead;  // 최대값을 가진 노드를 저장할 포인터, 처음엔 head로 시작
	ListNode *maxPrev = NULL;      // 최대 노드의 이전 노드를 저장할 포인터 (연결 변경용)

	ListNode *prev = NULL;         // 현재 노드의 이전 노드 추적용 포인터
	ListNode *curr = *ptrHead;     // 현재 순회 중인 노드를 가리키는 포인터

	// 최대값 찾기
	while(curr != NULL) {
		if(curr->item > maxNode->item){
			maxNode = curr;     // 더 큰 값을 발견하면 maxNode 갱신
			maxPrev = prev;     // 그리고 그 노드의 이전 노드도 기억해둠(전 노드로 이동시 사용)
		}
		prev = curr;            // prev를 현재 노드로 이동
		curr = curr->next;      // 다음 노드로 이동
	}

	// 최댓값이 이미 맨 앞(head)에 있다면 그대로 진행
	if(maxPrev == NULL) {
		return 0;
	}

	// maxNode를 기존 위치에서 제거 (이전 노드의 next를 다음 노드로 연결)
	maxPrev -> next = maxNode -> next;

	// maxNode를 리스트 맨 앞에 삽입
	maxNode->next = *ptrHead;
	*ptrHead = maxNode;

	return 1;    // 작업 성공 시 1 반환
}

//////////////////////////////////////////////////////////////////////////////////

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
