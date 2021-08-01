!include x64.nsh
Name "RealSenseID SDK for Visual C++ 64-bit"
OutFile "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}RealSenseID-2.1.0-vc64.exe"
InstallDir "c:\RealSenseID64"

SetCompressor bzip2

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "RealSenseID SDK for Visual C++ 64-bit (required)"
!ifdef WIN64
	${If} ${RunningX64}
	${DisableX64FSRedirection}
	${Endif}
!endif
	SectionIn RO
!ifdef GCC
	IfFileExists $SYSDIR/libturbojpeg.dll exists 0
!else
	IfFileExists $SYSDIR/turbojpeg.dll exists 0
!endif
	goto notexists
	exists:
!ifdef GCC
	MessageBox MB_OK "An existing version of the RealSenseID SDK for Visual C++ 64-bit is already installed.  Please uninstall it first."
!else
	MessageBox MB_OK "An existing version of the RealSenseID SDK for Visual C++ 64-bit or the TurboJPEG SDK is already installed.  Please uninstall it first."
!endif
	quit

	notexists:
	SetOutPath $SYSDIR
!ifdef GCC
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libturbojpeg.dll"
!else
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}turbojpeg.dll"
!endif
	SetOutPath $INSTDIR\bin
!ifdef GCC
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libturbojpeg.dll"
!else
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}turbojpeg.dll"
!endif
!ifdef GCC
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libjpeg-62.dll"
!else
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}jpeg62.dll"
!endif
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}cjpeg.exe"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}djpeg.exe"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}jpegtran.exe"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}tjbench.exe"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}rdjpgcom.exe"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}wrjpgcom.exe"
	SetOutPath $INSTDIR\lib
!ifdef GCC
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libturbojpeg.dll.a"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libturbojpeg.a"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libjpeg.dll.a"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\libjpeg.a"
!else
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}turbojpeg.lib"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}turbojpeg-static.lib"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}jpeg.lib"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\${BUILDDIR}jpeg-static.lib"
!endif
	SetOutPath $INSTDIR\lib\pkgconfig
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\pkgscripts\libjpeg.pc"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\pkgscripts\libturbojpeg.pc"
	SetOutPath $INSTDIR\lib\cmake\RealSenseID
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\pkgscripts\RealSenseIDConfig.cmake"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\pkgscripts\RealSenseIDConfigVersion.cmake"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\win\RealSenseIDTargets.cmake"
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\win\RealSenseIDTargets-release.cmake"
!ifdef JAVA
	SetOutPath $INSTDIR\classes
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\java\turbojpeg.jar"
!endif
	SetOutPath $INSTDIR\include
	File "C:/Elpas/e4ext-intel-realsense/windows/tools/3rdparty/libjpeg-turbo_2_1_0\jconfig.h"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\jerror.h"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\jmorecfg.h"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\jpeglib.h"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\turbojpeg.h"
	SetOutPath $INSTDIR\doc
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\README.ijg"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\README.md"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\LICENSE.md"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\example.txt"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\libjpeg.txt"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\structure.txt"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\usage.txt"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\wizard.txt"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\tjexample.c"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\java\TJExample.java"
!ifdef GCC
	SetOutPath $INSTDIR\man\man1
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\cjpeg.1"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\djpeg.1"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\jpegtran.1"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\rdjpgcom.1"
	File "C:/Elpas/e4ext-intel-realsense/windows/3rdparty/libjpeg-turbo_2_1_0\wrjpgcom.1"
!endif

	WriteRegStr HKLM "SOFTWARE\RealSenseID64 2.1.0" "Install_Dir" "$INSTDIR"

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RealSenseID64 2.1.0" "DisplayName" "RealSenseID SDK v2.1.0 for Visual C++ 64-bit"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RealSenseID64 2.1.0" "UninstallString" '"$INSTDIR\uninstall_2.1.0.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RealSenseID64 2.1.0" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RealSenseID64 2.1.0" "NoRepair" 1
	WriteUninstaller "uninstall_2.1.0.exe"
SectionEnd

