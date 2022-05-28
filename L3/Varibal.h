#pragma once
#include <cmath>
#include <vector>

class Varibal
{
public:
	double operator + (Varibal v2)
	{
		return this->m_value + v2.m_value;
	}

	double operator - (Varibal v2)
	{
		return this->m_value - v2.m_value;
	}

	double operator / (Varibal v2)
	{
		return this->m_value / v2.m_value;
	}

	double operator * (Varibal v2)
	{
		return this->m_value * v2.m_value;
	}

	double m_value = NAN;
	std::vector<Varibal*> m_dependencies;
};

