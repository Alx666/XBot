// XFileFormat.cpp: implementation of the CXFileFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "XFileFormat.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXFileFormat::CXFileFormat()
{
	currentlyOpenedFilePath.resize(0);
	
	xffMap.clear();

	isBusy						= false;
		
	XFF_FILE_TRANSFER_BUFFER	= STANDARD_TRANSFER_BUFFER;
		
	tempBuffer					= NULL;
		
	openedFileStream			= NULL;
}

CXFileFormat::~CXFileFormat()
{
	Close();
	
}

bool CXFileFormat::SetTransferBuffer(unsigned int size)
{
	if(GetIsBusy())
		return false;

	XFF_FILE_TRANSFER_BUFFER = size;
	
	delete[] tempBuffer;
	tempBuffer = NULL;
	
	return true;
}



void CXFileFormat::New(const char* filepath)
{
	Close();
	
	if(filepath != NULL)
		SetXffFilePath(filepath);
}

void CXFileFormat::SetXffFilePath(const char* filepath)
{
	currentlyOpenedFilePath.resize(0);
	currentlyOpenedFilePath.append(filepath);
	unsigned int offset = currentlyOpenedFilePath.rfind('\\');
	currentlyOpenedPath	= currentlyOpenedFilePath.substr(0,offset);
}


bool CXFileFormat::Open(const char* filename)
{
	if(!currentlyOpenedFilePath.empty())
		Close();

	SetXffFilePath(filename);
	
	if(openedFileStream)
		fclose(openedFileStream);

	openedFileStream = fopen(filename,"r+b");
	
	if(openedFileStream && CheckXFFHeader())
	{
		isBusy = true;

		bool result = GetFilesMap();
		
		fclose(openedFileStream);
		openedFileStream = NULL;

		isBusy = false;

		return result;
	
	}
	else 
	{
		
		//fclose(openedFileStream);
		openedFileStream = NULL;

		return false;
	}


}

bool CXFileFormat::CheckXFFHeader()
{
	if(!openedFileStream)
		return false;
	
	char header[4] = {0};
	char version[5]	= {0};
	
	fread(header,sizeof(char),3,openedFileStream);
	fread(version,sizeof(char),5,openedFileStream);

	if(strncmp(header,"XFF",3)==0)
		return true;
	else
		return false;

}

bool CXFileFormat::GetFilesMap()
{
	if(!openedFileStream)
		return false;
	
	struct _stat result;
	_stat(currentlyOpenedFilePath.c_str(),&result);
	
	while(ftell(openedFileStream)<result.st_size) // iteriamo il file, cercando tutte le extensions
	{
		string ext = ReadString(openedFileStream);
		unsigned int extSize;
		
		fread(&extSize,sizeof(char),sizeof(unsigned int),openedFileStream);


		unsigned int currentFilePos = ftell(openedFileStream);
		while(ftell(openedFileStream)<currentFilePos + extSize) //una volta trovata una extension, riempiamo la lista della xffMap con i nomi dei file relativi
		{
			string name = ReadString(openedFileStream);
			unsigned int fileSize;
			
			fread(&fileSize,sizeof(char),sizeof(unsigned int),openedFileStream);

			XFF_FILEDESCRIPTOR fd;

			fd.fileExtension	= ext;
			fd.fileName			= name;
			fd.filePath			= currentlyOpenedFilePath.c_str();
			fd.fileSize			= fileSize;
			fd.filePosInXFF		= ftell(openedFileStream);
				
			xffMap[ext].push_back(fd);

			fseek(openedFileStream,fileSize,SEEK_CUR);
		}
		
	}
	return true;
}

string CXFileFormat::ReadString(FILE* f)
{
	if(!f)
		return NULL;
	
	char tmp[2] = {0};
	string str;

	
	while(fread(&tmp[0],sizeof(char),1,f))
		if(tmp[0]==0)
			return str;
		else
			str.append(tmp);
	
		return str;

}



void CXFileFormat::Close()
{
	currentlyOpenedFilePath.resize(0); 
	
	xffMap.clear();
	
	if(openedFileStream)
	{
		fclose(openedFileStream);
		openedFileStream = NULL;
	}

	isBusy = false;
}

bool CXFileFormat::RemoveFile(const char* filename, const char* extension)
{
	string name(filename);
	
	_strupr((char*)extension);//convertiamo la stringa in uppercase
	
	list<XFF_FILEDESCRIPTOR>::iterator listIt = xffMap[extension].begin();
	while(listIt!=xffMap[extension].end())
		if(stricmp(name.c_str(),listIt->fileName.c_str())==0)
		{
			xffMap[extension].erase(listIt);
			
			if(xffMap[extension].size()==0)
				xffMap.erase(extension);

			return true;
		}
		else
			listIt++;

	return false;
}

