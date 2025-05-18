# ⚙️ domkrat3d
<a id="readme-top"></a> 

<div align="center">  
  <p align="center">
    DOMKRAT3D is a lightweight 3D engine in C++ & Vulkan
    <br />
    <a href="https://alexeev-prog.github.io/domkrat3d/"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://alexeev-prog.github.io/domkrat3d/">Documentation</a>
    ·
    <a href="https://github.com/alexeev-prog/domkrat3d/blob/main/LICENSE">License</a>
  </p>
</div>
<br>
<p align="center">
    <img src="https://img.shields.io/github/languages/top/alexeev-prog/domkrat3d?style=for-the-badge">
    <img src="https://img.shields.io/github/languages/count/alexeev-prog/domkrat3d?style=for-the-badge">
    <img src="https://img.shields.io/github/license/alexeev-prog/domkrat3d?style=for-the-badge">
    <img src="https://img.shields.io/github/stars/alexeev-prog/domkrat3d?style=for-the-badge">
    <img src="https://img.shields.io/github/issues/alexeev-prog/domkrat3d?style=for-the-badge">
    <img src="https://img.shields.io/github/last-commit/alexeev-prog/domkrat3d?style=for-the-badge">
    <img alt="GitHub contributors" src="https://img.shields.io/github/contributors/alexeev-prog/domkrat3d?style=for-the-badge">
</p>

<div align='center'>
    <img src="https://github.com/alexeev-prog/domkrat3d/actions/workflows/static.yml/badge.svg">
    <img src="https://github.com/alexeev-prog/domkrat3d/actions/workflows/ci.yml/badge.svg">
</div>

<p align="center">
    <img src="https://raw.githubusercontent.com/alexeev-prog/domkrat3d/refs/heads/main/docs/pallet-0.png">
</p>

![logo](./docs/logo.png)

 > [!CAUTION]
 > At the moment, domkrat3d is under active development, many things may not work, and this version is not recommended for use (all at your own risk)

 > [!NOTE]
 > Building and installion: See the [BUILDING](BUILDING.md) document.

 > [!NOTE]
 > Contributing: See the [CONTRIBUTING](CONTRIBUTING.md) document.

 > [!NOTE]
 > Licensing: [GNU GPL V3](./LICENSE)

Welcome to Domkrat3D, a cutting-edge 3D game engine built on the robust C++ programming language and leveraging the Vulkan graphics API. If you're a game developer looking for flexibility, performance, and absolute control over your rendering pipeline, you’ve just found your new best friend. Let’s dive deeper! 💡

Our engine is easy-to-learn and lightweight. We use Vulkan - fast and popular graphic API.

## Versioning

![versioning](./docs/versioning.png)

## Why Choose Domkrat3D? 🛠️

- Performance-Focused: Built with performance as a top priority, Domkrat3D is optimized for speed and efficiency. With Vulkan as its backbone, expect lightning-fast render times and responsive gameplay.

- Modular Design: Our engine’s architecture allows for flexibility and scalability. Whether you’re creating a small indie game or a large-scale AAA title, Domkrat3D adapts to your needs, enabling you to plug in or update components as required.

- Intuitive API: We’ve designed a developer-friendly API that balances power and usability. With comprehensive documentation and examples, developers at any level can dive in and start building quickly.

- Community-Driven: Domkrat3D isn’t just an engine; it's a thriving community of passionate developers. Engage with others, share knowledge, and collaborate on bringing your game ideas to life. Join us and shape the future of gaming technology together! 🤝

- Cross-Disciplinary Support: Whether you're a programmer, artist, or designer, the ease of use and the integration capabilities of Domkrat3D make it easy for all team members to contribute effectively to the project.

## Why Vulkan? 🌌

### Unmatched Performance
Vulkan is the latest graphics API developed by the Khronos Group, providing low-level control over the GPU. This means you can squeeze out every last drop of performance from your hardware, unlocking visceral graphics and seamless gameplay experiences. With Vulkan, you get:

