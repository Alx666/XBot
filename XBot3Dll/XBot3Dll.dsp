# Microsoft Developer Studio Project File - Name="XBot3Dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=XBot3Dll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XBot3Dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XBot3Dll.mak" CFG="XBot3Dll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XBot3Dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XBot3Dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XBot3Dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XBOT3DLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XBOT3DLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 Winmm.lib d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\Release\XBot Release 3.0\UT2k4.dll"

!ELSEIF  "$(CFG)" == "XBot3Dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XBOT3DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XBOT3DLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\Debug 3.0\UT2K4.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XBot3Dll - Win32 Release"
# Name "XBot3Dll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ApiHijack.cpp
# End Source File
# Begin Source File

SOURCE=.\CIniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\dllmain.cpp
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3D8.cpp
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3DDevice8.cpp
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3DTexture8.cpp
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirectInput8.cpp
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirectInputDevice8.cpp
# End Source File
# Begin Source File

SOURCE=.\Hooks.cpp
# End Source File
# Begin Source File

SOURCE=.\ModuleHider.cpp
# End Source File
# Begin Source File

SOURCE=.\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\UObject.cpp
# End Source File
# Begin Source File

SOURCE=.\UPickup.cpp
# End Source File
# Begin Source File

SOURCE=.\UTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\XAim.cpp
# End Source File
# Begin Source File

SOURCE=.\XAimMode.cpp
# End Source File
# Begin Source File

SOURCE=.\XAimModeInstantRay.cpp
# End Source File
# Begin Source File

SOURCE=.\XBot.cpp
# End Source File
# Begin Source File

SOURCE=.\XBot2.cpp
# End Source File
# Begin Source File

SOURCE=.\XClient.cpp
# End Source File
# Begin Source File

SOURCE=.\XCommandHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\XBotLauncher\XConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\XConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\XD3DAnalyzer.cpp
# End Source File
# Begin Source File

SOURCE=.\XDodger.cpp
# End Source File
# Begin Source File

SOURCE=.\XDrawer.cpp
# End Source File
# Begin Source File

SOURCE=.\XFileFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\XIMode.cpp
# End Source File
# Begin Source File

SOURCE=.\XIModeAuto.cpp
# End Source File
# Begin Source File

SOURCE=.\XInputHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\XMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\XParser.cpp
# End Source File
# Begin Source File

SOURCE=.\XSock.cpp
# End Source File
# Begin Source File

SOURCE=.\XTextureLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\XUT2k4CommandHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\XUTSock.cpp
# End Source File
# Begin Source File

SOURCE=.\XWeapon.cpp
# End Source File
# Begin Source File

SOURCE=.\XWeaponManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ApiHijack.h
# End Source File
# Begin Source File

SOURCE=.\CIniFile.h
# End Source File
# Begin Source File

SOURCE=.\Crc32.h
# End Source File
# Begin Source File

SOURCE=.\CrcTable.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3D8.h
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3DDevice8.h
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirect3DTexture8.h
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirectInput8.h
# End Source File
# Begin Source File

SOURCE=.\FAKE_IDirectInputDevice8.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\Hooks.h
# End Source File
# Begin Source File

SOURCE=.\ModuleHider.h
# End Source File
# Begin Source File

SOURCE=.\structs.h
# End Source File
# Begin Source File

SOURCE=.\Timer.h
# End Source File
# Begin Source File

SOURCE=.\UObject.h
# End Source File
# Begin Source File

SOURCE=.\UPickup.h
# End Source File
# Begin Source File

SOURCE=.\UTarget.h
# End Source File
# Begin Source File

SOURCE=.\XAim.h
# End Source File
# Begin Source File

SOURCE=.\XAimMode.h
# End Source File
# Begin Source File

SOURCE=.\XAimModeInstantRay.h
# End Source File
# Begin Source File

SOURCE=.\XBot.h
# End Source File
# Begin Source File

SOURCE=.\XClient.h
# End Source File
# Begin Source File

SOURCE=.\XCommandHandler.h
# End Source File
# Begin Source File

SOURCE=.\XConsole.h
# End Source File
# Begin Source File

SOURCE=.\XD3DAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\XDodger.h
# End Source File
# Begin Source File

SOURCE=.\XDrawer.h
# End Source File
# Begin Source File

SOURCE=.\XFileFormat.h
# End Source File
# Begin Source File

SOURCE=.\XIMode.h
# End Source File
# Begin Source File

SOURCE=.\XIModeAuto.h
# End Source File
# Begin Source File

SOURCE=.\XInputHandler.h
# End Source File
# Begin Source File

SOURCE=.\XMenu.h
# End Source File
# Begin Source File

SOURCE=.\XParser.h
# End Source File
# Begin Source File

SOURCE=.\XSock.h
# End Source File
# Begin Source File

SOURCE=.\XTextureLogger.h
# End Source File
# Begin Source File

SOURCE=.\XUT2k4CommandHandler.h
# End Source File
# Begin Source File

SOURCE=.\XUTSock.h
# End Source File
# Begin Source File

SOURCE=.\XWeapon.h
# End Source File
# Begin Source File

SOURCE=.\XWeaponManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
