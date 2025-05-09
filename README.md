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
    <img src="https://img.shields.io/pypi/wheel/domkrat3d?style=for-the-badge">
    <img alt="GitHub contributors" src="https://img.shields.io/github/contributors/alexeev-prog/domkrat3d?style=for-the-badge">
</p>

<div align='center'>
    <img src="https://github.com/alexeev-prog/domkrat3d/actions/workflows/static.yml/badge.svg">
    <img src="https://github.com/alexeev-prog/domkrat3d/actions/workflows/ci.yml/badge.svg">
</div>

<p align="center">
    <img src="https://raw.githubusercontent.com/alexeev-prog/domkrat3d/refs/heads/main/docs/pallet-0.png">
</p>

 > DOMKRAT3D is a lightweight 3D engine in C++ & Vulkan
 
 > [!CAUTION]
> At the moment, domkrat3d is under active development, many things may not work, and this version is not recommended for use (all at your own risk)

Welcome to DOMKRAT3D - blazing fast, lightweight 3D game engine in Python! You can use with for:

1. Create programs for work with 3D
2. Create 3D games with basic physics
3. And more!

Our engine is easy-to-learn and lightweight. We use Vulkan API - blazing fast, low-level graphic API.

 > [!NOTE]
 > Building and installion: See the [BUILDING](BUILDING.md) document.

 > [!NOTE]
 > Contributing: See the [CONTRIBUTING](CONTRIBUTING.md) document.

> [!NOTE]
> Licensing: [GNU GPL V3](./LICENSE)

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

> 💬 **"I’ve always wanted an engine that launches instantly, gives ultimate control, and uses modern technologies."** — [Developer testimonial]

---

## Why Choose **Domkrat3D**? 🚀

| 🌟 Feature               | 🔍 Why It Matters                                                       |
|-------------------------|------------------------------------------------------------------------|
| ⚡️ Fast & Lightweight     | Minimizes load times and maximizes runtime efficiency.                 |
| 🧩 Modular Architecture  | Enables easy extension, customization, and integration of new features.|
| 🎮 Vulkan API Integration | Leverages cutting-edge graphics API for maximum rendering performance. |
| 📚 Modern C++17 Codebase | Clean, maintainable, and future-proof code for professional workflows. |
| 🌍 Cross-Platform        | Runs seamlessly on Windows, Linux, and macOS.                          |

> [!NOTE]  
> Ensure your Vulkan SDK and GPU drivers are up to date for optimal experience.

---

## How To Use
Please, build and install lib. [Instruction here](./BUILDING.md).

You also can read [Hacking](./HACKING.md)

### Examples
Here is some examples of C++ code for work with domkrat3d engine.

---

## Architecture Overview 🏗️

Domkrat3D’s architecture is thoughtfully segmented into specialized modules, making it easier to maintain, extend, and customize. Each module focuses on a specific domain of engine functionality.

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

---

## Dependencies & Libraries 📦

Domkrat3D relies on a well-curated set of external libraries and tools to support its core functionality:

| Library                  | Purpose                                   | Explanation                                                                                 |
|--------------------------|-------------------------------------------|---------------------------------------------------------------------------------------------|
| **glfw**                 | Window and Context Management             | Creates OS windows and handles input devices, essential for Vulkan/OpenGL context creation. |
| **libGL**                | OpenGL Core Library                       | Provides OpenGL functionality if fallback is needed.                                       |
| **mesa**                 | OpenGL Implementation                     | Useful for development/testing on OpenGL.                                                  |
| **freeglut**             | Alternative for window and input handling| Lightweight alternative to GLFW or GLUT for simpler demos.                                |
| **gcc**                  | C++ Compiler                             | Needed to build engine and projects.                                                      |
| **glew**                 | OpenGL Extension Wrangler                 | Helps manage OpenGL extensions, mainly fallback use.                                     |
| **glm**                  | Math Library                             | Provides vector and matrix math tailored for graphics.                                   |
| **cmake**                | Build System                             | Widely used, cross-platform build configuration tool.                                    |
| **vulkan-tools**         | Vulkan SDK Tools                        | Debugging utilities like validation layer, Vulkan debugger, etc.                         |
| **vulkan-utility-libraries** | Vulkan helper libraries              | Manage buffers, images, memory — abstract complex Vulkan details.                         |
| **vulkan-headers**       | Vulkan API Header Files                  | Up-to-date API declarations needed for Vulkan calls.                                    |
| **vulkan-validation-layers** | Vulkan API Validator                 | Detects misuse or errors in Vulkan commands during development.                          |
| **vulkan-memory-allocator** | Simplified Vulkan memory allocation   | Streamlines GPU memory management and efficient usage.                                  |
| **vulkan-loader**        | Vulkan Loader                          | Dynamically loads Vulkan functions and manages API versions at runtime.                 |
| **stb**                  | Utility C libraries for images, fonts   | Widely used single-header libraries for image loading and more.                         |
| **entt**                 | Entity-Component-System library          | Lightweight and efficient ECS implementation for managing game entities.                |
| **vulkan-extension-layer** | Additional Vulkan capabilities          | Provides features when native Vulkan support is unavailable or limited.                 |
| **vulkan-cts**           | Vulkan Conformance Tests                  | Suite to verify adherence to the Vulkan specification on various platforms.             |
| **sfml**                 | Multimedia library (optional)              | Used for rapid prototyping, audio, and UI controls if needed.                           |

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
- Abstracts low-level Vulkan and system calls for smooth integration.
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

