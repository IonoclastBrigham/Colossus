/*
 *  CXE_Cpp.h
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/16/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */


#pragma once

#include <queue>
	using std::queue;


class Accessor: public Element // Language-specific
{
public:
	Accessor() : access(ACC_PUBLIC) {}
	Accessor(Access a) : access(a) {}
	string str() const { return access_text(access) + ":\n"; }
	Access access;
};

class MainCpp : public MethodCommon
{
public:
	MainCpp() : MethodCommon("static int", "main", "vector<string>& args") {}
	virtual void Return();
};

class ClassCpp : public Class
{
public:
	ClassCpp(const string& name)
	: name(name), Class(), currentAccess(ACC_PUBLIC), main_defined(false)
	{
		text += "public:\n";
	}
	ClassCpp(const string& name, const string& inheritance)
	: name(name), inheritance(inheritance), Class(), currentAccess(ACC_PUBLIC),
	  main_defined(false)
	{
		text += "public:\n";
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
	queue<Element*> body;
	bool main_defined;
};

class ModuleCpp : public Module
{
public:
	ModuleCpp(const string& path);

	virtual Class* NewClass(const string& name);
	virtual Class* NewClass(const string& name, const string& inheritance);
	virtual void End();
	
private:
	string path;
	queue<ClassCpp*> body;
};