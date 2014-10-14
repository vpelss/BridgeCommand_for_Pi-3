;setup names
!define PROGRAMNAME "Bridge Command 5.0 Alpha 1"
!define OUTPUTFILE "bc50a1_setup.exe"
!define INSTALLLOCATION "Bridge Command 5.0a1"
!define SMFOLDER "Bridge Command 5.0 Alpha 1"
!define REGKEY "BridgeCommand5.0a1"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Name "${PROGRAMNAME}"

OutFile "${OUTPUTFILE}"

InstallDir "$PROGRAMFILES\${INSTALLLOCATION}"

LicenseData "LICENSE.txt"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

Page license
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "Bridge Command (required)"

;set to all users for start menu
SetShellVarContext all

SectionIn RO

SetOutPath $INSTDIR

;include all files, excluding the .svn directories
File /r /x .svn /x .objs /x .git /x EnetServer /x *.m /x *.nsi /x RadarCache /x misc /x shiplights.ods *.*

  CreateDirectory "$SMPROGRAMS\${SMFOLDER}"
  CreateShortCut "$SMPROGRAMS\${SMFOLDER}\${PROGRAMNAME}.lnk" "$INSTDIR\BridgeCommand.exe"
  CreateShortCut "$SMPROGRAMS\${SMFOLDER}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0

; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REGKEY}" "DisplayName" "${PROGRAMNAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REGKEY}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REGKEY}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REGKEY}" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

Section "Uninstall"

;set to all users for start menu
SetShellVarContext all
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REGKEY}"

  ; Remove files and uninstaller
  RMDir /r "$INSTDIR\Models"  
  RMDir /r "$INSTDIR\Scenarios"
  RMDir /r "$INSTDIR\media"
  RMDir /r "$INSTDIR\world"
  RMDir /r "$INSTDIR\libs"

  Delete "$INSTDIR\Leg.hpp"
  Delete "$INSTDIR\Sky.hpp"
  Delete "$INSTDIR\Angles.hpp"
  Delete "$INSTDIR\Water.hpp"
  Delete "$INSTDIR\Network.hpp"
  Delete "$INSTDIR\Light.hpp"
  Delete "$INSTDIR\IniFile.hpp"
  Delete "$INSTDIR\StartupEventReceiver.hpp"
  Delete "$INSTDIR\RadarScreen.hpp"
  Delete "$INSTDIR\LandObject.hpp"
  Delete "$INSTDIR\MyEventReceiver.hpp"
  Delete "$INSTDIR\Tide.hpp"
  Delete "$INSTDIR\LandObjects.hpp"
  Delete "$INSTDIR\ScenarioChoice.hpp"
  Delete "$INSTDIR\RadarData.hpp"
  Delete "$INSTDIR\Sky.cpp"
  Delete "$INSTDIR\Utilities.hpp"
  Delete "$INSTDIR\LandLights.hpp"
  Delete "$INSTDIR\Constants.hpp"
  Delete "$INSTDIR\Terrain.hpp"
  Delete "$INSTDIR\Buoys.hpp"
  Delete "$INSTDIR\Camera.hpp"
  Delete "$INSTDIR\OtherShips.hpp"
  Delete "$INSTDIR\Angles.cpp"
  Delete "$INSTDIR\Buoy.hpp"
  Delete "$INSTDIR\NavLight.hpp"
  Delete "$INSTDIR\OtherShip.hpp"
  Delete "$INSTDIR\StartupEventReceiver.cpp"
  Delete "$INSTDIR\Ship.hpp"
  Delete "$INSTDIR\RadarCalculation.hpp"
  Delete "$INSTDIR\GUIMain.hpp"
  Delete "$INSTDIR\Ship.cpp"
  Delete "$INSTDIR\RadarScreen.cpp"
  Delete "$INSTDIR\Utilities.cpp"
  Delete "$INSTDIR\Light.cpp"
  Delete "$INSTDIR\OwnShip.hpp"
  Delete "$INSTDIR\main.cpp"
  Delete "$INSTDIR\BridgeCommand.cbp"
  Delete "$INSTDIR\bc5.ini"
  Delete "$INSTDIR\Structure.txt"
  Delete "$INSTDIR\Tide.cpp"
  Delete "$INSTDIR\LandObjects.cpp"
  Delete "$INSTDIR\Camera.cpp"
  Delete "$INSTDIR\LandObject.cpp"
  Delete "$INSTDIR\SimulationModel.hpp"
  Delete "$INSTDIR\LandLights.cpp"
  Delete "$INSTDIR\Network.cpp"
  Delete "$INSTDIR\Water.cpp"
  Delete "$INSTDIR\BridgeCommand.cscope_file_list"
  Delete "$INSTDIR\OtherShips.cpp"
  Delete "$INSTDIR\install.nsi"
  Delete "$INSTDIR\IniFile.cpp"
  Delete "$INSTDIR\GUIMain.cpp"
  Delete "$INSTDIR\ScenarioChoice.cpp"
  Delete "$INSTDIR\Buoys.cpp"
  Delete "$INSTDIR\Terrain.cpp"
  Delete "$INSTDIR\MyEventReceiver.cpp"
  Delete "$INSTDIR\NavLight.cpp"
  Delete "$INSTDIR\Buoy.cpp"
  Delete "$INSTDIR\OtherShip.cpp"
  Delete "$INSTDIR\SimulationModel.cpp"
  Delete "$INSTDIR\OwnShip.cpp"
  Delete "$INSTDIR\BridgeCommand.layout"
  Delete "$INSTDIR\RadarCalculation.cpp"
  Delete "$INSTDIR\LICENSE.txt"
  Delete "$INSTDIR\libenet.dll"
  Delete "$INSTDIR\BridgeCommand.depend"
  Delete "$INSTDIR\BridgeCommand.exe"
  Delete "$INSTDIR\Irrlicht.dll"
  Delete "$INSTDIR\uninstall.exe"
  Delete "$INSTDIR\IniEditor.exe"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\${SMFOLDER}\Settings\*.*"
  Delete "$SMPROGRAMS\${SMFOLDER}\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\${SMFOLDER}\Settings"
  RMDir "$SMPROGRAMS\${SMFOLDER}"
  RMDir "$INSTDIR"

SectionEnd
