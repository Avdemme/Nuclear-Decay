#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"
#include "float.h"

using namespace std;


double protons_initial = 100000;
double neutrons_initial = 0;
double protons_final = 0;
double neutrons_final = 0;
double del_p = 0;
double del_n = 0;
double deterium = 0;
double helium = 0;
double massP = 1.672621777e-27; //kg, free proton (H)
double massN = 1.674927471e-27; //also from Wikipedia
double massD = 3.344494397e-27; //from Google, rounded
double massHe = 6.644657230e-27; //Wikipedia in search

int main ( int argc, char** argv ) {
  double p_to_n = 0.1;
  double n_to_p = 0.6;
  double neutron_decay = 0.02;
  double n_to_d = 0.0075;
  double d_to_h = 0.5;
  double dt = 0.01;
  double time = 0.01;
  double temp = 0;

  

  std::remove( "time_and_temp.txt" );
  ofstream time_and_temp;

  std::remove( "time_and_protons.txt" );
  ofstream time_and_protons;

  std::remove( "time_and_neutrons.txt" );
  ofstream time_and_neutrons;

  std::remove( "time_and_deterium.txt" );
  ofstream time_and_deterium;

  std::remove( "time_and_helium.txt" );
  ofstream time_and_helium;

  std::remove( "time_and_pn_ratio.txt" );
  ofstream time_and_pn_ratio;

  std::remove( "time_and_total_pn.txt" );
  ofstream time_and_total_pn;

  std::remove( "time_and_hel_massfrac.txt" );
  ofstream time_and_hel_massfrac;

  std::remove( "time_and_hyd_massfrac.txt" );
  ofstream time_and_hyd_massfrac;

  
  while ( time < 300 ) {
    temp = 1e10 / sqrt ( time );
    if ( temp > 1000000000 ) {
      del_p = neutrons_initial*( n_to_p * dt ) - protons_initial * ( p_to_n * dt ) + neutrons_initial*(neutron_decay*dt) - neutrons_initial * ( n_to_d * dt ) ;
      del_n = protons_initial*(p_to_n * dt ) - neutrons_initial*(n_to_p * dt )  - neutrons_initial * ( neutron_decay*dt ) - neutrons_initial * ( n_to_d*dt );
      deterium += neutrons_initial*(n_to_d*dt);
      helium += deterium * (d_to_h *dt );
      deterium -= 2*deterium*(d_to_h *dt);
    }
    else {
    
     del_p = neutrons_initial * ( neutron_decay * dt ) - neutrons_initial * (n_to_d * dt );
     del_n = -neutrons_initial* ( neutron_decay * dt ) - neutrons_initial*( neutron_decay * dt );
     deterium += neutrons_initial * (n_to_d * dt);
     helium += deterium * ( d_to_h * dt );
     deterium -= 2*deterium*(d_to_h * dt);
    }
    protons_final = protons_initial + del_p;
    neutrons_final = neutrons_initial + del_n;
    
    if ( neutrons_final < 0 ) neutrons_final = 0 ;
    if ( protons_final < 0 ) protons_final = 0;
    if ( deterium < 0 ) deterium = 0;

    time_and_temp.open ("time_and_temp.txt", ios::app);
    time_and_temp << time << "\t" << temp << endl;
    time_and_temp.close();

    time_and_protons.open ("time_and_protons.txt", ios::app);
    time_and_protons << time << "\t" << protons_initial << endl;
    time_and_protons.close();
    
    time_and_neutrons.open ("time_and_neutrons.txt", ios::app);
    time_and_neutrons << time << "\t" << neutrons_initial << endl;
    time_and_neutrons.close();

    time_and_deterium.open ("time_and_deterium.txt", ios::app);
    time_and_deterium << time << "\t" << deterium << endl;
    time_and_deterium.close();
    
    time_and_helium.open ("time_and_helium.txt", ios::app);
    time_and_helium << time << "\t" << helium << endl;
    time_and_helium.close();
    
    time_and_pn_ratio.open ("time_and_pn_ratio.txt", ios::app);
    time_and_pn_ratio << time << "\t" << (protons_final)/(neutrons_final) << endl;
    time_and_pn_ratio.close();

   
    time_and_total_pn.open ("time_and_total_pn.txt", ios::app);
    time_and_total_pn << time << "\t" << 100000 << endl;
    time_and_total_pn.close();

    time_and_hel_massfrac.open ("time_and_hel_massfrac.txt", ios::app);
    time_and_hel_massfrac << time << "\t" << massHe*helium/(massD*deterium + massP*protons_final + massN*neutrons_final + massHe*helium) << endl;
    time_and_hel_massfrac.close();

    time_and_hyd_massfrac.open ("time_and_hyd_massfrac.txt", ios::app);
    time_and_hyd_massfrac << time << "\t" << massP*protons_final/(massD*deterium + massP*protons_final + massN*neutrons_final + massHe*helium) << endl;
    time_and_hyd_massfrac.close();

    //cout << time << "\t" << massP*protons_final/(massD*deterium + massP*protons_final + massN*neutrons_final + massHe*helium) << endl;

    protons_initial = protons_final;
    neutrons_initial = neutrons_final;
    time += dt;
  }
  return 0;
}
								  
    