# HumanityLastResort

> A 3D city-building survival game in Unreal Engine 5 — manage resources, construct buildings, and ensure humanity's survival against escalating threats.

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-0E1128?logo=unrealengine&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green)

## Overview

A 3D city-building survival game in Unreal Engine 5 — manage resources, construct buildings, and ensure humanity's survival against escalating threats.

Built with **Unreal Engine** and **C++**, demonstrating professional game development patterns: the Actor-Component model, Unreal's reflection system (UPROPERTY/UFUNCTION), Blueprint interoperability, and optimized gameplay systems.

## Features

- Unreal Engine gameplay framework (GameMode, GameState, PlayerController)
- Custom C++ Actor and Component classes
- Blueprint-C++ interoperability
- Physics and collision systems
- Optimized asset loading

## Technologies Used

| Technology | Details |
|------------|---------|
| Unreal Engine | 4.x / 5.x |
| C++ | Modern C++17 |
| Blueprints | Visual scripting |
| Chaos Physics | Physics simulation |

## Screenshots / Demo

![Screenshot 1](https://raw.githubusercontent.com/khaled71612000/HumanityLastResort/HEAD/Plugins/DataTableEditorUtilities/Resources/Icon128.png)

## Getting Started

### Prerequisites

- [Unreal Engine](https://www.unrealengine.com/en-US/download) 4.x or 5.x
- Visual Studio 2019 or 2022 with **Desktop development with C++**
- Git LFS

### Installation

```bash
git lfs install
git clone https://github.com/khaled71612000/HumanityLastResort.git
cd HumanityLastResort
```

1. Right-click `.uproject` → **Generate Visual Studio project files**
2. Open `.sln` in Visual Studio
3. Set config: **Development Editor | Win64**
4. Build (Ctrl+Shift+B) then launch the editor

## Project Structure

```
HumanityLastResort/
├── Source/                  # C++ source files
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Private/DataTableEditorUtilitiesBlueprintLibrary.cpp
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Private/DataTableEditorUtilitiesHelper.cpp
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Private/DataTableEditorUtilitiesHelper.h
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Private/DataTableEditorUtilitiesModule.cpp
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Public/DataTableEditorUtilitiesBlueprintLibrary.h
  Plugins/DataTableEditorUtilities/Source/DataTableEditorUtilities/Public/DataTableEditorUtilitiesModule.h
├── Content/                 # Assets, blueprints, levels
├── Config/                  # Project settings
└── HumanityLastResort.uproject
```

## License

[MIT License](LICENSE)
