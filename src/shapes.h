
#ifndef __Rectangles_h
#define __Rectangles_h

#include <vector>

#include <SDL/SDL.h>

using namespace std;

class Rectangles{

private:
    int xa,ya;
    int x_sel,y_sel;
    SDL_Surface *screen;
    vector <pair <pair <int,int>,pair <int,int> > > rectangles;


    bool selected(pair <pair <int,int>,pair <int,int> > corners);

    void drawRectangle(pair <pair <int,int>,pair <int,int> > corners);

public:

    void draw1rect(int xb, int yb);

    Rectangles(SDL_Surface *screenIn);

    void update();
    void openUpdate();
    void closeUpdate();
    //~Rectangles(){}

    void push_back(int x1, int y1, int x2, int y2);

    void pop_back();

    vector <pair <pair <int,int>,pair <int,int> > >::iterator erase(int ID);

    vector <pair <pair <int,int>,pair <int,int> > >::iterator erase(int x, int y);

    int GetID(int x, int y);

    void startRectangle(int x, int y);

    void finishRectangle(int x, int y);
};

#endif
