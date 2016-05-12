C++ 输入输出流和文件流
标签： 程序设计	分类： 程序
    接下来讲<iostream>头文件和<fstream>头文件的简单使用。
    正如文件名所表达的那样，这两个头文件分别处理输入/输出流以及文件流。
    cin和cout分别是输入流的对象和输出流的对象，cin从控制台读取数据，cout向控制台输出数据。如果读入和输出的数据类型是c++
内置数据类型，并不用考虑数据转换层面的东西。例如：

int i;
cin >> i;

或者
string s;
cin >> s;

都是正确的表达，只要使用程序的人清楚，什么地方需要输入什么类型的数据就可以了。
   fstream可以作为一个数据类型使用，不过大多数时候我却分别使用ifstream和ofstream两种数据类型，使用这两种数据类型定义变量的格式如下：
   ifstream ifile;
   ofstream ofile;
   有了上述定义之后，ifile的作用就类似于cin，ofile的作用就类似于cout了。只是它们不像cin和cout从控制台读/写数据，它们从文件读/写数据。在成功读/写数据之前，需要确定ifile和ofile读/写数据的目标文件，例如：
   ifile.open("a.txt");或者 ofile.open("a.txt");
   在这种情况下，如果ifile打不开文件，则会返回错误。ofile打不开文件，则创建一个文件。

   好吧，我承认，这儿有相当多琐碎的东西，我根本没有精力照顾到。比如ofile的打开新文件，或者追加打开一个文件，比如文件句柄(ifile或者ofile)的状态位。这些还是需要每个人自己在编程过程中积累的。下面给出一个简单的例子：
    文件a.txt每一行由两列组成，第一列是数字，第二列是一个字符串。如果某一行第一列的数字大于100，把该行写入文件b.txt，否则，把该行写入文件c.txt。

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int i;
    string s;
    ifstream ifile;
    ifile.open("a.txt");
    ofstream ofile1, ofile2;
    ofile1.open("b.txt");
    ofile2.open("c.txt");
    while(ifile >> i >> s)
    {
        if(i > 100) ofile1 << i << "\t" << s << endl;
        else ofile2 << i << "\t" << s << endl;
    }
    ifile.close();
    ofile1.close();
    ofile2.close();
}

如果a.txt中的内容是
139  asdfa
43   aas
987  aaaaf
则执行程序之后，b.txt中内容是
139  asdfa
987  aaaaf
c.txt中内容是
43   aas

    除了通过操作符 << >> 进行数据读写之外，我还常采用以下两种数据读写方式：
    1，用getline(ifile, str)行读写，通过函数getline，把一整行数据从ifile中读进字符串str中。以下代码段实现了把a.txt中长度超过10的行写如b.txt中的功能。
    string str;
    ifstream ifile;
    ifile.open("a.txt");
    ofstream ofile;
    ofile.open("b.txt");
    while(getline(ifile, str))
        if(str.size() > 10)
            ofile << str << endl;
    ifile.close();
    ofile.close();
   
    2，用read函数和write函数进行读写。以下代码断实现了把a.txt复制到b.txt的功能。
    char Buf[4096];
    ifstream ifile;
    ifile.open("a.txt", ios::binary);    //注意陷阱，这儿要以二进制打开，否则...
    ofstream ofile;
    ofile.open("b.txt", ios::binary);
    while(ifile.read(Buf, 4096))
        ofile.write(Buf, 4096);
    ofile.write(Buf, ofile.gcount());
    ifile.close();
    ofile.close();
