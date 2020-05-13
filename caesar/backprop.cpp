#include <iostream>
#include <vector>


//A good source for a start: (with some OO ranting)
//https://takinginitiative.wordpress.com/2008/04/23/basic-neural-network-tutorial-c-implementation-and-source-code/

/////////////////

class neural_net
{
public:
    neural_net(std::vector<unsigned int> const& topology);
    neural_net(neural_net& other);
    neural_net(neural_net&& other);
    ~neural_net();

    neural_net& operator=(neural_net& other);
    neural_net& operator=(neural_net&& other);

    std::vector<double>& feed_forward(std::vector<double> const& input);
    std::vector<double>& back_propagate(std::vector<double> const& output);
    std::vector<float> output() const; //a range specified by input iterators would work well as a return type

private:

    std::vector<layer> layers;
};

int main(int argc, char **argv)
{

}