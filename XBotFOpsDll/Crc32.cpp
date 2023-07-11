/*

This program is copyright 2003 by evilbert.
Parts of this code are taken from Crc32 by Brian Friesen

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include "crc32.h"

CCrc32::CCrc32(void)
{
	m_pdwCrc32Table = NULL;
}

CCrc32::~CCrc32(void)
{
	Free();
}

void CCrc32::Init(void)
{
	// This is the official polynomial used by CRC32 in PKZip.
	// Often times the polynomial shown reversed as 0x04C11DB7.
	DWORD dwPolynomial = 0xEDB88320;
	int i, j;

	Free();
	m_pdwCrc32Table = new DWORD[256];

	DWORD dwCrc;
	for (i = 0; i < 256; i++)
	{
		dwCrc = i;
		for (j = 8; j > 0; j--)
		{
			if (dwCrc & 1)
				dwCrc = (dwCrc >> 1) ^ dwPolynomial;
			else
				dwCrc >>= 1;
		}
		m_pdwCrc32Table[i] = dwCrc;
	}
}

void CCrc32::Free(void)
{
	if (m_pdwCrc32Table != NULL)
		delete m_pdwCrc32Table;
	m_pdwCrc32Table = NULL;
}

DWORD CCrc32::GetCrc32(BYTE *pData, unsigned int size)
{
	DWORD Result = 0xFFFFFFFF;
	for (unsigned int i = 0; i < size; i++)
	{
		Result = (Result >> 8) ^ m_pdwCrc32Table[(*pData++) ^ (Result & 0x000000FF)];
	}
	return Result;
}

