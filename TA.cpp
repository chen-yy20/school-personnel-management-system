#include "TA.h"//实现文件中需要把基类的头文件也Import了
#include"FileErr.h"

#include<iostream>
#include<fstream>
#include<strstream>
#include<iomanip>
#include<conio.h>
#include<string>

#pragma warning(disable:4996)

//有参构造函数
//参数：姓名、学号、性别、班别
//生成一个研究生类对象
TA::TA(string nm, string num, string sx, int yy, int mm, int dd, string clno, string sub, string dpmt, string prin) :
	People(nm, num, sx, yy, mm, dd), Graduate(nm, num, sx,yy,mm,dd,clno,sub), Teacher(nm,num,sx,yy,mm,dd,dpmt, prin)
{}

TA::~TA() {}

//无参构造函数
//参数：None
//通过调用无参构造函数使client可以直接在操作系统中构造想要的对象。
TA::TA() :People(),Graduate(),Teacher()
{ }

//复制构造函数
TA::TA(const TA& rhs) :People(rhs),Graduate(rhs),Teacher(rhs)
{ };

//赋值运算符的重载
//参数：一个常对象的引用 const Graduate&rhs
//通过一个已有对象对另一个已有对象赋值
//return：通过传址方式返回新的原有对象
TA& TA::operator= (const TA& rhs)
{
	if (this == &rhs) return *this;
	name = rhs.name;
	number = rhs.number;
	sex = rhs.sex;
	birthday = rhs.birthday;
	classno = rhs.classno;
	subject = rhs.subject;
	department = rhs.department;
	principal = rhs.principal;
	return *this;
}

//流输出运算符重载
//参数：output：输出流、rhs：目标Graduate object
//return：ostream& 返回输出流本身。
ostream& operator<<(ostream& output, const TA& rhs)
{
	output << "姓名：" << rhs.name << endl;
	output << "学号：" << rhs.number << endl;
	output << "性别：" << rhs.sex << endl;
	output << "生日：" << rhs.birthday << endl;
	output << "班别：" << rhs.classno << endl;
	output << "科目：" << rhs.subject << endl;
	output << "部门：" << rhs.department << endl;
	output << "职务：" << rhs.principal << endl;
	return output;
}
//对象保存函数
//参数：无
//在函数体中把此对象的各个信息储存到文件“学校人事管理系统.txt”中
//return: 无

void TA::save()
{
	char c[80];
	ostrstream strout(c, 80);
	try
	{
		ofstream ofile("学校人员记录表格.txt", ios::app);
		if (!ofile) throw (FileErr());
		else
		{
			strout << "5助教 " << this->name << setw(8) << " " << this->number << " " 
				<< this->sex << " " << this->birthday << " " << this->classno << " "
				<< this->subject << " " << this->department << " " << this->principal << " " << "#" << endl;
			strout << ends;
			cout << c;//调试
			ofile << c;
			cout << "信息保存成功。" << endl;
			ofile.close();
		}
	}
	catch (FileErr E)
	{
		E.reasonopen();
		cout << "按任意键返回。" << endl;
		char c = getch();
	}
}

//修改对象保存函数
//参数：target：用来储存对象所在文件行数/ i：目标文件所在的行数 / line_num:总行数 / line：string类数组指针 分别储存了文件中每一行的字符串 / ofile:输出流文件
//在modifymode()中调用此函数，可以把修改过的对象存入txt文件中。
// 用于保存，并非用于修改。
//return: 无

void TA::modify(int target, int i, int line_num, string* line, ofstream& ofile)
{
	target = i;
	for (i = 0; i < line_num; i++)
	{
		if (i != target) ofile << *(line + i) << endl;
		else
		{
			ofile.close();
			this->save();
			ofile.open("学校人员记录表格.txt", ios::app);
			continue;
		}
	}
	cout << "新信息已保存。" << endl;
}