#pragma once
#include <map>
#include "XWeapon.h"
#include "CrcTable.h" //TEMP, spostare i define su file di configurazione

using namespace std;

class XFireMode;
class XFireModeDirectInstantOnKeydown;
class XWeaponManager  
{
	typedef map<int, XWeapon*> XWeaponMap;

public:
	XWeaponManager();
	~XWeaponManager();

	void loadWeaponDefinitions();
	void checkCurrentWeapon(int crc);
private:
	int lastWeaponCrc;
	XWeapon* currentWeapon;
	XWeaponMap weapMap;

	void setWeaponFromLastCrc();

};
