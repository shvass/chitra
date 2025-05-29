# ***chitra - opengl based rendering engine***


![linux build](https://github.com/shvass/chitra/actions/workflows/linux-build.yml/badge.svg)
<!-- ![windows build](https://github.com/akbnsd/chitra/actions/workflows/windows-build.yml/badge.svg) -->

![wait for video to load. Chitra in action](media/preview.gif "chitra rendering gui over video render")

Chitra is an OpenGL-based media viewer and rendering engine designed for layered rendering of images, videos, and 3D models. It supports real-time playback and visualization, making it suitable for multimedia applications. The project integrates FFmpeg for video decoding and muxing, and utilizes Dear ImGui for GUI widgets. Chitra is currently a work in progress, with ongoing development to enhance its capabilities.



## Features
* **OpenGL-Based video rendering pipeline**
  Implements OpenGL rendering pipeline for video playback which compiles & links GLSL vertex and fragment shaders at runtime; loads decoded frames into OpenGL textures and renders in time synchronized manner.

* **FFmpeg Integration**
  Uses FFmpeg for hardware accelarated codecs for video decoding and demuxing capabilities. Support for **NVENC codecs**  is currently under testing.

* **Layered Rendering System**
  Supports rendering architecture with support for layered scene composition and isolation of render passes. See `layers` class for more details.  

* **Input Event Dispatcher**
  Input Events Dispatcher system to handle and route keyboard, mouse, and controller events to the stacked input layers. 

* **ImGui GUI Integration**
  Uses ImGui for dynamic and interactive GUI widgets and docking system, ideal for real-time debugging and user tools.

* **Doxygen Integration**
  Supports HTML and PDF documentation generation via Doxygen, ensuring maintainable and accessible code documentation.

* **Cross platform Cmake build system & Precompiled Headers (PCH)**
  Utilizes precompiled headers to significantly reduce compile times and improve developer productivity.






<!-- #TODO -->
<!-- 
## Implementation details
-  -->


<!-- 
## Features
- Opengl rendering pipeline based rendering engine
- pre-compiled headers for faster compile time
- Doxygen integration for html/pdf Documentation support
- layered rendering system
- integrated with FFmpeg for video muxing and decompression
- integrated with ImGui to render gui widgets
- Input Event system to process user inputs -->

### Prerequisites 
- cmake >= 2.9
- make >= 4.2
- FFmpeg 

## Build instructions
```
git clone https://github.com/shvass/chitra.git
```
```
mkdir build && cd build
```
```
cmake ..
```
```
make
```
