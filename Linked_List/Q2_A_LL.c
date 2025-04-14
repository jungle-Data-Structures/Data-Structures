//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;  // 노드에 저장될 실제 정수값
	struct _listnode *next;   // 다음 노드를 가리키는 포인터
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;   //리스트의 개수(노드 개수)
	ListNode *head;   // 첫 번째 노드를 가리킴
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

// ll1, ll2 두 개의 리스트를 생성 및 초기화
// 사용자 입력으로 리스트1 또는 2에 값 추가
// 두 리스트 병합, 프로그램 종료 및 메모리 해제 가능함.
int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    /*
	1. 두개의 연결 리스트를 받을 수 있어야한다.
	2. 리스트1의 각각의 수 사이에 리스트2의 수가 번갈아서 추가되야한다.(인덱스 재조정)
	3. 만약, 리스트2가 남는다면 남은 리스트2의 값을 출력한다.
	4. 결과로 리스트1과 리스트2를 출력한다.
	*/

	ListNode * L1 = ll1 -> head;  // L1을 리스트1으로 받음
	ListNode * L2 = ll2 -> head;  // L2을 리스트2으로 받음

	if(ll1 == NULL || ll2 == NULL){   // 리스트에 아무 것도 없을 떄의 예외처리
		return;
	}
	
	int index = 1; // 리스트 1에 끼워 넣을 위치 (처음은 1부터 시작)
	ListNode *temp; // L2에서 사용할 임시 포인터

	while (L1 != NULL && L2 != NULL) {
		// L2의 현재 값을 L1에 끼워 넣기
		insertNode(ll1, index, L2->item);

		// 다음 L1위치로 건너 뜀.(방금 삽입된 노드 다음부터 시작)
		L1 = findNode(ll1, index + 1);

		// temp로  L2 현재 노드 저장 후 다음 노드로 이동
		temp = L2;
		L2 = L2->next;

		// 끼워넣은 노드는 ll2에서 제거(free처리) 메모리 누수 방지
		free(temp);
		ll2->size--;

		// 다음 삽입 인덱스는 두 칸 뒤
		index += 2;
	}

	// 리스트2 헤드 갱신
	ll2->head = L2;

}

///////////////////////////////////////////////////////////////////////////////////

// 리스트의 모든 노드 값 출력
// 리스트가 비어 있으면 "Empty" 출력, 아니면 head부터 끝까지 순회하면서 item 출력
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

// 리스트 전체 노드를 순회하면서 전부 메모리 해제
// while문으로 하나씩 free하고 다음 노드로 이동
// 리스트 초기화 상태로 리셋(head=NULL, size=0)
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

//특정 위치의 노드를 반환
// 인덱스를 기준으로 리스트를 순회하며 해당 노드를 찾음
// 유효하지 ㅇ낳은 인덱스면 NULL 반환
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

// 특정 위치(index)에 새 노드 삽입, index == 0이면 첫 노드 삽입
// 그외엔 index -1 위치를 찾아 그 뒤에 새 노드 연결
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

// 특정 위치의 노드를 삭제
// index == 0일시 첫노드 삭제 후 head를 다음 노드로 바꾼다.
// 이전 노드를 찾아서 next포인터를 다음으로 건너뜀
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
