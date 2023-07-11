#pragma once
#include <windows.h>
#include <stdio.h>

/* values for root:
 *
 * HKEY_CLASSES_ROOT 
 * HKEY_CURRENT_USER 
 * HKEY_LOCAL_MACHINE 
 * HKEY_USERS 
 */
class XRegedit  
{
public:
	XRegedit();
	virtual ~XRegedit();

	//open an handle to a registy key with full access
	bool open(const HKEY root, const char* path);

	//retrive the key values, if the value expected isn't a string return false
	bool getString(const char* name, char* result, unsigned long* size);

	//close the handle to the registy key
	bool close();

private:
	HKEY key;
	bool isOpened;
};
