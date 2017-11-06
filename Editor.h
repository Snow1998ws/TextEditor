#pragma once
#include"Node.h"
#include"NodeList.h"
#include"String.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

class Editor
{
	int linecount;
	int count;
	Node<String>* Ptr;
	ifstream* input;
	ofstream* output;
	NodeList<String> list;
public:
	Editor();
	void read();  //读入缓冲区
	void view();  //显示文件内容
	void First(); //第一行
	void End();  //最后一行
	void Next();  //下一行
	void Prep(); //上一行
	void Skip();  //跳到某一行
	void insert();  //插入一行
	void Del();  //删除当前行
	void Change(); //替换某一行
	void Calculate();  //统计行数和字符数
	void find();  //字符串匹配
	void sub();  //字符串替换
	void write(); //写入输出文件
	void command_note();  //控制台帮助
	void command_go();  //控制台执行
};

Editor::Editor()
{
	char infile[50], outfile[50];
	cout << "Enter the input file: ";
	cin >> infile;
	cout << "Enter the output file: ";
	cin >> outfile;
	input = new ifstream(infile);
	output = new ofstream(outfile);
	count = 0;
	linecount = 0;
}

//读入缓冲区
void Editor::read()
{
	string line;
	int i = 1;
	while (getline(*input, line))
	{
		String x(line.c_str());
		list.Insert(i++, x);
		count++;
	}
	cout << "reading finished" << endl;
}

//显示文件内容
void Editor::view()
{
	Node<String>* curr;
	curr = list.head->next;
	linecount = 0;
	while (curr != NULL && curr != list.head)
	{
		cout << curr->data.CStr() << endl;
		curr = curr->next;
		linecount++;
	}
	Ptr = curr->prep;
	cout << linecount << ": " << Ptr->data.CStr() << endl;
}

//第一行
void Editor::First()
{
	Ptr = list.head->next;
	linecount = 1;
	cout << linecount << ": " <<Ptr->data.CStr() << endl;
}

//最后一行
void Editor::End()
{
	Ptr = list.head->prep;
	linecount = count;
	cout << linecount << ": " << Ptr->data.CStr() << endl;
}

//下一行
void Editor::Next()
{
	if (Ptr->next == list.head || Ptr->next == NULL)
		cout << "already the last line" << endl;
	else
	{
		Ptr = Ptr->next;
		linecount++;
		cout << linecount << ": " << Ptr->data.CStr() << endl;
	}
}

 //上一行
void Editor::Prep()
{
	if (Ptr->prep == list.head || Ptr->prep == NULL)
		cout << "already the first line" << endl;
	else
	{
		Ptr = Ptr->prep;
		linecount--;
		cout << linecount << ": " << Ptr->data.CStr() << endl;
	}
}

 //跳到某一行
void Editor::Skip()
{
	int position;
	cout << "Enter the line you want to skip to : ";
	cin >> position;
	if (position < 1 || position > list.length)
		cout << "out of the length" << endl;
	else
	{
		linecount = position;
		Ptr = list.GetItemPtr(position);
		cout << linecount << ": " << Ptr->data.CStr() << endl;
	}
}

 //插入一行
void Editor::insert()
{
	int position;
	cout << "Enter the line you want to insert to : ";
	cin >> position;
	if (position < 1 || position > list.length)
		cout << "out of the length" << endl;
	else
	{
		char ins[50];
		cout << "Enter the inserted line: ";
		cin >> ins;
		String in(ins);
		list.Insert(position, in);
		count++;
		Ptr = list.GetItemPtr(position);
		linecount = position;
		cout << linecount << ": " << Ptr->data.CStr() << endl;
	}
}

 //删除当前行
void Editor::Del()
{
	if (count < 1)
		cout << "out of the length" << endl;
	else
	{
		if (Ptr->next == list.head && Ptr->prep == list.head)
		{
			list.Delete(linecount);
			linecount--;
			count--;
			Ptr = list.head;
			cout << "read buff is empty" << endl;
		}
		else if (Ptr->next == list.head && Ptr->prep != list.head)
		{
			list.Delete(linecount);
			count--;
			linecount--;
			Ptr = list.GetItemPtr(linecount);
			cout << linecount << ": " << Ptr->data.CStr() << endl;
		}
		else
		{
			list.Delete(linecount);
			count--;
			Ptr = list.GetItemPtr(linecount);
			cout << linecount << ": " << Ptr->data.CStr() << endl;
		}
	}
}

