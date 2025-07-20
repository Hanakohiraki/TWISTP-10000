#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <cmath>

void drawText3D(const std::string& text, TTF_Font* font, float x, float y, float z) {
    SDL_Color color = {200, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) return;

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    SDL_LockSurface(surface);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_UnlockSurface(surface);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

    float w = surface->w / 400.0f;
    float h = surface->h / 400.0f;

    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-w, h, 0);
    glTexCoord2f(1, 0); glVertex3f(w, h, 0);
    glTexCoord2f(1, 1); glVertex3f(w, -h, 0);
    glTexCoord2f(0, 1); glVertex3f(-w, -h, 0);
    glEnd();
    glPopMatrix();

    glDeleteTextures(1, &texID);
    SDL_FreeSurface(surface);
}

void drawCube(float size) {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.9f);

    // Front
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    // Back
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);

    // Left
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);

    // Right
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);

    // Top
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    // Bottom
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    glEnd();
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("TWI Station Menu",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 32);
    if (!font) {
        std::cerr << "Font failed\n";
        return 1;
    }

    bool running = true;
    float angle = 0;
    float camY = 5.0f;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
                running = false;
        }

        glClearColor(0.0f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1280.0 / 720.0, 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, camY, 10, 0, 0, 0, 0, 1, 0);

        // หมอกเบาๆ
        glBegin(GL_QUADS);
        glColor4f(0.4f, 0.7f, 1.0f, 0.1f);
        glVertex3f(-100, -1, -50); glVertex3f(100, -1, -50);
        glVertex3f(100, 2, 50); glVertex3f(-100, 2, 50);
        glEnd();

        // หมุนกล่อง
        glPushMatrix();
        glTranslatef(-2, 0, 0);
        glRotatef(angle, 1, 1, 0);
        drawCube(1.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2, 0, 0);
        glRotatef(-angle * 1.2f, 0, 1, 1);
        drawCube(1.0f);
        glPopMatrix();

        // ข้อความ
        drawText3D("CONFIGURATION", font, -3.5f, -2.5f, 0);
        drawText3D("TWI STATION SETTINGS", font, -3.5f, -3.5f, 0);
        drawText3D("ABOUT", font, -3.5f, -4.5f, 0);

        SDL_GL_SwapWindow(window);
        angle += 0.5f;
        camY = std::max(2.0f, camY - 0.01f);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
