#include<iostream>
#include<math.h>

typedef float T;

// считает сумму геометрического ряда для q = 1/2
void geom_sum()
{
    T delta = 0.5, sum = 0;
    while(sum != sum + delta)
    {
        sum += delta;
        delta = 0.5 * delta;
    }
    std::cout << sum << std::endl; 
}

// считает сумму гармонического ряда
void harm_sum()
{
/*
    int i = 1;
    T delta = 1.0 / i, sum = 0;
    while(sum != sum + delta)
    {
        sum += delta;
        i++;
        delta = 1.0 / i;
    }
    std::cout << sum << std::endl;
*/
    T delta, sum = 0;
    for(int i = 1048576; i > 0; i--)
    {
        delta = 1.0 / i;
        sum += delta;
    }
    std::cout << sum << std::endl;
}

void sin_macl()
{
    
}

int main()
{
    //geom_sum();
    harm_sum();
    return 0;
}
