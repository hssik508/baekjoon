#include <iostream>

using namespace std;

class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle(int width, int height) : width(width), height(height) {}
    int get_width() const
    {
        return width;
    }
    int get_height() const
    {
        return height;
    }
    void set_width(int width)
    {
        if (width > 0 && width <= 1000)
            this->width = width;
    }
    void set_height(int height)
    {
        if (height > 0 && height <= 2000)
            this->height = height;
    }
    int area() const
    {
        return width * height;
    }
    int perimeter() const
    {
        return 2 * (width + height);
    }
    bool is_square() const
    {
        if (width == height)
            return true;
        else
            return false;
    }
};

int main()
{
    Rectangle r(3,4);
    cout<<r.is_square();
    return 0;
}