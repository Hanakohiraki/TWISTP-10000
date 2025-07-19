#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <cmath>

// ใช้แสดงข้อความจริง
void drawText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int alpha) {
    SDL_Color color = {255, 255, 255, (Uint8)alpha};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { (1280 - surface->w) / 2, 300, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// วาด cube หน้าหนึ่ง (3D placeholder)
void renderCube() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.8f);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);
    glEnd();
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL init failed\n";
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "TTF init failed\n";
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Audio init failed\n";
        return 1;
    }

    Mix_Music* music = Mix_LoadMUS("assets/boot.wav");
    if (!music) std::cerr << "Failed to load music: " << Mix_GetError() << "\n";

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Font load failed\n";
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("TWI Station",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    SDL_GLContext glctx = SDL_GL_CreateContext(win);
    glewInit();

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1280.0 / 720.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    Uint32 start = SDL_GetTicks();
    bool running = true;
    bool played = false;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        Uint32 now = SDL_GetTicks() - start;

        // Play sound once
        if (!played && music) {
            Mix_PlayMusic(music, 0);
            played = true;
        }

        // Render 3D
        glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        float camZ = 5.0f - std::min(2.0f, now / 3000.0f);
        glTranslatef(0, 0, -camZ);
        renderCube();
        SDL_GL_SwapWindow(win);

        // Render text overlay
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // transparent bg
        SDL_RenderClear(renderer);

        if (now < 2000) {
            int alpha = std::min(255, (int)(now / 2000.0 * 255));
            drawText(renderer, font, "THE WORLD IMPACT GROUP", alpha);
        } else if (now < 4000) {
            int alpha = std::min(255, (int)((now - 2000) / 2000.0 * 255));
            drawText(renderer, font, "TWI STATION PRO 1", alpha);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60fps
    }

    // Cleanup
    TTF_CloseFont(font);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
