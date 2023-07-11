# Microsoft Developer Studio Project File - Name="XTools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XTools - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XTools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XTools.mak" CFG="XTools - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XTools - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XTools - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XTools - Win32 Release"

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
# ADD CPP /nologo /MD /w /W0 /GX /O1 /I "." /I "$(QTDIR)\include" /I "C:\Cpp\XBot\XTools" /I "C:\Qt\3.3.3\mkspecs\win32-msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "QT_NO_DEBUG" /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "detours/detours.lib" "qt-mt333.lib" "qtmain.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "opengl32.lib" "glu32.lib" "delayimp.lib" delayimp.lib /nologo /subsystem:windows /machine:IX86 /out:"..\Release\XTools 2.0\XTools.exe" /libpath:"$(QTDIR)\lib" /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Zi /Od /I "." /I "$(QTDIR)\include" /I "C:\Cpp\XBot\XTools" /I "C:\Qt\3.3.3\mkspecs\win32-msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "UNICODE" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /FD /GZ -Zm200 /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "qt-mt333.lib" "qtmain.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "imm32.lib" "winmm.lib" "wsock32.lib" "winspool.lib" "opengl32.lib" "glu32.lib" "delayimp.lib" /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(QTDIR)\lib"

!ENDIF 

# Begin Target

# Name "XTools - Win32 Release"
# Name "XTools - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=CIniFile.cpp
# End Source File
# Begin Source File

SOURCE=LineEditEx.cpp
# End Source File
# Begin Source File

SOURCE=main.cpp
# End Source File
# Begin Source File

SOURCE=xbotlauncherdialog.cpp
# End Source File
# Begin Source File

SOURCE=xbotlauncherdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=XConfig.cpp
# End Source File
# Begin Source File

SOURCE=XFileFormat.cpp
# End Source File
# Begin Source File

SOURCE=XGlLogo.cpp
# End Source File
# Begin Source File

SOURCE=XListView.cpp
# End Source File
# Begin Source File

SOURCE=.\XTools.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=CIniFile.h
# End Source File
# Begin Source File

SOURCE=detours\detours.h
# End Source File
# Begin Source File

SOURCE=LineEditEx.h

!IF  "$(CFG)" == "XTools - Win32 Release"

USERDEP__LINEE=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing LineEditEx.h...
InputPath=LineEditEx.h

"moc_LineEditEx.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc LineEditEx.h -o moc_LineEditEx.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

USERDEP__LINEE=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing LineEditEx.h...
InputPath=LineEditEx.h

"moc_LineEditEx.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc LineEditEx.h -o moc_LineEditEx.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=resource.h
# End Source File
# Begin Source File

SOURCE=xbotlauncherdialog.h

!IF  "$(CFG)" == "XTools - Win32 Release"

USERDEP__XBOTL=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing xbotlauncherdialog.h...
InputPath=xbotlauncherdialog.h

"moc_xbotlauncherdialog.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc xbotlauncherdialog.h -o moc_xbotlauncherdialog.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

USERDEP__XBOTL=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing xbotlauncherdialog.h...
InputPath=xbotlauncherdialog.h

"moc_xbotlauncherdialog.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc xbotlauncherdialog.h -o moc_xbotlauncherdialog.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=xbotlauncherdialogbase.h

!IF  "$(CFG)" == "XTools - Win32 Release"

USERDEP__XBOTLA=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing xbotlauncherdialogbase.h...
InputPath=xbotlauncherdialogbase.h

"moc_xbotlauncherdialogbase.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc xbotlauncherdialogbase.h -o moc_xbotlauncherdialogbase.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

USERDEP__XBOTLA=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing xbotlauncherdialogbase.h...
InputPath=xbotlauncherdialogbase.h

"moc_xbotlauncherdialogbase.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc xbotlauncherdialogbase.h -o moc_xbotlauncherdialogbase.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=XConfig.h
# End Source File
# Begin Source File

SOURCE=XFileFormat.h
# End Source File
# Begin Source File

SOURCE=XGlLogo.h

!IF  "$(CFG)" == "XTools - Win32 Release"

USERDEP__XGLLO=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing XGlLogo.h...
InputPath=XGlLogo.h

"moc_XGlLogo.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc XGlLogo.h -o moc_XGlLogo.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

USERDEP__XGLLO=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing XGlLogo.h...
InputPath=XGlLogo.h

"moc_XGlLogo.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc XGlLogo.h -o moc_XGlLogo.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=XListView.h

!IF  "$(CFG)" == "XTools - Win32 Release"

USERDEP__XLIST=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing XListView.h...
InputPath=XListView.h

"moc_XListView.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc XListView.h -o moc_XListView.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "XTools - Win32 Debug"

USERDEP__XLIST=""$(QTDIR)\bin\moc.exe""	
# Begin Custom Build - Moc'ing XListView.h...
InputPath=XListView.h

"moc_XListView.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc XListView.h -o moc_XListView.cpp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\XTools.ico
# End Source File
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=moc_LineEditEx.cpp
# End Source File
# Begin Source File

SOURCE=moc_xbotlauncherdialog.cpp
# End Source File
# Begin Source File

SOURCE=moc_xbotlauncherdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=moc_XGlLogo.cpp
# End Source File
# Begin Source File

SOURCE=moc_XListView.cpp
# End Source File
# End Group
# End Target
# End Project
