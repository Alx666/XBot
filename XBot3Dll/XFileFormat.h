// XFileFormat.h: interface for the CXFileFormat class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <list>
#include <map>
#include <string>
#include <sys/types.h> 
#include <sys/stat.h>

using namespace std;

#define STANDARD_TRANSFER_BUFFER 5000000

struct XFF_FILEDESCRIPTOR
{
	string fileName;
	string fileExtension;
	string filePath;
	unsigned int fileSize;
	unsigned int filePosInXFF;
};


class CXFileFormat  
{
	typedef map <string, list<XFF_FILEDESCRIPTOR> > XffMAP;

	public:
		
		CXFileFormat();
		~CXFileFormat();

		void			New(const char* filepath = NULL);
		void			SetXffFilePath(const char* filepath);
		bool			Open(const char* filename);
		void			Close();
		bool			AddFile(const char* filepath, const char* filename, const char* extension);
		bool			RemoveFile(const char* filename, const char* extension);
		unsigned int	GetFile(const char* filename, const char* extension, void** dataBuffer);
		void			GetFileList(list<XFF_FILEDESCRIPTOR> *fileList);
		bool			ExtractFile(const char* destFilepath, const char* filename, const char* extension);
		bool			Write();
		bool			SetTransferBuffer(unsigned int size);

		bool			GetIsBusy()		{return isBusy;};

	private:

		string			currentlyOpenedFilePath;
		string			currentlyOpenedPath;

		FILE*			openedFileStream;
		
		char*			tempBuffer;

		unsigned int	XFF_FILE_TRANSFER_BUFFER;

		bool			isBusy;

		XffMAP			xffMap;


		void	WriteFilesIntoXFF();	
		void	WriteXFFHeader();
		bool	CheckXFFHeader();
		bool	GetFilesMap();
		string	ReadString(FILE* f);
		bool	GetFileDescriptor(const char* filename, const char* extension, XFF_FILEDESCRIPTOR* toFill);


};

