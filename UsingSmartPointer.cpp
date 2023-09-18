#include <iostream>

class Toy {

private:

    std::string name;

public:

    Toy(const std::string& inName) 
    {
        name = inName;
    }
    
    std::string getName() 
    {
        return name;
    }
    
    ~Toy() 
    {
        std::cout << "Toy " << name << " was dropped " << std::endl;
    }

};

class Dog
{
private:
    std::string name;
    int age;
    std::shared_ptr<Toy> lovelyToy;

public:

    Dog(std::string inName, int inAge) : name(inName)
    {
        if (inAge > 0 && inAge < 30)
            age = inAge;
        else age = 30;
        lovelyToy = nullptr;
    }

    Dog() : Dog("Beethoven", 1) {};
    Dog(std::string inName) : Dog(inName, 1) {};
    Dog(int inAge) : Dog("Beethoven", inAge) {};

    void getToy(std::shared_ptr<Toy> newToy)
    {
        if (newToy == lovelyToy)
        {
            std::cout << "I already have this toy!" << std::endl;
        }
        else if (newToy.use_count() == 3)
        {
            std::cout << newToy.use_count() << std::endl;
            std::cout << "Another dog is playing with this toy!" << std::endl;
        }
        else
        {
            lovelyToy = newToy;
            std::cout << name << " get" << lovelyToy->getName() << "!" << std::endl;
        }
    }

    void dropToy()
    {
        if (lovelyToy == nullptr)
        {
            std::cout << "Nothing to drop!" << std::endl;
        }
        else
        {
            std::cout << name << " drop" << lovelyToy->getName() << "!" << std::endl;
            lovelyToy.reset();
        }
    }
};

int main()
{
    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> bone = std::make_shared<Toy>("Bone");

    std::shared_ptr<Dog> b = std::make_shared<Dog>();
    std::shared_ptr<Dog> k = std::make_shared<Dog>("Korgi");
    b->getToy(ball);
    k->getToy(ball);
    b->dropToy();

}


