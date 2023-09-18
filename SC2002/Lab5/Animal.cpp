#include <iostream> 
#include <string>
#include <vector>
#include "Animal.hpp"

using namespace std;

int main() {
    int userInput;
    bool userQuit = false;
    int numMammals = 3;
    Mammal *zooMammals[numMammals];
    Dog dog("Courage", Black, "Xuan Yi");
    Cat cat("Garfield", Brown, "Xuan Yi");
    Lion lion("Simba", White);
    int length  = 0;

    bool dogCreate = false, catCreate = false, lionCreate = false;

    do {
        std::cout << "Select the animal to send to Zoo:" << endl;
        std::cout << "1. Dog" << endl << "2. Cat" << endl << "3. Lion" << endl << "4. Move all Animals" << endl << "5. Quit" << endl;
        std::cin >> userInput;
        
        switch (userInput) {
            case 1:
                if (!dogCreate) {
                    zooMammals[length] = &dog;
                    length++;
                    dogCreate = true;
                }
                else {
                    cout << "Invalid!" << endl;
                }
                break;
            case 2:
                if (!catCreate) {
                    zooMammals[length] = &cat;
                    length++;
                    catCreate = true;
                }
                else {
                    cout << "Invalid!" << endl;
                }
                break;
            case 3:
                if (!lionCreate) {
                    zooMammals[length] = &lion;
                    length++;
                    lionCreate = true;
                }
                else {
                    cout << "Invalid!" << endl;
                }
                break;
            case 4:
                for (int i = 0; i < length; i += 1) {
                    zooMammals[i]->move();
                    zooMammals[i]->speak();
                    zooMammals[i]->eat();
                }
                break;
            case 5:
                userQuit = true;
                break;
            default:
                std::cout << "Invalid input" << endl;
        }
    } while (userQuit == false);
    
    
    // std::cout << "What is the name of the Animal? " << endl;
    // cin >> animalName;
    // std::cout << "What is the color of the Animal?" << endl << "1. Green" << endl << "2. Blue" << endl << "3. White" << endl << "4. Black" << endl << "5. Brown" << endl;
    // cin >> colorInput;

    

    // // Initialising an Animal Object
    // Animal animal(animalName, animalColor);

    // // Caliing the Method
    // animal.speak();

    // // Creating a Mammal Object
    // Mammal mammal(animalName, animalColor);
    // mammal.speak();

    // Creating a Dog Object
    // Dog courage(animalName, animalColor, "Xuan Yi");
    // courage.speak();
    // courage.move();

    // // Polymorpherism - Using the Animal Ptr as a Reference Type
    // Animal *animalPtr = new Dog("Lassie", White, "Andy");
    // animalPtr->speak();
    // animalPtr->move();

    // Dog dogi("Lassie", White, "Andy");
    // Mammal *aniPtr = &dogi;
    // Mammal &aniRef = dogi;
    // Mammal aniVal = dogi;

    // aniPtr->speak();
    // aniRef.speak();
    // aniVal.speak();

    // Deallocate Pointer
    // delete aniPtr;

    std::cout << "Program exiting .... " << endl;
    return 0; 
}