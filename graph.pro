TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -g3
QT += opengl



LIBS += -lopengl32

SOURCES += \
        main.cpp \
    settings/classes/anti_aliasing.cpp \
    settings/classes/bloom_mapping.cpp \
    settings/classes/decor.cpp \
    settings/classes/display.cpp \
    settings/classes/framebuffer.cpp \
    settings/classes/imgu_manager.cpp \
    settings/classes/mesh.cpp \
    settings/classes/model.cpp \
    settings/classes/resource_manager.cpp \
    settings/classes/rm_config.cpp \
    settings/classes/shader.cpp \
    settings/classes/shader_arg_structs.cpp \
    settings/classes/shader_global_buffer.cpp \
    settings/classes/shadow_map.cpp \
    settings/classes/shadow_omni_map.cpp \
    settings/classes/stb_image.cpp \
    settings/classes/text_renderer.cpp \
    settings/classes/texture.cpp \
    settings/implant/bloom.cpp \
    settings/libs/imgui-master/examples/imgui_impl_glfw.cpp \
    settings/libs/imgui-master/examples/imgui_impl_opengl3.cpp \
    settings/libs/imgui-master/imgui.cpp \
    settings/libs/imgui-master/imgui_demo.cpp \
    settings/libs/imgui-master/imgui_draw.cpp \
    settings/libs/imgui-master/imgui_widgets.cpp \
    settings/objects/camera.cpp \
    settings/objects/cube_cluster.cpp \
    settings/objects/cube_normal_mapped.cpp \
    settings/objects/instance.cpp \
    settings/objects/light.cpp \
    settings/objects/plain.cpp \
    settings/objects/plain_normal_map.cpp \
    settings/objects/skybox.cpp \
    settings/objects/triangle.cpp \
    settings/objects/cube.cpp \
    settings/tools/main_tool.cpp

win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3
#
#INCLUDEPATH += $$PWD/../GLFW/lib-mingw
#DEPENDPATH += $$PWD/../GLFW/lib-mingw
#
#win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3dll
#
#INCLUDEPATH += $$PWD/../GLFW/lib-mingw
#DEPENDPATH += $$PWD/../GLFW/lib-mingw

#win32: LIBS += -L$$PWD/../GLFW/glfw-build/src/ -lglfw3

INCLUDEPATH += $$PWD/../GLFW/include
DEPENDPATH += $$PWD/../GLFW/include





INCLUDEPATH += $$PWD/../GLFW/include/GLFW/

win32: LIBS += -LE:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lgdi32

INCLUDEPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include
DEPENDPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include




win32: LIBS += -L$$PWD/../irrKlang-1.6.0/lib/Win32-gcc/ -lirrKlang

INCLUDEPATH += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc
DEPENDPATH += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc

INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc/irrKlang.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc/libirrKlang.a

LIBS += -L$$PWD/../irrKlang-1.6.0/bin/win32-gcc/ -likpMP3
INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include
#
#LIBS += -L$$PWD/../irrKlang-1.6.0/bin/win32-gcc/ -lirrKlang
#INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include

#win32: LIBS += -L$$PWD/../assimp-4.0.1-build/code/ -llibassimp.dll
#
#INCLUDEPATH += $$PWD/../assimp-4.0.1/include
#INCLUDEPATH += $$PWD/../assimp-4.0.1-build/include
#DEPENDPATH += $$PWD/../assimp-4.0.1/include


win32: LIBS += -L$$PWD/../GnuWin32/lib/f/ -lfreetype

INCLUDEPATH += $$PWD/../GnuWin32/include
DEPENDPATH += $$PWD/../GnuWin32/include

#win32: LIBS += -L$$PWD/../freetype2-build/ -lfreetype
#
#INCLUDEPATH += $$PWD/../freetype2-build/include/
#INCLUDEPATH += $$PWD/../freetype2/include/
#DEPENDPATH += $$PWD/../freetype2/include/

#win32: LIBS += -L$$PWD/../freetype2-build/ -lfreetype
#
#INCLUDEPATH += $$PWD/../freetype2/include
#DEPENDPATH += $$PWD/../freetype2/include





