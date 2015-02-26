#include <sys/queue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	SLIST_HEAD(slisthead, entry) head = SLIST_HEAD_INITIALIZER(head);
	struct entry {
		int id;
		char name[BUFSIZ];
		SLIST_ENTRY(entry) entries;
	} *el0, *np;

	SLIST_INIT(&head);

	el0 = malloc(sizeof(struct entry));
	if (el0 == NULL) {
		printf("Failed to malloc()\n");
		return 1;
	}
	el0->id = 0;
	strlcpy(el0->name, "youri", BUFSIZ);
	SLIST_INSERT_HEAD(&head, el0, entries);

	struct entry *el1;

	el1 = malloc(sizeof(struct entry));
	if (el1 == NULL) {
		printf("Failed to malloc()\n");
	}
	el1->id = 1;
	strlcpy(el1->name, "lelkek", BUFSIZ);
	SLIST_INSERT_AFTER(el0, el1, entries);

	SLIST_FOREACH(np,&head, entries)
	    printf("np->id = %d, np->name = %s\n", np->id, np->name);


	SLIST_REMOVE(&head, el0, entry, entries);
	SLIST_REMOVE(&head, el1, entry, entries);

	if (SLIST_EMPTY(&head)) {
		printf("list is empty\n");
	}

	if (el0 != NULL) {
		free(el0);
		el0 = NULL;
	}
	if (el1 != NULL) {
		free(el1);
		el1 = NULL;
	}
	if (np != NULL) {
		free(np);
		np = NULL;
	}
	return 0;
}

