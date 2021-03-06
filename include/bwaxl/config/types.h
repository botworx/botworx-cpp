/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/

/*This gets included by config.h*/
#include <bwai/config/types.h>

	TT_BX,
	TT_FN,
	TT_FN_UNKNOWN,
//
	TT_OP,
	OP_EXIT,
	OP_NOP,
	OP_END,
	OP_ERROR,
	OP_UNDEFINED,
	OP_PUSHARGS,
	OP_EVALARGS,
	OP_EVALARGS1,
	OP_EVALEND,
	OP_BXCALL,
	OP_BXEXEC,
	OP_BXEND,
	OP_POPCATCHER,
	OP_THROW,
	TT_OP_UNKNOWN,
//
	TT_XOP,
	XOP_EVAL,
	XOP_QUOTE,
	XOP_CONS,
	XOP_CAR,
	XOP_CDR,
	XOP_NULL,
	XOP_SET,
	XOP_SETQ,
	XOP_EQ,
	//Numbers
	XOP_NUMBER_EQUAL,
	XOP_NUMBER_NOT_EQUAL,
	XOP_ZEROP,
	XOP_SUB1,
	XOP_SUB,
	XOP_PLUS,
	TT_XOP_UNKNOWN,
//
//AxlTaskKit
	TT_TASK,
	TT_TASK_UNKNOWN,
//AxlFormKit
	BX_INNERFORM,
//AxlFnKit
	BX_DEFUN,
	BX_CATCHER,
	BX_COND,
	BX_AND,
	BX_OR,
	BX_TAGBODY,
	//BX_WHILE,
	TT_BX_UNKNOWN,
	TT_BLOB_UNKNOWN,
//AxlXnKit
	TT_XN,
	XN_UNBOUND,
	XN_TOO_MANY_ARGS,
	XN_NOT_ENOUGH_ARGS,
	XN_BAD_ARG,
	TT_XN_UNKNOWN,
//
	TT_SCOPE,
	TT_SCOPE_UNKNOWN,
