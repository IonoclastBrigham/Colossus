/*
 *  CXE_Cs.cpp
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/19/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */

#include <iostream>
using std::cout;
using std::endl;

#include "CXE.h"


// Main ////////////////////////////////////////////////////////////////////////

void MainCs::Return()
{
	throw Exception(__PRETTY_FUNCTION__, "main cannot return void in Colossus");
}

// Class ///////////////////////////////////////////////////////////////////////

void ClassCs::SetAccess(Access a)
{
	currentAccess = a;
}

Method* ClassCs::Ctor()
{
	Method* m = new MethodCommon("", name, "");
	body.push(new Member(ACC_PUBLIC, m));
	return m; 
}

Method* ClassCs::Dtor()
{
	Method* m = new MethodCommon("", "~" + name, "");
	body.push(new Member(ACC_PROTECTED, m));
	return m; 
}

Method* ClassCs::Main()
{
	//Method* m = new MethodCommon("static void", "Main", "string[] args");
	Method* m = new MainCs();
	body.push(new Member(ACC_PUBLIC, m));
	return m; 
}

Method* ClassCs::NewMethod(Access a, const string& ret, const string& name,
							 const string& params)
{
	Method* m = new MethodCommon(ret, name, params);
	body.push(new Member(currentAccess, m));
	return m; 
}

Var ClassCs::NewVar(Access a, const string& type, const string& name)
{
	body.push(new Member(currentAccess, new Var(type + " " + name + ";\n"))); 
	return Var(name);
}

void ClassCs::End()
{
	while (body.size())
	{
		text += body.front()->str();
		delete body.front();
		body.pop();
	}
	text += "}\n\n";
}

string ClassCs::str() const
{
	string inherit = (inheritance == "" ? "" : " extends " + inheritance) + "\n";
	return "class " + name + inherit + text;
}

// Module //////////////////////////////////////////////////////////////////////

ModuleCs::ModuleCs(const string& path) : path(path)
{
	text =	"// " + path + ".cs\n" +
	"// Generated by the Colossus compiler\n" +
	"// Do not modify this file unless you really need to\n\n";
	
}

Class* ModuleCs::NewClass(const string& name)
{
	ClassCs* c = new ClassCs(name);
	body.push(c);
	return c;
}

Class* ModuleCs::NewClass(const string& name, const string& inheritance)
{
	ClassCs* c = new ClassCs(name, inheritance);
	body.push(c);
	return c;
}

void ModuleCs::End()
{
	while (body.size())
	{
		text += body.front()->str();
		delete body.front();
		body.pop();
	}
	text += "\n";
	cout << text;
}