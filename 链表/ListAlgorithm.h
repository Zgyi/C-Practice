#pragma once

#include "ListTest.h"

/*
	����ת

	����: 1->2->3->4->5->NULL
	���: 5->4->3->2->1->NULL
*/

// ����ʽ
ListNode* reverseList(ListNode* head);

// �ݹ�ʽ
ListNode* recursionFuncList(ListNode* preNode, ListNode* curNode);
// ���
ListNode* reverseListInRecursion(ListNode* head);