#include <array>
#include <iostream>
#include <fstream>

// method of numerical solving
template<class T>
class Method
{
public:
    virtual void iteration(T &state) const = 0;
};

// Euler's method
template<class T>
class Euler: public Method<T>
{
public:
    Euler(): Method<T>() {}
    void iteration(T &state) const override
    {
        auto dt = state.get_dt();
        T k = state.dfdt();
        state = state + k * dt;
    }
};

// Heun's method
template<class T>
class Heun: public Method<T>
{
public:
    Heun(): Method<T>() {}
    void iteration(T &state) const override
    {
        auto dt = state.get_dt();
        T k_1 = state.dfdt();
        T k_2 = (state + k_1 * dt).dfdt();
        state = state + (k_1 + k_2) * (0.5 * dt);
    }
};

// Runge-Kutta's method
template<class T>
class RungeKutta: public Method<T>
{
public:
    RungeKutta(): Method<T>() {}
    void iteration(T &state) const override
    {
        auto dt = state.get_dt();
        T k_1 = state.dfdt();
        T k_2 = (state + k_1 * (0.5 * dt)).dfdt();
        T k_3 = (state + k_2 * (0.5 * dt)).dfdt();
        T k_4 = (state + k_3 * dt).dfdt();
        state = state + (k_1 + k_2 * 2 + k_3 * 2 + k_4) * (dt / 6);
    }
};

// abstract state of the system
template<typename T>
class State
{
private:
    T const dt = 0.01;
    int const size = 3;
    std::array<T, 3> variables;
public:
    State(std::array<T, 3> variables):
        variables(variables) {}
    // derivative
    State<T> dfdt() const
    {
        std::array<T, 3> tmp;
        tmp[0] = 1;
        tmp[1] = variables[2];
        tmp[2] = - variables[1];
        return State<T>(tmp);
    }
    // operators
    T& operator[](int idx) { return variables[idx]; }
    State<T> operator=(State<T> other)
    {
        if(this == &other) { return *this; }
        variables = other.variables;
        return *this;
    }
    State<T> operator+(State<T> other)
    {
        std::array<T, 3> tmp;
        for(int idx = 0; idx < size; idx++)
        {
            tmp[idx] = variables[idx] + other.variables[idx];
        }
        return State<T>(tmp);
    }
    State<T> operator*(T num)
    {
        std::array<T, 3> tmp;
        for(int idx = 0; idx < size; idx++)
        {
            tmp[idx] = variables[idx] * num;
        }
        return State<T>(tmp);
    }
    // prints state
    void print() const
    {
        for(int idx = 0; idx < size; idx++)
        {
            std::cout << variables[idx] << " ";
        }
        std::cout << "\n";
    }
    // returns dt
    T get_dt() const { return dt; }
    // returns size
    int get_size() const { return size; }
};

// solves differential equation
template<typename T>
void calculate(Method<State<T>> &method, State<T> initial, std::ofstream &out, T duration)
{
    State<T> tmp = initial;
    while(tmp[0] - initial[0] < duration)
    {
        method.iteration(tmp);
        for(int idx = 0; idx < tmp.get_size(); idx++)
        {
            out << tmp[idx] << " ";
        }
        out << "\n";
    }
}

int main() 
{
    using num_t = double;
    using state_t = State<num_t>;

    // initial state
    std::array<num_t, 3> a = {0, 1, 0};
    state_t initial(a);

    // record data in data.txt
    std::ofstream out;
    out.open("data.txt");

    // using methods
    Euler<state_t> e = Euler<state_t>();
    Heun<state_t> h = Heun<state_t>();
    RungeKutta<state_t> r = RungeKutta<state_t>();
    //calculate<num_t>(e, initial, out, 40);
    //calculate<num_t>(h, initial, out, 40);
    calculate<num_t>(r, initial, out, 1000);
    return 0;
}

