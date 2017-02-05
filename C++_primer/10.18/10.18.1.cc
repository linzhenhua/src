/******************************************************************************
*    > File Name: 10.18.1.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月13日 星期五 10时47分35秒
*    >Revision: none
*    >Compiler: gcc
*
*    > Author: linzhenhua
*    > Mail: linzhenhualzh@163.com 
*    > Company: 
*
******************************************************************************/
//定义一个map对象，其元素的键是家族姓氏，
//而值则是存储该家族孩子名字的vector对象。
//进行基于家族姓氏的查询，输出该家族所有孩子的名字
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::pair;
using std::string;

int main(int argc, char **argv)
{
    map<string, vector<string> > children;
    string surname, childName;

    //读入条目（家族姓氏及其所有孩子的名字）
    do
    {
        cout << "enter surname(ctrl+d to end):" << endl;
        cin >> surname;
        if(!cin)   //读入结束
            break;
        //插入新的条目
        vector<string> chd;
        pair<map<string, vector<string> >::iterator, bool> ret = 
            children.insert(make_pair(surname, chd));

        if(!ret.second) //该家庭姓氏已在map容器中
        {
            cout << "repeated surname: " << surname << endl;
            continue;
        }

        cout << "enter children's name(ctrl+d to end):" << endl;
        while(cin >> childName) //读入该家庭所有孩子的名字
        {
            ret.first->second.push_back(childName);
        }
        cin.clear();  //使输入流重新有效
    }
    while(cin);

    cin.clear();  //使输入流重新有效

    //读入查找的家庭
    cout << "enter a surname to search:" << endl;
    cin >> surname;

    //根据读入的家族姓氏进行查找
    map<string, vector<string> >::iterator iter = 
        children.find(surname);
    
    //输出查询的结果
    if(iter == children.end())  //找不到给家族姓氏
    {
        cout << "no this surname:" << surname << endl;
    }
    else   //找到该家族的姓氏
    {   
        cout << "children: " << endl;
        //输出该家族所有孩子的名字
        for(vector<string>::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
        {
            cout << *it << endl;
        }
    }

    return 0;
}
