cmake_minimum_required( VERSION 3.9.0 )

set( IMGUI_SOURCES  imconfig.h
                    imgui.cpp
                    imgui.h
                    imgui_demo.cpp
                    imgui_draw.cpp
                    imgui_impl_sdl_gl3.cpp
                    imgui_impl_sdl_gl3.h
                    imgui_internal.h
                    imgui_widgets.cpp
                    imstb_rectpack.h
                    imstb_textedit.h
                    imstb_truetype.h )

add_library( imgui ${IMGUI_SOURCES} )
