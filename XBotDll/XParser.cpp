#include "XCommandHandler.h"

bool XCommandHandler::XParser::getFunctionName(string* inStr, string* outStr)
{
	trimStr(inStr);

	int parenthesisOpen  = inStr->find("(");
	int parenthesisClose = inStr->find_last_of(")");
	
	if(parenthesisOpen >= 0 && parenthesisClose >= 0 && parenthesisClose > parenthesisOpen && inStr->size() - 1 == parenthesisClose)
	{
		outStr->assign(*inStr,0,parenthesisOpen);
		return true;
	}
	else
		return false;

}

int XCommandHandler::XParser::getFunctionArgs(string* inStr, vector<string> *outStr)
{
	int parenthesisOpen  = inStr->find("(");
	int parenthesisClose = inStr->find_last_of(")");



	if(parenthesisOpen + 1 != parenthesisClose && !isEmpytArgList(inStr, parenthesisOpen, parenthesisClose) ) 
	{
		string tmp("");
		bool doubleQuote = false;
		for(int i = parenthesisOpen + 1; i <= parenthesisClose ; i++)
		{
			if(inStr->at(i) == '"')
			{
				doubleQuote = !doubleQuote;
			}
			if(doubleQuote || (inStr->at(i) != ',' && inStr->at(i) != ')' ) )
			{
				if(inStr->at(i) != '"' )
					tmp.append(1,inStr->at(i));
			}
			else
			{
				outStr->push_back(tmp);
				tmp.erase();
			}

		}
		
		return outStr->size();
	}
	else
		return outStr->size();
}


bool XCommandHandler::XParser::isEmpytArgList(string* inStr, int start, int end )
{
	bool result = true;
	
	for(int i = start + 1; i < end; i++)
		if(inStr->at(i) !=  ' ')
		{
			result = false;
			break;
		}

	return result;
}

bool XCommandHandler::XParser::isNumericIntArg(string* inStr)
{
	if(inStr->size() == 0)
		return false;
	
	bool result = true;
	
	for(int i = 0; i < inStr->size() && result; i++)
	{
		switch(inStr->at(i))
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':break;
			default: result =  false;
		
		}
	}

	return result;
}

void XCommandHandler::XParser::trimStr(string* inStr)
{	
	if(inStr->size() == 0)
		return;
	
	int firstNonSpace = inStr->find_first_not_of(' ');
	if(firstNonSpace != -1)
		inStr->erase(0,firstNonSpace);

	int lastNonSpace  = inStr->find_last_not_of(' ');
	if(lastNonSpace != -1)
		inStr->erase(lastNonSpace + 1  , (inStr->size() - lastNonSpace) );

}
