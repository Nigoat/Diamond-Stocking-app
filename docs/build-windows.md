# Building on Windows

## Method A — GitHub Actions CI (Recommended)

The repository contains automated GitHub Actions workflows in `.github/workflows/build-windows.yml`.

To build a Windows release:
1. Push a commit or tag (e.g. `v1.0.0`) to GitHub, or trigger the workflow manually under **Actions → Windows Build & Package → Run workflow**.
2. The CI pipeline will:
   - Setup Qt 6.6.3 MSVC x64
   - Build the Release executable via CMake & Ninja
   - Run the QtTest suite
   - Deploy runtime dependencies with `windeployqt`
   - Generate `DiamondInventorySetup.exe` via NSIS
   - Upload the standalone installer as a downloadable GitHub Actions artifact.

---

## Method B — Native Windows Build

### 1. Prerequisites

- Visual Studio 2022 (Community or Professional) with "Desktop development with C++"
- Qt 6.4+ (MSVC 2019/2022 64-bit) installed via the Qt Online Installer
  - Required Qt modules: `Qt Core`, `Qt Gui`, `Qt Quick`, `Qt Quick Controls 2`, `Qt Qml`, `Qt SQL (SQLite)`, `Qt PrintSupport`, `Qt SVG`
- CMake 3.20+ and Ninja
- NSIS (Nullsoft Scriptable Install System) or InnoSetup (optional, for building the installer)

### 2. Open Developer Command Prompt

Open **x64 Native Tools Command Prompt for VS 2022**.

Set the path to your Qt installation:

```cmd
set Qt6_DIR=C:\Qt\6.6.3\msvc2019_64
set PATH=%Qt6_DIR%\bin;%PATH%
```

### 3. Configure and Build

```cmd
cd path\to\Diamond
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="%Qt6_DIR%"
cmake --build build --config Release
```

The executable will be produced at:

```text
build\bin\DiamondInventory.exe
```

### 4. Deploy Qt Runtime Dependencies

Use `windeployqt` to bundle all required DLLs, QML modules, and plugins into the output folder:

```cmd
windeployqt --qmldir qml --release --compiler-runtime build\bin\DiamondInventory.exe
```

### 5. Generate Installer

Using NSIS:

```cmd
makensis installer\installer.nsi
```

This creates `DiamondInventorySetup.exe` ready for distribution.
