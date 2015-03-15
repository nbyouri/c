#include <stdio.h>
#include <stdlib.h>
#include <list/list.h>
#include <sqlite3.h>

/*
 * Program that sets a pkgin remote package
 * list into an ArrayList.
 *
 */

/* pkgin db path */
#define PKGDB	"/var/db/pkgin/pkgin.db"

int main(void) {
	/* sql query */
	const char REMOTE_PACKAGE_LIST[] =
	    "SELECT FULLPKGNAME,PKGNAME,PKGVERS,"
	    "COMMENT,FILE_SIZE,SIZE_PKG,CATEGORIES,PKGPATH "
	    "FROM REMOTE_PKG "
	    "ORDER BY FULLPKGNAME ASC;";

	/* allocate memory for our list pointer */
	ArrayList *list;
	list = malloc(sizeof(*list));

	/* allocate memory for our head pointer */
	initList(list);

	/* index */
	unsigned int i = 0;

	/* execute sql query */
	sqlite3 *db;
	sqlite3_stmt *s = NULL;
	if (sqlite3_open(PKGDB, &db) == SQLITE_OK) {
		if (sqlite3_prepare_v2(db, REMOTE_PACKAGE_LIST,
			    -1, &s, NULL) == SQLITE_OK) {
			while (sqlite3_step(s) == SQLITE_ROW) {
				/* add sql query results in our list */
				list->obj = new(i++,sqlite3_column_text(s, 0));
				add(list, list->obj);
			}
		}

	}
	sqlite3_finalize(s);
	sqlite3_close(db);

	foreach(list) {
		toString(list->obj);
	}

	cleanList(list);

	free(list);
	list = NULL;
	return 0;
}
