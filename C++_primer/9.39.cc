/******************************************************************************
*    > File Name: 9.39.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年11月12日 星期二 19时39分12秒
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
#include <vector>

int main(int argc, char **argv)
{
    std::string s1 = "We were her pride of 10 she named us:";
    std::string s2 = "Benjamin, Phoenix, the Prodigal";
    std::string s3 = "and perspicacious pacific Suzanne";
    
    std::string sentence = s1 + ' ' + s2 + ' ' + s3;
    std::cout << sentence << std::endl;

    /*用作分隔符的字符*/
    std::string separators(" \t:,\v\r\n\f");
    std::string word;
    /*sentence中最长，最短单词以及下一个单词的长度，单词的数目*/
    std::string::size_type maxLen, minLen, wordLen, count = 0;
    /*存放最长及最短单词的vector容器*/
    std::vector<std::string> longestWords, shortestWords;
    /*单词的起始位置和结束位置*/
    std::string::size_type startPos = 0, endPos = 0;

    /*每次循环处理sentence中的一个单词*/
    while( (startPos = sentence.find_first_not_of(separators, endPos)) != std::string::npos )
    {
        //找到下一个单词的起始位置
        ++count;
        //找到下一个单词的结束位置
        endPos = sentence.find_first_of(separators, startPos);

        if(endPos == std::string::npos)
        {   //找不到下一个出现分隔符的位置，即该单词是最后一个单词
            wordLen = sentence.size() - startPos;
        }
        else
        {   //找到了下一个出现分隔符的位置
            wordLen = endPos - startPos;
        }

        //获取单词
        word.assign(sentence.begin() + startPos, sentence.begin() + startPos + wordLen);  

        //设置下次查找打起始位置
        startPos = sentence.find_first_not_of(separators, endPos);

        //找到的是第一个单词
        if(count == 1)
        {
            maxLen = minLen = wordLen;
            longestWords.push_back(word);
            shortestWords.push_back(word);
        }
        else
        {
            if(wordLen > maxLen)
            {   //当前单词比目前的最长单词更长
                maxLen = wordLen;
                longestWords.clear();      //清空存放最长单词的容器
                longestWords.push_back(word);
            }
            else if(wordLen == maxLen)
            {   //当前单词与目前的最长单词等长
                longestWords.push_back(word);
            }
            if(wordLen < minLen)
            {
                minLen = wordLen;
                shortestWords.clear();
                shortestWords.push_back(word);
            }
            else if(wordLen == minLen)
            {   //当前单词与目前的最长单词等长
                shortestWords.push_back(word);
            }
            
        }/*end of else*/
    }/*end of while( (startPos = sentence.find_first_not_of(separators, endPos)) != string::npos )*/
    
    //输出单词数目
    std::cout << "word amount: " << count << std::endl;

    std::vector<std::string>::iterator iter;
    //输出最长单词
    std::cout << "longest Words: " << std::endl;
    iter = longestWords.begin();
    while(iter != longestWords.end())
    {
        std::cout << *iter++ << std::endl;
    }

    //输出最短单词
    std::cout << "shortest Words: " << std::endl;
    iter = shortestWords.begin();
    while(iter != shortestWords.end())
    {
        std::cout << *iter++ << std::endl;
    }

    return 0;
}
