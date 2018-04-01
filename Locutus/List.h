#ifndef LIST_H
#define LIST_H

typedef struct _ListEntry_T {
	struct _ListEntry_T* Next;
	struct _ListEntry_T* Prev;
} ListEntry_T;

#define InitializeListHead(head) do { \
	(head)->Next = (head); \
	(head)->Prev = (head); \
} while(0);

#define InsertListTail(entry,head) do { \
	(entry)->Prev = (head)->Prev; \
	(head)->Prev->Next = (entry); \
	(head)->Prev = (entry); \
	(entry)->Next = (head); \
} while (0);

#define RemoveListEntry(entry) do { \
	(entry)->Next->Prev = (entry)->Prev; \
	(entry)->Prev->Next = (entry)->Next; \
} while (0);

#define ListEmpty(head) (head->Next == head)

#define ForEachInList(head,pos) \
	for (pos = (head)->Next; pos != (head); pos = pos->Next)

#endif
