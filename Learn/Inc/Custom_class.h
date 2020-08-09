#ifndef CUSTOM_CLASS_H
#define CUSTOM_CLASS_H

#include <iostream>
#include <string>
#include <vector>


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

    //Sales_data的拷贝构造函数
    Sales_data(const Sales_data& orig) :
        bookNo(orig.bookNo),          //使用string的拷贝构造函数
        units_sold(orig.units_sold),  //内置类型的，直接拷贝
        revenue(orig.revenue) {};
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




/*******************************************************************************************************/

class Screen_data{
friend class Windows_mgr;

public:
    typedef std::string::size_type pos;

    //构造函数
    Screen_data() = default;
    Screen_data(pos ht, pos wd, unsigned char c):
                height(ht), width(wd), contents(ht*wd,c) { }

    //成员函数
    unsigned char get() const { return contents[cursor];  }
    inline unsigned char get(pos ht, pos wd) const;
    Screen_data& move(pos r,pos c);
    Screen_data& set(unsigned char ch);
    Screen_data& set(pos r, pos col, unsigned char ch);
    void some_member() const { ++access_ctr; }
    Screen_data& display(std::ostream &os) { do_display(os);  return *this; }
    const Screen_data& display(std::ostream &os) const { do_display(os);  return *this; }

private:
    void do_display(std::ostream &os) const { os << contents; }


    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable pos access_ctr = 0;
};


class Windows_mgr{
public:
    using ScreenIndex = std::string::size_type;//typedef std::string::size_type ScreenIndex;
    void clear(ScreenIndex);

private:
    std::vector<Screen_data> screens{Screen_data(24,80,' ')};
};

unsigned char Screen_data::get(pos r, pos c) const
{
    pos row = r * width;

    return contents[row + c];
}

inline Screen_data& Screen_data::move(pos r, pos c)
{
    pos row = r * width;

    cursor = row + c;

    return *this;
}

inline Screen_data& Screen_data::set(unsigned char ch)
{
    contents[cursor] = ch;

    return *this;
}

inline Screen_data& Screen_data::set(pos r, pos col, unsigned char ch)
{
    contents[r * width + col] = ch;

    return *this;
}

void Windows_mgr::clear(ScreenIndex i)
{
    Screen_data &s = screens[i];

    s.contents = std::string(s.height * s.width, ' ');
}


/************************************************************************************************************/
//行为像值的类
//class Hasptr {
//public:
//    //构造函数
//    Hasptr(const std::string& s = std::string()) :
//        ps(new std::string(s)), i(0) { }
//
//    //拷贝构造函数
//    Hasptr(const Hasptr& p) :
//        ps(new std::string(*p.ps)), i(p.i) { }
//
//    //拷贝赋值函数
//    Hasptr& operator= (const Hasptr&);
//
//    //析构函数
//    ~Hasptr() { delete ps; }
//private:
//    std::string *ps;
//    int i;
//};
//
//Hasptr& Hasptr::operator=(const Hasptr& rhs)
//{
//    auto newp = new std::string(*rhs.ps);
//    delete ps;
//    ps = newp;
//    i = rhs.i;
//    return *this;
//}

//行为像指针的类
class Hasptr {
public:
    //构造函数
    Hasptr(const std::string& s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    //拷贝构造函数
    Hasptr(const Hasptr &p):
        ps(p.ps), i(p.i), use(p.use) { ++*use;}
    //拷贝赋值函数
    Hasptr& operator= (const Hasptr& rhs);
    //析构函数
    ~Hasptr();

private:
    std::string *ps;
    int i;
    std::size_t *use;
};

Hasptr& Hasptr::operator= (const Hasptr &rhs)
{
    ++ *rhs.use; //递增右侧运算对象的引用计数
    if (-- *use == 0) { //递减本对象的引用计数
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

Hasptr::~Hasptr()
{
    if (-- * use == 0) {
        delete ps;
        delete use;
    }
}













#endif // CUSTOM_CLASS_H
