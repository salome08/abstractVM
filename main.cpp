#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Exception.hpp"
#include "main.hpp"
#include <unistd.h>
#include <map>
	
eOperandType strToEoperand(std::string str)
{
	if (str == "int8") return INT8;
	else if (str == "int16") return INT16;
	else if (str == "int32") return INT32;
	else if (str == "float") return FLOAT;
	else return DOUBLE;

}

void run_comand(std::string comand, eOperandType type, std::string value, Factory& factory)
{
	if (comand == "push")  {
		factory.push(factory.createOperand(type, value));
		
	}
	else if (comand == "pop")  {factory.pop();}
	else if (comand == "dump") {factory.dump();}
	else if (comand == "assert") 
	{
		if ((stod(factory.get_frontstack()->toString())) != stod(value))
 			throw Exception("An assert instruction is not true");
	}
	else if (comand == "add") {factory.add();}
	else if (comand == "sub") {factory.sub();}
	else if (comand == "mul") {factory.mul();}
	else if (comand == "div") {factory.div();}
	else if (comand == "mod") {factory.mod();}
	else if (comand == "print") {factory.print();
		
	}
}

void lexer_line(std::string &line, Factory& factory)
{
	std::string comand; 
	std::string type;
	std::string value;
	std::regex reg("\\s?;(?!;)(.*)");
	size_t idx;
  	std::string substring = ";;";
 
  if ((idx = line.find(substring)))
		line = regex_replace(line, reg, "");
	std::regex expression("^((push|assert) (float|double|int8|int16|int32)\\([+-]?([0-9]*[.])?[0-9]+\\))$|^((add|pop|dump|sub|mul|div|mod|print|exit))$|^(;;)$" ); 
	std::smatch match;
	if (regex_search(line, match, expression) || line == "")
	{
		if (match.str(5) != "")
			comand = match.str(5);
		else 
		{
			comand = match.str(2);
			type = match.str(3);
			std::regex expression2("(\\()([+-]?([0-9]*[.])?[0-9]+)(\\))");
			std::smatch match_val;
			if (regex_search(line, match_val, expression2))
			{
				value = match_val.str(2);
			}
		}
	}
	else 
		throw Exception("Error Syntax");


	run_comand(comand, strToEoperand(type), value, factory);
}

void read_standard()
{
	Factory factory;
	std::string line;
	int exit = 0;
	do{
		std::getline (std::cin, line);
	
		lexer_line(line, factory);
		if (line == "exit")
			exit = 1;
		}
	while (line != "exit" && line != ";;");
	if (exit == 0) throw Exception("No exit instruction");
} 

void read_file(char *av)
{
	std::ifstream file(av, std::ios::in);
	std::string line;
	int exit = 0;
	if (file){
	Factory factory;
	while(std::getline(file, line))
	{
		lexer_line(line, factory);
		if (line == "exit")
			exit = 1;
	}
	file.close();
	}
	else 
	std::cerr << "Unable open file" << std::endl;
	if (exit == 0) throw Exception("No exit instruction");
}

int main(int argc, char **argv)
{
	try
	{
	if (argc == 1)
		read_standard();
	else if (argc == 2)
		read_file(argv[1]);	
	else 
		throw Exception("Wrong Format");
	}
	catch (const Exception &e) {
          std::cerr << "ERROR : " << e.what() << std::endl;
   }
	return 0;
}

