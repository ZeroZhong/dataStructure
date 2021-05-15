#ifndef __GRAPHMTR_CPP_H__
#define __GRAPHMTR_CPP_H__

#include "graphabc_c++.h"
namespace shitong
{
    template <typename Tv>
    struct Vertex
    {
        /* data */
        Tv data;
        int inDegree, outDegree;
        VStatus status;
        int dTime, fTime;
        int parent;
        int priority;
        Vertex(Tv const &d = (Tv)0) : data(d), inDegree(0), outDegree(0), dTime(-1), fTime(-1), parent(-1), priority(INT32_MAX){};
    };

    template <typename Te>
    struct Edge
    {
        /* data */
        Te data;
        int weight;
        EType type;
        Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED){};
    };

    template <typename Te, typename Tv>
    class GraphMatrix : public Graph<Te, Tv>
    {
    private:
        Vector<Vertex<Tv>> V;
        Vector<Vector<Edge<Te> *>> E;

    public:
        GraphMatrix() { this->n = this->e = 0; }
        ~GraphMatrix()
        {
            for (int j = 0; j < this->n; j++)
            {
                for (int i = 0; i < this->n; i++)
                    delete E[i][j];
            }
        }
    };

} // namespace shitong

#endif