#include "Decode.h"
#include <string>
#include <sstream>
#include <map>

#include <iostream>
std::string HtmlDecode(const std::string& html)
{
	std::string out = "";
	std::string htmlObj = "";

	std::map<std::string, char> htmlObjects = {
		{"&quot;", '\"'},
		{"&apos;", '\''},
		{"&lt;",   '<' },
		{"&gt;",   '>' },
		{"&amp;",  '&' }
	};

	int posApmp = 0;
	int posSemi = -1;
	int findIndex = 0;
	while ((posApmp = html.find('&', findIndex)) != -1)
	{
		out.append(html, findIndex, posApmp - findIndex);
		findIndex = posApmp; 
		if ((posApmp > posSemi) && ((posSemi = html.find(';', findIndex)) == -1))
		{
			break;
		}

		htmlObj.append(html, findIndex, posSemi - findIndex + 1);

		auto it = htmlObjects.find(htmlObj);
		if (it != htmlObjects.end())
		{
			out += htmlObjects[htmlObj];
			findIndex = posSemi + 1;
		}
		else
		{
			out += '&';
			posApmp = findIndex + 1;
			findIndex = posApmp;
		}
		htmlObj = "";
		
		
	}
	out.append(html, findIndex);
	
	return out;
}