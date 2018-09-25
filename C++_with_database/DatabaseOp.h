#ifndef DATABASEOP_H
#define DATABASEOP_H

#include <string>

class DatabaseOp {
    public:
       DatabaseOp(const std::string &str = "database.txt"):fileName_(str), data_(""), quotient_(0), mod_(0){}
       DatabaseOp(const DatabaseOp &rhs):fileName_(rhs.fileName_), data_(rhs.data_), quotient_(rhs.quotient_), mod_(rhs.mod_){}
       DatabaseOp& operator=(const DatabaseOp &rhs)
       {
           fileName_ = rhs.fileName_;
           data_ = rhs.data_;
           quotient_ = rhs.quotient_;
           mod_ = rhs.mod_;

           return *this;
       }

       ~DatabaseOp(){}

    public:
       //数据插入到表中
       bool InsertDataToDatabase();
        //写数据字符串中
        bool WriteDataToStr();
        //数据写到文件中
        bool WriteDataToFile();
    private:
        std::string fileName_;
        std::string data_;
        int quotient_;
        int mod_;
};

#endif
