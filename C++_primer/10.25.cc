/******************************************************************************
*    > File Name: 10.25.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月13日 星期五 19时10分06秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;

int main(int argc, char **argv)
{
    vector<string> books;
    set<string> readedbooks;
    string name;

    //建立保存未来6个月要阅读的书名的vector对象
    cout << "enter names for books you'd like to read(ctrl+d to end):" << endl;
    while(cin >> name)
    {
        books.push_back(name);
    }

    cin.clear();   //使流对象重新有效

    bool timeOver = false;
    string answer, bookName;
    
    //用当前系统时间设置随机数发生器种子
    srand((unsigned)time(NULL));

    //模拟随时间的流逝而改变读书记录
    while(!timeOver && !books.empty())
    {
        //时间未到6个月且还有书没有读过
        cout << "would you like to read a book?(yes/no)" << endl;
        cin >>answer;
        if(answer[0] == 'Y' || answer[0] == 'y')
        {
            //在vector中随机选择一本书
            int i = rand() % books.size();    //产生一个伪随机数
            bookName = books[i];
            cout << "you can read this book: " << bookName << endl;
            readedbooks.insert(bookName);  //将该书放入已读集合
            books.erase(books.begin()+i);  //从vector对象中删除该书

            cout << "did you read it?(yes/no)" << endl;
            cin >> answer;
            if(answer[0] == 'N' || answer[0] == 'n')
            {
                //没有读这本书
                readedbooks.erase(bookName);
                books.push_back(bookName);
            }
        }/*end of if(answer[0] == 'Y' || answer[0] == 'y')*/

        cout << "time over?(yes/no)" << endl;
        cin >>answer;
        if(answer[0] == 'Y' || answer[0] == 'y')
        {
            timeOver = true;
        }
    }/*end of while(!timeOver && !books.empty())*/

    //虚拟的6个月结束了
   if(timeOver) 
   {
       //输出已读书目
       cout << "book read:" << endl;
       for(set<string>::iterator sit = readedbooks.begin(); sit != readedbooks.end(); ++sit)
       {
           cout << *sit << endl;
       }
       //输出还没有读的书目
       cout << "books not read:" << endl;
       for(vector<string>::iterator vit = books.begin(); vit != books.end(); ++vit)
       {
           cout << *vit << endl;
       }
   }
   else
   {
       cout << "congratulations! you have read all these books." << endl;
   }

    return 0;
}
