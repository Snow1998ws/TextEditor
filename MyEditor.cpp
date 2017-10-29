#include "stdafx.h"
#include "String.h"
#include "NodeList.h"
#include "Node.h"
#include "Editor.h"
#include<iostream>
#include<string>
using namespace std;

int main()
{
	Editor editor;
	editor.command_note();
	while (true)
	{
		editor.command_go();
	}
    return 0;
}

