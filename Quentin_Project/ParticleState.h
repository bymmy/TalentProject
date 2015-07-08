//Author: fable

#include <vector>

class ParticleState
{
 protected :
 
 vector<double> fstate;
 
 private :
 
 public : 
 
 ParticleState();
 
 void Convoluate(*vector<double> other_state);
 
 Print();
 
 virtual ~ParticleState();
 
  
//  ClassDef();
};
