#include <iostream>
class Pixel2 {
    public:
        float gray;
        float red;
        float green;
        float blue;
        float alpha;
        Pixel2(){
            gray = 0;
            red = 0;
            green = 0;
            blue = 0;
            alpha = 0;
        }
        Pixel2(float g){
            gray = g;
            red = 0;
            green = 0;
            blue = 0;
            alpha = 0;
        }
        friend std::ostream& operator<<(std::ostream& os, const Pixel2& p);
        Pixel2 operator* (float f);
        Pixel2 operator/ (float f);
        Pixel2 operator+= (float f);
        Pixel2 operator+= (Pixel2 p);
};

std::ostream& operator << (std::ostream& os, const Pixel2&p){
    os << "rgba("<<p.red<<","<<p.green<<","<<p.blue<<","<<p.alpha<<")";
    return os;
}

Pixel2 Pixel2::operator*(float f){
    Pixel2 p;
    p.gray = this->gray * f;
    p.red = this->gray * f;
    p.green = this->green * f;
    p.blue = this->blue * f;
    p.alpha = this->alpha * f;
    return p;
}
Pixel2 Pixel2::operator/(float f){
    Pixel2 p;
    p.gray = this->gray / f;
    p.red = this->gray / f;
    p.green = this->green / f;
    p.blue = this->blue / f;
    p.alpha = this->alpha / f;
    return p;
}
Pixel2 Pixel2::operator+=(float f){
    this->gray += f;
    this->red += f;
    this->green += f;
    this->blue += f;
    this->alpha += f;
    return *this;
}
Pixel2 Pixel2::operator+=(Pixel2 p){
    this->gray += p.gray;
    this->red += p.red;
    this->green += p.green;
    this->blue += p.blue;
    this->alpha += p.alpha;
    return *this;
}