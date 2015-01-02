/*
 *  CXE_Cs.h
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/19/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */

#pragma once

#include <queue>
	using std::queue;


class MainCs : public MethodCommon
{
public:
	MainCs() : MethodCommon("static int", "Main", "string[] args") {}
	virtual void Return();
};

class ClassCs : public Class
{
public:
	ClassCs(const string& name)
	: name(name), Class(), currentAccess(ACC_PUBLIC)
	{
	}
	ClassCs(const string& name, const string& inheritance)
	: name(name), inheritance(inheritance), Class(), currentAccess(ACC_PUBLIC)
	{
	}
	
	virtual void SetAccess(Access a);
	
	virtual Method* Ctor();
	virtual Method* Dtor();
	
	virtual Method* Main();
	virtual Method* NewMethod(Access a, const string& ret, const string& name,
							  const string& params);
	virtual Var NewVar(Access a, const string& type, const string& name);
	
	virtual void End();
	
	string str() const;
	
private:
	string name, inheritance; // Element::text is class body
	Access currentAccess;
	queue<Member*> body;
};

class ModuleCs : public Module
{
public:
	ModuleCs(const string& path);
	
	virtual Class* NewClass(const string& name);
	virtual Class* NewClass(const string& name, const string& inheritance);
	virtual void End();
	
private:
	string path;
	queue<ClassCs*> body;
};