INCLUDEPATH += $$PWD/settings/libs/imgui-master
INCLUDEPATH += $$PWD/settings/libs/imgui-master/examples

HEADERS += \
    settings/classes/anti_aliasing.h \
    settings/classes/bloom_mapping.h \
    settings/classes/decor.h \
    settings/classes/display.h \
    ../GLFW/include/GLFW/glfw3.h \
    ../GLFW/include/GLFW/glfw3native.h \
    settings/classes/framebuffer.h \
    settings/classes/imgu_manager.h \
    settings/classes/mesh.h \
    settings/classes/model.h \
    settings/classes/resource_manager.h \
    settings/classes/shader.h \
    settings/classes/shader_arg_structs.h \
    settings/classes/shader_global_buffer.h \
    settings/classes/shadow_map.h \
    settings/classes/shadow_omni_map.h \
    settings/classes/stb_image.h \
    settings/classes/text_renderer.h \
    settings/classes/texture.h \
    settings/implant/bloom.h \
    settings/libs/imgui-master/examples/imgui_impl_glfw.h \
    settings/libs/imgui-master/examples/imgui_impl_opengl2.h \
    settings/libs/imgui-master/examples/imgui_impl_opengl3.h \
    settings/libs/imgui-master/imconfig.h \
    settings/libs/imgui-master/imgui.h \
    settings/libs/imgui-master/imgui_internal.h \
    settings/libs/imgui-master/imstb_rectpack.h \
    settings/libs/imgui-master/imstb_textedit.h \
    settings/libs/imgui-master/imstb_truetype.h \
    settings/objects/camera.h \
    settings/objects/cube_cluster.h \
    settings/objects/cube_normal_mapped.h \
    settings/objects/instance.h \
    settings/objects/light.h \
    settings/objects/plain.h \
    settings/objects/plain_normal_map.h \
    settings/objects/skybox.h \
    settings/objects/triangle.h \
    settings/objects/cube.h \
    settings/tools/main_tool.h

DISTFILES += \
    settings/libs/imgui-master/examples/imgui_examples.sln \
    settings/shaders/blinn_phong/blinn_phong.frag \
    settings/shaders/blinn_phong/blinn_phong.vert \
    settings/shaders/blinn_phong_shadow/blinn_phong_shadow.frag \
    settings/shaders/blinn_phong_shadow/blinn_phong_shadow.vert \
    settings/shaders/cluster/cluster.frag \
    settings/shaders/cluster/cluster.geom \
    settings/shaders/cluster/cluster.vert \
    settings/shaders/cube/cube.frag \
    settings/shaders/cube/cube.vert \
    settings/shaders/instance/instance.frag \
    settings/shaders/instance/instance.vert \
    settings/shaders/light/light.frag \
    settings/shaders/light/light.vert \
    settings/shaders/model_cluster/model_cluster.frag \
    settings/shaders/model_cluster/model_cluster.geom \
    settings/shaders/model_cluster/model_cluster.vert \
    settings/shaders/rax/rax.frag \
    settings/shaders/rax/rax.vert \
    settings/shaders/screen/screen.frag \
    settings/shaders/screen/screen.vert \
    settings/shaders/shadow_map/shadow_map.frag \
    settings/shaders/shadow_map/shadow_map.vert \
    settings/shaders/shadow_omni_map/shadow_omni_map.frag \
    settings/shaders/shadow_omni_map/shadow_omni_map.geom \
    settings/shaders/shadow_omni_map/shadow_omni_map.vert \
    settings/shaders/skybox/skybox.frag \
    settings/shaders/skybox/skybox.vert \
    settings/shaders/stencil/stencil.frag \
    settings/shaders/stencil/stencil.vert \
    settings/vertices/rax_vertex \
    settings/vertices/rax_color

win32: LIBS += -L$$PWD/assimp-4.0.1-build/code/ -llibassimp.dll

INCLUDEPATH += $$PWD/assimp-4.0.1/include
INCLUDEPATH += $$PWD/assimp-4.0.1-build/include
