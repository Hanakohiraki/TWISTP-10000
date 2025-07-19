#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <thread>

// Simple draw text placeholder (you can replace with SDL_ttf)
void drawText(SDL_Renderer* renderer, const std::string& text, int alpha) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_Rect rect = { 300, 300, 800, 100 };
    SDL_RenderFillRect(renderer, &rect);
}

// Simple cube render placeholder
void renderCube() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.8f);

    // Front
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);
    glEnd();
}

int main(int argc, char* argv[]) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL failed\n";
        return 1;
    }

    // Init Audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* music = Mix_LoadMUS("assets/boot.wav");

    // Window
    SDL_Window* win = SDL_CreateWindow("TWI Station", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    SDL_GLContext glctx = SDL_GL_CreateContext(win);
    glewInit();

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1280.0/720.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    bool running = true;
    Uint32 start = SDL_GetTicks();
    int phase = 0;

    if (music) Mix_PlayMusic(music, 0);

    while (running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        Uint32 now = SDL_GetTicks() - start;

        glClearColor(0.1f, 0.1f, 0.3f, 1.0f); // blue "cloudy" background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glLoadIdentity();

        // Fake camera movement
        float camZ = 5.0f - std::min(2.0f, now / 3000.0f);
        glTranslatef(0, 0, -camZ);

        // Draw cube
        renderCube();

        SDL_GL_SwapWindow(win);

        // Overlay 2D text
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(renderer);

        if (now < 2000) {
            drawText(renderer, "THE WORLD IMPACT GROUP", now / 8);
        } else if (now < 4000) {
            drawText(renderer, "TWI STATION PRO 1", (now - 2000) / 8);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
