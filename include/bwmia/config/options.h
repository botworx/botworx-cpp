/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Mia_options_H
#define _Mia_options_H

#include <bwai/config/options.h>

//TODO:no distinguishable difference ... possibly even better without copy-on-write.
//although ... topics don't copy facts ... just copy list ...
#define MIA_OPTION_COPYONWRITE 0
#define MIA_OPTION_TOPIC_DEEPCOPY 0

#endif //_Mia_options_H