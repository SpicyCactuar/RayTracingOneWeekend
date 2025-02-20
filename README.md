# Ray Tracing in One Weekend

![Scene](https://user-images.githubusercontent.com/7926479/168508033-9fb740a9-8378-45ac-bf70-bc60b168addf.png)

Implementation of the [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) exercise. This codebase includes some naming and convention differences compared to the textbook implementation. The overall structure remains almost untouched therefore readers of the book should be able to navigate it with ease.

Different results can be achieved by tweaking the scene in `main.cpp`.

# Building & Running

The project uses [CMake](https://cmake.org/), set to C++17, as its build system. The structure is [CLion](https://www.jetbrains.com/clion/) based, however its usage is not mandatory.

The following instructions assume CMake is already installed. The commands are meant for a Unix based OS, nevertheless they should run on Windows with the appropiate tweaks.

Running the following command will create a `$PATH_TO_PROJECT/cmake-build-release` folder:

`$PATH_TO_CMAKE -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" $PATH_TO_PROJECT`

To then build build the release flavor:

`$PATH_TO_CMAKE --build $PATH_TO_PROJECT/cmake-build-release --target RayTracingOneWeekend`

This will create a `cmake-build-release/RayTracingOneWeekend` executable. Finally, render the ray traced scene to an example `~/Desktop/image.ppm` file:

`$PATH_TO_PROJECT/cmake-build-release/RayTracingOneWeekend > ~/Desktop/image.ppm`

Users of CLion can simply compile using its tools. Do note that prior to compiling users should create a **Release** profile as the IDE only provides a default **Debug** one. Alternatively, the embedded version of CMake can be referenced by pointing the command to `$PATH_TO_CLION/bin/cmake/$OS/bin/cmake`.
