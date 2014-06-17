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
  nb_usarios = 4;
  int Graph[4][4] =  {{1,1,1,1},{1,1,1,0},{1,1,1,0},{1,0,0,1}};
  double edge = nb_usarios;
  double vertice;
  for(int i = 0; i<nb_usarios;i++)
    {
      vector<int> a;
      for(int j=0; j<nb_usarios;j++)
        {
          a.push_back((int)(i==j));
        }
      amigos.push_back(a);
    }
  
  ifstream fichier("my_red.txt", ios::in); 
  if(fichier)
    {
      string ligne;
      while(getline(fichier, ligne))
        {
          vertice ++;
          string ind_1 = ligne.substr(0,ligne.find(" "));
          int i1 = atoi(ind_1.c_str()); 
          
          string ind_2 = ligne.substr(ligne.find(" ")+1,ligne.size());
          int i2 = atoi(ind_2.c_str()); 
          
          amigos.at(i1).at(i2) = 1;
          amigos.at(i2).at(i1) = 1;
          
        }
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  
  int tam_pob = 10;
  cout <<"init_pob"<<endl;
  srand(time(NULL));
  for(int i = 0; i<tam_pob; i++)
    {
      vector<int> ind;
      for(int j = 0; j<4; j++)
        {
          ind.push_back(rand()%2);
        }
        poblacion.push_back(ind);
    }
  
/*
  for(int i = 0; i<10;i++)
    {
          for(int j=0; j<4;j++)
            {
              cout <<poblacion.at(i).at(j);
            }
          cout <<endl;
    }
  cout <<"Amigos "<<endl;
  for(int i = 0; i<4;i++)
    {
          for(int j=0; j<4;j++)
            {
              cout <<amigos.at(i).at(j);
            }
          cout <<endl;
    }

*/
}
//Destructor
Red::~Red(void)
{
}

//Public Methods
int Red::algo(){
  cout <<"algo:"<<endl;
  cout <<"fitness: ";
  for(int i=0;i<get_nb_usarios();i++){
    cout <<get_poblacion().at(1).at(i);
  }
  cout <<": "<< fitness(get_poblacion().at(1))<<endl;
  return 0;
}

//Protected Methods

/* Calculo de la fitness del individuo ind dado en parametro */
double Red::fitness(const vector<int>& ind){
  double fitness = 0;
  
  // set de los usarios amigos con un usario de ind
  int set[get_nb_usarios()];
  for(int i = 0; i<get_nb_usarios(); i++) set[i] = 0;
  for(int i = 0; i<get_nb_usarios(); i++){
    if(ind.at(i)==1){
      set[i]=1; //los usarios en ind son "hitted"

      //para cada usario, vemos si esta amigo con el usario i en ind.
      for(int j=0; j<get_nb_usarios(); j++){	
        if(get_amigos().at(j).at(i)==1) set[j]=1;
      }

    }
  }

  //suma de los usarios  "hitted"
  for(int i=0; i<get_nb_usarios(); i++) fitness += set[i];
  return fitness;
}




//Non inline accessors
