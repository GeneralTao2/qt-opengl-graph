TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -g3

QT += opengl

linux-g++* {
 LIBS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lpng16 -lm -lz -lbz2 -lharfbuzz -lglib-2.0
}

win32 {
 LIBS += -lopengl32 -lstdc++fs
}
#sudo pacman -S lib32-openal libogg libvorbis opusfile libsndfile physfs libdumb
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
    ../imgui/examples/imgui_impl_glfw.cpp \
    ../imgui/examples/imgui_impl_opengl3.cpp \
    ../imgui/imgui.cpp \
    ../imgui/imgui_demo.cpp \
    ../imgui/imgui_draw.cpp \
    ../imgui/imgui_widgets.cpp \
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

#win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3
#
#INCLUDEPATH += $$PWD/../GLFW/lib-mingw
#DEPENDPATH += $$PWD/../GLFW/lib-mingw
#
#win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3dll
#
#INCLUDEPATH += $$PWD/../GLFW/lib-mingw
#DEPENDPATH += $$PWD/../GLFW/lib-mingw

#win32: LIBS += -L$$PWD/../GLFW/glfw-build/src/ -lglfw3

#INCLUDEPATH += $$PWD/../GLFW/include
#DEPENDPATH += $$PWD/../GLFW/include
#INCLUDEPATH += $$PWD/../GLFW/include/GLFW/

#unix:!macx: LIBS += -L$$PWD/../glfw-build/src/ -lglfw3
#
#INCLUDEPATH += $$PWD/../glfw-build/src
#DEPENDPATH += $$PWD/../glfw-build/src
#
#INCLUDEPATH += $$PWD/../glfw/include/GLFW/
#DEPENDPATH += $$PWD/../glfw/include/GLFW/

#unix:!macx: PRE_TARGETDEPS += $$PWD/../glfw-build/src/libglfw3.a

#
#win32: LIBS += -LE:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lgdi32
#
#INCLUDEPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include
#DEPENDPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include




#win32: LIBS += -L$$PWD/../irrKlang-1.6.0/lib/Win32-gcc/ -lirrKlang
#
#INCLUDEPATH += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc
#DEPENDPATH += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc
#
#INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include
#
#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc/irrKlang.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.6.0/lib/Win32-gcc/libirrKlang.a
#
#LIBS += -L$$PWD/../irrKlang-1.6.0/bin/win32-gcc/ -likpMP3
#INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include


#
#LIBS += -L$$PWD/../irrKlang-1.6.0/bin/win32-gcc/ -lirrKlang
#INCLUDEPATH += $$PWD/../irrKlang-1.6.0/include

#win32: LIBS += -L$$PWD/../assimp-4.0.1-build/code/ -llibassimp.dll
#
#INCLUDEPATH += $$PWD/../assimp-4.0.1/include
#INCLUDEPATH += $$PWD/../assimp-4.0.1-build/include
#DEPENDPATH += $$PWD/../assimp-4.0.1/include


#win32: LIBS += -L$$PWD/../GnuWin32/lib/f/ -lfreetype
#
#INCLUDEPATH += $$PWD/../GnuWin32/include
#DEPENDPATH += $$PWD/../GnuWin32/include

#win32: LIBS += -L$$PWD/../freetype2-build/ -lfreetype
#
#INCLUDEPATH += $$PWD/../freetype2-build/include/
#INCLUDEPATH += $$PWD/../freetype2/include/
#DEPENDPATH += $$PWD/../freetype2/include/

#win32: LIBS += -L$$PWD/../freetype2-build/ -lfreetype
#
#INCLUDEPATH += $$PWD/../freetype2/include
#DEPENDPATH += $$PWD/../freetype2/include





#INCLUDEPATH += $$PWD/settings/libs/imgui-master
#INCLUDEPATH += $$PWD/settings/libs/imgui-master/examples

HEADERS += \
    settings/classes/anti_aliasing.h \
    settings/classes/bloom_mapping.h \
    settings/classes/decor.h \
    settings/classes/display.h \
    #../GLFW/include/GLFW/glfw3.h \
    #../GLFW/include/GLFW/glfw3native.h \
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
    imgui/examples/imgui_impl_glfw.h \
    imgui/examples/imgui_impl_opengl2.h \
    imgui/examples/imgui_impl_opengl3.h \
    imgui/imconfig.h \
    imgui/imgui.h \
    imgui/imgui_internal.h \
    imgui/imstb_rectpack.h \
    imgui/imstb_textedit.h \
    imgui/imstb_truetype.h \
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

#win32: LIBS += -L$$PWD/assimp-4.0.1-build/code/ -llibassimp.dll
#
#INCLUDEPATH += $$PWD/assimp-4.0.1/include
#INCLUDEPATH += $$PWD/assimp-4.0.1-build/include



