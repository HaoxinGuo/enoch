#ifndef NLHINGE
#define NLHINGE

#include "util/structure.hpp"

class NLHingeNonLin: public Element {
public:
  NLHingeNonLin (Node **nodes, int nNodes, double K1, double K2, double My);
  int getElementK(double** K);
  bool isLinear();

protected:
  double K1, K2, dP, Po, P;
};

#endif


