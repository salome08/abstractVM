#ifndef MAIN_HPP
# define MAIN_HPP

#include <climits>
#include <cfloat>

enum eOperandType {
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
};
typedef enum eOperandType eOperandType;

typedef struct s_opType {
	eOperandType 	type;
	std::string 	name;
	int 			precision; ///// type = opTypes[name].type
	double			min;
	double			max;
} t_opType;

static t_opType opTypes[] =
{
	{INT8, "int8", 0, CHAR_MIN, CHAR_MAX},
	{INT16, "int16", 1, INT_MIN, INT_MAX},
	{INT32, "int32", 2, LONG_MIN, LONG_MAX},
	{FLOAT, "float", 3, FLT_MIN, FLT_MAX},
	{DOUBLE, "double", 4, DBL_MIN, DBL_MAX}
};

#endif