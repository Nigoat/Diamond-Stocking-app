[Setup]
AppId={{D1A30001-9876-4FDE-8822-D1A900112233}
AppName=Diamond Inventory
AppVersion=1.0.0
AppPublisher=DiamondStore
DefaultDirName={autopf}\Diamond Inventory
DefaultGroupName=Diamond Inventory
AllowNoIcons=yes
OutputDir=.
OutputBaseFilename=DiamondInventorySetup
Compression=lzma2/ultra64
SolidCompression=yes
WizardStyle=modern
ArchitecturesInstallIn64BitMode=x64compatible
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "..\build\DiamondInventory.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\build\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\build\plugins\*"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\build\qml\*"; DestDir: "{app}\qml"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\Diamond Inventory"; Filename: "{app}\DiamondInventory.exe"
Name: "{group}\{cm:UninstallProgram,Diamond Inventory}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Diamond Inventory"; Filename: "{app}\DiamondInventory.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\DiamondInventory.exe"; Description: "{cm:LaunchProgram,Diamond Inventory}"; Flags: nowait postinstall skipifsilent
