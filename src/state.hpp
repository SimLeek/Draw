
#ifndef __State_h
#define __State_h

#include <SDL/SDL.h>
#include "shapes.h"

class StateMachine;

class State{

    protected:

    Rectangles* window1rects;
    StateMachine* parent;

    SDLKey mode;
    bool ctrl, alt, shift;

    virtual void Activate();
    virtual void KeyboardDown();
    virtual void KeyboardUp();
    virtual void MouseMotion();
    virtual void MouseButtonDown();
    virtual void MouseButtonUp();
    virtual void Resize();
    virtual void Quit();

    public:

    virtual void eventHandler();

    void run();

    State(Rectangles* window1rectsIn, StateMachine* machineIn);
};

class mainState : public State{

    private:

    void Activate();
    void KeyboardDown();
    void KeyboardUp();
    void MouseMotion();
    void MouseButtonDown();
    void MouseButtonUp();
    void Resize();
    void Quit();

    public:

    mainState(Rectangles* theShapes, StateMachine* myParent);

};

class StateMachine{

private:
SDL_Surface *screen;

Rectangles* window1rects;
State* currentState;

public:

    StateMachine(State* stateIn);
    StateMachine();
    ~StateMachine();

    void changeState(State* nextState);

    SDL_Event* event;

};

#endif
