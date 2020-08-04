#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>

class Sales_data {
//友元
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
friend std::istream& read(std::istream &is, Sales_data &item);
friend std::ostream& print(std::ostream &os, const Sales_data &item);

public:
    //Sales_data的构造函数
    Sales_data() = default;
    Sales_data(const std::string &s):bookNo(s){ }
    Sales_data(const std::string &s, unsigned int n, double p):
               bookNo(s), units_sold(n), revenue(n*p) { }
    Sales_data(std::istream &);

    //Sales_data的相关操作
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

private:
    //Sales_data的相关数据成员
    std::string bookNo;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};

Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
std::istream& read(std::istream &is, Sales_data &item);
std::ostream& print(std::ostream &os, const Sales_data &item);


#endif // SALES_DATA__H
