#include <vector>
#include <iostream>
#include <fstream>

// параметры модели 
float const
    w = 1,
    t_0 = 0,
    x_0 = 1,
    v_0 = 0,
    dt = 0.01,
    t_end = 40;

// метод Эйлера
void euler(std::vector<float> &txv, std::ofstream &out) 
{
    float x, v;
    while(txv[0] < t_end)
    {
        x = txv[1];
        v = txv[2];
        txv[0] += dt;
        txv[1] += dt * v;
        txv[2] += dt * (- w * w * x);
        out << txv[0] << " " << txv[1] << " " << txv[2] << "\n";
    }
}

//метод Хойна
void heun(std::vector<float> &txv, std::ofstream &out)
{
    float x_1, x_2, v_1, v_2;
    while(txv[0] < t_end)
    {
        x_1 = txv[1];
        v_1 = txv[2];
        x_2 = x_1 + dt * v_1;
        v_2 = v_1 + dt * (- w * w * x_1);
        txv[0] += dt;
        txv[1] += 0.5 * dt * (v_1 + v_2);
        txv[2] += 0.5 * dt * (- w * w) * (x_1 + x_2);
        out << txv[0] << " " << txv[1] << " " << txv[2] << "\n";
    }
}

int main() 
{
    // переменные-вектор
    std::vector<float> txv(3);
    txv[0] = t_0;
    txv[1] = x_0;
    txv[2] = v_0;     

    // записываем данные в data.txt
    std::ofstream out;
    out.open("data.txt");
    out << txv[0] << " " << txv[1] << std::endl;

    // euler(txv, out);
    heun(txv, out);
    return 0;
}

