// Exception.cpp
// Exception class
//
// Copyright ©2009 - 2010 Brigham Toskin
// This software is part of the Rogue-Opcode game framework. It is distributable
// under the terms of a modified MIT License. You should have received a copy of
// the license in the file LICENSE. If not, see:
// <http://code.google.com/p/rogue-op/wiki/LICENSE>
//
// Formatting:
//	80 cols ; tabwidth 4
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <exception>
#include <string>
 using std::string;
#include <iostream>
 using std::ostream;

class Exception : public std::exception
{
public:
	Exception(const string& msg) throw()
	: msg("Error at " + string(__PRETTY_FUNCTION__) + ": " + msg)
	{
	}
	Exception(const string& function, const string& msg) throw()
	: msg("Error at " + function + ": " + msg)
	{
	}
	virtual ~Exception() throw() {}
	virtual const char* what() const throw() { return msg.c_str(); }
private:
	const string msg;
};

ostream& operator<<(ostream& os, Exception& e);