- Asynchronous Compute: Use your GPU's resources more efficiently by overlapping rendering and compute tasks.
- Explicit Control: Fine-tune your memory management and synchronization—Vulkan allows you to dictate how and when things render and resources are used, putting you in the driver’s seat.

### Cross-Platform Compatibility 🌍
Whether you're developing for Windows, Linux, or other platforms, Vulkan’s cross-platform support makes it an ideal choice for Domkrat3D. Reach a broader audience and ensure your game runs smoothly across various devices with minimal effort.

### Advanced Rendering Techniques
Vulkan supports advanced techniques such as tessellation, volumetric lighting, and more, allowing you to create visual masterpieces without the abstraction layers obstructing your vision. Elevate your game aesthetics to professional levels! 🎨

---

## Table of Contents

- [Introduction](#introduction)
- [Why Choose Domkrat3D?](#why-choose-domkrat3d)
- [How to use](#how-to-use)
  - [Examples](#examples)
- [Architecture Overview](#architecture-overview)
  - [Core Modules](#core-modules)
- [Dependencies & Libraries](#dependencies--libraries)
- [Engine Architecture](#engine-architecture)
  - [SoundSys](#soundsys)
  - [D3DOL](#d3dol)
  - [Physics Engine](#physics-engine)
  - [Math Module](#math-module)
  - [Core & Basic Modules](#core--basic-modules)
- [Why Use Domkrat3D?](#why-use-domkrat3d)
- [Get Started](#ready-to-start)
- [Final Words](#final-words)
- [Join the Community](#join-the-community)
- [Thanks & Creator](#thanks--creator)

---

## Introduction

Welcome! ✨  
**Domkrat3D** is not just another 3D engine. It is the culmination of years spent developing a lightweight, fast, and highly modular framework built on Vulkan and modern C++17 standards. Designed for creators who value control, flexibility, and performance, Domkrat3D empowers you to build anything from rapid prototypes to fully-featured 3D games and simulations.

> 💬 **"I’ve always wanted an engine that launches instantly, gives ultimate control, and uses modern technologies."** — [Alexeev Bronislaw]

---

## Why Choose **Domkrat3D**? 🚀

| 🌟 Feature                | 🔍 Why It Matters                                                      |
|---------------------------|------------------------------------------------------------------------|
| ⚡️ Fast & Lightweight     | Minimizes load times and maximizes runtime efficiency.                 |
| 🧩 Modular Architecture   | Enables easy extension, customization, and integration of new features.|
| 🎮 Vulkan API Integration | Leverages cutting-edge graphics API for maximum rendering performance. |
| 📚 Modern C++17 Codebase  | Clean, maintainable, and future-proof code for professional workflows. |
| 🌍 Cross-Platform         | Runs seamlessly on Windows, Linux, and macOS.                          |

> [!NOTE]  
> Ensure your Vulkan and GPU drivers are up to date for optimal experience.

---

## How To Use
Please, build and install lib. [Instruction here](./BUILDING.md).

You also can read [Hacking](./HACKING.md)

### Examples
Here is some examples of C++ code for work with domkrat3d engine.

---

## Architecture Overview 🏗️
Domkrat3D’s architecture is thoughtfully segmented into specialized modules, making it easier to maintain, extend, and customize. Each module focuses on a specific domain of engine functionality.

### Debug levels
Domkrat3D have seven debug levels:

1. Trace - `::TRACE::`
2. Vulkan Debug - `::VK DEBUG::`
3. Debug - `::DEBUG::`
4. Info - `::INFO::`
5. Warning - `::WARNING::`
6. Error - `::ERROR::`
7. Critical - `::CRITICAL::`

![debug levels](./docs/debug_levels.png)

### Engine Architecture at a Glance

| Module          | Description                                                                                                   | Roles & Key Features                                                                                   |
|-----------------|---------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|
| **SoundSys**    | Comprehensive audio system, split into functional subsections.                                                | - **ambient**: continuous background soundscapes (e.g. wind, city bustle)<br>- **beep**: single event sounds (notifications, clicks)<br>- **music**: looping background or dynamic scene music<br>- **sound**: core engine for 3D sound positioning, effects, and playback control |
| **D3DOL**       | DOMKRAT 3D Object Loader — manages importing, parsing, and efficiently organizing 3D models and meshes.       | Supports popular formats like glTF and OBJ, automatically loads meshes, materials, and textures.       |
| **physics**     | Physics simulation module focused on rigid bodies, collisions, and forces.                                    | Handles accurate collision detection, rigid body dynamics, gravity, and physical interactions.         |
| **math**       | Foundational mathematical primitives and utilities.                                                          | Provides vectors, matrices, quaternions, transforms, and optimized routines essential for graphics and physics. |
| **basic**      | Essential engine infrastructure — scene graph management, resource loading, and core logic.                    | Manages state updates, resource lifecycle, and ties together different modules through unified interfaces. |
| **plainimg**   | Simple image loader and handler.                                                                              | Supports texture loading from PNG, JPEG, DDS; used in materials and UI textures.                        |
| **dml**        | DOMKRAT Map Loader — efficient parsing and management of level data and terrain.                              | Handles map data, spatial partitioning, and streaming for large environments.                           |
| **desm**       | DOMKRAT Event System Manager — centralized event dispatching and handling.                                    | Facilitates message passing, listener registration, and event-driven architecture patterns.            |
| *dmms*         | DOMKRAT Media Management System | Manage the media: video, some objects and other files |
| *dscenes*      | DOMKRAT Scenes | Manage the scenes for your game |

### File Structure

```
source
├── domkrat3d.cpp
├── graphics
│   └── core.cpp
├── informatics
│   └── core.cpp
├── logging.cpp
├── mathematics
│   ├── core.cpp
│   └── statistics.cpp
└── physics
    ├── core.cpp
    └── kinematics.cpp

include/
└── domkrat3d
    ├── domkrat3d.hpp
    ├── export.h
    ├── graphics
    │   └── core.hpp
    ├── informatics
    │   └── core.hpp
    ├── mathematics
    │   ├── core.hpp
    │   └── statistics.hpp
    └── physics
        ├── core.hpp
        └── kinematics.hpp
```

---

## Dependencies & Libraries 📦

Domkrat3D relies on a well-curated set of external libraries and tools to support its core functionality:

| Library                  | Purpose                                   | Explanation                                                                                |
|-------------------------|-------------------------------------------|------------------------------------------------------------------------------------------|
| **glfw**                | Window and Context Management             | Creates OS windows and handles input devices, essential for Vulkan context creation.     |
| **libGL**               | Vulkan Core Library                       | Provides Vulkan functionality, especially useful when a fallback is needed.              |
| **libGLU**              | Vulkan Utility Library                    | Provides additional functionalities for Vulkan, such as simplifying matrix and primitive operations. |
| **mesa**                | Vulkan Implementation                     | Useful for development and testing on Vulkan, especially on systems without hardware acceleration. |
| **glew**                | Vulkan Extension Wrangler                 | Helps manage Vulkan extensions, particularly important for compatibility.                 |
| **glm**                 | Math Library                             | Offers specialized vector and matrix operations optimized for graphics.                  |
| **stb**                 | Utility C Libraries for Images and Fonts | Popular single-header libraries for loading and working with images.                      |
| **entt**                | Entity-Component-System Library          | A lightweight and efficient ECS implementation for managing game entities.               |
| **cmake**               | Build System                             | The most widely used tool for cross-platform project build configuration.                |
| **gcc**                 | C++ Compiler                             | Required to build the engine and projects, providing numerous options and standard support. |
| **clang**               | Compiler and Code Analysis Tools          | A highly efficient compiler with powerful code analysis and diagnostics capabilities.      |
| **clang-tidy-sarif**   | Static Code Analysis Tool                 | Performs static code analysis to find potential errors before running the program.       |
| **clang-tools**         | Tools for Working with Clang              | A suite of tools aimed at improving code quality and automating development processes.   |
| **imgui**               | Immediate Mode GUI Library               | A simple yet powerful library for creating graphical user interfaces in applications.    |
| **freeglut**           | Alternative for Window and Input Handling  | A lightweight alternative for managing windows and input, often used in demo projects. |
| **portaudio**          | Audio Library                            | Provides user-friendly interfaces for working with audio devices.                         |
| **valgrind**           | Performance Analysis Tool                | Used for detecting memory leaks and profiling performance.                                |
| **gdb**                 | Debugger                                  | A tool for debugging programs, allowing the analysis of execution and error finding.     |
| **apitrace**           | API Tracing Tool                         | Enables tracking API calls in Vulkan, useful for debugging and performance analysis.     |
| **glava**              | Vulkan Performance Testing                | A utility designed for testing Vulkan performance and frame analysis.                    |
| **glui**               | GUI Library for Vulkan                   | Provides a set of tools for creating graphical user interfaces based on Vulkan.          |
| **glmark2**            | Performance Benchmark                     | Evaluates the performance of a system based on Vulkan, well-suited for graphics testing. |
| **glpng**              | PNG Library                               | Allows loading and processing PNG formatted images in graphics applications.               |

---

## Engine Architecture – Detailed Module Descriptions 🛠️

### SoundSys 🎵

The sound system is organized into dedicated subsections for clear separation of responsibilities:

| Section  | Role & Description                                                                         |
|----------|-------------------------------------------------------------------------------------------|
| **ambient** | Background environmental sounds that create immersion: rustling leaves, city noise, rain sounds that play continuously. |
| **beep**    | Short, one-off sounds typically used for UI feedback like ‘clicks’, alerts, and notifications. |
| **music**   | Handles looping background music tracks or dynamic scene music changes during gameplay.   |
| **sound**   | Core sound engine responsible for 3D audio positioning, distance attenuation, reverb, and applying audio effects.       |

> [!IMPORTANT]  
> Dividing sound into these sections allows efficient resource management, mixing, and prioritization, ensuring a smooth and rich audio experience.

---

### D3DOL (DOMKRAT 3D Object Loader) 🧸

- Robust 3D object loading supporting industry-standard formats like glTF and OBJ.
- Supports skinning, meshes, materials, and texture bindings.
- Implements optimizations such as vertex buffer batching and hierarchical scene representation.

---

### Physics Engine ⚖️

- Implements rigid body physics, continuous collision detection, and response.
- Supports gravity, forces, and constraints.
- Designed to be extensible for custom physics behavior or integration with external physics engines.

---

### Math Module ➗✖️

- Core mathematical types: vector2/3/4, matrices (3×3, 4×4), quaternions.
- Highly optimized for real-time computation, especially GPU-friendly transformations and calculations.
- Includes utility routines for interpolation, projection, and spatial queries.

---

### Core & Basic Modules 🔑

- Manages scene graph, resource lifecycles, and timing.
- Abstracts Vulkan and system calls for smooth integration.
- Implements task scheduling and multi-threaded resource loading.

---

## Why Use **Domkrat3D**? ✨

- **Performance driven:** Vulkan-based backend harnesses full GPU power.
- **Extensible by design:** Modular, loosely coupled systems; add or replace features gracefully.  
- **Modern standards:** C++17 compliance ensures clean, maintainable, future-proof code.  
- **Cross-platform:** Write once, run on Windows, Linux, and macOS seamlessly.  
- **Built-in key systems:** Sound, physics, map loading, events right out of the box.

> [!TIP]  
> Start small with minimal core scenes, then progressively add physics, sound, and map support for manageable development cycles.

---

## Ready to Start? 🚦

Get building — prototyping or full game development — and enjoy a direct, no-nonsense toolchain centered on productivity and clarity.

---

## Final Words ✨

If you’re in need of:

- A lightning-fast and lightweight engine  
- Full Vulkan support  
- Modular and adaptable framework  
- Easy-to-understand architecture to fully control your project  

**Domkrat3D is the perfect fit.**

---

## Join the Community! 🌐

- **GitHub Issues** — for bug reporting and feature requests.  
- **Discord / Telegram** — for live chats and help (links forthcoming).  
- **Contact Email** — for direct feedback, suggestions, and collaboration inquiries.

---

Thank you for exploring **Domkrat3D** — let’s create extraordinary 3D experiences together! 🚀

