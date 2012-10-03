

#include <utility>
//#include <vector>
#include <algorithm>
#include <boost/bind.hpp>

#include "shapes.h"

    bool Rectangles::selected(pair <pair <int,int>,pair <int,int> > corners){

    int x1 = corners.first.first,y1 = corners.first.second;
    int x2= corners.second.first,y2 = corners.second.second;

        if(corners.second.first - corners.first.first < 0){
            x1 = corners.second.first;
            x2 = corners.first.first;
        }

        if(corners.second.second - corners.first.second < 0){
            y1 = corners.second.second;
            y2 = corners.first.second;
        }

        if( x_sel > x1 &&
            x_sel < x2 &&
            y_sel > y1 &&
            y_sel < y2)
            return true;
        return false;

    }

    void Rectangles::drawRectangle(pair <pair <int,int>,pair <int,int> > corners){
        int x = corners.first.first,y = corners.first.second;

        if(corners.second.first - corners.first.first < 0)
            x = corners.second.first;

        if(corners.second.second - corners.first.second < 0)
            y = corners.second.second;

        SDL_Rect rect = {   x,y,
                            abs(corners.second.first - corners.first.first),
                                abs(corners.second.second - corners.first.second)};

        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));

       /* SDL_UpdateRect(screen, x, y,
                        abs(corners.second.first - corners.first.first),
                        abs(corners.second.second - corners.first.second));*/
    }

//public:

    void Rectangles::update(){

        SDL_FillRect(screen, NULL, 0x000000);

        if ( SDL_MUSTLOCK(screen) ) {
            if ( SDL_LockSurface(screen) < 0 ) {
                return;
            }
        }

        for_each(rectangles.begin(), rectangles.end(), boost::bind( &Rectangles::drawRectangle, this, _1));

        if ( SDL_MUSTLOCK(screen) ) {
            SDL_UnlockSurface(screen);
        }
            //SDL_UpdateRect(screen, 0, 0, 0, 0);
            SDL_Flip(screen);
    }



    void Rectangles::openUpdate(){

        SDL_FillRect(screen, NULL, 0x000000);

        if ( SDL_MUSTLOCK(screen) ) {
            if ( SDL_LockSurface(screen) < 0 ) {
                return;
            }
        }

        for_each(rectangles.begin(), rectangles.end(), boost::bind( &Rectangles::drawRectangle, this, _1));
    }

    void Rectangles::closeUpdate(){

        if ( SDL_MUSTLOCK(screen) ) {
            SDL_UnlockSurface(screen);
        }
            //SDL_UpdateRect(screen, 0, 0, 0, 0);
            SDL_Flip(screen);
    }


    Rectangles::Rectangles(SDL_Surface *screenIn){
            screen=screenIn;
    }
    //~Rectangles(){}

    void Rectangles::push_back(int x1, int y1, int x2, int y2){
        rectangles.insert(rectangles.begin(), make_pair(make_pair(x1,y1), make_pair(x2,y2)));

        update();
    }

    void Rectangles::pop_back(){
        rectangles.pop_back();
    }

    vector <pair <pair <int,int>,pair <int,int> > >::iterator Rectangles::erase(int ID){
        vector <pair <pair <int,int>,pair <int,int> > >::iterator temp;

        if(ID != -1){
            temp = rectangles.erase(rectangles.begin() + ID);
            update();
            return temp;
        }
        else
            return rectangles.end();
    }

    vector <pair <pair <int,int>,pair <int,int> > >::iterator Rectangles::erase(int x, int y){
        int ID= GetID(x,y);
        vector <pair <pair <int,int>,pair <int,int> > >::iterator temp;
        if(ID != -1){
            temp = rectangles.erase(rectangles.begin() + ID);
            update();
            return temp;
        }
        else
            return rectangles.end();
    }

    int Rectangles::GetID(int x, int y){
        vector <pair <pair <int,int>,pair <int,int> > >::iterator it;
        x_sel=x;y_sel=y;
        it= find_if(rectangles.begin(), rectangles.end(), boost::bind( &Rectangles::selected, this, _1));
        if(it != rectangles.end())
            return int(it-rectangles.begin());
        else
            return -1;
    }

    void Rectangles::startRectangle(int x, int y){
        xa=x;ya=y;
    }

    void Rectangles::finishRectangle(int x, int y){
        push_back(xa,ya,x,y);
    }

    void Rectangles::draw1rect(int xb, int yb){

        openUpdate();


        drawRectangle(make_pair(make_pair(xa,ya), make_pair(xb,yb)));

        //SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));


        closeUpdate();

    }
