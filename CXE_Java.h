/*
 *  CXE_Java.h
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/18/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */


#pragma once

#include <queue>
	using std::queue;


class MainJava : public MethodCommon
{
public:
	MainJava() : MethodCommon("static void", "main", "String[] args") {}
	
	virtual void Return(const Expr&);
	virtual void Return();
};

class ClassJava : public Class
{
public:
	ClassJava(const string& name)
	: name(name), Class(), currentAccess(ACC_PUBLIC)
	{
	}
	ClassJava(const string& name, const string& inheritance)
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

class ModuleJava : public Module
{
public:
	ModuleJava(const string& path);
	
	virtual Class* NewClass(const string& name);
	virtual Class* NewClass(const string& name, const string& inheritance);
	virtual void End();
	
private:
	string path;
	queue<ClassJava*> body;
};