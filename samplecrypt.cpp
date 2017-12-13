#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

int main ()
{
	int rc;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *password = "demo";

	rc = sqlite3_open ("demo.db", &db);
	if (rc != SQLITE_OK)
	{
		printf ("failed to open database\n");
	}
    else
    {
		printf ("Open database demo.db OK\n");
    }

	rc = sqlite3_key (db, password, strlen (password));
	if (rc != SQLITE_OK)
	{
		printf ("failed to key database\n");
	}
    else
    {
		printf ("Defining password demo to database demo.db OK\n");
    }

	rc =
		 sqlite3_exec (db,
		 "create table if not exists version(version_id integer primary key);", 0,
		 0, NULL);
	if (rc != SQLITE_OK)
	{
		printf ("failed to create version table\n");
	}
    else
    {
		printf ("Creating table version OK\n");
    }

	rc =
		 sqlite3_exec (db, "insert into version(version_id) values(5);", 0, 0,
		 NULL);
	if (rc != SQLITE_OK)
	{
		printf ("failed to insert data into version table\n");
	}
    else
    {
		printf ("Inserting record into table version OK\n");
    }

	if (db != NULL)
	{
		sqlite3_close (db);
	}

	rc = sqlite3_open ("demo.db", &db);
	if (rc != SQLITE_OK)
	{
		printf ("failed to open database\n");
	}
	rc = sqlite3_key (db, password, strlen (password));
	if (rc != SQLITE_OK)
	{
		printf ("failed to key database\n");
	}
    else
    {
        printf("Closing and oppening again with password OK\n");
    }

	rc = sqlite3_exec (db, "PRAGMA synchronous = OFF;", 0, 0, NULL);
	if (rc != SQLITE_OK)
	{
		printf ("failed to set syncrhronous to OFF\n");
	}
	rc = sqlite3_exec (db, "PRAGMA journal_mode = MEMORY;", 0, 0, NULL);
	if (rc != SQLITE_OK)
	{
		printf ("failed to set journal mode to MEMORY\n");
	}
	rc = sqlite3_prepare (db, "select count(*) from version;", -1, &stmt, NULL);
	rc = sqlite3_step (stmt);
	if (rc == SQLITE_ROW)
	{
		printf ("Current version:%s, register recovered OK\n", sqlite3_column_text (stmt, 0));
	}
	sqlite3_finalize (stmt);
	if (db != NULL)
	{
		sqlite3_close (db);
	}
	return 0;
}
