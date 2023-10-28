#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

class PerlinNoise {
private:
    std::vector<int> p;

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double grad(int hash, double x, double y) {
        int h = hash & 15;
        double u = h < 8 ? x : y,
            v = h < 4 ? y : x;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double lerp(double a, double b, double x) {
        return a + x * (b - a);
    }

public:
    PerlinNoise() {
        p.resize(512);
        std::iota(p.begin(), p.end(), 0);
        std::random_shuffle(p.begin(), p.end());
        for (unsigned i = 0; i < 256; ++i) {
            p[256 + i] = p[i];
        }
    }

    double noise(double x, double y) {
        int X = (int)floor(x) & 255;                  // Modulo 256
        int Y = (int)floor(y) & 255;
        x -= floor(x);
        y -= floor(y);
        double u = fade(x);
        double v = fade(y);
        int a = p[X] + Y;
        int b = p[X + 1] + Y;
        a = a & 255;   // Assurez-vous que a est dans la plage [0, 255]
        b = b & 255;   // Assurez-vous que b est dans la plage [0, 255]
        return lerp(lerp(grad(p[a], x, y), grad(p[b], x - 1, y), u),
            lerp(grad(p[a + 1], x, y - 1), grad(p[b + 1], x - 1, y - 1), u),
            v);
    }
};

#endif // PERLINNOISE_H
