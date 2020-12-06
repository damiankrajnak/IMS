#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "simpleca.h"

using namespace std;

typedef struct {
    int population;
    int state;
    int sus;
    int next_state;

} cell;
//glob premenna
vector<vector<cell>> lattice;
int height = 5;
int width = 5;
int starting_infected = 1;

int start()
{
    int sus_again = 5;
    double p_infect = 0;
    double p_recover = 0;
    double p = 1;
    double q = 0.0;
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

    for (int t = 0; t < 100; t++) {
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {

                if (lattice[x][y].state == SUSCEPTIBLE && lattice[x][y].next_state == SUSCEPTIBLE) {
                    lattice[x][y].next_state = SUSCEPTIBLE;
                }

                //cout << "TIME " << t << " " << lattice[x][y].state << " " << x << " " << y <<endl;
                if (lattice[x][y].state == INFECTED) {
                    if ((double) rand() / RAND_MAX < q) {
                        lattice[x][y].next_state = RECOVERED;
                    } else {

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1 && y < width - 1) {
                            if (lattice[x + 1][y + 1].state == SUSCEPTIBLE) {
                                lattice[x + 1][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x + 1][y + 1].next_state = SUSCEPTIBLE;
                            }
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && y < width - 1) {
                            if (lattice[x][y + 1].state == SUSCEPTIBLE) {
                                lattice[x][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x][y + 1].next_state = SUSCEPTIBLE;
                            }
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0 && y < width - 1) {
                            if (lattice[x - 1][y + 1].state == SUSCEPTIBLE) {
                                lattice[x - 1][y + 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x - 1][y + 1].next_state = SUSCEPTIBLE;
                            }
                        }


                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0) {
                            if (lattice[x - 1][y].state == SUSCEPTIBLE) {
                                lattice[x - 1][y].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x - 1][y].next_state = SUSCEPTIBLE;
                            }
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x > 0 && y > 0) {
                            if (lattice[x - 1][y - 1].state == SUSCEPTIBLE) {
                                lattice[x - 1][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x - 1][y - 1].next_state = SUSCEPTIBLE;
                            }
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && y > 0) {
                            if (lattice[x][y - 1].state == SUSCEPTIBLE) {
                                lattice[x][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            }
                        } else {
                            lattice[x][y - 1].next_state = SUSCEPTIBLE;
                        }


                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1 & y > 0) {
                            if (lattice[x + 1][y - 1].state == SUSCEPTIBLE) {
                                lattice[x + 1][y - 1].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x + 1][y - 1].next_state = SUSCEPTIBLE;
                            }
                        }

                        if (((double) rand() / RAND_MAX < (1 - pow((1 - p), 9))) && x < height - 1) {
                            if (lattice[x + 1][y].state == SUSCEPTIBLE) {
                                lattice[x + 1][y].next_state = INFECTED;
                                lattice[x][y].next_state = INFECTED;
                            } else {
                                lattice[x + 1][y].next_state = SUSCEPTIBLE;
                            }
                        }
                    }
                }

                if (lattice[x][y].state == RECOVERED) {
                    if (lattice[x][y].sus <= sus_again) {
                        lattice[x][y].sus++;
                    }
                    else if (lattice[x][y].sus > sus_again) {
                        lattice[x][y].next_state = SUSCEPTIBLE;
                    }
                }
            }
        }

        cout << num_susceptible << " ";
        cout << num_infected << " ";
        cout << num_recovered << endl;

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
            lattice[x][y].population = 100;
            lattice[x][y].state = SUSCEPTIBLE;
            lattice[x][y].next_state = SUSCEPTIBLE;
        }
    }
    //vyber nahodne vybranej infikovanej populacie
    for (int i = 0; i < starting_infected; i++) {
        int x = rand() % height;
        int y = rand() % width;
        lattice[x][y].state = INFECTED;
        lattice[x][y].next_state = INFECTED;
    }
}

int main() {
    srand(time(NULL));
    set_lattice();
    start();
    return 0;
}
