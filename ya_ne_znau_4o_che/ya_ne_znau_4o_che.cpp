#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class Equation {
public:
    virtual double* roots() const = 0;
    virtual ~Equation() = default;
};

class LinearEquation : public Equation {
private:
    double a;
    double b;

public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    double* roots() const override {
        if (a == 0) {
            if (b == 0) {
                throw runtime_error("Безліч розв'язків");
            }
            else {
                throw runtime_error("Немає розв'язків");
            }
        }
        double* root = new double[1];
        root[0] = -b / a;
        return root;
    }
};

class QuadraticEquation : public Equation {
private:
    double a;
    double b;
    double c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {
        if (a == 0) {
            throw invalid_argument("Квадратне рівняння має a != 0");
        }
    }

    double* roots() const override {
        double discriminant = b * b - 4 * a * c;
        double* root = nullptr;

        if (discriminant > 0) {
            root = new double[2];
            root[0] = (-b + sqrt(discriminant)) / (2 * a);
            root[1] = (-b - sqrt(discriminant)) / (2 * a);
        }
        else if (discriminant == 0) {
            root = new double[1];
            root[0] = -b / (2 * a);
        }
        else {
            return nullptr;
        }

        return root;
    }
};

int main() {
    try {
        LinearEquation linear(2, -4);
        double* linearRoot = linear.roots();
        cout << "Корінь лінійного рівняння: " << linearRoot[0] << endl;
        delete[] linearRoot;

        QuadraticEquation quadratic(1, -3, 2);
        double* quadraticRoots = quadratic.roots();
        if (quadraticRoots == nullptr) {
            cout << "Немає дійсних коренів квадратного рівняння." << endl;
        }
        else {
            cout << "Корені квадратного рівняння: ";
            if (sqrt(quadraticRoots[0]) == quadraticRoots[0]) {
                cout << quadraticRoots[0] << endl;
            }
            else {
                cout << quadraticRoots[0] << " " << quadraticRoots[1] << endl;
            }
            delete[] quadraticRoots;
        }
    }
    catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }

    return 0;
}
