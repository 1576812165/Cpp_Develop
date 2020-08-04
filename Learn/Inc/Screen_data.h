#ifndef SCREEN_DATA_H
#define SCREEN_DATA_H

#include <string>
#include <vector>

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


#endif // SCREEN_DATA_H
