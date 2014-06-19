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
  
  // parametros para el calculo de la densidad
  double edge = nb_usarios;
  double vertice;

  // generacion de amigos.
  amigos = new vector< vector<int>* >;
  for(int i = 0; i<nb_usarios;i++)
    {
      vector<int>* a = new vector<int>;
      for(int j=0; j<nb_usarios;j++)
        {
          a->push_back((int)(i==j));
        }
      amigos->push_back(a);
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
          
          amigos->at(i1)->at(i2) = 1;
          amigos->at(i2)->at(i1) = 1;
          
        }
      fichier.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  
  densidad  = 2*edge/float(vertice*(vertice-1));
  cout <<"densidad: "<<densidad<<endl;


  poblacion = new vector< vector<int>* >;
  tam_pob = 10;
  srand(time(NULL));
  for(int i = 0; i<tam_pob; i++)
    {
      vector<int>* ind = new vector<int>;
      for(int j = 0; j<4; j++)
        {
          ind->push_back(rand()%2);
        }
        poblacion->push_back(ind);
    }
  
  // visualisacion de poblacion y amigos
  for(int i = 0; i<10;i++)
    {
          cout <<i<<": ";
          for(int j=0; j<4;j++)
            {
              cout <<poblacion->at(i)->at(j);
            }
          cout <<endl;
    }
/* 
 cout <<"Amigos "<<endl;
  for(int i = 0; i<4;i++)
    {
          for(int j=0; j<4;j++)
            {
              cout <<amigos->at(i)->at(j);
            }
          cout <<endl;
    }

*/
}
//Destructor
Red::~Red(void)
{
  for(int i=0; i<get_nb_usarios(); i++)
    delete amigos->at(i);
  delete amigos;

  for(int i=0; i<get_tam_pob();i++)
    delete poblacion->at(i);
  delete poblacion;
}

//Public Methods
int Red::algo()
{
  cout <<"algo:"<<endl;

  /* // test fitness
  cout <<"fitness: ";
  for(int i=0;i<get_nb_usarios();i++){
    cout <<get_poblacion().at(1).at(i);
  }
  cout <<": "<< fitness(get_poblacion().at(1))<<endl;
  */

  cout <<"seleccion:"<<endl;
  vector<int>* sel = seleccion();
  for(int i=0; i<sel->size(); i++)
    cout <<sel->at(i)<<" ";
  cout <<endl;

  cout <<"recombinacion:"<<endl;
  vector< vector<int>* >* hijos = recombinacion(sel->at(0),sel->at(1));
  for(int i=0; i<hijos->size(); i++){
    for(int j=0; j<get_nb_usarios(); j++){
      cout <<hijos->at(i)->at(j);
    }
    cout <<endl;
  }

  cout <<"mutacion:"<<endl;
  vector<int>* hijo_m = mutacion(sel->at(0));
  for(int i=0; i<hijo_m->size(); i++)
    cout <<hijo_m->at(i);
  cout <<endl;

  delete sel;
  return 1;
}

//Protected Methods

/* Calculo de la fitness del individuo ind dado en parametro */
double Red::fitness(const vector<int>* ind){
  double fitness = 0;
  
  // set de los usarios amigos con un usario de ind
  int set[get_nb_usarios()];
  int tam_ind = 0;
  for(int i = 0; i<get_nb_usarios(); i++){
    set[i] = 0;
    tam_ind += ind->at(i);
  }

  if(tam_ind != 0){
    for(int i = 0; i<get_nb_usarios(); i++){
      if(ind->at(i)==1){
        set[i]=1; //los usarios en ind son "hitted"

        //para cada usario, vemos si esta amigo con el usario i en ind.
        for(int j=0; j<get_nb_usarios(); j++){	
          if(get_amigos()->at(j)->at(i)==1)
            set[j]=1;
        }

      }
    }

    //suma de los usarios  "hitted" y de los en ind
    int hitted = 0;
    for(int i=0; i<get_nb_usarios(); i++){
      hitted += set[i];
    }

    int a=1; //modificar segun densidad
   fitness = hitted/pow(float(tam_ind),a);
  }//endif  
  //cout <<"f:"<<fitness<<" ";
  return fitness;
}

/* Este metodo vuelve los indexos de los individuos seleccionados
*/
vector<int>* Red::seleccion( void )
{
  //tabla de proporcion (ruleta)
  double fi[get_tam_pob()];
  double sum_fit = 0;
  for(int i=0; i<get_tam_pob(); i++){
    fi[i] = fitness(get_poblacion()->at(i));
    sum_fit += fi[i];
  }
  //cout <<endl;
  for(int i=0; i<get_tam_pob(); i++){
    fi[i] = fi[i]/sum_fit;
    if(i>0) fi[i] += fi[i-1];
    //cout <<i<<":"<<fi[i]<<" ";
  }
  //cout <<endl;

  //seleccion
  vector<int>* seleccionados = new vector<int>;
  for(int i=0; i<get_tam_pob()/2; i++){
    double p = rand()/float(RAND_MAX);
    int ind=get_tam_pob()-1;
    while(ind !=0 && p<fi[ind-1])
      ind --;
    seleccionados->push_back(ind);
  
    //cout <<p<<":"<<ind<<endl;
  }

  return seleccionados;  
}

/* Vuelve un vector de dos hijos, que son la combinacion des los individuos seleccionados ind1 y ind2.
*/
vector< vector<int>*>* Red::recombinacion(const int ind1, const int ind2)
{
  // punto de recombinacion
  int r = rand()%(get_nb_usarios()-2) +1;
  //cout <<"r = "<<r<<endl;

  // creacion de los hijos
  vector<int>* hijo1 = new vector<int>;
  vector<int>* hijo2 = new vector<int>;
  for(int i=0; i<get_nb_usarios(); i++){
    if(i<=r){
      hijo1->push_back(get_poblacion()->at(ind1)->at(i));
      hijo2->push_back(get_poblacion()->at(ind2)->at(i));
    }
    else{
      hijo1->push_back(get_poblacion()->at(ind2)->at(i));
      hijo2->push_back(get_poblacion()->at(ind1)->at(i));
    }
  }
  vector< vector<int>* >* hijos = new vector< vector<int>* >;
  hijos->push_back(hijo1);
  hijos->push_back(hijo2);

  return hijos;  
}

/* Operator de mutacion, vuelve un hijo
*/
vector<int>* Red::mutacion(const int ind)
{
  //punto de mutacion
  int r = rand()%get_nb_usarios();
  cout <<"r_m: "<<r<<endl;

  vector<int>* hijo = new vector<int>;
  for(int i=0; i<get_nb_usarios(); i++){
    if(i!=r)
      hijo->push_back(get_poblacion()->at(ind)->at(i));
    else
      hijo->push_back(1 - get_poblacion()->at(ind)->at(i));
  }

  return hijo;
}

//Non inline accessors
