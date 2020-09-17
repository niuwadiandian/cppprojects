#include <iostream>
#include <limits>
using namespace std;
#define LENGTH  100
#define WIDTH   80
#define NEWLINE "\n"
extern int a,b;
extern float j;
int main(void)
{
    int a = 0x12;
    int b(017);
    float j;
    int area = LENGTH * WIDTH;
    cout << a <<"+" << b <<"=" << (a+b) << "\n"; 
    cout << a <<"/" << b <<"=" << ((float)a/(float)b); 
    cout << NEWLINE;
    cout << "Area is " << area << "m^2" << endl;
    cout << "Here we go!\n";
    return 0;
}