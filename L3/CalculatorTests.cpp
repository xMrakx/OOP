#define CATCH_CONFIG_MAIN
#include "../../catch/catch.hpp"
#include "../Calculator/Calculator.h"

// GetValue

SCENARIO("GetValue with incorrect name must return exception")
{
	Calculator calc;
	calc.AddVaribal("varibal1");
	REQUIRE_THROWS_WITH(calc.GetValue("varibal22"), "No object with this name");
}

SCENARIO("GetValue must return correct value")
{
	Calculator calc;
	calc.SetValueVaribal("varibal1", 12);
	REQUIRE(calc.GetValue("varibal1") == 12);
}

//AddVaribal

SCENARIO("Adding new varibal, varibal must have value = NAN")
{
	Calculator calc;
	calc.AddVaribal("varibal");
	double result = calc.GetValue("varibal");
	REQUIRE(std::isnan(result) == true);
}

SCENARIO("Adding varibal with incorrect name, must return exception 'Incorrect identifier name'")
{
	Calculator calc;
	REQUIRE_THROWS_WITH(calc.AddVaribal("1varibal"), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.AddVaribal(" varibal"), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.AddVaribal("v aribal"), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.AddVaribal(""), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.AddVaribal("переменная"), "Incorrect identifier name");
}

SCENARIO("Adding varibal with alredy busy name, must return exception 'Idenifier name is busy'")
{
	Calculator calc;
	calc.AddVaribal("varibal1");
	REQUIRE_THROWS_WITH(calc.AddVaribal("varibal1"), "Idenifier name is busy");
}

//SetValueVaribal

SCENARIO("Seting value to varibal")
{
	Calculator calc;
	calc.AddVaribal("varibal1");
	calc.SetValueVaribal("varibal1", 12);
	REQUIRE(calc.GetValue("varibal1") == 12);
}

SCENARIO("If varibal does not exist, function should add new varibal. New varibal should equal right value")
{
	Calculator calc;
	calc.SetValueVaribal("varibal1", 10);
	REQUIRE(calc.GetValue("varibal1") == 10);
}

SCENARIO("if new varibal have incorrect name, function should retur exception 'Incorrect identifier name'")
{
	Calculator calc;
	REQUIRE_THROWS_WITH(calc.SetValueVaribal("1varibal", 24), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.SetValueVaribal(" varibal", 24), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.SetValueVaribal("v aribal", 24), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.SetValueVaribal("", 24), "Incorrect identifier name");
	REQUIRE_THROWS_WITH(calc.SetValueVaribal("Переменная", 24), "Incorrect identifier name");
}

//AddFunctionIdentifier

SCENARIO("Adding function equal indentifier, value function should be equal value indentifier")
{
	Calculator calc;
	calc.SetValueVaribal("varibal1", 10);
	calc.AddFunctionIdentifier("function1", "varibal1");
	REQUIRE(calc.GetValue("function1") == 10);
}

SCENARIO("Adding function with alredy busy name, must return exception 'Idenifier name is busy'")
{

	Calculator calc;
	calc.AddVaribal("varibal1");
	calc.AddFunctionIdentifier("function1", "varibal1");
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("function1", "varibal1"), "Idenifier name is busy");
}

SCENARIO("Adding function equal non-existent identifier, must return exception 'Identifier 2 does not exist'")
{
	Calculator calc;
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("function1", "varibal1"), "Identifier 2 does not exist");
}

SCENARIO("Adding function with incorrect name, must return exception 'Incorrect identifier 1 name'")
{
	Calculator calc;
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("1function", "varibal1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier(" function", "varibal1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("f unction", "varibal1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("", "varibal1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionIdentifier("Функция", "varibal1"), "Incorrect identifier 1 name");
}

//AddFunctionOperation


SCENARIO("Adding function with addition 2 varibals, value function must be equal sum of these varibals")
{
	Calculator calc;
	calc.SetValueVaribal("var1", 5);
	calc.SetValueVaribal("var2", 10);
	calc.AddFunctionOperation("fn1", "var1", Operation::add, "var2");
	REQUIRE(calc.GetValue("fn1") == 15);
}

SCENARIO("Adding function with subtraction 2 varibals, value function must be equal sub of these varibals")
{
	Calculator calc;
	calc.SetValueVaribal("var1", 10);
	calc.SetValueVaribal("var2", 5);
	calc.AddFunctionOperation("fn1", "var1", Operation::sub, "var2");
	REQUIRE(calc.GetValue("fn1") == 5);
}

SCENARIO("Adding function with multiply 2 varibals, value function must be equal multiply of these varibals")
{
	Calculator calc;
	calc.SetValueVaribal("var1", 10);
	calc.SetValueVaribal("var2", 5);
	calc.AddFunctionOperation("fn1", "var1", Operation::mult, "var2");
	REQUIRE(calc.GetValue("fn1") == 50);
}

SCENARIO("Adding function with division 2 varibals, value function must be equal div of these varibals")
{
	Calculator calc;
	calc.SetValueVaribal("var1", 10);
	calc.SetValueVaribal("var2", 5);
	calc.AddFunctionOperation("fn1", "var1", Operation::div, "var2");
	REQUIRE(calc.GetValue("fn1") == 2);
}

SCENARIO("Adding function with using one varibal for operation")
{
	Calculator calc;
	calc.SetValueVaribal("var1", 5);
	calc.AddFunctionOperation("fn1", "var1", Operation::add, "var1");
	REQUIRE(calc.GetValue("fn1") == 10);
}

SCENARIO("Adding function where value of one varibal equal NAN, value of function should be equal NAN")
{
	Calculator calc;
	calc.AddVaribal("var1");
	calc.AddVaribal("var2");
	calc.AddFunctionOperation("fn1", "var1", Operation::add, "var2");

	double result = calc.GetValue("fn1");
	REQUIRE(std::isnan(result) == true);

	calc.SetValueVaribal("var1", 12);
	calc.AddFunctionOperation("fn2", "var1", Operation::add, "var2");
	result = calc.GetValue("fn2");
	REQUIRE(std::isnan(result) == true);

	calc.AddFunctionOperation("fn3", "var2", Operation::add, "var1");
	result = calc.GetValue("fn3");
	REQUIRE(std::isnan(result) == true);
}

SCENARIO("Adding function with busy name, should return exception, 'Idenifier 1 name is busy'")
{
	Calculator calc;
	calc.AddVaribal("var1");
	calc.AddFunctionIdentifier("fn1", "var1");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("fn1", "var1", Operation::add, "var1"), "Idenifier 1 name is busy");
	
}

SCENARIO("Addind function with incorrect name")
{
	Calculator calc;
	calc.AddVaribal("var1");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("1fn", "var1", Operation::add, "var1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation(" fn1", "var1", Operation::add, "var1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("f n1", "var1", Operation::add, "var1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("", "var1", Operation::add, "var1"), "Incorrect identifier 1 name");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("функция", "var1", Operation::add, "var1"), "Incorrect identifier 1 name");
}

SCENARIO("Adding function, when one of the varibal does not exist, function must return exception 'Identifier (number) does not exist'")
{
	Calculator calc;
	calc.AddVaribal("var1");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("fn1", "var2", Operation::add, "var1"), "Identifier 1 does not exist");
	REQUIRE_THROWS_WITH(calc.AddFunctionOperation("fn1", "var1", Operation::add, "var2"), "Identifier 2 does not exist");
}



