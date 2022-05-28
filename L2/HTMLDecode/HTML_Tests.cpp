#define CATCH_CONFIG_MAIN
#include "../../catch/catch.hpp"
#include "../HTML/Decode.h"
#include <iostream>

SCENARIO("Empty string, function must return empty string")
{
	std::string inputString = "";
	REQUIRE(HtmlDecode(inputString) == "");
}

SCENARIO("String with html obj, function must decode them")
{
	std::string inputString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(inputString) == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("& and ; without html obj, must writing in out string")
{
	std::string inputString = "hi & i&apos;am ;";
	REQUIRE(HtmlDecode(inputString) == "hi & i'am ;");
}

SCENARIO("Html object in other html object")
{
	std::string inputString = "hi i&&apos;apos;m";
	REQUIRE(HtmlDecode(inputString) == "hi i&'apos;m");
}

SCENARIO("String '&&&&;;;;;' should not change")
{
	std::string inputString = "&&&&;;;;;";
	REQUIRE(HtmlDecode(inputString) == inputString);
}

SCENARIO("String '&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;' should should not change")
{
	std::string inputString = "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;";
	REQUIRE(HtmlDecode(inputString) == inputString);
}


