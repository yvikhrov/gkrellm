#ifndef SDL_HPP
# define SDL_HPP

# include "IMonitorDisplay.hpp"
# define GLEW_STATIC
# include <GL/glew.h>

# include <SDL.h>
# include <SDL_opengl.h>

class SDL : public IMonitorDisplay {
public:
    SDL();
    SDL(SDL const& inf);
    ~SDL();

    SDL &operator=(SDL const& inf);

    void Update(std::vector<IMonitorModule*>& modules);
    bool PollEvent(UIEvent &event);
    void Render();
private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
};

#endif

