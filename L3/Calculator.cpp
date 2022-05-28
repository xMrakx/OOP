#include "Calculator.h"
#include <regex>
#include <iostream>
#include <algorithm>
#include <string>

bool Calculator::AddVaribal(const std::string& name)
{
	std::regex regular(R"(^([a-z_A-Z]\w*)$)");
	if (std::regex_match(name.c_str(), regular))
	{	
		auto it = m_indentifersNames.find(name);
		if (it == m_indentifersNames.end())
		{
			Varibal var;
			m_varibals.insert(make_pair(name, var));
			m_indentifersNames.insert(make_pair(name, CalcObjectType::varibal));
			return true;
		}
		throw std::exception("Idenifier name is busy");
	}
	throw std::exception("Incorrect identifier name");
	
}

double Calculator::GetValue(const std::string& name)const
{
	auto it = m_indentifersNames.find(name);
	if (it != m_indentifersNames.end())
	{
		if (it->second == CalcObjectType::varibal)
		{
			return m_varibals.at(name).m_value;
		}
		return m_functions.at(name).m_value;
	}

	throw std::exception("No object with this name");
}

bool Calculator::SetValueVaribal(const std::string& name, double value)
{
	auto it = m_varibals.find(name);
	if (it == m_varibals.end())
	{
		try
		{
			AddVaribal(name);
		}
		catch (const std::exception& err)
		{
			throw err;
		}
	}
	m_varibals[name].m_value = value;
	return true;
}

bool Calculator::AddFunctionIdentifier(const std::string& name, const std::string& varName)
{
	std::regex regular(R"(^([a-z_A-Z]\w*)$)");
	if (std::regex_match(name.c_str(), regular))
	{
		auto it = m_indentifersNames.find(name);
		if (it == m_indentifersNames.end())
		{
			auto it1 = m_indentifersNames.find(varName);
			if (it1 != m_indentifersNames.end())
			{
				Function fn;
				fn.m_var2 = NULL;
				fn.m_operation = Operation::non;
				if (it1->second == CalcObjectType::varibal)
				{
					fn.m_value = m_varibals[varName].m_value;
					fn.m_var1 = &m_varibals[varName];
				}
				else
				{
					fn.m_value = m_functions[varName].m_value;
					fn.m_var1 = &m_functions[varName];
				}
				m_functions.insert(make_pair(name, fn));
				m_indentifersNames.insert(make_pair(name, CalcObjectType::function));
				

				return true;
			}
			
			throw std::exception("Identifier 2 does not exist");
		}

		throw std::exception("Idenifier name is busy");
	}

	throw std::exception("Incorrect identifier 1 name");
}

bool Calculator::AddFunctionOperation(
	  const std::string& name
	, const std::string& var1Name
	, Operation operation
	, const std::string& var2Name
)
{
	std::regex regular(R"(^([a-z_A-Z]\w*)$)");
	if (std::regex_match(name.c_str(), regular))
	{
		auto it = m_indentifersNames.find(name);
		if (it == m_indentifersNames.end())
		{
			Function fn;
			fn.m_operation = operation;
			std::string varName = var1Name;
			for (int i = 0; i < 2; i++)
			{
				auto var = m_indentifersNames.find(varName);
				if (var != m_indentifersNames.end())
				{
					if (var->second == CalcObjectType::varibal)
					{
						(i == 0) ? fn.m_var1 = &m_varibals[varName] : fn.m_var2 = &m_varibals[varName];
					}
					else
					{
						(i == 0) ? fn.m_var1 = &m_functions[varName] : fn.m_var2 = &m_functions[varName];
					}
					varName = var2Name;
					continue;
				}

				std::string err = "Identifier " + std::to_string(i + 1) + " does not exist";
				throw std::exception(err.c_str());
			}
			fn.CalculateFunction();
			m_functions.insert(make_pair(name, fn));
			m_indentifersNames.insert(make_pair(name, CalcObjectType::function));
			return true;
			
		}

		throw std::exception("Idenifier 1 name is busy");
	}

	throw std::exception("Incorrect identifier 1 name");
}
