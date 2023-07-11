# Microsoft Developer Studio Project File - Name="XBotLauncher" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XBotLauncher - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XBotLauncher.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XBotLauncher.mak" CFG="XBotLauncher - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XBotLauncher - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XBotLauncher - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XBotLauncher - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /O2 /Ob2 /I "$(QTDIR)\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib glaux.lib opengl32.lib glu32.lib detours\detours.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt333.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386 /out:"..\Release\XBot Release 2.0\XBot.exe"

!ELSEIF  "$(CFG)" == "XBotLauncher - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib glaux.lib opengl32.lib glu32.lib detours\detours.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt323.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XBotLauncher - Win32 Release"
# Name "XBotLauncher - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CiniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\LineEditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_LineEditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_xbotlauncherdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_xbotlauncherdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_XGlLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_XListView.cpp
# End Source File
# Begin Source File

SOURCE=.\XBotLauncher.rc
# End Source File
# Begin Source File

SOURCE=.\xbotlauncherdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\xbotlauncherdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\XConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\XBotDll\XFileFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\XGlLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\XListView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CiniFile.h
# End Source File
# Begin Source File

SOURCE=.\LineEditEx.h

!IF  "$(CFG)" == "XBotLauncher - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing LineEditEx.h...
InputDir=.
InputPath=.\LineEditEx.h
InputName=LineEditEx

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XBotLauncher - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing LineEditEx.h...
InputDir=.
InputPath=.\LineEditEx.h
InputName=LineEditEx

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xbotlauncherdialog.h

!IF  "$(CFG)" == "XBotLauncher - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing xbotlauncherdialog.h...
InputDir=.
InputPath=.\xbotlauncherdialog.h
InputName=xbotlauncherdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XBotLauncher - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing xbotlauncherdialog.h...
InputDir=.
InputPath=.\xbotlauncherdialog.h
InputName=xbotlauncherdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xbotlauncherdialogbase.h

!IF  "$(CFG)" == "XBotLauncher - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing xbotlauncherdialogbase.h...
InputDir=.
InputPath=.\xbotlauncherdialogbase.h
InputName=xbotlauncherdialogbase

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XBotLauncher - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing xbotlauncherdialogbase.h...
InputDir=.
InputPath=.\xbotlauncherdialogbase.h
InputName=xbotlauncherdialogbase

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XConfig.h
# End Source File
# Begin Source File

SOURCE=.\XGlLogo.h

!IF  "$(CFG)" == "XBotLauncher - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing XGlLogo.h...
InputDir=.
InputPath=.\XGlLogo.h
InputName=XGlLogo

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XBotLauncher - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing XGlLogo.h...
InputDir=.
InputPath=.\XGlLogo.h
InputName=XGlLogo

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XListView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\xbot.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# End Target
# End Project
