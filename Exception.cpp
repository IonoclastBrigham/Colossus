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

#include "Exception.h"


// error printing helper
ostream& operator<<(ostream& os, Exception& e)
{
	return os << e.what();
}
