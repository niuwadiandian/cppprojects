/*
    这是注释部分
    不同的部分
*/
// 不同的枚举类不能互相赋值
#if false   //预处理
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color{
    Red, Orange, Yellow, Green, Blue, Black
};
enum class Color2{
    Red, Orange, Yellow, Green
};

int main(void){
    string s1("hello"),s2="world",s3;
    s3 = s1 + s2;
    cout << s3 << "sizeof s3 is" << s3.size() << endl;
}

#endif

// c++17 新特性 optional函数返回多个变量
#if 0 
#include <iostream>
#include <optional>

using namespace std;

struct Out {
    string out1 { "" };
    string out2 { "" };
};

optional<Out> func(const string& in) {
    Out o;
    if (in.size() == 0)
        return nullopt;
    o.out1 = "hello";
    o.out2 = "world";
    return { o };
}

int main() {
    if (auto ret = func("hi"); ret.has_value()) {
        cout << ret->out1 << endl;
        cout << ret->out2 << endl;
    }
    return 0;
}
#endif

// 输入3个数字，从小到大排列
#if 0
#include <iostream>

using namespace std;
// rank from small to large
auto rank3r(double a, double b, double c){
    struct result {double x; double y; double z;};
    double temp = 0.0;
    if (a > b){
        temp = a;
        a = b;
        b = temp;
    }
    if (a > c){
        temp = a;
        a = c;
        c = temp;
    }
    if (b > c){
        temp = b;
        b = c;
        c = temp;
    }
    return result {a, b, c};
}
int main(void){
    double a,b,c;
    cout << "Please input three real numbers seperated by 'Enter key'"<< endl;
    cin >> a
        >> b
        >> c;
    auto [x, y, z] = rank3r(a, b, c);
    cout << "\nFrom small to big:" << x << "'" << y << "'" << z << endl;
    return 0;
}


#endif 

// 输入数字，随时输出最大值
#if 0
#include <iostream>
#include <iosfwd>
using namespace std;
int main(){
    long signed int a, max;
    cout << "Please input a series of number,end with a dot(.):" << endl;
    cin >> a ;
    if (a == '.'){
        return 1;
    }else{
        max = a;
    }
    while(cin >> a){
        if (a == '.'){
            break;
        }else if (a >= max)
        {
            max = a;
        }  
    }
    cout << "the max number is :" << max << endl;
    return 0;
}
#endif 

//输入行数n，输出前n行三角金字塔
#if 0
#include <iostream>
using namespace std;

int main(){
    int n = 0;
    cout << "Please input number of rows(int):" << endl;
    cin >> n;
    if (n > 40){
        cout << "n is too big!" << endl;
        return 1;
    }else if(n < 1){
        cout << "n is too small!" << endl;
        return 1;
    }
    for (int i=1;i<=n;i++){
        for(int j=1; j<=(n-i); j++){
            cout << " ";
        }
        for(int k=1; k<=(2*i-1); k++){
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
#endif 

//输入行数n，输出前n行数字三角
#if 1
#include <iostream>
//#include <math>
using namespace std;

int main(){
    int n = 0;
    cout << "Please input number of rows(int):" << endl;
    cin >> n;
    if (n > 40){
        cout << "n is too big!" << endl;
        return 1;
    }else if(n < 1){
        cout << "n is too small!" << endl;
        return 1;
    }
    for (int i=1;i<=n;i++){
        for(int j=1; j<=(n-i); j++){
            cout << " ";
        }
        for(int k=1; k<=(2*i-1); k++){
            int num = 0;
            num = (2*i-1)-abs(i-k);
            cout << num;
        }
        cout << endl;
    }
    return 0;
}
#endif 

//输入正整数，判断是否为质数
#if 0

#endif 

#if 0


#endif 

#if 0


#endif 
