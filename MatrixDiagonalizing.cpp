#include <iostream>
#include <armadillo>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace arma;
using namespace std;

int main(void)
{
   ofstream my_file;
   my_file.open("diago_out.dat");
   
  
   for (double g=-1;g<1;g+=.01)
   {
    mat Hamiltonian1;
    Hamiltonian1.set_size(6,6);
    Hamiltonian1 << 2 - g << -g / 2. << -g / 2. << -g / 2. << -g / 2. << 0  << endr 
		 << -g / 2. << 4 - g << -g / 2. << -g / 2. << 0. << -g / 2.  << endr 
		 << -g / 2. << -g / 2. << 6 - g << 0 << -g / 2. << -g / 2.   << endr 
		 << -g / 2. << -g / 2. << 0 << 6 - g << -g / 2. << -g / 2.   << endr 
		 << -g / 2. << 0 << -g / 2. << -g / 2. << 8 - g << -g / 2.   << endr 
		 << 0 << -g / 2. << -g / 2. << -g / 2. << -g / 2. << 10 - g  << endr; 

    mat Hamiltonian2;
    Hamiltonian2.set_size(5,5);
    Hamiltonian2 << 2 - g << -g / 2. << -g / 2. << -g / 2.    << -g / 2.  << endr 
  		 << -g / 2. << 4 - g << -g / 2. << -g / 2. << 0.  << endr 
		 << -g / 2. << -g / 2. << 6 - g << 0 << -g / 2.   << endr 
  		 << -g / 2. << -g / 2. << 0 << 6 - g << -g / 2.   << endr 
  		 << -g / 2. << 0 << -g / 2. << -g / 2. << 8 - g   << endr; 

  cx_vec eigval1;
  cx_vec eigval2;

  eig_gen(eigval1, Hamiltonian1);
  eig_gen(eigval2, Hamiltonian2);

  std::cout << g << " " << real(eigval1.at(0)) << " " << real(eigval2.at(0)) << std::endl;
  my_file   << g << " " << real(eigval1.at(0)) << " " << real(eigval2.at(0)) << std::endl;
  
  }
  
  my_file.close();
  
  return 0;
}
