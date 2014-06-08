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

//Project Files
#include "Red.h"

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
    
    //Accessors: setters

    //Operators

    //Public Methods

  //void print_rubik(void);
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
  //vector< vector<int> >* init_poblacion(int tam_pob);

    //Protected Attributes
  vector<vector<int> > Amigos;
  vector<vector<int> > Poblacion;
  int nb_usarios;
  int tam_pob;


};


//Getters' definitions

//Operators' definitions

//Inline functions' definition

#endif // __RED_H__
