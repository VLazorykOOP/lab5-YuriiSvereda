#include <iostream>
#include "Header1.h"

using namespace std;


/*Задача 1.13. Створити клас Pair (пара чисел); визначити методи зміни полів і вичисления твори чисел.
Визначити похідний клас Rectangle (прямокутник) з полями-сторонами.
Визначити методи обчислення периметра і площі прямокутника.
*/
class Pair
{
public:
    Pair() {
        a = 0;
        b = 0;
    }

    Pair(double a, double b) {
        this->a = a;
        this->b = b;
    }

    double multiplication() {
        return a * b;
    }

    void setA(double a) {
        if (a<DBL_MIN || a>DBL_MAX)
            cout << "Size A error";
        else
            this->a = a;
    }
    void setB(double b) {
        if (b<DBL_MIN || b>DBL_MAX)
            cout << "Size B error";
        else
            this->b = b;
    }

protected:
    double a, b;
};




class Rectangle :public Pair
{
public:
    Rectangle() :Pair() {};
    Rectangle(double a, double b) : Pair(a, b) {};


    double perimetr() {
        return (a + b) * 2;
    }

};


/*Задача 2.13. Використовуючи ієрархію й композицію класів, створити бінарне дерево.
У бінарного дерева є кореневий вузол. Ми можемо вставляти вузол.
Ми можемо обходити завширшки.

Реалізувати класи завдань 1.21-1.29, але замість успадкування композицію.*/


template<typename T>
class BinaryTree
{





public:
    BinaryTree();
    BinaryTree(T root);
    BinaryTree(const BinaryTree& other);

    void push_back(T data);

    T& operator[](T key)
    {
        Node* current = this->root;
        while (true)
        {
            if (key > current->data) {
                current = current->right;
            }
            else if (key < current->data) {
                current = current->left;
            }
            else
                return key;

        }
    }

    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }

private:
    class Node
    {
    public:

        Node(T data = T(), Node* right = nullptr, Node* left = nullptr)
        {
            this->data = data;
            this->right = right;
            this->left = left;
        }

        Node* right;
        Node* left;
        T data;
    };



    Node* copyNodes(Node* current) {
        if (current == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(current->data);
        newNode->left = copyNodes(current->left);
        newNode->right = copyNodes(current->right);

        return newNode;
    }

    void printInOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->data << " \n";
        printInOrder(node->right);
    }

    Node* root;
};

template<typename T>
BinaryTree<T>::BinaryTree() {
    this->root = nullptr;
}
template<typename T>
BinaryTree<T>::BinaryTree(T root) {
    this->root = new Node(root);
}
template<typename T>
void BinaryTree<T>::push_back(T data)
{
    if (this->root == nullptr) {
        root = new Node(data);
    }
    else {
        Node* current = this->root;
        while (true) {
            if (data < current->data) {
                if (current->left == nullptr) {
                    current->left = new Node(data);
                    break;
                }
                current = current->left;
            }
            else if (data > current->data) {
                if (current->right == nullptr) {
                    current->right = new Node(data);
                    break;
                }
                current = current->right;
            }
            else {
                cout << "\nERROR OF PUSHING:\n" << data << endl;
                break;
            }
        }
    }

}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    root = copyNodes(other.root);
}



/*Задача 3.13. Створити ієрархію класів крапка й кольорова крапка.
Перевизначити вивід у потік і введення з потоку, конструктор копіювання,
оператор присвоювання через відповідні функції базового класу.

Реалізувати класи завдань 1.21-1.29 з конструкторами копіювання, перенесення та операцій присвоєння та перенесення.*/

class Point
{
public:
    Point() {
        x = 0;
        y = 0;
    }
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
    }

    friend istream& operator>>(istream& input, Point& obj);
    friend ostream& operator<<(ostream& output, Point& obj);

protected:
    double x;
    double y;

};

istream& operator>>(istream& input, Point& obj) {
    input >> obj.x;
    input >> obj.y;
    return input;
}
ostream& operator<<(ostream& output, Point& obj) {
    output << "x: " << obj.x << '\t';
    output << "y: " << obj.y << endl;
    return output;
}

class ColorPoint : public Point
{
public:
    ColorPoint() : Point() {

        this->color = "white";
    }
    ColorPoint(double x, double y, string color) : Point(x, y) {
        this->color = color;
    }
    ColorPoint(const ColorPoint& other) :Point(other) {
        this->color = other.color;
    }

    friend istream& operator>>(istream& input, ColorPoint& obj);
    friend ostream& operator<<(ostream& output, ColorPoint& obj);
private:
    string color;
};

istream& operator>>(istream& input, ColorPoint& obj) {
    input >> obj.x;
    input >> obj.y;
    input >> obj.color;
    return input;
}
ostream& operator<<(ostream& output, ColorPoint& obj) {
    output << "x: " << obj.x << '\t';
    output << "y: " << obj.y << '\t';
    output << "color: " << obj.color << endl;
    return output;
}


void Task1()
{
    Rectangle a(4, 8);
    cout << "Perimetr of rectangle:\n" << a.perimetr() << endl;
    cout << "Square of rectangle:\n" << a.multiplication() << endl;
}

void Task2()
{
    WebSite root("I love Dashilya <33"), drainage("dry sink"), rand1, rand2, car("carpet");
    BinaryTree <WebSite> binary_web_tree(root);
    binary_web_tree.push_back(drainage);
    binary_web_tree.push_back(rand1);
    binary_web_tree.push_back(rand2);
    binary_web_tree.push_back(car);
    /*48 203 303 100*/

    WebSite::IP IP_key;
    short arr[] = { 48, 203, 303, 100 };
    IP_key.setIP(arr);
    WebSite key(IP_key);
    cout << rand1 << endl << binary_web_tree[key] << endl;


    BinaryTree<int> inttree(34);
    inttree.push_back(38);
    inttree.push_back(23);
    inttree.push_back(45);
    inttree.push_back(78);
    inttree.push_back(12);
    inttree.push_back(27);
    inttree.push_back(35);

    inttree.printInOrder();




}

void Task3()
{
    Point a(9.5, 18.11);
    ColorPoint b(9.08, 16.11, "yellow");
    cout << a;
    cout << b;

}

int main()
{
    int choise = 0;
    cout << "enter number:\n" << "1. Task1;\n" << "2. Task2;\n" << "3. Task3\n";
    cin >> choise;
    if (choise == 1) {
        Task1();
    }
    else if (choise == 2) {
        Task2();
    }
    else if (choise == 3) {
        Task3();
    }
    else
        cout << "incorect input";

    return 0;
}
































//// OOPLab5T.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
////
//
//
//#include <iostream>
//
//// Ваші файли загловки 
////
//#include "Lab5Exmaple.h"
//int main()
//{
//    std::cout << " Lab #5  !\n";
//    //  Код виконання завдань
//    //  Головне меню завдань
//    //  Функції та класи можуть знаходитись в інших файлах проекту
//
//    int chain = 1;
//    if (chain == 1) chain = mainExample1();
//    if (chain == 2) chain = mainExample2();
//    if (chain == 3) chain = mainExample3();
//    if (chain == 4) chain = mainExample4();
//    if (chain == 5) chain = mainExample5();
//
//}
