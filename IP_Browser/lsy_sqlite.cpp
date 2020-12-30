#include "lsy_sqlite.h"

using namespace LSY;

SQLite3::SQLite3()
{

}

SQLite3::SQLite3(const std::string &db_path)
{
	db_path_ = db_path;
}

SQLite3::~SQLite3()
{

}

int SQLite3::callback(void *data, int col_nums, char **col_data, char **col_names)
{
	Table *table_ptr = (Table *)data;

	std::vector<std::string> column_data_vec;

	bool is_col_names_empty = table_ptr->column_names.empty();

	for (int i = 0; i < col_nums; i++)
	{
		// Add column names to table if not already added
		if (is_col_names_empty)
		{
			table_ptr->column_names.push_back(std::string(col_names[i]));
		}

		column_data_vec.push_back(std::string(col_data[i]));
	}

	// Add column to table
	table_ptr->data.push_back(column_data_vec);

	return 0;

}


bool SQLite3::GetTable(const std::string &query, Table &result)
{
	bool ret = true;
	last_query_ = query;
	result.clear();

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	
	/* Open database */
	rc = sqlite3_open(db_path_.c_str(), &db);

	if (rc)
	{
		last_error_msg_ = std::string(sqlite3_errmsg(db));
		ret = false;
		return ret;
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, last_query_.c_str(), SQLite3::callback, (void*)&result, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		last_error_msg_ = std::string(zErrMsg);
		sqlite3_free(zErrMsg);
		ret = false;
	}

	/* Close database */
	sqlite3_close(db);

	return ret;
}

