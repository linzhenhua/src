/******************************************************************************
*    > File Name: 10.26.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月13日 星期五 20时59分41秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::multimap;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

int main(int argc, char **argv)
{
    multimap<string, string> bookauthor;
    string book;
    string author;

    do
    {
        cout << "enter author(ctrl+d to end):" << endl;
        cin >> author;
        
        if(!cin)
        {
            break;
        }

        cout << "enter author's book(ctrl+d to end): " << endl;
        while(cin >> book)
        {
            bookauthor.insert(make_pair(author, book));
        }
        cin.clear();
    }while(cin);
    cin.clear();

    string findAuthor;
    cout << "enter you want to find author:" << endl;
    cin >> findAuthor;
    multimap<string, string>::iterator iter = bookauthor.find(findAuthor);

    if(iter != bookauthor.end())
    {
        bookauthor.erase(findAuthor);
    }
    else
    {
        cout << "can not find author" << endl;
    }

    cout << "author\t\tbooks: " << endl;
    for(iter = bookauthor.begin(); iter != bookauthor.end(); ++iter)
    {
        cout << iter->first << "\t\t" << iter->second << endl;
    }

    return 0;
}
