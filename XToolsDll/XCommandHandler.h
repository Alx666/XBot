#pragma once

#include <vector>
#include <string>
#include <map>
using namespace std;

class XCommandHandler
{
	public:

		virtual void processParsedCommand(char* &result) = 0;
		virtual void buildCommandList() = 0;
	
		void processCommand(const char* command, char* &result);
		bool autoCompleteLine(string* inStr, string* outStr);

	protected:

		string rawCommand;
		string funcName;
		vector<string> funcArgs;
		char nFuncArgs;

		map<string , string*> commandList;

		class XParser
		{
			public:
						
				bool getFunctionName(string* inStr, string* outStr);
				int  getFunctionArgs(string* inStr, vector<string> *outStr);
				bool isEmpytArgList(string* inStr, int start, int end );
				bool isNumericIntArg(string* inStr);
				void trimStr(string* inStr);

		};

		XParser parser;


};