#include "SDL.hpp"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include "IMonitorModule.hpp"

SDL::SDL() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("Failed to init SDL");
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSdlGL3_Init(m_window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_window = SDL_CreateWindow("ft_gkrellm",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             400, 800, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        std::cerr << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL Window");
    }

    SDL_SetWindowMinimumSize(m_window, 400, 800);

    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_glContext == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create GL context");
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << glewGetErrorString(glewError) << std::endl;
        throw std::runtime_error("Failed to init GLEW");
    }
}

SDL::~SDL() {
    ImGui_ImplSdlGL3_Shutdown();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDL::Update(std::vector<IMonitorModule*>& modules) {
    glClear(GL_COLOR_BUFFER_BIT);

    int w;
    int h;
    SDL_GetWindowSize(m_window, &w, &h);

    ImGui_ImplSdlGL3_NewFrame(m_window);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(w, h));

    ImGui::Begin("ft_gkrellm");

    std::vector<IMonitorModule*>::iterator it;
    for (it = modules.begin(); it != modules.end(); ++it) {
        (*it)->UpdateData();
        if (ImGui::CollapsingHeader((*it)->GetName().c_str())) {
            std::vector<std::string> data = (*it)->GetData();
            for (size_t i = 0; i < data.size(); ++i) {
                ImGui::Text("%s", data[i].c_str());
            }
        }
    }

    ImGui::End();
    ImGui::Render();
}

bool SDL::PollEvent(UIEvent &event) {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            return event.type = kEventQuit;
        } else if (sdlEvent.type == SDL_KEYUP || sdlEvent.type == SDL_KEYDOWN) {
            const int keyCode = sdlEvent.key.keysym.sym;
            if (sdlEvent.type == SDL_KEYDOWN) {
                if (keyCode == SDLK_ESCAPE) {
                    return event.type = kEventQuit;
                } else if (keyCode == SDLK_s)
                    return event.type = kEventSwitch;
            }

        }
    }

    return false;
}

void SDL::Render() {
    SDL_GL_SwapWindow(m_window);
}
