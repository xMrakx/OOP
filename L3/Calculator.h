#pragma once
#include <string>
#include <map>
#include <vector>
#include "Function.h"

enum class CalcObjectType
{
	varibal,
	function
};

class Calculator
{
public:
	bool AddVaribal(const std::string& name);
	double GetValue(const std::string& name)const;
	bool SetValueVaribal(const std::string& name, double value);
	bool AddFunctionIdentifier(const std::string& name, const std::string& varName);
	bool AddFunctionOperation(
		  const std::string& name
		, const std::string& var1Name
		, Operation operation
		, const std::string& var2Name
	);

private:
	std::map<std::string, CalcObjectType> m_indentifersNames;
	std::map<std::string, Varibal> m_varibals;
	std::map<std::string, Function> m_functions;




	/*
	std::vector<std::string> m_varibals;
	std::vector<std::string> m_functions;
	*/
};