Section "Uninstall"
!ifdef WIN64
	${If} ${RunningX64}
	${DisableX64FSRedirection}
	${Endif}
!endif

	SetShellVarContext all

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RealSenseID64 2.1.0"
	DeleteRegKey HKLM "SOFTWARE\RealSenseID64 2.1.0"

!ifdef GCC
	Delete $INSTDIR\bin\libjpeg-62.dll
	Delete $INSTDIR\bin\libturbojpeg.dll
	Delete $SYSDIR\libturbojpeg.dll
	Delete $INSTDIR\lib\libturbojpeg.dll.a
	Delete $INSTDIR\lib\libturbojpeg.a
	Delete $INSTDIR\lib\libjpeg.dll.a
	Delete $INSTDIR\lib\libjpeg.a
!else
	Delete $INSTDIR\bin\jpeg62.dll
	Delete $INSTDIR\bin\turbojpeg.dll
	Delete $SYSDIR\turbojpeg.dll
	Delete $INSTDIR\lib\jpeg.lib
	Delete $INSTDIR\lib\jpeg-static.lib
	Delete $INSTDIR\lib\turbojpeg.lib
	Delete $INSTDIR\lib\turbojpeg-static.lib
!endif
	Delete $INSTDIR\lib\pkgconfig\libjpeg.pc
	Delete $INSTDIR\lib\pkgconfig\libturbojpeg.pc
	Delete $INSTDIR\lib\cmake\RealSenseID\RealSenseIDConfig.cmake
	Delete $INSTDIR\lib\cmake\RealSenseID\RealSenseIDConfigVersion.cmake
	Delete $INSTDIR\lib\cmake\RealSenseID\RealSenseIDTargets.cmake
	Delete $INSTDIR\lib\cmake\RealSenseID\RealSenseIDTargets-release.cmake
!ifdef JAVA
	Delete $INSTDIR\classes\turbojpeg.jar
!endif
	Delete $INSTDIR\bin\cjpeg.exe
	Delete $INSTDIR\bin\djpeg.exe
	Delete $INSTDIR\bin\jpegtran.exe
	Delete $INSTDIR\bin\tjbench.exe
	Delete $INSTDIR\bin\rdjpgcom.exe
	Delete $INSTDIR\bin\wrjpgcom.exe
	Delete $INSTDIR\include\jconfig.h
	Delete $INSTDIR\include\jerror.h
	Delete $INSTDIR\include\jmorecfg.h
	Delete $INSTDIR\include\jpeglib.h
	Delete $INSTDIR\include\turbojpeg.h
	Delete $INSTDIR\uninstall_2.1.0.exe
	Delete $INSTDIR\doc\README.ijg
	Delete $INSTDIR\doc\README.md
	Delete $INSTDIR\doc\LICENSE.md
	Delete $INSTDIR\doc\example.txt
	Delete $INSTDIR\doc\libjpeg.txt
	Delete $INSTDIR\doc\structure.txt
	Delete $INSTDIR\doc\usage.txt
	Delete $INSTDIR\doc\wizard.txt
	Delete $INSTDIR\doc\tjexample.c
	Delete $INSTDIR\doc\TJExample.java
!ifdef GCC
	Delete $INSTDIR\man\man1\cjpeg.1
	Delete $INSTDIR\man\man1\djpeg.1
	Delete $INSTDIR\man\man1\jpegtran.1
	Delete $INSTDIR\man\man1\rdjpgcom.1
	Delete $INSTDIR\man\man1\wrjpgcom.1
!endif

	RMDir "$INSTDIR\include"
	RMDir "$INSTDIR\lib\pkgconfig"
	RMDir "$INSTDIR\lib\cmake\RealSenseID"
	RMDir "$INSTDIR\lib\cmake"
	RMDir "$INSTDIR\lib"
	RMDir "$INSTDIR\doc"
!ifdef GCC
	RMDir "$INSTDIR\man\man1"
	RMDir "$INSTDIR\man"
!endif
!ifdef JAVA
	RMDir "$INSTDIR\classes"
!endif
	RMDir "$INSTDIR\bin"
	RMDir "$INSTDIR"

SectionEnd
