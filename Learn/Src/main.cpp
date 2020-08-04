//#include "Sales_data.h"
//#include "Screen_data.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::end;

int main()//(int argc, char *argv[])
{
    int a[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};   
    vector<int> va(a,end(a));

    auto ruslt = find(va.begin(), va.end(), 1);




    return 0;
}


//    vector <int> number{1,2,3,4,5,6,7,8,9};
//
////    for(auto &i:number)
////    {
////        i += i;
////    }
//
//    for (auto it= number.cbegin();
//         it != number.cend(); it++)
//    {
//        cout << *it << endl;
//    }
//
//    auto beg = number.begin(), end = number.end();
//    auto mid = beg + (end - beg)/2;
//
//    cout << *beg << " " << *mid << endl;
//
//    while (mid != end && *mid != 3)
//    {
//        if (3 < *mid)
//            end = mid;
//        else
//            beg = mid + 1;
//
//        mid = beg + (end - beg)/2;
//    }
//
//    cout << *mid << endl;

//  Sales_data total;
//
//  if (read(cin,total)){
//      Sales_data trans;
//
//      if(read(cin,trans)){
//            if (trans.isbn() == total.isbn()){
//                total.combine(trans);
//                print(cout,total);
//            }else{
//                   print(cout,total);
//                   print(cout,trans);
//            }
//
//      }else print(cout,total);
//  }

//  string str;
//
//  for (int i = 1;i != argc;i++){
//       str += argv[i];
//       str += " ";
//  }
//
//  cout << str << endl;