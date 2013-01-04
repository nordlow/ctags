/*
*   $Id: parrot.c 571 2011-04-15 14:17:48Z lateau $
*
*   Copyright (c) 2011, Daehyub Kim <lateau@gmail.com>
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   This module contains functions for generating tags for Parrot files.
*/

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */
#include "parse.h"

/*
*   DATA DEFINITIONS
*/
#if 0
typedef enum {
    K_NONE = -1,
    K_SUBROUTINE,
    K_RULE,
    K_TOKEN
} parrotKind;

static kindOption ParrotKinds [] = {
	{TRUE, 's', "subroutine", "subroutines"},
	{TRUE, 'r', "rule", "rules"},
	{TRUE, 't', "token", "tokens"}
};
#endif

#define ALNUM "a-zA-Z0-9"
#define PUNCT "!#$%&*+,.\\/:;<=>?@^_`\\{\\|\\}~\\-"

/*
 * Bellow regular expression is not clearly to read and not completed.
 */
static void installParrotRegex (const langType language)
{
    addTagRegex (language, "^\\.sub[ \\t]*'?(infix:)*([" ALNUM "" PUNCT "]+)'?[ \\t]*.*",
            "\\2", "s,subroutine,subroutines", NULL);
    addTagRegex (language, "^rule[ \\t]*([" ALNUM "_]+)[ \\t]*(:\"[" ALNUM "" PUNCT "]+\"*)*",
            "\\1", "r,rule,rules", NULL);
    addTagRegex (language, "^token[ \\t]*([" ALNUM "_]+)[ \\t]*(:\"[" ALNUM "" PUNCT "]+\"*)*",
            "\\1", "t,token,tokens", NULL);
}

extern parserDefinition* ParrotParser (void)
{
	 static const char *const extensions [] = { "pir", "pg", "pasm", "nqp", "pmc", NULL };
	 parserDefinition* def = parserNew ("Parrot");
     def->extensions = extensions;
     def->initialize = installParrotRegex;
     def->regex      = TRUE;
	 return def;
}

/* vi:set tabstop=4 shiftwidth=4: */
