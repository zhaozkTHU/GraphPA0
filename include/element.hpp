#pragma once

#include <image.hpp>
#include <algorithm>
#include <queue>
#include <cstdio>

class Element {
public:
    virtual void draw(Image& img) = 0;
    virtual ~Element() = default;
};

class Line: public Element {

public:
    int xA, yA;
    int xB, yB;
    Vector3f color;
    void draw(Image& img) override {
        // TODO: Implement Bresenham Algorithm
        struct Point {
            int x, y;
        };
        Point start, end;
        if (xA < xB) {
            start.x = xA; start.y = yA;
            end.x = xB; end.y = yB;
        }
        else {
            start.x = xB; start.y = yB;
            end.x = xA; end.y = yA;
        }
        if (start.x == end.x) {
            for (int y = start.y; y <= end.y; y++) {
                img.SetPixel(start.x, y, color);
            }
            return;
        }
        if (start.y == end.y) {
            for (int x = start.x; x <= end.x; x++) {
                img.SetPixel(x, start.y, color);
            }
            return;
        }
        int dx = end.x - start.x;
        int dy = end.y - start.y;
        double k = double(dy) / double(dx);
        double e = -0.5;
        if (k <= 1 && k >= -1) {
            int x = start.x, y = start.y;
            while (x <= end.x) {
                img.SetPixel(x, y, color);
                e += k;
                if (e >= 0) {
                    y++;
                    e -= 1;
                }
                x++;
            }
        }
        else {
            int x = start.x, y = start.y;
            while (y <= end.y) {
                img.SetPixel(x, y, color);
                e += 1 / k;
                if (e >= 0) {
                    x++;
                    e -= 1;
                }
                y++;
            }
        }
    }
};

class Circle: public Element {

public:
    int cx, cy;
    int radius;
    Vector3f color;
    void draw(Image& img) override {
        // TODO: Implement Algorithm to draw a Circle
        printf("Draw a circle with center (%d, %d) and radius %d using color (%f, %f, %f)\n", cx, cy, radius,
            color.x(), color.y(), color.z());
    }
};

class Fill: public Element {

public:
    int cx, cy;
    Vector3f color;
    void draw(Image& img) override {
        // TODO: Flood fill
        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
            color.x(), color.y(), color.z());
    }
};