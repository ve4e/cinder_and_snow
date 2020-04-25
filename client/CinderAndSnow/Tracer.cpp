#include "Tracer.h"
#include <iostream>
#include <iomanip>

const int WALL   = -1;            // impassable cell
const int BLANK  = -2;            // free unlabeled cell

Tracer::Tracer()
{
}

void Tracer::setPassabilityMtrx(std::vector<std::vector<int> > passabilityMtrx)
{
    if(passabilityMtrx.empty()){
        return;
    }

    passabilityMtrx_ = passabilityMtrx;

    width_ = static_cast<int>(passabilityMtrx_.size());
    height_ = static_cast<int>(passabilityMtrx_[0].size());

    originalTraceMtrx_ = passabilityMtrx;
    for(int i = 0; i < width_; ++i){
        for(int j = 0; j < height_; ++j){
            if(passabilityMtrx_[i][j] == -1){
                originalTraceMtrx_[i][j] = -1;
            }
            else{
                originalTraceMtrx_[i][j] = -2;
            }
        }
    }

#ifdef DEBUG
    for(int i = 0; i < width_; ++i){
        for(int j = 0; j < height_; ++j){
            std::cout << std::setw(2) <<originalTraceMtrx_[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "************" << std::endl;
#endif
}

bool Tracer::checkTracePoints(int ax, int ay, int bx, int by)
{
    bool errorFlag = false;

    if(ax >= width_ || ay >= height_){
        lastErrors_.push_back(Error::StartPointOutside);
        errorFlag = true;
    }
    else if(originalTraceMtrx_[ax][ay] == WALL){
        lastErrors_.push_back(Error::StartPointOnWall);
        errorFlag = true;
    }

    if(bx >= width_ || by >= height_){
        lastErrors_.push_back(Error::EndPointOutside);
        errorFlag = true;
    }
    else if(originalTraceMtrx_[bx][by] == WALL){
        lastErrors_.push_back(Error::EndPointOnWall);
        errorFlag = true;
    }

    return errorFlag;
}


std::vector<std::pair<int, int> > Tracer::trace(int ax, int ay, int bx, int by)   // поиск пути из ячейки (ax, ay) в ячейку (bx, by)
{
#ifdef DEBUG
    std::cout << "ax_ = " << ax << std::endl;
    std::cout << "ay_ = " << ay << std::endl;
    std::cout << "bx_ = " << bx << std::endl;
    std::cout << "by_ = " << by << std::endl;
    std::cout << "width = " << width_ << std::endl;
    std::cout << "height = " << height_ << std::endl;
    std::cout << "TEST this = " << this << std::endl;
#endif

    static const int dx_ [6] = { 0,-1,-1, 0, 1, 1};  // neighboring hexes
    static const int dy_o[6] = {-1, 0, 1, 1, 1, 0};  // for odd index
    static const int dy_e[6] = {-1,-1, 0, 1, 0,-1};  // for even index

    lastErrors_.clear();

    if(checkTracePoints(ax, ay, bx, by)){
        return std::vector<std::pair<int, int> >();
    }

    // reset trace
    auto traceMtrx = originalTraceMtrx_;

    // распространение волны
    int d = 0;
    bool stop;
    traceMtrx[ax][ay] = 0;                     // starting cell labeled 0
    do {
        stop = true;                            // предполагаем, что все свободные клетки уже помечены
        for (int y = 0; y < height_; ++y ){
            for (int x = 0; x < width_; ++x ){
                if ( traceMtrx[x][y] == d )                     // ячейка (x, y) помечена числом d
                {
                    for (int k = 0; k < 6; ++k )                    // проходим по всем непомеченным соседям
                    {
                        int dx = dx_[k];
                        int dy = (x%2 == 0) ? dy_e[k] : dy_o[k];

                        int ix = x + dx, iy = y + dy;
                        if ( ix >= 0 && ix < width_ && iy >= 0 && iy < height_ &&
                             traceMtrx[ix][iy] == BLANK )
                        {
                            stop = false;                       // найдены непомеченные клетки, распространяем волну
                            traceMtrx[ix][iy] = (d + 1);
                        }
                    }
                }
            }
        }
        d++;
    } while ( !stop && traceMtrx[bx][by] == BLANK );

#ifdef DEBUG
    for(int j = 0; j < height_; ++j){
        for(int i = 0; i < width_; ++i){
            std::cout << std::setw(2) <<traceMtrx[i][j];
        }
        std::cout << std::endl;
    }
#endif

    // if trace nod found
    if (traceMtrx[bx][by] == BLANK){
        lastErrors_.push_back(Error::TraceNotFound);
        return std::vector<std::pair<int,int> >();
    }

    // recovery of trace
    int len = traceMtrx[bx][by];
    std::vector<std::pair<int,int> > trace;
    trace.resize(len);

    int x = bx;
    int y = by;
    for(auto it = trace.rbegin(); it!=trace.rend(); ++it)
    {
        *it = std::pair<int,int>(x,y);
        --len;

        for (int k = 0; k < 6; ++k)
        {
            int dx = dx_[k];
            int dy = (x%2 == 0) ? dy_e[k] : dy_o[k];

            int iy=y + dy, ix = x + dx;
            if ( iy >= 0 && iy < height_ && ix >= 0 && ix < width_ && traceMtrx[ix][iy] == len)
            {
                x = x + dx;
                y = y + dy;           // переходим в ячейку, которая на 1 ближе к старту
                break;
            }
        }
    }

    return trace;
}

std::string Tracer::errorToText(Error er)
{
    switch (er)
    {
    case Error::StartPointOnWall:
        return "Start point on wall.";
    case Error::StartPointOutside:
        return "Start point outside.";
    case Error::EndPointOnWall:
        return "End point on wall.";
    case Error::EndPointOutside:
        return "End point outside.";
    case Error::TraceNotFound:
        return "Trace not found.";
    default:
        return "Unknown error.";
    };
}




