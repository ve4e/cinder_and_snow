#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include <string>

class Tracer
{
public:
    Tracer();

    //void setPassabilityMtrx(std::vector<std::vector<int> > passabilityMtrx);
    void setPassabilityMtrx(std::vector<std::vector<int> > passabilityMtrx);
    std::vector <std::pair<int, int> > trace(int ax, int ay, int bx, int by);

    enum class Error{
        StartPointOnWall,
        StartPointOutside,
        EndPointOnWall,
        EndPointOutside,
        TraceNotFound
    };
    std::vector<Error> lastErrors() {return lastErrors_;}

    static std::string errorToText(Error er);

private:
    bool checkTracePoints(int ax, int ay, int bx, int by);
    void resetTraceMtrx();

    std::vector<std::vector<int> > passabilityMtrx_;
    std::vector<std::vector<int> > originalTraceMtrx_;
    int width_ {0};
    int height_ {0};

    std::vector<Error> lastErrors_ ;
};

#endif // TRACER_H




