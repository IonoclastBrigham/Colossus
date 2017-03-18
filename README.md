# Colossus - a multi-platform source code translation language and tool

----
## Prototype Warning!
This code is the result of an undergrad research project. It is incomplete,
broken in places, and generally not ready for prime time. I found it in my
archives, and decided to make it available on Github because, why not?

----
## What's All This, Then?
The idea behind Colossus is to create a simple OO language to make cross-platform
software development easy. This means that a lot of esoteric language features
you'd find elsewhere are eschewed, the syntax is greatly simplified, and many little
bits of syntactic sugar and unique features are introduced.

But the real raison d'etre for Colossus is that it compiles to C++, Java, C#, or
any other language that it might be extended to support. It was meant to bring your
apps and other code to your target platform on its own terms. This means that rather
than a large, complex, and foreign runtime like Mono or Node, it translates to the
native API language with only a small compatibility layer to normalize resource
utilization.

----
## Current State
The most complete and functional module is CXE, the Colossus Translation Engine.
When you build the XCode project, it will compile in main() from the file CXE_Test.cpp,
which instantiates the C++, Java, and C# flavors of the engine, and programmatically
builds a simple test class.

CXE was meant to be called from the parser's reduction rules, building a working
model of the user's source code as it goes. The grammar and lexical description
from which the parser and lexer are generated, respectively, are incomplete and
should be considered in a wild state of flux. Probably buggy, possibly broken, and
certainly in no way complete, they should be considered as a sandbox I used for toying
around with language syntax ideas.

----
## Building
Should build with XCode 4+. Adjust platform SDK/Target to match your situation.
Would be pretty trivial to write a make file, but I couldn't be chuffed to do it
while I was developing these ideas.

Of note, it depends on [LMNO](https://github.com/IonoclastBrigham/lmno) to generate
the parser and Ragel to generate the lexer. Adjust the scripts that invoke these
in the build rules, if you install them anywhere other than `/usr/local/bin/`.

----
## License
Copyright © 2010-2015 Brigham Toskin. [MIT License](https://github.com/IonoclastBrigham/Colossus/blob/master/LICENSE).
