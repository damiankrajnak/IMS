#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "main.h"

using namespace std;

/*typedef struct {
    int x;
    int y;
} lattice;*/

typedef struct {
    double cell_concentration;
    bool occupied;

    int human_x;
    int human_y;
    int human_state;
    double human_conc;
    double human_tolerance;
    double human_threshold;
    double human_surface_contamination;
    double human_antibody;
} cell;

//glob premenna
vector<vector<cell>> lattice;

//koeficient ubytku virusu v tele za pomoci protilatok, BUDE SA MENIT
double rc = 1;

/*int calculateChange(int height, int width) {
    for (int x; x < height; x++) {
        for (int y; y < width; y++) {
            if (lattice[x][y].occupied == true) {
            }

        }
    }

}*/
double tolerance_distribution ()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    //static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution (0.0,10.0);
    return distribution(generator);
}

double threshold_distribution ()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    //static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution (0.0,8.0);
    return distribution(generator);
}


int start()
{
    srand(time(NULL));

    int height = 10;
    int width = 10;
    int num_of_humans = 5;
    int confirm = 1;

    int starting_infected = 1;
    int assigned_infected = 0;

    lattice.resize(height, vector<cell>(width));

    // nastavenie vsetkych buniek na nemajuce ludi
    for (int x = 0; x < height; x++){
        for (int y = 0; y < width; y++) {
            lattice[x][y].occupied = false;
            lattice[x][y].human_conc = 0;
            lattice[x][y].cell_concentration = 0;
            lattice[x][y].human_surface_contamination = 0;
            lattice[x][y].human_antibody = 0.1;
        }
    }

    //Random rozdelenie ludi do gridu
    for (int i = 1; i <= num_of_humans; i++){
        int x = rand() % height;
        int y = rand() % width;

        if (lattice[x][y].occupied == false)
        {
            lattice[x][y].occupied = true;
        } else {
            i--;
        }
    }

    //random priradenie tolerancie a thresholdu každemu človeku
    for (int x = 0; x < height; x++){
        for (int y = 0; y < width; y++) {
            if (lattice[x][y].occupied == true) {
                lattice[x][y].human_tolerance = tolerance_distribution() * pow(10, 4);
                lattice[x][y].human_threshold = threshold_distribution() * pow(10, 4);
                confirm++;
            }
        }
    }
    confirm = 1;

    //Vyber nahodne nakazenej osoby, zatial iba full infected so symptomami, mozno dorobit infikovaneho v inkubacnej dobe
    while (assigned_infected != starting_infected) {
        for (int x = 0; x < height; x++){
            for (int y = 0; y < width; y++) {
                if (lattice[x][y].occupied == true && assigned_infected != starting_infected && lattice[x][y].human_conc == 0) {
                  if ((rand() % 10 + 1) > 7) {
                    lattice[x][y].human_conc = lattice[x][y].human_threshold + 1;
                    assigned_infected++;
                  }
                }
            }
        }
    }

    //Reprodukcia virusu v tele
  /*  for (int x = 0; x < height; x++){
        for (int y = 0; y < width; y++) {
            if (lattice[x][y].occupied == true && lattice[x][y].human_conc > 0){
                //reprodukcia virusu v tele
                double rate = (3 * (1 + tanh(1 * (lattice[0][0].human_conc - lattice[0][0].human_threshold))));
                lattice[0][0].human_conc = lattice[0][0].human_conc * rate;

                //uvolnovanie virusu do priestoru
                double numerator = 2 * pow(10, -4) * pow(lattice[0][0].human_conc, 3);
                double denominator = 1 + 2 * pow(10, -4) * pow(lattice[0][0].human_conc, 3);
                double okolie = ((1/6.28) * (1 + numerator/denominator));
                lattice[0][0].cell_concentration += okolie;
                //Znizenie koncrentracie v tele vplyvom protilatok
                lattice[0][0].human_conc -= (rc * lattice[0][0].human_antibody);
                //Tvorba protilatok
                lattice[0][0].human_antibody += lattice[0][0].human_antibody * 0.005 * pow(10, 4); //Presna hodnota niekde medzi 0 - 0.01

            }
        }
    }*/

    //Kontaminacia bloku uvolnovanim virusu z tela
  /*  for (int x = 0; x < height; x++){
        for (int y = 0; y < width; y++) {
            if (lattice[x][y].occupied == true){
                double numerator = 2 * pow(10, -4) * pow(lattice[x][y].human_conc, 3);
                double denominator = 1 + 2 * pow(10, -4) * pow(lattice[x][y].human_conc, 3);
                lattice[x][y].cell_concentration += lattice[x][y].human_conc * ((1/6.28) * (1 + numerator/denominator));
            }
        }
    }*/

    lattice[5][5].human_conc = 0;
    lattice[5][5].human_threshold = 5;
    lattice[5][5].cell_concentration = 10;

    //cout << lattice[5][5].human_conc - lattice[5][5].human_threshold << endl;

        for (int i = 0; i < 30; i++){
          //  cout << lattice[5][5].cell_concentration << " ";
                //miera reprodukcie virusu v tele
                double rate = (3 * (1 + tanh(1 * (lattice[5][5].human_conc - lattice[5][5].human_threshold))));

                //bunka kontaminuje povrch tela
                lattice[5][5].human_surface_contamination += lattice[5][5].cell_concentration * 2.3;

                //povrch tela vypusta vorus do bunky
                lattice[5][5].cell_concentration += lattice[5][5].human_surface_contamination * 0.1;
               // cout << lattice[5][5].cell_concentration << " ";

            //Virus z povrchu tela sa dostava do organizmu
                lattice[5][5].human_conc += lattice[5][5].human_surface_contamination * 1.8;
                //cout << lattice[5][5].human_surface_contamination << endl;
            //uvolnovanie virusu do priestoru
                double numerator = (2 * pow(10, -4)) * (pow(lattice[5][5].human_conc, 3));
                double denominator = (1 + (2* pow(10, -4))) * (pow(lattice[5][5].human_conc, 3));

                double lol = numerator/denominator;

                //cout << numerator << " " << denominator << endl;

                lattice[5][5].cell_concentration += lattice[5][5].human_conc * ((1/6) * (1 + (numerator/denominator)));
                cout << lattice[5][5].cell_concentration <<endl;

                //reproduckia virusu v tele
                 lattice[5][5].human_conc += (lattice[5][5].human_conc * rate) / 2;

                //Znizenie koncrentracie v tele vplyvom protilatok
                lattice[5][5].human_conc += lattice[5][5].human_conc * rc * lattice[5][5].human_antibody;
                //Tvorba protilatok
                lattice[5][5].human_antibody += (lattice[5][5].human_antibody*0.005)/2; //Presna hodnota niekde medzi 0 - 0.01


        }







    //vypis hodnot
    for (int x = 0; x < height; x++){
        for (int y = 0; y < width; y++) {
            if (lattice[x][y].occupied == true){
                //cout << lattice[x][y].human_threshold << " " << lattice[x][y].human_tolerance << endl;
                //cout << lattice[x][y].human_conc << endl;
            }
        }
    }


    return 1;
}


int main() {
    start();
    return 0;
}
