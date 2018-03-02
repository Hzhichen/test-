
#include "list.h"

// ��ʼ������
void init(plist_t pl)
{
	pl->head.next = NULL;
	pl->len = 0;
}

// ��ֵ����
pnode_t find(plist_t pl, pelem_t pe)
{
	pnode_t pnode = pl->head.next;

	// ������ͷ��ʼһ��һ�����ȶ�Ԫ��ֵ
	while (pnode)
	{
		// �ҵ�Ԫ��
		if (pnode->data == *pe)
		{
			break;
		}
		// δ�ҵ�Ԫ�أ���ָ����һ��
		pnode = pnode->next;
	}

	// ���ؽ��ָ�룬���δ�ҵ�����������Ϊ�գ��ͷ��� NULL
	return pnode;
}

// ��ͷ���룬�ص㣺������Ľ������ǰ��
void insert_head(plist_t pl, pelem_t pe)
{
	// Ϊ��Ԫ�ط�����ռ�
	pnode_t pnode = (pnode_t) malloc(sizeof (node_t));

	// ��Ԫ�ش�����
	pnode->data = *pe;

	// ������������ͷ
	pnode->next = pl->head.next;
	pl->head.next = pnode;

	// ��������
	pl->len++;
}

// ��β���룬�ص㣺�����а������˳������
void insert_tail(plist_t pl, pelem_t pe)
{
	pnode_t pt = &pl->head;
	// Ϊ��Ԫ�ط�����ռ�
	pnode_t pnode = (pnode_t) malloc(sizeof (node_t));
	
    // ��Ԫ�ش�����
    pnode->data = *pe;
	pnode->next = NULL;  // ������ next �����Ϊ NULL

	// �ҵ�β�����
	while (pt->next)
	{
		pt = pt->next;
	}
	// ���뵽β��
	pt->next = pnode;

	// ��������
	pl->len++;
}

// ��ͷɾ��
// ����ֵ��1 ɾ���ɹ���0 ɾ��ʧ��
int delete_head(plist_t pl, pelem_t pe)
{
	pnode_t pnode = pl->head.next;

	// ����Ϊ����ɾ��ʧ��
	if (is_empty(pl))
	{
		return 0;
	}

	// ȡ��Ԫ��ֵ
	*pe = pnode->data;

	// ������ͷɾ��ͷ���
	pl->head.next = pnode->next;

	// ����ɾ���Ľ��
	free(pnode);

	// �����Լ�
	pl->len--;

	// ���سɹ�
	return 1;
}

// ��ҵ����βɾ�� 
// ��ҵ���������
// ��ҵ����ת����
// ��ҵ����������������ԭ������һ��������

// ��������
void print(plist_t pl)
{
	pnode_t pnode = pl->head.next;

	while (pnode)
	{
		printf("%d  ", pnode->data);
		pnode = pnode->next;
	}

	printf("\n");
}

// �������������ϲ�
// �� la �� lb �ϲ��� lc���Ⱥϲ� la���ٺϲ� lb
void merge(plist_t lc, plist_t la, plist_t lb)
{
	pnode_t pt = NULL;

	// �Ƚ� la �ϲ��� lc
	lc->head.next = la->head.next;
	la->head.next = NULL;  // �Ͽ� la ��ԭͷ���
	
	// ���ҵ� lc ��β�����
	pt = &lc->head;
	while (pt->next)
	{
		pt = pt->next;
	}
	// ��� lb �ϲ��� lc β��
	pt->next = lb->head.next;
	lb->head.next = NULL;

	// ���� lc��la��lb ����
	lc->len = la->len + lb->len;
	la->len = 0;
	lb->len = 0;
}

// �������������ϲ�
// ������������������ la �� lb �ϲ��� lc
void merge_order(plist_t lc, plist_t la, plist_t lb)
{
	pnode_t pa = la->head.next, pb = lb->head.next, pc = &lc->head;
	
	// ��������û����ʱ�����н��ĺϲ�
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			la->head.next = pa->next;
			pc->next = pa;
			pa = la->head.next;
		}
		else
		{
			lb->head.next = pb->next;
			pc->next = pb;
			pb = lb->head.next;
		}
		pc = pc->next;
	}
	// ��û�н����ı��ʣ�ಿ�ֺϲ��� lc
	if (pa)
	{
		pc->next = pa;
		la->head.next = NULL;
	}
	if (pb)
	{
		pc->next = pb;
		lb->head.next = NULL;
	}
	// ���ó���
	lc->len = la->len + lb->len;
	la->len = 0;
	lb->len = 0;
}

// �ж������Ƿ�Ϊ��
// ����ֵ��1 ��գ�0 ��ǿ�
int is_empty(plist_t pl)
{
	return pl->len == 0;
}

