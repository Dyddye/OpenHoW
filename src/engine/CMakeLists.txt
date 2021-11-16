#[[
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
]]

project(OpenHoW)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_definitions(
        "-DIMGUI_IMPL_OPENGL_LOADER_GLEW"   # Required for OpenGL3.x imgui setup
)

file(GLOB OPENHOW_SOURCE_FILES
        *.cpp *.c
        *.h

        script/duktape-2.2.0/*.c
        script/duktape-2.2.0/*.h

        audio/AudioManager.cpp

        # Physics Sub-System
        physics/PhysicsInterface.cpp
        physics/PhysicsInterface.h

        editor/*.*
        graphics/*.*
        script/*.*
        game/*.*
        loaders/*.*

        Utilities.cpp

        ################## ImGui

        ../3rdparty/imgui/imgui.cpp
        ../3rdparty/imgui/imgui_draw.cpp
        ../3rdparty/imgui/imgui_widgets.cpp
        ../3rdparty/imgui/imgui_demo.cpp
        ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
        ../3rdparty/imgui/examples/imgui_impl_opengl3.h
        )

add_executable(OpenHoW ${OPENHOW_SOURCE_FILES} App.cpp App.h)

target_include_directories(OpenHoW PRIVATE
        ./
        ./audio/
        ./editor/
        ./game/
        ./graphics/
        ./loaders/
        ./physics/
        ./script/)
target_link_libraries(OpenHoW platform)

if (WIN32)
    target_link_libraries(OpenHoW SDL2::SDL2 SDL2::SDL2main OpenAL::OpenAL GLEW::GLEW
            # Window Libraries
            Version SetupAPI Winmm Imm32)
elseif (APPLE)
    target_include_directories(OpenHoW PRIVATE
            ../3rdparty/platform/platform/3rdparty/glew-2.2.0/include/)
    target_link_libraries(OpenHoW OpenAL SDL2)
elseif (UNIX)
    target_link_libraries(OpenHoW openal SDL2 pthread dl)
    target_compile_options(OpenHoW PUBLIC -fPIC)
else ()
    message("Unsupported platform!")
endif ()

target_include_directories(OpenHoW PUBLIC ../3rdparty/imgui/ script/duktape-2.2.0/)
