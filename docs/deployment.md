# Windows Deployment & Packaging Guide

## Overview

The Windows distribution is self-contained and does not require Qt or any developer tools to be pre-installed on the client machine.

## Structure of the Standalone Distribution

```text
DiamondInventory/
├── DiamondInventory.exe
├── Qt6Core.dll
├── Qt6Gui.dll
├── Qt6Qml.dll
├── Qt6Quick.dll
├── Qt6QuickControls2.dll
├── Qt6Sql.dll
├── Qt6PrintSupport.dll
├── Qt6Svg.dll
├── Qt6Widgets.dll
├── Qt6Network.dll
├── Qt6OpenGL.dll
├── D3Dcompiler_47.dll
├── opengl32sw.dll
├── sqldrivers/
│   └── qsqlite.dll
├── imageformats/
│   ├── qjpeg.dll
│   ├── qsvg.dll
│   └── qwebp.dll
├── platforms/
│   └── qwindows.dll
├── styles/
│   └── qquickstyleimplplugin.dll
└── qml/
    ├── DiamondInventory/
    ├── QtQuick/
    └── QtQuick.Controls/
```

## Creating the Installer

### Using NSIS

Configuration file: `installer/installer.nsi`

To compile:

```cmd
makensis installer/installer.nsi
```

Outputs: `DiamondInventorySetup.exe`

### Features of the Installer

1. Clean modern wizard UI
2. Installs application binaries and Qt runtime to `C:\Program Files\Diamond Inventory`
3. Creates Start Menu and Desktop shortcuts
4. Embeds high-resolution application icon
5. Preserves all user databases, images, and backups during application upgrades (user data is stored in `%LOCALAPPDATA%`, not the program folder)
6. Includes complete uninstaller registered in Windows Add/Remove Programs
