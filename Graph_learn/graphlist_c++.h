#ifndef __GRAPHLIST_CPP_H__
#define __GRAPHLIST_CPP_H__
#include "graphabc_c++.h"
namespace shitong
{
    template <typename Tv>
    struct Vertex
    {
        /* data */
        Tv data;
        int inDegree, outDegree;
        int fTime, dTime;
        VStatus status;
        int parent;
        int priority;
        Vertex(Tv const &d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), parent(-1), priority(INT32_MAX) { ; }
    };
    template <typename Te>
    struct Edge
    {
        /* data */
        Te data;
        EType type;
        int weight;
        int v;
        Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) { ; }
    };
    template <typename Tv, typename Te>
    class GraphList : public Graph<Tv, Te>
    {
    private:
        /* data */
        Vector<Vertex<Tv>> V;
        Vector<List<Edge<Te> *>> E;

    public:
        GraphList(/* args */);
        ~GraphList()
        {
            for (int i = 0; i < this->n; i++)
            {
                ListNodePosi(Te) p = E[i].first();
                do
                {
                    /* code */
                    List<Edge<Te>>::remove(p);
                    p = p->succ;
                } while (p);
            }
        }
        ListNodePosi(Te) EDGE(int i, int j)
        {
            ListNodePosi(Te) p = E[i].first();
            do
            {
                /* code */
                if (p->data->v == j)
                    return p;
            } while ((p = p->succ));
            return nullptr;
        }

        virtual Tv &vertex(int i) { return V[i].data; }
        virtual int inDegree(int i) { return V[i].inDegree; }
        virtual int outDegree(int i) { return V[i].outDegree; }
        virtual int firstNbr(int i) { return nextNbr(i, this->n); }
        virtual int nextNbr(int i, int j)
        {
            ListNodePosi(Te) p = EDGE(i, j);
            return p->pred->data->v;
        }
        virtual VStatus &status(int i) { return V[i].status; }
        virtual int &dTime(int i) { return V[i].dTime; }
        virtual int &fTime(int i) { return V[i].fTIme; }
        virtual int &parent(int i) { return V[i].parent; }
        virtual int &priority(int i) { return V[i].priority; }
        virtual int insert(Tv const &vertex)
        {
            E.insert(List<Edge<Te> *>());
            return V.insert(Vector<Tv>(vertex));
        }
        virtual Tv remove(int i)
        {
            ListNodePosi(Te) p = E[i].first();
            do
            {
                /* code */
                V[p->data->v].inDegree--;
                E[i].remove(p);
                p = p->succ;

            } while (p);
            E.remove(i);
            Tv vBak = vertex(i);
            V.remove(i);
            this->n--;
            for (int j = 0; j++; j < this->n)
            {
                if (Edge<Te> *e = E[j].remove(i))
                {
                    delete e;
                    V[j].outDegree--;
                }
            }
            return vBak;
        }
        virtual bool exist(int i, int j)
        {
            bool ret;
            if ((ret = ((i >= 0) && (i < this->n) && (j >= 0) && (j < this->n))))
            {
                ret = false;
                ListNodePosi(Te) p = E[i].first();
                do
                {
                    /* code */
                    if (p->data->v == j)
                        ret = true;
                } while ((p = p->succ));
            }
            return ret;
        }
        virtual EType &type(int i, int j)
        {
            ListNodePosi(Te) p = E[i].first();
            EType &ret = p->data->type;
            do
            {
                /* code */
                if (p->data->v == j)
                    ret = p->data->type;
            } while ((p = p->succ));
            return ret;
        }
        virtual Te &edge(int i, int j)
        {
            // ListNodePosi(Te) p = E[i].first();
            // Te &ret = p->data->data;
            // do
            // {
            //     /* code */
            //     if (p->data->v == j)
            //         ret = p->data->data;
            // } while ((p = p->succ));
            // return ret;
            ListNodePosi(Te) p = EDGE(i, j);
            return p->data->data;
        }
        virtual int &weight(int i, int j)
        {
            ListNodePosi(Te) p = E[i].first();
            int &ret = p->data->weight;
            do
            {
                /* code */
                if (p->data->v == j)
                    ret = p->data->weight;
            } while ((p = p->succ));
            return ret;
        }
        virtual void insert(Te const &edge, int w, int i, int j)
        {
            if (exist(i, j))
                return;
            Edge<Te> *p = new Edge<Te>(edge, w);
            E[i].insertAsLast(p);
            this->e++;
            V[i].inDegree++;
            V[j].outDegree++;
        }
        virtual Te remove(int i, int j)
        {
            ListNodePosi(Te) p = EDGE(i, j);
            Te eBak = p->data->data;
            remove(p);
            this->e--;
            V[i].outDegree--;
            V[j].inDegree--;
            return eBak;
        }
    };

} // namespace shitong

#endif