#include "image.hpp" 

int main(int argc, char** argv){
    Image img2("ana-xs.jpg");
    // img2.print("-");
    img2.filterMultiple(3)->print(argv[1]);
    return 2;
}