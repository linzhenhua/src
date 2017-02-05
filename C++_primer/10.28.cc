/******************************************************************************
*    > File Name: 10.28.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月14日 星期六 14时44分08秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::multimap;
using std::pair;

int main(int argc, char **argv)
{
    multimap<string, string> authors;
    string author;
    string books;

    //建立作者及其作品的multimap容器
    do
    {
        cout << "enter author name(ctrl+d to end):" << endl;
        cin >> author;
        if(!cin)
            break;

        cout << "enter author's books(ctrl+d to end):" << endl;
        while(cin >> books)
        {
            authors.insert(make_pair(author, books));
        }
        cin.clear();

    }while(cin);

    cout << "============================================================================" << endl;

    //输出multimap对象
    typedef multimap<string, string>::iterator itType;
    itType iter = authors.begin();
    if(iter == authors.end())
    {
        cout << "empty multimap" << endl;
        return -1;
    }

    string currAuthor, preAuthor;   //当前作者和前一个作者

    do
    {
        currAuthor = iter->first;   //取键
        pair<itType, itType> pos = authors.equal_range(currAuthor);

        if(preAuthor.empty() || currAuthor[0] != preAuthor[0])
        {
            cout << "Author Names Beginning with '" << iter->first[0] << "': " << endl;

            //输出作者
            cout << currAuthor;

            //输出作者的作品
            while(pos.first != pos.second)
            {
                cout << ", " << pos.first->second;
                ++pos.first;
            }
            cout << endl;   //输出完一个作者的所有作品
        }/*end to if(preAuthor.empty() || currAuthor[0] != preAuthor[0])*/

        iter = pos.second;    //关键的一步，是iter指向下一个作者
        preAuthor = currAuthor;   //将当前作者设置为上一个作者

    }while(iter != authors.end());

    return 0;
}
