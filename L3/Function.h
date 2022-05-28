#pragma once
#include "Varibal.h"

enum class Operation
{
	non,
	add,
	sub,
	mult,
	div
};

class Function : public Varibal
{
public:
	Operation m_operation;
	Varibal* m_var1;
	Varibal* m_var2;
	bool CalculateFunction();
};

