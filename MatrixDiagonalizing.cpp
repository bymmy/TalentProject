#include <iostream>
#include <armadillo>
#include <fstream>
#include <iostream>
#include <math.h>

//using namespace arma;
//using namespace std;

int main(void)
{
   //declaring and creating (or erasing the content if already exists) the output file
   std::ofstream my_file("diago_out.dat", std::ios::out | std::ios::trunc); 
   
   if(my_file)
   {
       
    for (double g=-1;g<1;g+=.01)
    {
     //Definition of the matrices
     arma::Mat<double> Hamiltonian1;         //or on armadillo arma::mat : mat=Mat<double>
     Hamiltonian1.set_size(6,6);             //matrix size
     //Fill
     Hamiltonian1 << 2 - g   << -g / 2. << -g / 2. << -g / 2.  << -g / 2. << 0         << arma::endr 
		  << -g / 2. << 4 - g   << -g / 2. << -g / 2.  << 0.      << -g / 2.   << arma::endr 
  		  << -g / 2. << -g / 2. << 6 - g   << 0        << -g / 2. << -g / 2.   << arma::endr 
		  << -g / 2. << -g / 2. << 0       << 6 - g    << -g / 2. << -g / 2.   << arma::endr 
		  << -g / 2. << 0       << -g / 2. << -g / 2.  << 8 - g   << -g / 2.   << arma::endr 
		  << 0       << -g / 2. << -g / 2. << -g / 2.  << -g / 2. << 10 - g    << arma::endr; 

     arma::Mat<double> Hamiltonian2;
     Hamiltonian2.set_size(5,5);
     Hamiltonian2 << 2 - g   << -g / 2. << -g / 2.    << -g / 2. << -g / 2.  << arma::endr 
  		  << -g / 2. << 4 - g   << -g / 2.    << -g / 2. << 0.       << arma::endr 
		  << -g / 2. << -g / 2. << 6 - g      << 0       << -g / 2.  << arma::endr 
  		  << -g / 2. << -g / 2. << 0          << 6 - g   << -g / 2.  << arma::endr 
  		  << -g / 2. << 0       << -g / 2.    << -g / 2. << 8 - g    << arma::endr; 

     //Declare column vectors for eigen values
     arma::cx_vec eigval1;
     arma::cx_vec eigval2;

     //Compute and store the eigen values of Hamiltonian in the corresponding eigval column vector
     arma::eig_gen(eigval1, Hamiltonian1);
     arma::eig_gen(eigval2, Hamiltonian2);

     //Print results and write in the file
     //We only keep the groundstate energy (lowest eigenvalue)
     
     for(int aa=0; aa<Hamiltonian1.n_rows; aa++)
        {
	  std::cout << g << " " << real(eigval1.at(aa)) << std::endl;
	}
     //std::cout << g << " " << real(eigval1.at(0)) << " " << real(eigval2.at(0)) << std::endl;
     my_file   << g << " " << real(eigval1.at(0)) << " " << real(eigval2.at(0)) << std::endl;  
    }
  
   // Drawing with 
  
   my_file.close();
  }
  return 0;
}
