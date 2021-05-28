#include <iostream>

template <class T>
class Matrix{
    public:
        int x;
        int y;
        T ** values;
        Matrix(){
            this->x = 0;
            this->y = 0;
        }
        Matrix(int x, int y){
            dimensions(x, y);
        }
        void dimensions(int x, int y){
            this->x = x;
            this->y = y;
            this->values = (T **) malloc(sizeof(T*) * y);
            for(int i = 0; i<y; i++){ 
                this->values[i] = (T *) malloc(sizeof(T) * x);
            };
        }
        void fill(T k){
            for(int i = 0; i < this->y; i++){
                for(int j = 0; j < this->x; j++){
                    this->values[i][j] = k;
                    k++;
                }
            }
        }
        void print(){
            for(int i = 0; i < this->y; i++){
                for(int j = 0; j < this->x; j++){
                    std::cout<<this->values[i][j];
                }
                std::cout<<std::endl;
            }
        }
        T getAvergeAtPoint(int y, int x){
            float cornerWeight = 0.5;
            float neighorWeight = 1;
            float centerWeight = 6;
            T avg = this->values[y][x] * centerWeight;
            if(y >= this->y || x >= this->x) return avg;
            // Top left
            if(y > 0 && x > 0) avg += (this->values[y-1][x-1] * cornerWeight);
            // Top right
            if(y > 0 && x < this->x) avg += (this->values[y-1][x+1] * cornerWeight);
            // Bottom left
            if(y < this->y && x > 0) avg += (this->values[y+1][x-1] * cornerWeight);
            // Bottom right
            if(y < this->y && x < this->x) avg+= (this->values[y+1][x+1] * cornerWeight);
            // Top center
            if(y > 0) avg+= (this->values[y-1][x] * neighorWeight);
            // Right center
            if(x < this->x) avg += (this->values[y][x+1] * neighorWeight);
            // Bottom center
            if(y < this->y) avg += (this->values[y][x-1] * neighorWeight);
            // Left center
            if(x > 0) avg += (this->values[y-1][x] * neighorWeight);

            return avg / (4*cornerWeight + 4*neighorWeight + centerWeight);
        }

        Matrix<T> *filter(){
            if(this->x <= 2 || this->y <= 2) return this;
            Matrix<T> *filtered = new Matrix<T>(this->x-2, this->y-2);
            for(int i = 0; i < filtered->y; i++){
                for(int j = 0; j < filtered->x; j++){
                    filtered->values[i][j] = this->getAvergeAtPoint(i+1, j+1);
                }
            }
            return filtered;
        }
        Matrix<T> *filterMultiple(int n){
            Matrix<T> *filtered = this;
            for(int i = 0; i < n; i++){
                filtered = filtered->filter();
            }
            return filtered;
        }
        Matrix<T> *filterToWidth(int w){
            int n = (this->x - w)/2;
            return filterMultiple(n);
        }
};