/*
 *  CXE_Common.h
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/16/10.
 *  Copyright 2010 brigham toskin. All rights reserved.
 *
 */


#pragma once


// provides common functionality for Method interface //////////////////////////

class MethodCommon : public Method
{
public:
	MethodCommon(const string& ret, const string& name, const string& params)
	: tmpCount(0), ret(ret), name(name), params("(" + params + ")"),
	  Method("{\n") {}

	virtual Var NewVar(const string& type, const string& name);
	virtual void Allocate(const Var& var, const string& type);
	
	// compile instructions into the method
	virtual Var Call(Method* method);
	virtual void CallVoid(Method* method);
	virtual Var Call(const Var& cls, Method* method);
	virtual void CallVoid(const Var& cls, Method* method);
	virtual void Assign(const Var&, const Expr&);
	virtual void Return(const Expr&);
	virtual void Return();
	
	virtual void End();
	
	virtual string str() const;

	virtual const string& Ret();
	virtual const string& Name();
	virtual const string& Params();
	virtual string Sig() const;
	virtual const string& Body() const;
	
private:
	int tmpCount;
	string ret, name, params; // Element::text is method body
};