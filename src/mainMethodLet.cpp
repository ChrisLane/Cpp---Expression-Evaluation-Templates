#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

#include "templatesast.h" 

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

int addInt(int x, int y) { return x + y; }

int multInt(int x, int y) { return x * y; }

float addFloat(float x, float y) { return x + y; }

float multFloat(float x, float y) { return x * y; }

int main(int argc, const char *argv[]) {
    operators<int> intopsA = {addInt, 0};
    operators<int> intopsM = {multInt, 1};
    operators<float> floatopsA = {addFloat, 0};
    operators<float> floatopsM = {multFloat, 1};

    //test let bind one variable (int) (=x (* 15 2) (+ x 2)) = 32
    ExpList<int> *l = nullptr;
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    Exp<int> *e1 = new OpApp<int>(intopsA, l);
    l = nullptr;
    l = new ExpList<int>(new Constant<int>(15), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    Exp<int> *e2 = new Let<int>("x", new OpApp<int>(intopsM, l), e1);
    if (e2->eval(nullptr) == 32)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;

    //test let bind two variables (int) (= x 3 (= y 30 (+ x y))) = 33
    l = nullptr;
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Var<int>("y"), l);
    e1 = new OpApp<int>(intopsA, l);
    e1 = new Let<int>("y", new Constant<int>(30), e1);
    e2 = new Let<int>("x", new Constant<int>(3), e1);
    if (e2->eval(nullptr) == 33)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;

    //test let bind with one variable with multiple purposes (int) (= x (= x 30 (+ x 10)) (* 2 x)) = 80
    l = nullptr;
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Constant<int>(10), l);
    e1 = new OpApp<int>(intopsA, l);
    e1 = new Let<int>("x", new Constant<int>(30), e1);
    l = nullptr;
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e2 = new OpApp<int>(intopsM, l);
    e2 = new Let<int>("x", e1, e2);
    if (e2->eval(nullptr) == 80)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;


    double epsilon = 0.001;
    //test let bind one variable (float) (=x (* 15.2 2.1) (+ x 2.0)) = 32
    ExpList<float> *lf = nullptr;
    lf = new ExpList<float>(new Var<float>("x"), lf);
    lf = new ExpList<float>(new Constant<float>(2.0), lf);
    Exp<float> *e3 = new OpApp<float>(floatopsA, lf);
    lf = nullptr;
    lf = new ExpList<float>(new Constant<float>(15.2), lf);
    lf = new ExpList<float>(new Constant<float>(2.1), lf);
    Exp<float> *e4 = new Let<float>("x", new OpApp<float>(floatopsM, lf), e3);
    if (abs(e4->eval(nullptr) - 33.92) < epsilon)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;

    //test let bind two variables (float) (= x 3.5 (= y 30.5 (+ x y))) = 34
    lf = nullptr;
    lf = new ExpList<float>(new Var<float>("x"), lf);
    lf = new ExpList<float>(new Var<float>("y"), lf);
    e3 = new OpApp<float>(floatopsA, lf);
    e3 = new Let<float>("y", new Constant<float>(30.5), e3);
    e4 = new Let<float>("x", new Constant<float>(3.5), e3);
    if (abs(e4->eval(nullptr) - 34) < epsilon)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;

    //test let bind with one variable with multiple purposes (float) (= x (= x 30.5 (+ x 10.2)) (* 2.4 x)) = 80
    lf = nullptr;
    lf = new ExpList<float>(new Var<float>("x"), lf);
    lf = new ExpList<float>(new Constant<float>(10.2), lf);
    e3 = new OpApp<float>(floatopsA, lf);
    e3 = new Let<float>("x", new Constant<float>(30.5), e3);
    lf = nullptr;
    lf = new ExpList<float>(new Var<float>("x"), lf);
    lf = new ExpList<float>(new Constant<float>(2.4), lf);
    e4 = new OpApp<float>(floatopsM, lf);
    e4 = new Let<float>("x", e3, e4);
    if (abs(e4->eval(nullptr) - 97.68) < epsilon)
        cout << "Yes!" << endl;
    else
        cout << "No!" << endl;

}