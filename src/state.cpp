#include "state.hpp"

State::State(Rectangles* window1rectsIn, StateMachine* myParent):
    window1rects(window1rectsIn),
    parent(myParent)
    {

    }

void State::eventHandler(){
    switch (parent->event->type) {
        case SDL_KEYDOWN:
                KeyboardDown();
                break;
        case SDL_MOUSEBUTTONDOWN:
                MouseButtonDown();
                break;
        case SDL_MOUSEMOTION:
                MouseMotion();
                break;
        case SDL_MOUSEBUTTONUP:
                MouseButtonUp();
                break;
        case SDL_QUIT:
            exit(0);
    }

}

void State::run(){

    while(true){

    SDL_WaitEvent(parent->event);
    eventHandler();

        while ( SDL_PollEvent(parent->event) ) {
            eventHandler();
        }
    }


}

void State::Activate(){}
void State::KeyboardDown(){}
void State::KeyboardUp(){}
void State::MouseMotion(){}
void State::MouseButtonDown(){}
void State::MouseButtonUp(){}
void State::Resize(){}
void State::Quit(){}


mainState::mainState(Rectangles* theShapes, StateMachine* myParent):
    State(theShapes, myParent)
    {

    }


    void mainState::Activate(){
    }
    void mainState::KeyboardDown(){
        if(parent->event->key.keysym.sym == SDLK_ESCAPE)
            SDL_Quit();

    }
    void mainState::KeyboardUp(){
    }
    void mainState::MouseMotion(){
        if(SDL_BUTTON(1) == parent->event->motion.state)
            window1rects->draw1rect(parent->event->motion.x, parent->event->motion.y);
    }
    void mainState::MouseButtonDown(){

        if(parent->event->button.button == SDL_BUTTON_LEFT)
            window1rects->startRectangle(parent->event->button.x, parent->event->button.y);
        else if(parent->event->button.button == SDL_BUTTON_RIGHT)
            window1rects->erase(parent->event->button.x, parent->event->button.y);

    }
    void mainState::MouseButtonUp(){
        if(parent->event->button.button == SDL_BUTTON_LEFT)
            window1rects->finishRectangle(parent->event->button.x, parent->event->button.y);
    }
    void mainState::Resize(){
    }
    void mainState::Quit(){
        SDL_Quit();     //less segfaults
    }


StateMachine::StateMachine(State* stateIn):
        screen(SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)),
        window1rects(new Rectangles(screen)),
        currentState(stateIn),
        event(new SDL_Event)
        {

            if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_DOUBLEBUF) < 0 ) {
                fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
                exit(1);
            }
            //atexit(SDL_Quit);     //more segfaults

            //screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
            if ( screen == NULL ) {
                fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
                exit(1);
            }


            currentState->run();


        };

StateMachine::StateMachine():
        screen(SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)),
        window1rects(new Rectangles(screen)),
        currentState(new mainState(window1rects, this)),
        event(new SDL_Event)
        {

            if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_DOUBLEBUF) < 0 ) {
                fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
                exit(1);
            }
            //atexit(SDL_Quit);     //more segfaults

            //screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
            if ( screen == NULL ) {
                fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
                exit(1);
            }


            currentState->run();
        };

StateMachine::~StateMachine(){
    delete event;
}

void StateMachine::changeState(State* nextState){

    currentState=nextState;

}