#------------------------------------------FREETYPE-------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../freetype2/freetype2-build/release/ -lfreetyper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../freetype2/freetype2-build/ -lfreetyped
else:unix:!macx: LIBS += -L$$PWD/../freetype2/freetype2-build/ -lfreetype

INCLUDEPATH += $$PWD/../freetype2/include
DEPENDPATH += $$PWD/../freetype2/include

INCLUDEPATH += $$PWD/../freetype2/freetype2-build/include
DEPENDPATH += $$PWD/../freetype2/freetype2-build/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../freetype2/freetype2-build/release/libfreetyper.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../freetype2/freetype2-build/debug/libfreetyped.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../freetype2/freetype2-build/release/freetyper.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../freetype2/freetype2-build/debug/freetyped.lib
#else:unix:!macx: PRE_TARGETDEPS += $$PWD/../freetype2/freetype2-build/libfreetype.a

#-------------------------------------------ASSIMP--------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../assimp/assimp-build/bin/release/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../assimp/assimp-build/code/ -lassimp.dll
else:unix:!macx: LIBS += -L$$PWD/../assimp/assimp-build/bin/ -lassimp

INCLUDEPATH += $$PWD/../assimp/include
DEPENDPATH += $$PWD/../assimp/include

INCLUDEPATH += $$PWD/../assimp/assimp-build/include
DEPENDPATH += $$PWD/../assimp/assimp-build/include

#--------------------------------------------GLFW---------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../glfw/glfw-build/src/release/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../glfw/glfw-build/src -lglfw3
else:unix:!macx: LIBS += -L$$PWD/../glfw/glfw-build/src/ -lglfw3

#linux-g++* {
# # your includes
#}
#
#win32 {
# # your includes
#}

INCLUDEPATH += $$PWD/../glfw/include/GLFW
DEPENDPATH += $$PWD/../glfw/include/GLFW

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../glfw/glfw-build/src/release/libglfw3.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../glfw/lib-mingw/libglfw3.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../glfw/glfw-build/src/release/glfw3.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../glfw/lib-mingw/glfw3.lib
#else:unix:!macx: PRE_TARGETDEPS += $$PWD/../glfw/glfw-build/src/libglfw3.a

#------------------------------------------IrrKlang-------------------------

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/irrKlang-64bit-1.6.0/bin/linux-gcc-64/release/ -lIrrKlang
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/irrKlang-64bit-1.6.0/bin/linux-gcc-64/release/ -lIrrKlang
#else:unix: LIBS += -L$$PWD/irrKlang-64bit-1.6.0/bin/linux-gcc-64/ -lIrrKlang
#
#INCLUDEPATH += $$PWD/irrKlang-64bit-1.6.0/include
#DEPENDPATH += $$PWD/irrKlang-64bit-1.6.0/include

#------------------------------------------Other-----------------------------

INCLUDEPATH += $$PWD/../glm/
DEPENDPATH += $$PWD/../glm/

INCLUDEPATH += $$PWD/../imgui/
DEPENDPATH += $$PWD/../imgui/

INCLUDEPATH += $$PWD/../imgui/examples/
DEPENDPATH += $$PWD/../imgui/examples/

INCLUDEPATH += $$PWD/../imgui/examples/
DEPENDPATH += $$PWD/../imgui/examples/

INCLUDEPATH += $$PWD/settings/libs/
DEPENDPATH += $$PWD/settings/libs/

INCLUDEPATH += $$PWD/../SOIL2/incs
DEPENDPATH += $$PWD/../SOIL2/incs


win32:CONFIG(release, debug|release): LIBS += -LE:/Programs/qt/Tools/mingw730_64/x86_64-w64-mingw32/lib/ -lgdi32
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/Programs/qt/Tools/mingw730_64/x86_64-w64-mingw32/lib/ -lgdi32

#INCLUDEPATH += E:/Programs/qt/Tools/mingw730_64/x86_64-w64-mingw32/include
#DEPENDPATH += E:/Programs/qt/Tools/mingw730_64/x86_64-w64-mingw32/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../glfw/lib-mingw/ -lglfw3
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../glfw/lib-mingw/ -lglfw3d
#else:unix:!macx: LIBS += -L$$PWD/../glfw/lib-mingw/ -lglfw3
#
#INCLUDEPATH += $$PWD/../glfw/lib-mingw
#DEPENDPATH += $$PWD/../glfw/lib-mingw

unix:!macx|win32: LIBS += -L$$PWD/../alure/build/ -lalure2

INCLUDEPATH += $$PWD/../alure/include/AL
DEPENDPATH += $$PWD/../alure/include/AL

INCLUDEPATH += $$PWD/../alure/include
DEPENDPATH += $$PWD/../alure/include
