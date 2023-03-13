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
            if (start.y > end.y) {
                for (int y = end.y; y <= start.y; y++) {
                    img.SetPixel(start.x, y, color);
                }
            }
            else {
                for (int y = start.y; y <= end.y; y++) {
                    img.SetPixel(start.x, y, color);
                }
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
        if (k <= 1 && k > 0) {
            double e = -0.5;
            for (int x = start.x, y = start.y; x <= end.x; x++) {
                img.SetPixel(x, y, color);
                e += k;
                if (e >= 0) {
                    y++;
                    e -= 1;
                }
            }
        }
        else if (k > 1) {
            double e = -0.5;
            for (int x = start.x, y = start.y; y <= end.y; y++) {
                img.SetPixel(x, y, color);
                e += 1 / k;
                if (e >= 0) {
                    x++;
                    e -= 1;
                }
            }
        }
        else if (k < 0 && k >= -1) {
            double e = -0.5;
            for (int x = start.x, y = start.y; x <= end.x; x++) {
                img.SetPixel(x, y, color);
                e -= k;
                if (e >= 0) {
                    y--;
                    e -= 1;
                }
            }
        }
        else if (k < -1) {
            double e = -0.5;
            for (int x = start.x, y = start.y; y >= end.y; y--) {
                img.SetPixel(x, y, color);
                e -= 1 / k;
                if (e >= 0) {
                    x++;
                    e -= 1;
                }
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
        int x = 0, y = radius;
        double d = 1.25 - radius;
        while (x <= y) {
            img.SetPixel(cx + x, cy + y, color); 
            img.SetPixel(cx + x, cy - y, color); 
            img.SetPixel(cx - x, cy + y, color); 
            img.SetPixel(cx - x, cy - y, color);
            img.SetPixel(cx + y, cy + x, color);
            img.SetPixel(cx + y, cy - x, color);
            img.SetPixel(cx - y, cy + x, color);
            img.SetPixel(cx - y, cy - x, color);
            if (d < 0) {
                d += 2 * x + 3;
            }
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
        }
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
        int width = img.Width();
        int height = img.Height();
        Vector3f oldColor = img.GetPixel(cx, cy);
        std::queue<std::pair<int, int>> q;
        q.push(std::make_pair(cx, cy));
        while (!q.empty()) {
            std::pair<int, int> p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            if (x < 0 || x >= width || y < 0 || y >= height) {
                continue;
            }
            if (img.GetPixel(x, y) != oldColor) {
                continue;
            }
            img.SetPixel(x, y, color);
            q.push(std::make_pair(x + 1, y));
            q.push(std::make_pair(x - 1, y));
            q.push(std::make_pair(x, y + 1));
            q.push(std::make_pair(x, y - 1));
        }
        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
            color.x(), color.y(), color.z());
    }
};