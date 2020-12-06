#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cctype>
#include <unistd.h>
#include "simpleca.h"

using namespace std;

typedef struct {
    int state;
    int sus;
    int next_state;

} cell;
//glob premenna
vector<vector<cell>> lattice;
int c;
int priemer[16];
int height = 61;
int width = 61;
int starting_infected = 10;
double mask = 0;
double distancing = 0;
double p = 0.016;

int start()
{

    int num_infected = starting_infected;
    int num_recovered = 0;
    int num_susceptible = height * width -num_infected;

    /*for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (lattice[x][y].state == INFECTED) {
                cout << "INFECTED" << endl;
            }
        }
        }*/

    for (int t = 0; t < 16; t++) {
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {

                /*if (lattice[x][y].state == SUSCEPTIBLE && lattice[x][y].next_state == SUSCEPTIBLE) {
                    lattice[x][y].next_state = SUSCEPTIBLE;
                }*/

               // cout << "TIME " << t << " " << lattice[x][y].state << " " << x << " " << y <<endl;

                if (lattice[x][y].state == INFECTED) {

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1 && y < width - 1) {
                            if (lattice[x + 1][y + 1].state == SUSCEPTIBLE) {
                                lattice[x + 1][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                            } else if ( x < height - 1 && y < width - 1 && lattice[x + 1][y + 1].state == SUSCEPTIBLE) {
                            lattice[x + 1][y + 1].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && y < width - 1) {
                            if (lattice[x][y + 1].state == SUSCEPTIBLE) {
                                lattice[x][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                            } else if (y < width - 1 && lattice[x][y + 1].state == SUSCEPTIBLE) {
                            lattice[x][y + 1].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0 && y < width - 1) {
                            if (lattice[x - 1][y + 1].state == SUSCEPTIBLE) {
                                lattice[x - 1][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                            } else if (x > 0 && y < width - 1 && lattice[x - 1][y + 1].state == SUSCEPTIBLE) {
                            lattice[x - 1][y + 1].next_state = SUSCEPTIBLE;
                        }


                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0) {
                            if (lattice[x - 1][y].state == SUSCEPTIBLE) {
                                lattice[x - 1][y].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                            } else if (x > 0 && lattice[x - 1][y].state == SUSCEPTIBLE){
                            lattice[x - 1][y].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0 && y > 0) {
                            if (lattice[x - 1][y - 1].state == SUSCEPTIBLE) {
                                lattice[x - 1][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                            } else if (x > 0 && y > 0 && lattice[x - 1][y - 1].state == SUSCEPTIBLE){
                            lattice[x - 1][y - 1].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && y > 0) {
                            if (lattice[x][y - 1].state == SUSCEPTIBLE) {
                                lattice[x][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                        } else if (y > 0 && lattice[x][y - 1].state == SUSCEPTIBLE){
                            lattice[x][y - 1].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1 & y > 0) {
                            if (lattice[x + 1][y - 1].state == SUSCEPTIBLE) {
                                lattice[x + 1][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                        } else if (x < height - 1 & y > 0 && lattice[x + 1][y - 1].state == SUSCEPTIBLE){
                            lattice[x + 1][y - 1].next_state = SUSCEPTIBLE;
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1) {
                            if (lattice[x + 1][y].state == SUSCEPTIBLE) {
                                lattice[x + 1][y].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                        } else if (x < height - 1 && lattice[x + 1][y].state == SUSCEPTIBLE){
                            lattice[x + 1][y].next_state = SUSCEPTIBLE;
                        }
                }
            }
        }

        /*cout << num_susceptible << " ";
        cout << num_infected << " ";
        cout << num_recovered << endl;*/

        priemer[t] += num_infected;

        num_infected = 0;
        num_recovered = 0;
        num_susceptible = 0;

        //aktualizacia state
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                lattice[x][y].state = lattice[x][y].next_state;
            }
        }

        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                if (lattice[x][y].state == INFECTED) {
                    num_infected++;
                }
                else if (lattice[x][y].state == SUSCEPTIBLE) {
                    num_susceptible++;
                }
                else if (lattice[x][y].state == RECOVERED) {
                    num_recovered++;
                }
            }
        }
    }
    return 1;
}

int set_lattice() {
    lattice.resize(height, vector<cell>(width));
    //nastevene buniek
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            lattice[x][y].state = SUSCEPTIBLE;
            lattice[x][y].next_state = SUSCEPTIBLE;
            lattice[x][y].sus = 0;
        }
    }
    //vyber nahodne vybranej infikovanej populacie
    for (int i = 0; i < starting_infected; i++) {
        int x = rand() % height;
        int y = rand() % width;
        lattice[x][y].state = INFECTED;
        lattice[x][y].next_state = INFECTED;
    }
    return 0;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    while ((c = getopt(argc, argv, "md")) != -1) {
        switch (c) {
            case 'm':
                mask = 0.0104;
                break;

            case 'd':
                distancing = 0.0144;
                break;

            default:
                fprintf(stderr, "Nespravny parameter\n");
                exit(1);
        }
    }

    if (mask != 0 && distancing == 0) {
        p = ((p*35)/100);
    }

    if (mask == 0 && distancing != 0) {
        p = (p * 10) / 100;
    }

    if (mask != 0 && distancing != 0){
        p = ((p*35)/100);
        p = (p*10)/100;
    }

    for (int i = 0; i < 10; i++) {
        set_lattice();
        start();
    }

    for (int i = 0; i < 16; i++) {
        priemer[i] = priemer[i]/10;
    }
        cout << "Data predstavuju celkovy pocet nakazenych v dany den" << endl;
        cout << "---------------- Results ----------------------" <<endl;
        cout << "Date           " << "Real Data    " << "Model Data" << endl;
        cout << " 5 February   " << "10            " << priemer[0] <<endl;
        cout << " 6 February   " << "20            " << priemer[1] <<endl;
        cout << " 7 February   " << "61            " << priemer[2]  <<endl;
        cout << " 8 February   " << "64            " << priemer[3]  <<endl;
        cout << " 9 February   " << "70            " << priemer[4]  <<endl;
        cout << "10 February   " << "135          " << priemer[5]  <<endl;
        cout << "12 February   " << "174          " << priemer[7]  <<endl;
        cout << "13 February   " << "218          " << priemer[8]  <<endl;
        cout << "15 February   " << "285          " << priemer[10]  <<endl;
        cout << "16 February   " << "355          " << priemer[11]  <<endl;
        cout << "17 February   " << "454          " << priemer[12]  <<endl;
        cout << "18 February   " << "542          " << priemer[13]  <<endl;
        cout << "19 February   " << "621          " << priemer[14]  <<endl;
        cout << "20 February   " << "634          " << priemer[15]  <<endl;
        cout << "----------------------------------------------" << endl;




    return 0;
}
