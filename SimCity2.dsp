# Microsoft Developer Studio Project File - Name="SimCity2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SimCity2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SimCity2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimCity2.mak" CFG="SimCity2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimCity2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SimCity2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimCity2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SimCity2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SimCity2 - Win32 Release"
# Name "SimCity2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MaskedBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\SimCity2.cpp
# End Source File
# Begin Source File

SOURCE=.\SimCity2.rc
# End Source File
# Begin Source File

SOURCE=.\SimCity2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolsDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Classes.h
# End Source File
# Begin Source File

SOURCE=.\MaskedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimCity2.h
# End Source File
# Begin Source File

SOURCE=.\SimCity2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolsDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_10.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_11.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_12.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_13.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_14.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_15.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_5.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_6.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_7.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_8.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\_9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\airport.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blank.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ch1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ch2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ch3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ch4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cl1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cl2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cl3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cl4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cm1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cm2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cm3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cm4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\coal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cu1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cu2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cu3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cu4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\cur.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fire.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forest.bmp
# End Source File
# Begin Source File

SOURCE=.\res\i.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ih1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ih2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ih4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\nopower.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Nuclear.bmp
# End Source File
# Begin Source File

SOURCE=.\res\p.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pline3id.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pline3il.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pline3ir.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pline3iu.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pline4i.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plinebl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plinebr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plineh.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plinetl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plinetr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\plinev.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\POLICE.BMP
# End Source File
# Begin Source File

SOURCE=.\res\rail3id.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rail3il.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Rail3ir.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rail3iu.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Rail4i.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railbl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railbr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railh.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railtl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railtr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Railv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rh1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rh3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rh4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rl1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rl2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rl3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rl4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rm1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rm2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rm3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rm4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Road3id.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Road3il.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Road3ir.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Road3iu.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Road4i.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Roadbl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Roadbr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\roadh.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Roadtl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Roadtr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\roadv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ru1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ru2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ru3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ru4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\seaport.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SimCity2.ico
# End Source File
# Begin Source File

SOURCE=.\res\SimCity2.rc2
# End Source File
# Begin Source File

SOURCE=.\res\stadium.bmp
# End Source File
# Begin Source File

SOURCE=.\res\water.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~10.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~11.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~12.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~13.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~14.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~15.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~5.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~6.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~7.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~8.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\~9.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
