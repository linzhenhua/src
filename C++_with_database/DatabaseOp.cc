#include <iostream>
#include <string>
#include <mysql.h>

#include "DatabaseOp.h"

bool DatabaseOp::InsertDataToDatabase()
{
    MYSQL mysql;
    MYSQL *con = NULL;
    int res = 0;

    con = mysql_init(&mysql);   //初始化句柄
    if(NULL == con)
    {
        std::cout << "mysql_init() errno: " << mysql_errno(&mysql) << ", error: " << mysql_error(&mysql) << std::endl;
        return false;
    }

    con = mysql_real_connect(&mysql, "localhost", "root", "", "test", 3305, NULL, 0);    //连接到数据库
    if(NULL == con) 
    {
        std::cout << "mysql_real_connect() errno: " << mysql_errno(&mysql) << ", error: " << mysql_error(&mysql) << std::endl;
        mysql_close(&mysql);
        return false;
    }
    std::string insertSQL;
    //插入10000数据
    for(int i = 0; i < 10; ++i)
    {
        insertSQL = "insert into emp(number)values(" + std::to_string(i) + ")";      //C++11 std::to_string
        
        res = mysql_query(&mysql, insertSQL.c_str()); 
        if(0 != res)
        {
            std::cout << "mysql_query() errno: " << mysql_errno(&mysql) << ", error: " << mysql_error(&mysql) << std::endl;
            mysql_close(&mysql);
            return false;
        }
    }

    mysql_close(&mysql);
    return true;
}

bool DatabaseOp::WriteDataToStr()
{
    //读取MySQL数据库的表

    return false;
}

bool DatabaseOp::WriteDataToFile()
{
    return false;
}
