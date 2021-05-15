#ifndef __GRAPHABC_CPP_H__
#define __GRAPHABC_CPP_H__

#include "../stack_learn/stack/stack_c++.h"
#include "../Quene_learn/Quene_c++.h"
#include "../vecter_learn/vector/vector_c++.h"
namespace shitong
{
    typedef enum
    {
        UNDISCOVERED,
        DISCOVERED,
        VISITED
    } VStatus;
    typedef enum
    {
        UNDETERMINED,
        TREE,
        CROSS,
        FORWARD,
        BACKWARD
    } EType;

    template <typename Tv, typename Te>
    class Graph
    {
    private:
        void reset()
        {
            for (int i = 0; i < n; i++)
            {
                status(i) = UNDISCOVERED;
                dTime(i) = fTime(i) = -1;
                parent(i) = -1;
                priority(i) = INT32_MAX;
                for (int j = 0; j < n; j++)
                    if (exist(i, j))
                        type(i, j) = UNDETERMINED;
            }
        }
        void BFS(int, int &);
        void DFS_R(int, int &);
        void visitDeepestNbr(int v, Stack<int> &S);
        void DFS_I(int, int &);
        void BCC(int, int &, Stack<int> &);
        bool TSort(int, int &, Stack<Tv> *);
        template <typename PU>
        void PFS(int, PU);

    public:
        Graph(/* args */);
        ~Graph();
        //点操作
        int n;
        virtual int insert(Tv const &) = 0;
        virtual Tv remove(int) = 0;
        virtual Tv &vertex(int) = 0;
        virtual int inDegree(int) = 0;
        virtual int outDegree(int) = 0;
        virtual int firstNbr(int) = 0;
        virtual int nextNbr(int, int) = 0;
        virtual VStatus &status(int) = 0;
        virtual int &dTime(int) = 0;
        virtual int &fTime(int) = 0;
        virtual int &parent(int) = 0;
        virtual int &priority(int) = 0;

        //边操作
        int e;
        virtual bool exist(int, int) = 0;
        virtual void insert(Te const &, int, int) = 0;
        virtual Te remove(int, int) = 0;
        virtual EType &type(int, int) = 0;
        virtual Te &edge(int, int) = 0;
        virtual int &weight(int, int) = 0;

        //算法
        void bfs(int);
        void dfs(int);
        void bcc(int);
        Stack<Tv> *tSort(int);
        void prim(int);
        void dijkstra(int);
        template <typename PU>
        void pfs(int, PU);
    };
    template <typename Tv, typename Te>
    void Graph<Tv, Te>::BFS(int v, int &clock)
    {
        //广度遍历算法（单个连通域）
        Quene<int> Q;
        status(v) = DISCOVERED;
        Q.enquene(v);
        while (!Q.empty())
        {
            int v = Q.dequene();
            dTime(v) = ++clock;
            for (int i = firstNbr(v); i > -1; i = nextNbr(v, i))
                if (status(v) == UNDISCOVERED)
                {
                    status(v) = DISCOVERED;
                    type(v, i) = TREE;
                    parent(i) = v;
                    Q.enquene(i);
                }
                else
                {
                    type(v, i) = CROSS;
                }
            status(v) = VISITED;
        }
    }
    template <typename Tv, typename Te>
    void Graph<Tv, Te>::bfs(int s) //breadth-first search
    {
        //全图广度遍历算法
        reset();
        int clock = 0;
        int v = s;
        do
        {
            /* code */
            if (status(v) == UNDISCOVERED)
                BFS(v, clock); //调用单个连同域遍历算法
        } while (s != (v = (++v % n)));
    }

    template <typename Tv, typename Te>
    void Graph<Tv, Te>::DFS_R(int v, int &clock) //recuesive depth-first search
    {
        status(v) = DISCOVERED;
        dTime(v) = ++clock;
        for (int i = firstNbr(v); i > -1; i = nextNbr(v, i))
        {
            switch (status(i))
            {
            case UNDISCOVERED:
                /* code */
                type(v, i) = TREE;
                parent(i) = v;
                DFS_R(i, clock);
                break;
            case DISCOVERED:
                type(v, i) = BACKWARD;

            default:
                type(v, i) = dTime(v) > dTime(i) ? FORWARD : CROSS;
                break;
            }
        }
        status(v) = VISITED;
        fTime(v) = ++clock;
    }

