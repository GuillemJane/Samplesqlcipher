Based on a sample from developers of SQLCipher; 
Helps checking that everything is working great in your environment. (c++)
It helped me I hope it helps you.
Avoid linking with (libsqlite3) -lsqlite3 in your binary at the same time because generates a core dump.

To compile it in Linux use "sh build.sh", check the location of your library this assumes it is under $HOME/lib 
To execute the sample "sh test.sh"

After runnig the test you could open demo.db with sqlcipher and check what has been created:

$HOME>sqlcipher
SQLCipher version 3.15.2 2016-11-28 19:13:37
Enter ".help" for instructions
Enter SQL statements terminated with a ";"
sqlite> PRAGMA key="demo";
sqlite> .schema
CREATE TABLE version(version_id integer primary key);
sqlite> select * from version;
5
