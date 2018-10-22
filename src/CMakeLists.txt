cmake_minimum_required( VERSION 3.9.0 )

add_executable( ft_gkrellm
                main.cpp
                IMonitorDisplay.hpp
                Ncurses.cpp
                Ncurses.hpp
                SDL.cpp
                SDL.hpp
                App.cpp
                App.hpp
                CPUModule.cpp
                CPUModule.hpp
                DateTimeModule.cpp
                DateTimeModule.hpp
                HostnameUsernameModule.cpp
                HostnameUsernameModule.hpp
                NetworkModule.cpp
                NetworkModule.hpp
                IMonitorModule.hpp
                OSInfoModule.cpp
                OSInfoModule.hpp
                RAMModule.cpp
                RAMModule.hpp )

target_link_libraries( ft_gkrellm ${CURSES_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${GLEW_LIBRARIES} imgui )
