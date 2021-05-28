#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "matrix.hpp" 
#include "pixel.hpp"
#include <string>
class Image : public Matrix<Pixel2>{
    public:
        int contrast_0 = 255*0.4;
        int contrast_1 = 255*0.5;
        int textArea = 0;
        std::string text;
        Image() : Matrix<Pixel2>() {};
        Image(char const* src) : Matrix<Pixel2>(){
            int n, x, y;
            unsigned char * data = stbi_load(src, &x, &y, &n, 1);
            this->dimensions(x, y);
            for(int i = 0; i < this->y; i++){
                for(int j = 0; j < this->x; j++){
                    this->values[i][j] = Pixel2( (float) data[i*this->x + j] );
                }
            }
            // std::cout<<"Image with dimensions: "<<x<<", "<<y<<std::endl;
        }
        void print(char const* text){
            int k = 0;
            for(int i = 0; i < this->y; i++){
                for(int j = 0; j < this->x; j++){
                    if( text[k+1] == '\0' ) k = 0;
                    if(this->values[i][j].gray < this->contrast_0){
                        std::cout<<"  ";
                    } else if(this->values[i][j].gray <= this->contrast_1){
                        std::cout<<text[k]<<text[k+1];
                        k+=2;
                    } else {
                        std::cout<<"\033[1m"<<text[k]<<text[k+1]<<"\033[0m";
                        k+=2;
                    }
                }
                std::cout<<std::endl;
            }
        }
        Image* filter(){
            Image *img = (Image*) Matrix<Pixel2>::filter();
            img->contrast_0 = this->contrast_0;
            img->contrast_1 = this->contrast_1;
            img->review();
            return img;
        }
        Image* filterMultiple(int n){
            Image *img = (Image*) Matrix<Pixel2>::filterMultiple(n);
            img->contrast_0 = this->contrast_0;
            img->contrast_1 = this->contrast_1;
            img->review();
            return img;
        }
        Image* filterToWidth(int w){
            Image *img = (Image*) Matrix<Pixel2>::filterToWidth(w);
            img->contrast_0 = this->contrast_0;
            img->contrast_1 = this->contrast_1;
            img->review();
            return img;
        }
        void review(){
            this->textArea = 0;
            for(int i=0; i<this->y; i++){
                for(int j=0; j<this->x; j++){
                    if( this->values[i][j].gray >= this->contrast_0 ){
                        this->textArea+=2;
                    }
                }
            }
            // std::cout<<textArea<<std::endl;
        }
};