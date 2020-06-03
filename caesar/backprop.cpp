#include <iostream>
#include <vector>


//A good source for a start: (with some OO ranting)
//https://takinginitiative.wordpress.com/2008/04/23/basic-neural-network-tutorial-c-implementation-and-source-code/

/////////////////

class neural_net
{
public:
    neural_net(const std::vector<unsigned int>& topology = std::vector<unsigned int>());
    neural_net(const neural_net& other);
    neural_net(neural_net&& other);
    ~neural_net();

    neural_net& operator=(const neural_net& other);
    neural_net& operator=(neural_net&& other);

    std::vector<double> input() const;
    std::vector<double>::const_iterator input_begin() const; //Iterátorok arra az esetre, ha nincs szükségünk másolásra
    std::vector<double>::const_iterator input_end() const;
    void feed_input(const std::vector<double>& input);

    std::vector<double> output() const;
    std::vector<double>::const_iterator output_begin() const;
    std::vector<double>::const_iterator output_end() const;
    void back_propagate(const std::vector<double>& output);

private:
    /* Példa topológára: 3 4 3 2
       Értelmezés: 3+1 bemeneti neuron, egy rejtett réteg 4+1 neuronnal,
                   mégegy rejtett réteg 3+1 neuronnal, 2 kimeneti neuron
                   (a +1 neuronok az eltolósúly-értékekhez kellenek (bias))
    */
    std::vector<unsigned int> topology;

protected:
    /* Dolgozhatnánk nyers dinamikus tömbökkel is, de nem C-ben vagyunk, nem szükséges.
       (A teljesítményre nincs számottevő hatással, a közvetlen elérés miatt,
       ráadásul így nem kell memóriát kezelnünk) */
    typedef std::pair<double, std::vector<double>> neuron;
    typedef std::vector<neuron> layer;

    std::vector<layer> neurons;

    double neuron_value(int layer, int neuron) const;
    void set_neuron_value(int layer, int neuron, double value);

    double weight_value(int layer_from, int neuron_from, int neuron_to) const;
    void set_weight_value(int layer_from, int neuron_from, int neuron_to, double weight);
};

int main(int argc, char **argv)
{

    return 0;
}