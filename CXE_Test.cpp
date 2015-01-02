/*
 *  CXE_Test.cpp
 *  Colossus
 *
 *  Created by Awesomest Prime on 7/15/10.
 *  Copyright ©2010 brigham toskin. All rights reserved.
 *
 */


#include "CXE.h"


void compile(Module* mod)
{
	Class* cmath = mod->NewClass("Mathinator");
	Var x("x");
	Var y("y");
	Method* ctor = cmath->Ctor();
	ctor->Assign(x, Expr("7"));
	ctor->Assign(y, Expr("42"));
	ctor->End();
	
	Method* mathy = cmath->NewMethod(ACC_PRIVATE, "int", "mathy", "");
	Expr e = Expr(y) / Expr(x) + Expr(y);
	mathy->Return(e);
	mathy->End();
	
	cmath->SetAccess(ACC_PRIVATE);
	cmath->NewVar(ACC_PRIVATE, "int", "x");
	cmath->NewVar(ACC_PRIVATE, "int", "y");
	
	Class* cmain = mod->NewClass("TestClass");
	Method* m = cmain->Main();
	Var math = m->NewVar("Mathinator", "math");
	m->Allocate(math, "Mathinator");
	Var result = m->Call(math, mathy);
	m->Return(result);
	m->End();
	
	cmath->End();
	cmain->End();
	mod->End();
}

int main()
{
	Module* modcpp = new ModuleCpp("test");
	Module* modjava = new ModuleJava("test");
	Module* modcs = new ModuleCs("test");
	
	compile(modcpp);
	compile(modjava);
	compile(modcs);
}