bool CXFileFormat::AddFile(const char* filepath, const char* filename, const char* extension)
{
	XFF_FILEDESCRIPTOR fd;
	memset(&fd,0,sizeof(fd));
	
	struct _stat result;
	_stat(filepath,&result);	
	
	string path(filepath);
	string name(filename);
	string ext(extension);

	fd.fileSize			= result.st_size;
	fd.fileExtension	= ext;
	fd.filePath			= path;
	fd.fileName			= name;
	
	_strupr((char*)extension);//convertiamo la stringa in uppercase

	//controlliamo non esistano altri file con lo stesso nome ed estensione
	list<XFF_FILEDESCRIPTOR>::iterator listIt = xffMap[extension].begin();
	while(listIt!=xffMap[extension].end())
		if(stricmp(name.c_str(),listIt->fileName.c_str())==0)
			return false;
		else
			listIt++;


	xffMap[extension].push_back(fd);
	
	return true;
}

bool CXFileFormat::Write()
{

	isBusy = true;
	
	//Creiamo un File Temporaneo
	char* tmpFileName = tmpnam(NULL);
	char* tmpFilePath = new char[currentlyOpenedPath.length() + 64];
	
	int strLen = currentlyOpenedPath.length();

	memset(tmpFilePath, 0, strLen + 64);
	memcpy(tmpFilePath, currentlyOpenedPath.c_str(), strLen);
	strcat(tmpFilePath,tmpFileName);
	
	if(openedFileStream)
		fclose(openedFileStream);
	
	openedFileStream = fopen(tmpFilePath,"w+b");
	//Ora abbiamo creato un File Temporaneo


	if (!openedFileStream) // se  la creazione del nuovo file fallisce, return
	{
		isBusy = false;
		return false;
	}
	
	if(!tempBuffer)
		tempBuffer	= new char[XFF_FILE_TRANSFER_BUFFER];
	
	if(!tempBuffer) // se  l'allocazione del tempBuffer fallisce, return
	{
		isBusy = false;
		return false;
	}
	
	memset(tempBuffer,0,XFF_FILE_TRANSFER_BUFFER);

	
	//Scriviamo prima l'header del XFF e poi tutti i file
	WriteXFFHeader();
	
	WriteFilesIntoXFF();	
		
	
	remove(currentlyOpenedFilePath.c_str());
	fclose(openedFileStream);
	openedFileStream = NULL;
	rename(tmpFilePath,currentlyOpenedFilePath.c_str());


	//procedure di CleanUp
	isBusy = false;
	
	delete[] tempBuffer;
	tempBuffer = NULL;
	
	delete[] tmpFilePath;
	tmpFilePath = NULL;	
	//procedure di CleanUp
	
	//riapriamo il file per updatare la fileMap
	string reopen(currentlyOpenedFilePath);
	return Open(reopen.c_str());


}


void CXFileFormat::WriteXFFHeader()
{
	if(!openedFileStream)
		return;
	
	char header[] = "XFFv1.0";
	fwrite(header,sizeof(char),sizeof(header),openedFileStream);

}

void CXFileFormat::WriteFilesIntoXFF()
{
	
	if (!openedFileStream)
		return;

	XffMAP::iterator it = xffMap.begin();
	
	//iteriamo tutte le chiavi della mappa (cioe' tutte le extension)
	for (int i = 0 ; i<xffMap.size() ; i++)
	{
		const char* ext = (it->first).c_str();

		fwrite(ext, sizeof(char), sizeof(ext), openedFileStream);
		
		
		//prendiamo la grandezza totale di tutti i file dell'extension
		//////////////////BEGIN///////////////////////////
		list<XFF_FILEDESCRIPTOR> l = it->second;
		list<XFF_FILEDESCRIPTOR>::iterator listIt = l.begin();
		unsigned int totSize = 0;
		
		while(listIt != l.end())
		{
			totSize+= (listIt->fileSize + sizeof(unsigned int) + listIt->fileName.length() + 1);
			listIt++;
		}
		fwrite(&totSize, sizeof(char), sizeof(totSize), openedFileStream);
		//////////////////END///////////////////////////


		//scriviamo tutti i file dell'extension 
		//////////////////BEGIN///////////////////////////
		listIt = l.begin();
		while(listIt != l.end())
		{
			fwrite(listIt->fileName.c_str(), sizeof(char), listIt->fileName.length() + 1, openedFileStream);
			fwrite(&listIt->fileSize, sizeof(char), sizeof(listIt->fileSize), openedFileStream);

			FILE* fToOpen = fopen(listIt->filePath.c_str(),"rb");

			if(listIt->filePosInXFF!=0)
				fseek(fToOpen,listIt->filePosInXFF,SEEK_SET);
						
			unsigned int readCount = 0, toRead = 0, totReadCount = 0;
			do
			{	
				toRead =	listIt->fileSize - totReadCount;
				if(toRead>XFF_FILE_TRANSFER_BUFFER)
					toRead = XFF_FILE_TRANSFER_BUFFER;
				else
					toRead = listIt->fileSize - totReadCount;

				readCount = fread(tempBuffer,sizeof(char),toRead,fToOpen);
				fwrite(tempBuffer, sizeof(char), readCount, openedFileStream);
				totReadCount += readCount;
			}
			while(totReadCount<listIt->fileSize);

			fclose(fToOpen);
			
			listIt++;
		}
		//////////////////END///////////////////////////

		it++;
	}

}

