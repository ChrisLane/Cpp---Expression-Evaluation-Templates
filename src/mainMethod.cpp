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

int main(int argc, const char *argv[])
{
  operators<int> intopsA = { addInt, 0 };
  operators<int> intopsM = { multInt, 1 };
  operators<float> floatopsA = { addFloat, 0 };
  operators<float> floatopsM = { multFloat, 1 };

  //test add int 30+12 + 2 = 44
  ExpList<int> *l = nullptr;
  l = new ExpList<int>(new Constant<int>(30), l);
  l = new ExpList<int>(new Constant<int>(12), l);
  l = new ExpList<int>(new Constant<int>(2), l);
  Exp<int> *e1 = new OpApp<int>(intopsA, l);
  if (e1->eval(nullptr)==44)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;


  //test mult int 30 * 12 * 2 = 720
  Exp<int> *e2 = new OpApp<int>(intopsM, l);
  if (e2->eval(nullptr)==720)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;
  //test add and mult int (30+12 + 2)*2*3 = 264
  l = nullptr;
  l = new ExpList<int>(e1, l);
  l = new ExpList<int>(new Constant<int>(2), l);
  l = new ExpList<int>(new Constant<int>(3), l);
  e2 = new OpApp<int>(intopsM, l);
  if (e2->eval(nullptr)==264)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;

  //test add float 30.2+12.3 + 2.5 = 45
  double epsilon = 0.001;
  ExpList<float> *lf = nullptr;
  lf = new ExpList<float>(new Constant<float>(30.2), lf);
  lf = new ExpList<float>(new Constant<float>(12.3), lf);
  lf = new ExpList<float>(new Constant<float>(2.5), lf);
  Exp<float> *e3 = new OpApp<float>(floatopsA, lf);
  if (std::abs(e3->eval(nullptr)-45)<epsilon)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;

  //test mult int 30.2*12.3 * 2.5  = 928.65
  Exp<float> *e4 = new OpApp<float>(floatopsM, lf);
  if (std::abs(e4->eval(nullptr)-928.65)<epsilon)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;

  //test add and mult int (30.2+12.3 + 2.5)*2.1*3.5 = 330.75
  lf = nullptr;
  lf = new ExpList<float>(e3, lf);
  lf = new ExpList<float>(new Constant<float>(2.1), lf);
  lf = new ExpList<float>(new Constant<float>(3.5), lf);
  e4 = new OpApp<float>(floatopsM, lf);
  if (std::abs(e4->eval(nullptr)-330.75)<epsilon)
	  cout << "Yes!" << endl;
  else
	  cout << "No!" << endl;

}