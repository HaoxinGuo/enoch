#include <math.h>

#include "NLHinge.hpp"

NLHinge::NLHinge(Node **nodes, int nNodes,
		       double K1, double K2, double My) : Element(nodes, nNodes) {
  if(nNodes != 2) {
    // BORK!!
    cerr << "Non-linear hinge objects can only be associated w/ two nodes" << endl;
    exit(1);
  }
  
  for(int i = 0; i < nNodes; i++) {
    if(nodes[i]->nDoF != 3) {
      // BORK!!
      cerr << "Non-linear hinges must connect nodes w/ 3 DoFs!" << endl;
      exit(2);
    }
  }

  this->K1 = K1;
  this->K2 = K2;
  this->dPpos = this->dPneg = this->dPo = (My/K1);

  // sanity check
  if(nDoF != 6) {
    // BORK !!!
    cerr << "NLHinge really ought to have 6 DoFs" << endl;
    exit(1);
  }
  
  double dx = nodes[1]->Xo[0] - nodes[0]->Xo[0];
  double dy = nodes[1]->Xo[1] - nodes[0]->Xo[1];
  double L = sqrt(dx*dx + dy*dy);
  
  K[0][0] = K[1][1] = K[3][3] = K[4][4] = K[0][3]= K[3][0]= K[1][4]= K[4][1] = 1000000000;
  K[2][2] = K[5][5] =  K1;
  K[2][5] = K[5][2] = -K1;

  cerr << K[0][0] << endl;

  double cos = dx / L;
  double sin = dy / L;

  double** gamma = new double*[nDoF];
  for(int i = 0; i < nDoF; i++)
    gamma[i] = new double[nDoF];

  for(int i = 0; i < nDoF; i++)
    for(int j = 0; j < nDoF; j++)
      gamma[i][j] = 0.0;

  gamma[0][0] = gamma[1][1] = gamma[3][3] = gamma[4][4] = cos;
  gamma[0][1] = gamma[3][4] = sin;
  gamma[1][0] = gamma[4][3] = -1*sin;
  gamma[2][2] = gamma[5][5] = 1.0;

  for(int i = 0; i < nDoF; i++)
    for(int j = 0; j < nDoF; j++)
      Ko[i][j] = 0.0;


  // transform K into global coordinates
  // this is a double sum (j & k) on each matrix term (i & l)
  for(int i = 0; i < nDoF; i++)
    for(int j = 0; j < nDoF; j++)
      for(int k = 0; k < nDoF; k++)
	for(int l = 0; l < nDoF; l++)
	  Ko[i][l] += gamma[j][i]*K[j][k]*gamma[k][l];

  for(int i = 0; i < nDoF; i++) {
    for(int j = 0; j < nDoF; j++)
      cerr << Ko[i][j] << ", ";
    cerr << endl;
  }


  // Ko is now in global coordinates
  // copy it over to K
  for(int i = 0; i < nDoF; i++) {
    for(int j = 0; j < nDoF; j++) {
      K[i][j] = Ko[i][j];
    }
  }
  
}

int NLHinge::getElementK(double** K) {
  
  P = (nodes[0]->Xo[3] + nodes[0]->Xo[3])/2;
  
  if (P > (Po + dPpos)){
    if ((dPneg - (P - (Po + dPpos)) ) > dPo) {
      dPneg = dPneg - (P - (Po + dPpos));
    }else{
      dPneg = dPo;}
    dPpos = ((dPpos * K1) + ((P - (Po + dPpos)) * K2)) / K1;
    Po = P - dPpos;
    this->K[2][2] = this->K[5][5] =  K2;
    this->K[2][5] = this->K[5][2] = -K2;
  }else if(P < (Po - dPneg)){
    if ((dPpos - ((Po - dPneg) - P)) > dPo){
      dPpos = dPpos - ((Po - dPneg) - P) ;
    }else{
      dPpos = dPo;}
    dPneg = (((P - (Po - dPneg)) * K2) - (dPneg * K1))/K1;
    Po = P + dPneg;
    this->K[2][2] = this->K[5][5] =  K2;
    this->K[2][5] = this->K[5][2] = -K2;
  }else{
    this->K[2][2] = this->K[5][5] =  K1;
    this->K[2][5] = this->K[5][2] = -K1;
  }

  for(int i = 0; i < nDoF; i++)
    for(int j = 0; j < nDoF; j++)
      K[i][j] = this->K[i][j];

  return 0;
}


