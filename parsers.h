/*
*   $Id$
*
*   Copyright (c) 2000-2003, Darren Hiebert
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   External interface to all language parsing modules.
*
*   To add a new language parser, you need only modify this single source
*   file to add the name of the parser definition function.
*/
#ifndef _PARSERS_H
#define _PARSERS_H

/* Add the name of any new parser definition function here */
#define PARSER_LIST \
    AdaParser, \
	AntParser, \
	AsmParser, \
  AsnParser,                                \
	AspParser, \
	AwkParser, \
	BasicParser, \
	BetaParser, \
	CParser, \
	CppParser, \
	CsharpParser, \
	CobolParser, \
  DParser, \
	DosBatchParser, \
	EiffelParser, \
	ErlangParser, \
	FlexParser, \
  FalconParser,                               \
	FortranParser, \
  GoParser,  \
	HtmlParser, \
	JavaParser, \
	JavaScriptParser, \
	LispParser, \
	LuaParser, \
	MakefileParser, \
	MatLabParser, \
	ObjcParser , \
	OcamlParser, \
  ParrotParser,                             \
	PascalParser, \
	PerlParser, \
	PhpParser, \
  ProtobufParser,                           \
	PythonParser, \
	RexxParser, \
	RubyParser, \
	SchemeParser, \
	ShParser, \
	SlangParser, \
	SmlParser, \
	SqlParser, \
	TclParser, \
	TexParser, \
	VeraParser, \
	VerilogParser, \
	VhdlParser, \
	VimParser, \
	YaccParser

#endif  /* _PARSERS_H */

/* vi:set tabstop=4 shiftwidth=4: */
