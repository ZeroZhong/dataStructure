#if !defined(__BITMAO__CPP_H__)
#define __BITMAO__CPP_H__
#include <iostream>
#include <fstream>
#include <cstring>
namespace shitong
{
    class Bitmap
    {
    private:
        char *M;
        int N;

    protected:
        void init(int n)
        {
            M = new char[N = (N + 7) / 8];
            memset(M, 0, N);
        }

    public:
        Bitmap(int n = 8) { init(n); }
        Bitmap(char *file, int n = 8)
        {
            init(n);
            FILE *fl = fopen(file, "r");
            fread(M, sizeof(char), N, fl);
            fclose(fl);
        };
        ~Bitmap()
        {
            delete[] M;
            M = nullptr;
        }
        void set(int k)
        {
            expand(k);
            M[k >> 8] |= (0x80 >> (k & 0x07));
        }
        void clear(int k)
        {
            expand(k);
            M[k >> 8] &= ~(0x80 >> (k & 0x07));
        }
        bool get(int k)
        {
            expand(k);
            return M[k >> 8] & (0x80 >> (k & 0x07));
        }
        void dump(char *file)
        {
            FILE *fp = fopen(file, "w");
            fwrite(M, sizeof(char), N, fp);
            fclose(fp);
        }
        char *bits2strings(int n)
        {
            expand(n - 1);
            char *str = new char[n + 1];
            str[n] = '\0';
            for (int i = 0; i < n; i++)
                str[i] = get(i) ? 1 : 0;
            return str;
        }
        void expand(int k)
        {
            if (k < N * 8)
                return;
            int oldN = N;
            char *oldM = M;
            init(2 * k);
            memcpy(M, oldM, oldN);
            delete[] oldM;
        }
    };
} // namespace shitong
#endif // __BITMAO__CPP_H__