//替换某一行
void Editor::Change()
{
	int x;
	char s[50];
	cout << "Enter the line you want to change: ";
	cin >> x;
	cout << "Enter the string:";
	cin >> s;
	if (x < 1 || x > count)
		cout << "out of the length" << endl;
	else
	{
		String subs(s);
		linecount = x;
		Ptr = list.GetItemPtr(linecount);
		Ptr->data = subs;
		cout << linecount << ": " << Ptr->data.CStr() << endl;
	}
}

 //统计行数和字符数
void Editor::Calculate()
{
	Node<String>* temp;
	temp = list.head->next;
	int sum = 0;
	while (temp != list.head && temp != NULL)
	{
		int s = temp->data.Length();
		sum += s;
		temp = temp->next;
	}
	cout << "line: " << count << endl;
	cout << "character: " << sum << endl;
}

//字符串匹配
void Editor::find()
{
	char a[50];
	cout << "Enter a string: ";
	cin >> a;
	String x(a);
	int index = Ptr->data.Index(x);
	if (index != -1)
	{
		cout << Ptr->data.CStr() << endl;
		for (int i = 0; i < index; i++)
		{
			cout << " ";
		}
		for (int i = 0; i < x.Length(); i++)
		{
			cout << "^";
		}
		cout << endl;
	}
	else
		cout << "search false" << endl;
}

//字符串替换
void Editor::sub()
{
	char a[50], b[50];
	cout << "Enter the string you want to sub : ";
	cin >> a;
	cout << "Enter a string : ";
	cin >> b;
	String x(a);
	int index = Ptr->data.Index(x);
	if (index == -1)
		cout << "The string not exist" << endl;
	else
	{
		char temp[50];
		for (int i = 0; i < index; i++)
			temp[i] = Ptr->data.CStr()[i];
		for (int i = index; i < index + strlen(b); i++)
			temp[i] = b[i - index];
		for (int i = index + strlen(b); i <= Ptr->data.Length() + strlen(b) - x.Length(); i++)
		{
			if (i == Ptr->data.Length() + strlen(b) - x.Length())
				temp[i] = '\0';
			else
				temp[i] = Ptr->data.CStr()[i - strlen(b) + x.Length()];
		}
		String str(temp);
		Ptr->data = str;
		cout << Ptr->data.CStr() << endl;
	}
}

//写入输出文件
void Editor::write()
{
	Node<String>* temp;
	temp = list.head->next;
	while(temp != list.head)
	{
		*output << temp->data.CStr() << endl;
		temp = temp->next;
	}
}

void Editor::command_note()
{
	cout << "r: read the input buff" << endl;
	cout << "v: show the content of input file" << endl;
	cout << "f: to the first line" << endl;
	cout << "e: to the end line" << endl;
	cout << "n: to the next line" << endl;
	cout << "p: to the last line" << endl;
	cout << "i: insert a new line" << endl;
	cout << "d: delete the current line" << endl;
	cout << "s: skip to a line" << endl;
	cout << "c: change a line" << endl;
	cout << "z: show the number of lines and characters" << endl;
	cout << "l: find a string in the current line" << endl;
	cout << "b: sub a string in the current line" << endl;
	cout << "w: write to the output line" << endl;
	cout << "q: quit the console" << endl;
}
void Editor::command_go()
{
	char x;
	cout << "Enter a character:";
	cin >> x;
	switch (x)
	{
	case 'r': read(); break;
	case 'v': view(); break;
	case 'f': First(); break;
	case 'e': End(); break;
	case 'n': Next(); break;
	case 'p': Prep(); break;
	case 'i': insert(); break;
	case 'd': Del(); break;
	case 's': Skip(); break;
	case 'c': Change(); break;
	case 'z': Calculate(); break;
	case 'l': find(); break;
	case 'b': sub(); break;
	case 'w': write(); break;
	case 'q': exit(0);
	default: End();
	}
}
