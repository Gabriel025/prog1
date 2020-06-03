#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

class polargen
{
public:
    polargen()
        : rdev(std::chrono::system_clock::now().time_since_epoch().count()),
        r_unif_dist(-1.0, 1.0), hasStoredValue(false) { }

    polargen(uint_fast32_t seed)
        : rdev(seed), r_unif_dist(-1.0, 1.0), hasStoredValue(false) { }

    double next()
    {
        if(hasStoredValue)
        {
            hasStoredValue = false;
            return storedValue;
        }

        double v1, v2, w;

        do
        {
            v1 = r_unif_dist(rdev);
            v2 = r_unif_dist(rdev);
            w = v1 * v1 + v2 * v2;
        } while(w > 1);

        double r = std::sqrt(-2.0 * std::log(w) / w);

        hasStoredValue = true;
        storedValue = r * v2;

        return r * v1;
        
    }
private:
    std::default_random_engine rdev;
    std::uniform_real_distribution<double> r_unif_dist;
    bool hasStoredValue;
    double storedValue;
};


int main(int argc, char **argv)
{
    polargen p;

    for(int i = 0; i < 10; i++) std::cout<<p.next()<<' ';

    return 0;
}