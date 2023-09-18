#ifndef HEADER_FILE_NAME_H
#define HEADER_FILE_NAME_H

#include <iostream> 
#include <string>

using namespace std;

enum COLOR { Green, Blue, White, Black, Brown };

class Animal {
    public :
        // Default Constructor
        Animal() : _name("unknown") {
            cout << "constructing Animal object " << _name << endl;
        } 
        // Parameterised Constructor
        Animal(string n, COLOR c) {
            _name = n;
            _color = c;
            cout << "Constructing an Animal Object " << _name << " of color " << colorToString(_color) << " using the Paramterised Constructor" <<endl;
        }
        
        virtual ~Animal() {
            cout << "destructing Animal object " << _name << endl; 
        }

        // virtual keyword is used to create virtual functions in a base class. A virtual function is a function that is declared in a base class and is intended to be overridden by a derived class.

        // A pure function is a member function of a class that does not modify the state of the object and does not have any side effects. 
        // A pure function is defined using the const keyword at the end of the function signature.

        // =0 specifier indicates that the function has no implementation in the base class and must be overridden in any derived classes.
        

        string colorToString(COLOR c) {
            switch(c) {
                case Green:
                    return "Green";
                case Blue:
                    return "Blue";
                case White:
                    return "White";
                case Black:
                    return "Black";
                case Brown:
                    return "Brown";
                default:
                    return "Unknown";
            }
        }
    
    protected:
        // Attributes
        string _name;
        COLOR _color ;

};

// Mammal Subclass
class Mammal: public Animal {
    public:
        // Default Constructor
        Mammal() {
            cout << "constructing unknown Mammal object" << endl;
        }

        // Subclass Constructor that uses the Base Class Constructor
        Mammal(string mammalName, COLOR mammalColor): Animal(mammalName, mammalColor) {
            // _name and _color cannot be assessed since the attributes are private, not protected.
            cout << "Constructing Mammal Object " << _name << " of color " << colorToString(_color) << endl;
        }

        // Destructor for Mammal
        ~Mammal(){
            cout << "Destructing Mammal Object " << _name << endl;
        }

        // const keyword is used to indicate that a method or function will not modify the object or variable it is called on
        virtual void move() const = 0;
        virtual void speak() const = 0;
        virtual void eat() const = 0;
       
        // void eat() const override = 0;

        // // Override move
        // void move() const override = 0;

        // void speak() const override = 0;

};

// Dog Subclass
class Dog: public Mammal {
    public:
        // Constructor of Dog that makes use of Mammal
        Dog(string dogName, COLOR dogColor, string dogOwner): Mammal(dogName, dogColor), _dogOwner(dogOwner) {
            cout << "Constructing a Dog Object " << _name << " of color " << colorToString(_color) << " whose dog owner is "<< _dogOwner << endl;
        }

        Dog(const char* dogName, COLOR dogColor, const char* dogOwner): Mammal(dogName, dogColor), _dogOwner(dogOwner) {
            cout << "Constructing a Dog Object " << _name << " of color " << colorToString(_color) << " whose dog owner is "<< _dogOwner << endl;
        }

        // Destructor
        ~Dog() {
            cout << "Destructing " << colorToString(_color) << " Dog Object " << _name << " belonging to " << _dogOwner << endl;
        }
    
        // Override Speak
        void speak() const override {
            cout << "WOOF!!!" << endl;
        }

        // Override move
        void move() const override {
            cout << "Dog moves!!" << endl;
        }

        // Override eat
        void eat() const override {
            cout << "Dog eat!!" << endl;
        }


    // Specialised Attributes
    protected:
        string _dogOwner;
};

// Cat Subclass
class Cat: public Mammal {
    public:
        Cat(string catName, COLOR catColor, string catOwner): Mammal(catName, catColor), _catOwner(catOwner) {
                cout << "Constructing a Cat Object " << _name << " of color " << colorToString(_color) << " whose owner is "<< _catOwner << endl;
        }

        Cat(const char* catName, COLOR catColor, const char* catOwner): Mammal(catName, catColor), _catOwner(catOwner) {
                cout << "Constructing a Cat Object " << _name << " of color " << colorToString(_color) << " whose owner is "<< _catOwner << endl;
        }

        ~Cat() {
            cout << "Destructing " << colorToString(_color) << " Cat Object " << _name << " belonging to " << _catOwner << endl;
        }

        // Override Speak
        void speak() const override {
            cout << "Cat meow!!!" << endl;
        }

        // Override move
        void move() const override {
            cout << "Cat moves!!" << endl;
        }

        // Override eat
        void eat() const override {
            cout << "Cat eat!!" << endl;
        }

    protected:
        string _catOwner;
};

// Cat Subclass
class Lion: public Mammal {
    public:
        Lion(string lionName, COLOR lionColor): Mammal(lionName, lionColor) {
                cout << "Constructing a Lion Object " << _name << " of color " << colorToString(_color) << endl;
        }

        Lion(const char* lionName, COLOR lionColor): Mammal(lionName, lionColor) {
                cout << "Constructing a Lion Object " << _name << " of color " << colorToString(_color) << endl;
        }

        ~Lion() {
            cout << "Destructing " << colorToString(_color) << " Lion Object " << _name << endl;
        }

        // Override Speak
        void speak() const override {
            cout << "Lion roar!!!" << endl;
        }

        // Override move
        void move() const override {
            cout << "Lion moves!!" << endl;
        }

        // Override eat
        void eat() const override {
            cout << "Lion eat!!" << endl;
        }
};

#endif
