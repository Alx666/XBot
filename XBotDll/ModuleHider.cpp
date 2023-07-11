// References:
//  Tetsuo       (http://www.game-deception.com)
//  NTinternals  (http://undocumented.ntinternals.net)
//  Phrack Inc.  (http://www.phrack.org)


//#define TEST

#include "ModuleHider.h"


void  HideModuleEx (const unsigned short * szPath , ELIST eList)
{
	PPEB Peb = (PPEB)0x7ffdf000; // Static pointer to the Process Environment Block

	if (Peb && Peb->LoaderData && Peb->LoaderData->Initialized)
	{
		PLIST_ENTRY pListHead = NULL, pListPtr = NULL;
		DWORD dOffset = 0;

		switch (eList) // There are 3 module lists with different offsets
		{
			case LIST_LoadOrder:
				pListHead = pListPtr = &(Peb->LoaderData->InLoadOrderModuleList);
				dOffset = 0x24;
				break;

			case LIST_MemoryOrder:
				pListHead = pListPtr = &(Peb->LoaderData->InMemoryOrderModuleList);
				dOffset = 0x1C;
				break;

			case LIST_InitOrder:
				pListHead = pListPtr = &(Peb->LoaderData->InInitializationOrderModuleList);
				dOffset = 0x14;
				break;
		}

		if (pListHead && pListPtr)
		{
			int i = 0;//TMP

			do // Loop thru Flink
			{
				pListPtr = pListPtr->Flink;
				unsigned short* p = ((PUNICODE_STRING)((PCHAR)pListPtr + dOffset))->Buffer;

				if (!_wcsicmp(p, szPath)) // We found our module, so lets hide it
				{
						//(pListPtr->Blink)->Flink = pListPtr->Flink;
						//(pListPtr->Flink)->Blink = pListPtr->Blink;
						memset(((PUNICODE_STRING)((PCHAR)pListPtr + dOffset))->Buffer,0,((PUNICODE_STRING)((PCHAR)pListPtr + dOffset))->Length);
						#ifdef TEST
							char str[MAX_PATH];
							sprintf(str,"\n-> OK ");
							fwrite(str,sizeof(char),strlen(str),logfile);
						#endif

					break;
				}
				#ifdef TEST
					i++;
					char str2[MAX_PATH];
					wsprintf(str2,"\n->FLINK %i  %ls",i,p);
					fwrite(str2,sizeof(char),strlen(str2),logfile);
				#endif
			
			} while (pListPtr->Flink != pListHead );
		}
	}
	
	return;
}


void HideModule (HINSTANCE hModule)
{					

	unsigned short szPath[MAX_PATH];

	GetModuleFileNameW(hModule, szPath, MAX_PATH);

	HideModuleEx(szPath, LIST_LoadOrder);
	HideModuleEx(szPath, LIST_MemoryOrder);
	HideModuleEx(szPath, LIST_InitOrder);

						#ifdef TEST
						char str[MAX_PATH];
						sprintf(str,"\n-> END! ");
						fwrite(str,sizeof(char),strlen(str),logfile);
						#endif


}

