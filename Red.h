//Red.h


#ifndef __RED_H__
#define __RED_H__

//Libraries
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <math.h>

//Project Files
//#include "Red.h"

// Class declarations

using namespace std;

class Red
{
//Friend Class

 public :
    //Enums
    
    //Constructors
  Red(void);
    
    //Destructor
  virtual ~Red(void);

    //Accessors: getters
  inline const vector< vector<int>* >* get_poblacion( void ) const;
  inline const vector< vector<int>* >* get_amigos( void ) const;
  inline const int get_nb_usarios( void) const;
  inline const int get_tam_pob( void) const;
    //Accessors: setters

    //Operators

    //Public Methods

  int algo(void);
  //vector<Cubitos*>* give_face(int i);

    //Public Attributes

  protected :

    //Forbidden Constructors

    /*  Red( void )
    {
      printf( "%s:%d: error: call to forbidden constructor.\n", __FILE__, __LINE__ );
      exit( EXIT_FAILURE );
    };
  
    
    Red( const Red &model )    {
      printf( "%s:%d: error: call to forbidden constructor.\n", __FILE__, __LINE__ );
      exit( EXIT_FAILURE );
    };
    **/

    //Protected Methods
  double fitness(const vector<int>* ind);
  vector<int>* seleccion();
  vector< vector<int>* >* recombinacion(const int ind1, const int ind2);
  vector<int>* mutacion(const int ind);

    //Protected Attributes
  vector<vector<int>* >* amigos;
  vector<vector<int>* >* poblacion;
  int nb_usarios;
  int tam_pob;
  double densidad;


};


//Getters' definitions
inline const vector< vector<int>* >* Red::get_poblacion( void ) const
{
  return poblacion;
}

inline const vector< vector<int>* >* Red::get_amigos( void ) const
{
  return amigos;
}

inline const int Red::get_nb_usarios( void) const
{
  return nb_usarios;
}

inline const int Red::get_tam_pob( void) const
{
  return tam_pob;
}
//Operators' definitions

//Inline functions' definition

#endif // __RED_H__
