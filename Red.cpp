//Red

//Libraries
#include <fstream>

//Project Files
#include "Red.h"


using namespace std;
//####  Class Red  ########

//Definition of static attributes

//Constructors

Red::Red(void)
{
  int nb_usarios = 4;
  int Graph[4][4] =  {{1,1,1,1},{1,1,1,0},{1,1,1,0},{1,0,0,1}};
  vector< vector<int> > Amigos;
  for(int i = 0; i<nb_usarios;i++)
    {
      vector<int> a;
      for(int j=0; j<nb_usarios;j++)
        {
          a.push_back((int)(i==j));
        }
      Amigos.push_back(a);
    }
  
  ifstream fichier("my_red.txt", ios::in); 
  if(fichier)
    {
      string ligne;
      while(getline(fichier, ligne))
        {
          string ind_1 = ligne.substr(0,ligne.find(" "));
          int i1 = atoi(ind_1.c_str()); 
          
          string ind_2 = ligne.substr(ligne.find(" ")+1,ligne.size());
          int i2 = atoi(ind_2.c_str()); 
          
          Amigos.at(i1).at(i2) = 1;
          Amigos.at(i2).at(i1) = 1;
          
        }
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  
  int tam_pob = 10;
  cout <<"init_pob"<<endl;
  srand(time(NULL));
  vector< vector<int> > Poblacion;
  for(int i = 0; i<tam_pob; i++)
    {
      vector<int> ind;
      for(int j = 0; j<4; j++)
        {
          ind.push_back(rand()%2);
        }
        Poblacion.push_back(ind);
    }
  
  for(int i = 0; i<10;i++)
    {
          for(int j=0; j<4;j++)
            {
              cout <<Poblacion.at(i).at(j);
            }
          cout <<endl;
    }

}

//Destructor
Red::~Red(void)
{
}

//Public Methods
/*void Rubik::print_rubik(void)
{

}*/


//Protected Methods


//Non inline accessors
