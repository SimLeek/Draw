
#ifndef __State_h
#define __State_h

#include <SDL/SDL.h>
#include "shapes.h"

class StateMachine{

private:
SDL_Event* event;
Rectangles *window1rects;

SDLKey mode;
bool ctrl, alt, shift;

    void Activate(SDL_ActiveEvent* event);
    void Keyboard(SDL_KeyboardEvent* event);
    void MouseMotion(SDL_MouseMotionEvent* event);
    void MouseButtonDown(SDL_MouseButtonEvent* event);
    void MouseButtonUp(SDL_MouseButtonEvent* event);
    void Resize(SDL_ResizeEvent* event);
    void Quit();

public:

    void eventHandler(SDL_Event *eventIn, Rectangles *window1rectsIn):
        event(eventIn),
        window1rects(window1rectsIn){
        };





};

#endif
