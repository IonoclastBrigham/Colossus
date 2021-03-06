/*
 *  CXE_Java.cpp
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/18/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */


#include <iostream>
	using std::cout;
	using std::endl;

#include "CXE.h"


// Main ////////////////////////////////////////////////////////////////////////

void MainJava::Return(const Expr& e)
{
	text += "System.exit(" + e.str() + ");\n";
}

void MainJava::Return()
{
	throw Exception(__PRETTY_FUNCTION__, "main cannot return void in Colossus");
}

// Class ///////////////////////////////////////////////////////////////////////

void ClassJava::SetAccess(Access a)
{
	currentAccess = a;
}

Method* ClassJava::Ctor()
{
	Method* m = new MethodCommon("", name, "");
	body.push(new Member(ACC_PUBLIC, m));
	return m; 
}

Method* ClassJava::Dtor()
{
	Method* m = new MethodCommon("void", "finalize", "");
	body.push(new Member(ACC_PROTECTED, m));
	return m; 
}

Method* ClassJava::Main()
{
	//Method* m = new MethodCommon("static void", "main", "String[] args");
	Method* m = new MainJava();
	body.push(new Member(ACC_PUBLIC, m));
	return m; 
}

Method* ClassJava::NewMethod(Access a, const string& ret, const string& name,
							 const string& params)
{
	Method* m = new MethodCommon(ret, name, params);
	body.push(new Member(currentAccess, m));
	return m; 
}

Var ClassJava::NewVar(Access a, const string& type, const string& name)
{
	body.push(new Member(currentAccess, new Var(type + " " + name + ";\n"))); 
	return Var(name);
}

void ClassJava::End()
{
	while (body.size())
	{
		text += body.front()->str();
		delete body.front();
		body.pop();
	}
	text += "}\n\n";
}

string ClassJava::str() const
{
	string inherit = (inheritance == "" ? "" : " extends " + inheritance) + "\n";
	return "class " + name + inherit + text;
}

// Module //////////////////////////////////////////////////////////////////////

ModuleJava::ModuleJava(const string& path) : path(path)
{
	text =	"// " + path + ".java\n" +
	"// Generated by the Colossus compiler\n" +
	"// Do not modify this file unless you really need to\n\n" +
	"package " + path + ";\n\n";
	
}

Class* ModuleJava::NewClass(const string& name)
{
	ClassJava* c = new ClassJava(name);
	body.push(c);
	return c;
}

Class* ModuleJava::NewClass(const string& name, const string& inheritance)
{
	ClassJava* c = new ClassJava(name, inheritance);
	body.push(c);
	return c;
}

void ModuleJava::End()
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