#include "XRegedit.h"

XRegedit::XRegedit()
{
	isOpened = false;
}

XRegedit::~XRegedit()
{

}

bool XRegedit::open(const HKEY root, const char* path)
{
	int res;
	res = RegOpenKeyEx(HKEY_LOCAL_MACHINE , path, 0, KEY_ALL_ACCESS, &key);

	if(res == ERROR_SUCCESS)
		isOpened = true;
	else
		isOpened = false;

	return isOpened;
}

bool XRegedit::getString(const char* name, char* result, unsigned long* size)
{
	int res;
	DWORD type;

	res = RegQueryValueEx(key, name, 0, &type, (LPBYTE)result, size);

	if(ERROR_SUCCESS != res || type != REG_SZ)
		return false;

	return true;
}

bool XRegedit::close()
{
	if(isOpened)
	{
		int res = RegCloseKey(key);
		
		if(ERROR_SUCCESS == res)
			return false;

		isOpened = false;
	}

	return true;
}