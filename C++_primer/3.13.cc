/*
 * =====================================================================================
 *
 *       Filename:  3.13.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月02日 17时16分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    vector<int> ivec(3, 2);
    int ival;
/*
    读入数据到vector对象
    cout<<"Enter numbers(Ctrl + z to end):"<<endl;
    while(cin>>ival)
    {
        ivec.push_back(ival);
    }*/
    /*计算相邻元素的和并求输出*/
    if(ivec.size() == 0)
    {
        cout<<"No element?"<<endl;
        return -1;
    }
    cout<<"Sum of each pair of adjacent elements in the vectrot"<<endl;

    for(vector<int>::size_type ix = 0; ix < ivec.size()-1; ix = ix+2)
    {
        cout<<ivec[ix] + ivec[ix+1]<<"\t";
        if((ix + 1) % 6 == 0)  //每行输出6个和
            cout << endl;
    }

    if(ivec.size() % 2 != 0)    //提示最后一个元素没有求和
    {
        cout << endl << "The last element is not been summed " << "and its value is "
            << ivec[ivec.size() - 1] << endl;
    }

    return 0;
}