void CXFileFormat::GetFileList(list<XFF_FILEDESCRIPTOR> *fileList)
{

	XffMAP::iterator mapIt = xffMap.begin();
	
	while(mapIt != xffMap.end())
	{
		list<XFF_FILEDESCRIPTOR>::iterator listIt = mapIt->second.begin();
		while(listIt != mapIt->second.end())
		{
			fileList->push_back(*listIt);
			listIt++;
		}
		mapIt++;
	}
		
}


bool CXFileFormat::GetFileDescriptor(const char* filename, const char* extension,XFF_FILEDESCRIPTOR* toFill)
{
	
	_strupr((char*)extension);//convertiamo la stringa in uppercase

	//iteriamo la mappa dei file, se troviamo il file cercato, diamo la sua posizione all'interno del file
	list<XFF_FILEDESCRIPTOR>::iterator listIt = xffMap[extension].begin();
	while(listIt!=xffMap[extension].end())
		if(stricmp(filename,listIt->fileName.c_str())==0)
		{
			toFill->fileExtension = listIt->fileExtension;
			toFill->fileName	  = listIt->fileName;
			toFill->filePath	  = listIt->filePath;
			toFill->filePosInXFF  =	listIt->filePosInXFF;
			toFill->fileSize	  = listIt->fileSize;
			return true;
		}
		else
			listIt++;

	return false;
}

bool CXFileFormat::ExtractFile(const char* destFilepath, const char* filename, const char* extension)
{
	FILE* f		= fopen(destFilepath,"w+b");

	if(openedFileStream)
		fclose(openedFileStream);
	openedFileStream	= fopen(currentlyOpenedFilePath.c_str(),"rb");
	
	if(!f || !openedFileStream)
	{// se l'apertura di uno dei 2 file fallisce, return;
		fclose(f);
		fclose(openedFileStream);
		openedFileStream = NULL;
		return false;
	}
	isBusy = true;

	
	if(!tempBuffer)
		tempBuffer	= new char[XFF_FILE_TRANSFER_BUFFER];
	
	if(!tempBuffer) // se  l'allocazione del tempBuffer fallisce, return
	{
		isBusy = false;
		return false;
	}
	
	memset(tempBuffer,0,XFF_FILE_TRANSFER_BUFFER);

	

	//ora estraiamo il file
	//////////////////BEGIN///////////////////////////
	XFF_FILEDESCRIPTOR fd;
	if(!GetFileDescriptor(filename,extension,&fd))
		return false;

	fseek(openedFileStream,fd.filePosInXFF,SEEK_SET);
	
	unsigned int readCount = 0, toRead = 0, totReadCount = 0;
	do
	{	
		toRead =	fd.fileSize - totReadCount;
		if(toRead>XFF_FILE_TRANSFER_BUFFER)
			toRead = XFF_FILE_TRANSFER_BUFFER;
		else
			toRead = fd.fileSize - totReadCount;

		readCount = fread(tempBuffer,sizeof(char),toRead,openedFileStream);
		fwrite(tempBuffer, sizeof(char), readCount, f);
		totReadCount += readCount;
	}
	while(totReadCount<fd.fileSize);
	//////////////////END///////////////////////////
	
	
	//procedure di CleanUp
	fclose(f);
	fclose(openedFileStream);
	openedFileStream = NULL;

	isBusy = false;
	
	delete[] tempBuffer;
	tempBuffer = NULL;
	//procedure di CleanUp

	return true;
}
unsigned int CXFileFormat::GetFile(const char* filename, const char* extension, void** dataBuffer)
{
	if(GetIsBusy())
		return 0;

	XFF_FILEDESCRIPTOR fd;
	if(!GetFileDescriptor(filename,extension,&fd))
		return 0;	

	if(!openedFileStream)
	{
		openedFileStream = fopen(currentlyOpenedFilePath.c_str(),"rb");
		if(!openedFileStream)
		{
			*dataBuffer = NULL;
			return 0;
		}
	}

	*dataBuffer = (void*)new char[fd.fileSize];
	memset(*dataBuffer,0,fd.fileSize);

	fseek(openedFileStream,fd.filePosInXFF,SEEK_SET);
	unsigned int byteReads = fread(*dataBuffer,sizeof(char),fd.fileSize,openedFileStream);

	return byteReads;
}
