# Building on Arch Linux

## 1. Install Prerequisites

Install the required packages using `pacman`:

```bash
sudo pacman -Syu --needed \
    base-devel \
    cmake \
    ninja \
    gcc \
    qt6-base \
    qt6-declarative \
    qt6-svg \
    qt6-tools
```

## 2. Clone and Configure

```bash
git clone <repository_url> DiamondInventory
cd DiamondInventory

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

## 3. Build Application and Tests

```bash
cmake --build build
```

The executable is generated at:

```text
build/bin/DiamondInventory
```

## 4. Run the Application

```bash
./build/bin/DiamondInventory
```

## 5. Run Automated Tests

```bash
ctest --test-dir build --output-on-failure
```

Individual test binaries can also be executed:

```bash
./build/bin/tst_database
./build/bin/tst_pricing
./build/bin/tst_validation
./build/bin/tst_import_export
```
