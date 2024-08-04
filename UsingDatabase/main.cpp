#include <iostream>
#include "mysql.h"


int main()
{
	if (mysql_get_client_info())
	{
		std::cout << "SQL ready\n";
	}

	MYSQL database;
	mysql_init(&database);

	MYSQL* handle = mysql_real_connect(&database, "127.0.0.1", "root", "root", "test1", 3306, nullptr, 0);
	if (!handle)
	{
		std::cout << "Failed to connect database\n";
		return -1;
	}

	std::cout << "Database connected\n";

	const char* query = "SELECT * FROM `test1`.`character`";

	if (mysql_query(handle, query))			// function : mysql_query return 0 when succeed, and if statement passes condition is 0.
	{
		const char* errMsg = mysql_error(handle);
		std::cout << "Query failed\n" << errMsg << std::endl;
		return -1;
	}

	std::cout << "Sending query\n";

	MYSQL_RES* result = mysql_store_result(handle);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		std::cout << row[0] << ", " << row[1] << std::endl;
	}
	mysql_free_result(result);
	mysql_close(handle);

}