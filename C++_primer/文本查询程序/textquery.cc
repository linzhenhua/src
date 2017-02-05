/******************************************************************************
*    > File Name: textqueryquery.cc
*
*    >Description: 
*
*    >Version: 1.0
*    > Created Time: 2013年12月14日 星期六 16时10分05秒
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
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <stdexcept>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::set;

/*TextQuery类*/
class TextQuery
{
    public:
        typedef vector<string>::size_type line_no;    //行号
        void read_file(ifstream &is)
        {
            store_file(is);
            build_map();
        }
        set<line_no> run_query(const string&) const;
        string text_line(line_no) const;

    private:
        void store_file(ifstream&);
        void build_map();
        vector<string> lines_of_text;
        map<string, set<line_no> > word_map;
};

/*函数声明*/
void print_results(const set<TextQuery::line_no>& locs, const string& sought, const TextQuery &file);
ifstream& open_file(ifstream &in, const string &file);
string make_plural(size_t ctr, const string &word, const string &ending);

/*
 * ============================================================================
 * 函数名:主函数main
 * 参数:
 * argc:待输入命令的数目
 * argv:待输入的命令名
 * 返回值: 成功返回0，失败返回-1
 *============================================================================= 
 */
int main(int argc, char **argv)
{
    ifstream infile;

    /*如果打开文件失败程序将退出*/
    if(argc < 2 || !open_file(infile, argv[1]))
    {
        cerr << "No input file!" << endl;
        return -1;
    }

    TextQuery tq;
    tq.read_file(infile);     //将所有单词的行号都记录下来了

    /*实现查询*/
    while(true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        cin >> s;
        if(!cin || s == "q")
            break;

        set<TextQuery::line_no> locs = tq.run_query(s);
        /*输出结果*/
        print_results(locs, s, tq);
    }

    return 0;
}

/*
 * ============================================================================
 * 函数名:TextQuery::store_file(ifstream &is)
 * 功能:存储输入文件
 * 参数:
 * is: 输入的文件
 * 返回值: 无
 *============================================================================= 
 */
void TextQuery::store_file(ifstream &is)
{
    string textline;
    
    while(getline(is, textline))
    {
        lines_of_text.push_back(textline);
    }
}

/*
 * ============================================================================
 * 函数名: void TextQuery::build_map()
 * 功能: 建立单词map容器
 * 参数: 无
 * 返回值: 无
 *============================================================================= 
 */
void TextQuery::build_map()
{
    for(line_no line_num = 0; line_num != lines_of_text.size(); ++line_num)
    {
        istringstream line(lines_of_text[line_num]);
        string word;

        while(line >> word)
        {
            word_map[word].insert(line_num);
        }
    }
}

/*
 * ============================================================================
 * 函数名: set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
 * 功能：支持查询
 * 参数:
 * query_word: 待查询的单词
 * 返回值:  没有找到返回空，查找到返回单词的行号
 *============================================================================= 
 */
set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
{
    map<string, set<line_no> >::const_iterator loc = word_map.find(query_word);

    if(loc == word_map.end())
    {
        return set<line_no>();
    }
    else
    {
        return loc->second;
    }
}

/*
 * ============================================================================
 * 函数名: string TextQuery::text_line(line_no line) const
 * 功能：run_query返回值的使用
 * 参数:
 * line: 行号
 * 返回值: 
 *============================================================================= 
 */
string TextQuery::text_line(line_no line) const
{
    if(line < lines_of_text.size())
    {
        return lines_of_text[line];
    }

    throw std::out_of_range("line number out of range");
}

/*
 * ============================================================================
 * 函数名:open_file
 * 参数:
 * in: 待输入的文件
 * file: 待输入的文件名
 * 返回值: 把in和file绑定,然后返回输入文件in的状态
 *============================================================================= 
 */
ifstream& open_file(ifstream &in, const string &file)
{
    in.close();
    in.clear();
    in.open(file.c_str());

    return in;
}

/*
 * ============================================================================
 * 函数名:void print_results(const set<TextQuery::line_no>& locs, 
 * const string& sought, const TextQuery &file)
 * 功能: 输出结果
 * 参数:
 * locs: 单词的出现次数
 * sought: 查找的单词
 * file: TextQuery类
 * 返回值: 无
 *============================================================================= 
 */
void print_results(const set<TextQuery::line_no>& locs, const string& sought, const TextQuery &file)
{
    typedef set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();

    cout << "\n" << sought << " occurs " << size << " " << make_plural(size, "time", "s") << endl;

    line_nums::const_iterator it = locs.begin();
    for( ; it != locs.end(); ++it)
    {
        cout << "\t(line" << (*it)+1 << ") " << file.text_line(*it) << endl;
    }
}

/*
 * ============================================================================
 * 函数名:make_plural(size_t ctr, const string &word, const string &ending)
 * 功能：输出单词的单数或复数形式
 * 参数:
 * ctr: 计数器
 * word: 单词
 * ending: 单词结束字符串
 * 返回值: 当计数器的值大于1时，返回该单词的复数版本
 *============================================================================= 
 */
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr == 1)? word : word + ending;
}
