#include "Function.h"

bool Function::CalculateFunction()
{
	if (m_operation == Operation::non)
	{
		m_value = m_var1->m_value;
		return true;
	}
	if (std::isnan(m_var1->m_value) || std::isnan(m_var2->m_value))
	{
		m_value = NAN;
		return true;
	}
	
	switch (m_operation)
	{
	case Operation::add:
		m_value = *m_var1 + *m_var2;
		break;
	case Operation::sub:
		m_value = *m_var1 - *m_var2;
		break;
	case Operation::mult:
		m_value = *m_var1 * *m_var2;
		break;
	case Operation::div:
		m_value = *m_var1 / *m_var2;
		break;
	}
	return true;
}
