#include <iostream>
#include <random>
#include <cmath>

class polargen
{
public:
    polargen() : rdev(), r_unif_dist(0.0, 1.0), hasStoredValue(false) { }

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
        } while(w > 1);

        double r = std::sqrt((-2.0 * log(w)) / w);

        hasStoredValue = true;
        storedValue = r * v2;

        return r * v1;
        
    }
private:
    std::random_device rdev;
    std::uniform_real_distribution<double> r_unif_dist;
    bool hasStoredValue;
    double storedValue;
};


int main(int argc, char **argv)
{

    return 0;
}