    template <typename Tv, typename Te>
    void Graph<Tv, Te>::visitDeepestNbr(int v, Stack<int> &S)
    {
        bool next = false;
        int u = v;
        for (int i = firstNbr(v); i > -1; i = nextNbr(v, i))
        {
            switch (status(i))
            {
            case UNDISCOVERED:
                /* code */
                if (!next)
                {
                    next = true;
                    status(i) = DISCOVERED;
                    type(u, i) = TREE;
                    dTime(i) = ++clock;
                    v = i;
                }
                S.push(i);
                break;
            case DISCOVERED:
                type(u, i) = BACKWARD;
                break;

            default:
                type(u, i) = (dTime(i) > dTime(v) ? FORWARD : CROSS);
                break;
            }
        }
    }

    template <typename Tv, typename Te>
    void Graph<Tv, Te>::DFS_I(int v, int &clock) //iteration depth-first search
    {
        Stack<int> S;
        status(v) = DISCOVERED;
        dTime(v) = ++clock;
        S.push(v);
        while (!S.empty())
        {
            visitDeepestNbr(v, S);
            v = S.pop();
            status(v) = VISITED;
            fTime(v) = ++clock;
        }
    }

    template <typename Tv, typename Te>
    void Graph<Tv, Te>::dfs(int s) //depth-first search
    {
        reset();
        int v = s;
        int clock = 0;
        do
        {
            /* code */
            if (status(v) == UNDISCOVERED)
                DFS_R(v, clock);
        } while (s != (++v) % n);
    }
    template <typename Tv, typename Te>
    bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *S)
    {
        status(v) = DISCOVERED;
        dTime(v) = ++clock;
        for (int i = firstNbr(v); i > -1; i = nextNbr(v, i))
        {
            switch (status(i))
            {
            case UNDISCOVERED:
                /* code */
                type(v, i) = TREE;
                parent(i) = v;
                if (!TSort(i, clock, S))
                    return false;
                break;
            case DISCOVERED:
                type(v, i) = BACKWARD;
                return false;
                break;

            default:
                type(u, i) = (dTime(i) > dTime(v) ? FORWARD : CROSS);
                break;
            }
        }
        fTime(v) = ++clock;
        status(v) = VISITED;
        S->push(vertex(v));
        return true;
    }
    template <typename Tv, typename Te>
    Stack<Tv> *Graph<Tv, Te>::tSort(int v)
    {
        reset();
        int clock = 0;
        Stack<Tv> *S = new Stack<Tv>;
        int u = v;
        do
        {
            /* code */
            if (status(u) != UNDISCOVERED)
                if (!TSort(u, clock, S))
                {
                    while (!S->empty())
                        S->pop();
                    break;
                }
        } while (v != (++u) % n);
        return S;
    }
    template <typename Tv, typename Te>
    template <typename PU>
    void Graph<Tv, Te>::pfs(int s, PU prioUpdate)
    {
        reset();
        int v = s;
        do
        {
            /* code */
            if (status(v) == UNDISCOVERED)
                PFS(v, prioUpdate);
        } while (s != (++v) % n);
    }
    template <typename Tv, typename Te>
    template <typename PU>
    void Graph<Tv, Te>::PFS(int s, PU prioUpdate)
    {
        priority(s) = o;
        parent(s) = -1;
        status(s) = VISITED;
        while (1)
        {
            for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
                prioUpdate(this, s, w);
            for (int shortest = INT32_MAX, w = 0; w < n; w++)
            {
                if (UNDISCOVERED == status(w))
                    if (shortest > priority(w))
                        shortest = priority(w);
                s = w;
            }
            if (status(s) == VISITED)
                break;
            status(s) = visite;
            type(parent(s), s) = TREE;
        }
    }
    template <typename Tv, typename Te>
    struct primPU
    {
        /* data */
        virtual operator()(Graph<Tv, Te> *g, int uk, int v)
        {
            if (g->status(v) == UNDISCOVERED)
                if (g->priority(v) > g->weight(uk, v))
                {
                    g->priority(v) = g->weight(uk, v);
                    g->parent(v) = uk;
                }
        }
    };
    template <typename Tv, typename Te>
    void Graph<Tv, Te>::prim(int s)
    {
        primPU prioUpdate;
        pfs(s, prioUpdate);
    }
    template <typename Tv, typename Te>
    struct DijkstraPU
    {
        /* data */
        virtual operator()(Graph<Tv, Te> *g, int uk, int v)
        {
            if (g->status(v) == UNDISCOVERED)
                if (g->priority(v) > g->priority(uk) + g->weight(uk, v))
                {
                    g->priority(v) = g->priority(uk) + g->weight(uk, v);
                    g->parent(v) = uk;
                }
        }
    };
    template <typename Tv, typename Te>
    void Graph<Tv, Te>::dijkstra(int s)
    {
        DijkstraPU prioUpdate;
        pfs(s, prioUpdate);
    }

} // namespace shitong
#endif