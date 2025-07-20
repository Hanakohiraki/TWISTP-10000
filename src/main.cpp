#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>

GLuint createTextTexture(TTF_Font* font, const std::string& text, SDL_Color color, int* w, int* h) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) return 0;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        surface->w, surface->h, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    *w = surface->w;
    *h = surface->h;

    SDL_FreeSurface(surface);
    return tex;
}

void renderTextTexture(GLuint tex, int w, int h, float alpha) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 720, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f((1280 - w) / 2, 300);
    glTexCoord2f(1, 0); glVertex2f((1280 + w) / 2, 300);
    glTexCoord2f(1, 1); glVertex2f((1280 + w) / 2, 300 + h);
    glTexCoord2f(0, 1); glVertex2f((1280 - w) / 2, 300 + h);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); // เพิ่ม buffer ลดสะดุด

    SDL_Window* win = SDL_CreateWindow("TWI Station",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    glewInit();

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Font error: " << TTF_GetError() << "\n";
        return 1;
    }

    Mix_Chunk* sound = Mix_LoadWAV("assets/boot.wav");
    if (!sound) {
        std::cerr << "Sound error: " << Mix_GetError() << "\n";
        return 1;
    }

    Mix_PlayChannel(-1, sound, 0);

    SDL_Color white = {255, 255, 255, 255};
    int w1, h1, w2, h2;
    GLuint tex1 = createTextTexture(font, "THE WORLD IMPACT GROUP", white, &w1, &h1);
    GLuint tex2 = createTextTexture(font, "TWI STATION PRO 1", white, &w2, &h2);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1280.0/720.0, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    Uint32 start = SDL_GetTicks();
    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        Uint32 now = SDL_GetTicks() - start;

        glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        float camZ = 5.0f - std::min(2.0f, now / 3000.0f);
        glTranslatef(0, 0, -camZ);
        renderCube();

        if (now < 2000) {
            float a = now / 2000.0f;
            renderTextTexture(tex1, w1, h1, a);
        } else if (now < 4000) {
            float a = (now - 2000) / 2000.0f;
            renderTextTexture(tex2, w2, h2, a);
        }

        SDL_GL_SwapWindow(win);
        SDL_Delay(16);
    }

    glDeleteTextures(1, &tex1);
    glDeleteTextures(1, &tex2);
    Mix_FreeChunk(sound);
    TTF_CloseFont(font);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
