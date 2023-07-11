#include "XCommandHandler.h"


void XCommandHandler::processCommand(const char* command, char* &result)
{
	
	rawCommand.erase();
	rawCommand.append(command);
	funcName.erase();
	funcArgs.clear();

	if(parser.getFunctionName(&rawCommand, &funcName))
		nFuncArgs = parser.getFunctionArgs(&rawCommand, &funcArgs);

	_strlwr((char*)funcName.c_str());
	
	processParsedCommand(result);

}

bool XCommandHandler::autoCompleteLine(string* inStr, string* outStr)
{
	string workStr(*inStr);
	
	parser.trimStr(&workStr);
	
	if(workStr.size() == 0)
	{
		outStr->erase();
		return false;
	}
	
	string str("");

	int spacePos = workStr.find_last_of(' ');
	outStr->assign(workStr, spacePos + 1 , workStr.size() - spacePos );	
	string firstChar(1,(*outStr)[0]);

	if(commandList.find(firstChar) == commandList.end())
	{
		outStr->erase();
		return false;
	}

	int count = 0;
	for(int i = 0; commandList[firstChar][i].size() != 0 ; i++)
	{
		if(commandList[firstChar][i].find(*outStr) == 0 )
		{
			if(count)
				str.append("\n  ");
			str.append(commandList[firstChar][i]);
			str.append("() ");
			count++;
		}
	}
	
	if(count == 1)
	{
		str.insert(0, workStr, 0 , spacePos + 1);
		str.erase(str.size() - 1,1);
		*outStr = str;
		return true;
	}
	else if (count > 0)
	{
		string s("Commands Begininning With \'");
		s.append(*outStr);
		s.append("\' : \n\n  ");
		s.append(str);
		*outStr = s;
		return false;
	}
	else
	{
		outStr->erase();
		return false;
	}
}



