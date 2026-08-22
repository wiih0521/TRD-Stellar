
int extendedGCD(int a, int b, int &x, int &y){
    x = 1, y= 0;
    int _x = 0, _y = 1;
    while(b > 0){
        int q = a / b;
        tie(x, _x) = make_tuple(_x, x - q * _x);
        tie(y, _y) = make_tuple(_y, y - q * _y);
        tie(a, b) = make_tuple(b, a - q * b);
    }
    return a;
}