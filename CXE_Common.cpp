// CXE_Common.cpp
// Colossus compiler
// CXE Common Classes


#include <sstream>
	using std::stringstream;

#include "CXE.h"


string access_text(Access a)
{
	
	switch (a)
	{
		case ACC_PUBLIC:
			return "public";
			break;
		case ACC_PRIVATE:
			return "private";
			break;
		case ACC_PROTECTED:
			return "protected";
			break;
		default:
			return "";
			break;
	}
}

// Element /////////////////////////////////////////////////////////////////////

string Element::str() const
{
	return text;
}

// Expr ////////////////////////////////////////////////////////////////////////

// unary ops

Expr  Expr::operator-() const
{
	return Expr(" -" + text);
}

Expr Expr::operator++()
{
	return Expr(" ++" + text);
}

Expr Expr::operator++(int dummy)
{
	return Expr(text + "++ ");
}

Expr Expr::operator--()
{
	return Expr(" --" + text);
}

Expr Expr::operator--(int dummy)
{
	return Expr(text + "-- ");
}

// binary ops

Expr  Expr::operator+(const Expr& e) const
{
	return Expr(text + "+" + e.text);
}

Expr  Expr::operator-(const Expr& e) const
{
	return Expr(text + "-" + e.text);
}

Expr  Expr::operator*(const Expr& e) const
{
	return Expr(text + "*" + e.text);
}

Expr  Expr::operator/(const Expr& e) const
{
	return Expr(text + "/" + e.text);
}

Expr  Expr::operator%(const Expr& e) const
{
	return Expr(text + "%" + e.text);
}

// MethodCommon //////////////////////////////////////////////////////////////////

Var MethodCommon::NewVar(const string& type, const string& name)
{
	text += type + " " + name + ";\n";
	return Var(name);
}

void MethodCommon::Allocate(const Var& var, const string& type)
{
	text += var.str() + " = new " + type + "();\n";
}

void MethodCommon::CallVoid(Method* method)
{
	text += method->Name() + "();\n";
}

Var MethodCommon::Call(Method* method)
{
	if(method->Ret() == "void")
		throw Exception("Void method cannot be an r-value");

	stringstream ss;
	ss << tmpCount++;
	Var tmp = NewVar(method->Ret(), "__tmp" + ss.str() + "__");
	Assign(tmp, Expr(method->Name() + "()"));
	return tmp;
}

void MethodCommon::CallVoid(const Var& cls, Method* method)
{
	text += cls.str() + "." + method->Name() + "();\n";
}

Var MethodCommon::Call(const Var& cls, Method* method)
{
	if(method->Ret() == "void")
		throw Exception("Void method cannot be an r-value");

	stringstream ss;
	ss << tmpCount++;
	Var tmp = NewVar(method->Ret(), "__tmp" + ss.str() + "__");
	Assign(tmp, Expr(cls.str() + "." + method->Name() + "()"));
	return tmp;
}

void MethodCommon::Assign(const Var& v, const Expr& e)
{
	text += v.str() + " = " + e.str() + ";\n";
}

void MethodCommon::Return(const Expr& e)
{
	text += "return " + e.str() + ";\n";
}

void MethodCommon::Return()
{
	text += "return;\n";
}

void MethodCommon::End()
{
	text += "}\n\n";
}

string MethodCommon::str() const
{
	return Sig() + Body();
}

const string& MethodCommon::Ret()
{
	return ret;
}

const string& MethodCommon::Name()
{
	return name;
}

const string& MethodCommon::Params()
{
	return params;
}

string MethodCommon::Sig() const
{
	return ret + " " + name + params + "\n";
}

const string& MethodCommon::Body() const
{
	return text;
}