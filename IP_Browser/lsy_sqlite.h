#pragma once

#include <vector>
#include <string>

#include "sqlite3.h"

namespace LSY
{

	class SQLite3
	{

	public:
		struct Table
		{
			std::vector<std::string> column_names;
			std::vector<std::vector<std::string>> data; //data[row][col]

			void clear()
			{
				column_names.clear(); data.clear();
			}
				
			int num_rows()
			{
				return data.size();
			}
				
		};


	public:
		std::string db_path_;
		std::string last_error_msg_;
		std::string last_query_;


	public:
		SQLite3();
		SQLite3(const std::string &db_path);
		~SQLite3();


	public:
		bool GetTable(const std::string &query, Table &result);

	public:
		static int callback(void *data, int col_nums, char **col_data, char **col_names);

	};

}





