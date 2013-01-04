/*
*   $Id$
*
*   Copyright (c) 2000-2002, Darren Hiebert
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   This module contains functions for generating tags for LISP files.
*/

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */

#include "parse.h"
#include "read.h"
#include "vstring.h"

/*
*   DATA DEFINITIONS
*/
typedef enum {
	LISP_K_FUNCTION,
	LISP_K_ALIAS,
	LISP_K_VARIABLE,
	LISP_K_CONSTANT,
	LISP_K_MACRO,
	LISP_K_GROUP,
	LISP_K_ADVICE,
	LISP_K_FACE
} lispKind;

static kindOption LispKinds [] = {
	{ TRUE, 'f', "function", "functions" }, /* defun, defun* */
	{ TRUE, 'a', "alias", "aliases" },      /* defalias */
	{ TRUE, 'v', "variable", "variables" }, /* defvar, defvaralias */
	{ TRUE, 'c', "constant", "constants" }, /* defconst, defconst-mode-local */
	{ TRUE, 'm', "macro",    "macros"  },   /* defmacro, defmacro* */
	{ TRUE, 'g', "group",    "groups"  },   /* defgroup * */
	{ TRUE, 'A', "advice",    "advice"  },  /* defadvice * */
	{ TRUE, 'E', "face",    "faces"  },     /* defface * */
};

/*
*   FUNCTION DEFINITIONS
*/

/*
 * lisp tag functions
 *  look for (def or (DEF, quote or QUOTE
 */
static int L_isdef (const unsigned char *strp)
{
	return ( (strp [1] == 'd' || strp [1] == 'D') &&
           (strp [2] == 'e' || strp [2] == 'E') &&
           (strp [3] == 'f' || strp [3] == 'F'));
}

static int L_isquote (const unsigned char *strp)
{
	return ( (*(++strp) == 'q' || *strp == 'Q') &&
           (*(++strp) == 'u' || *strp == 'U') &&
           (*(++strp) == 'o' || *strp == 'O') &&
           (*(++strp) == 't' || *strp == 'T') &&
           (*(++strp) == 'e' || *strp == 'E') &&
           isspace (*(++strp)));
}

static void L_getit (vString *const name, const unsigned char *dbp)
{
	const unsigned char *p;

	if (*dbp == '\'')  /* Skip prefix quote */
		dbp++;
	else if (*dbp == '(' && L_isquote (dbp))  /* Skip "(quote " */
	{
		dbp += 7;
		while (isspace (*dbp))
		dbp++;
	}
	for (p=dbp ; *p!='\0' && *p!='(' && !isspace ((int) *p) && *p!=')' ; p++)
		vStringPut (name, *p);
	vStringTerminate (name);

	if (vStringLength (name) > 0)
		makeSimpleTag (name, LispKinds, LISP_K_FUNCTION);
	vStringClear (name);
}

/* Algorithm adapted from from GNU etags.
 */
static void findLispTags (void)
{
	vString *name = vStringNew ();
	const unsigned char* p;


	while ((p = fileReadLine ()) != NULL)
	{
		if (*p == '(')
		{
			if (L_isdef (p))
			{
				while (*p != '\0' && !isspace ((int) *p))
					p++;
				while (isspace ((int) *p))
					p++;
				L_getit (name, p);
			}
			else
			{
				/* Check for (foo::defmumble name-defined ... */
				do
					p++;
				while (*p != '\0' && !isspace ((int) *p)
						&& *p != ':' && *p != '(' && *p != ')');
				if (*p == ':')
				{
					do
						p++;
					while (*p == ':');

					if (L_isdef (p - 1))
					{
						while (*p != '\0' && !isspace ((int) *p))
							p++;
						while (isspace (*p))
							p++;
						L_getit (name, p);
					}
				}
			}
		}
	}
	vStringDelete (name);
}

extern parserDefinition* LispParser (void)
{
	static const char *const extensions [] = {
		"cl", "clisp", "el", "l", "lisp", "lsp", NULL
	};
	parserDefinition* def = parserNew ("Lisp");
	def->kinds      = LispKinds;
	def->kindCount  = KIND_COUNT (LispKinds);
	def->extensions = extensions;
	def->parser     = findLispTags;
	return def;
}

/* vi:set tabstop=4 shiftwidth=4: */
