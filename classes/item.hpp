#include <string>

class Item
{
private:
    float weight;
    int cost;
    std::string name;
    int quantity;
public:
    //constructor
    Item();

    //getters
    std::string getName();
    float getSingleWeight();
    int getSingleCost();
    int getQuantity();

    // setters
    void setName(std::string name);
    void setSingleWeight(float weight);
    void setSingleCost(int cost);
    void setQuantity(int quantity);

    // additional methods
    float calculateTotalWeight();
    int calculateTotalValue();

};