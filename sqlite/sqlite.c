#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static sqlite3 *db;
static char *db_err = NULL;
static FILE *sql_log_fp;

int pdb_get_value(void *, int, char **, char **);
int pkgindb_doquery(const char *, int (*)(void *, int, char **, char **), void *);

int pdb_get_value(void *param, int argc, char **argv, char **columns) {
    char *value = (char *)param;

    if (argv != NULL) {
        strlcpy(value, argv[0], sizeof(value));
        return 0;
    }

    return -1;
}

int pkgindb_doquery(const char *query,
        int (*pkgindb_callback)(void *, int, char **, char **), void *param) {
    if (sqlite3_exec(db, query, pkgindb_callback, param, &db_err)
            != SQLITE_OK) {
        if (sql_log_fp != NULL) {
            if (db_err != NULL)
                fprintf(sql_log_fp, "SQL error: %s\n", db_err);
            fprintf(sql_log_fp, "SQL query: %s\n", query);
        }
        sqlite3_free(db_err);

        return -1;
    }
    return 0;
}

int main(void) {
    char query[BUFSIZ];
    if (sqlite3_open("/var/db/pkgin/pkgin.db", &db) != SQLITE_OK)
        return -1;
    else {
        char count[BUFSIZ];
        pkgindb_doquery("SELECT COUNT(PKG_ID) FROM REMOTE_PKG;", pdb_get_value, count);
        printf("%d\n", atoi(count));


        char count2[BUFSIZ];
        snprintf(query, BUFSIZ, "SELECT PKGNAME FROM REMOTE_PKG WHERE PKG_ID = %d;", 3);
        pkgindb_doquery(query, pdb_get_value, count2);
        printf("%s\n", count2);
    }
    sqlite3_close(db);
    db = NULL;
    return 0;
}

