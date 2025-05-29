#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Team {
    string name;
    int played;
    int wins;
    int draws;
    int losses;
    int goals_for;
    int goals_against;
    int points;
    double strength;
};
//Function that calculates how many goals a team will score based on offensive and defensive strength
int generateGoals(int attackStrength, int defenseStrength) {
    int base = rand() % 4; // random number
    double modifier = (double)(attackStrength - defenseStrength) / 100.0;
    int goalEstimate = base + (modifier * 3); // Adjustment based on power difference

    if (goalEstimate < 0) goalEstimate = 0;
    if (goalEstimate > 5) goalEstimate = 5;

    return rand() % (goalEstimate + 1); // Goals between 0 and goalEstimate
}


// Update statistical groups
void updateStats(Team& home, Team& away, int goalsHome, int goalsAway) {
    home.played++;
    away.played++;

    home.goals_for += goalsHome;
    home.goals_against += goalsAway;

    away.goals_for += goalsAway;
    away.goals_against += goalsHome;

    if (goalsHome > goalsAway) {
        home.wins++;
        away.losses++;
        home.points += 3;
    } else if (goalsHome < goalsAway) {
        away.wins++;
        home.losses++;
        away.points += 3;
    } else {
        home.draws++;
        away.draws++;
        home.points += 1;
        away.points += 1;
    }
}

// Ranking of teams based on points and goal difference
void sortTeams(Team teams[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int diff_i = teams[i].goals_for - teams[i].goals_against;
            int diff_j = teams[j].goals_for - teams[j].goals_against;
            if (teams[j].points > teams[i].points ||
                (teams[j].points == teams[i].points && diff_j > diff_i)) {
                Team temp = teams[i];
                teams[i] = teams[j];
                teams[j] = temp;
            }
        }
    }
}

int main() {
    srand(time(0));

    const int teamCount = 14;
    Team teams[teamCount];

    string names[teamCount] = {
        "Panathinaikos", "Olympiakos", "AEK", "PAOK",
        "Aris", "OFI", "Asteras Tripolis", "Atromitos",
        "Volos", "Lamia", "Levadiakos", "Panserraikos",
        "Kallithea", "Panetolikos"
    };
    float strengthValues[teamCount] = {
    39.4, // Panathinaikos
    40, // Olympiakos
    39.4, // AEK
    39.8, // PAOK
    25, // Aris
    6, // OFI
    6, // Asteras
    6, // Atromitos
    4, // Volos
    4, // Lamia
    4, // Levadiakos
    4, // Panserraikos
    4, // Kallithea
    5  // Panetolikos
};

    // initializing names resetting statistics
    for (int i = 0; i < teamCount; ++i) {
        teams[i].name = names[i];
        teams[i].played = 0;
        teams[i].wins = 0;
        teams[i].draws = 0;
        teams[i].losses = 0;
        teams[i].goals_for = 0;
        teams[i].goals_against = 0;
        teams[i].points = 0;
        teams[i].strength = strengthValues[i];
    }

    // 2 rounds: each team plays each other twice (home-away)
    for (int i = 0; i < teamCount; ++i) {
        for (int j = i + 1; j < teamCount; ++j) {
            // First match (home for team i)
            int goalsHome1 = generateGoals(teams[i].strength, teams[j].strength);
            int goalsAway1 = generateGoals(teams[j].strength, teams[i].strength);
            updateStats(teams[i], teams[j], goalsHome1, goalsAway1);

            // Second match (home for team j)
            int goalsHome2 = generateGoals(teams[j].strength, teams[i].strength);
            int goalsAway2 = generateGoals(teams[i].strength, teams[j].strength);
            updateStats(teams[j], teams[i], goalsHome2, goalsAway2);
        }
    }


    sortTeams(teams, teamCount);

    // Show leaderboard
    cout << "Super League Table:\n";
    cout << "-----------------------------------------------------------------------------\n";
    cout << left << setw(18) << "Team"
         << right << setw(5) << "P"
         << setw(5) << "W"
         << setw(5) << "D"
         << setw(5) << "L"
         << setw(7) << "GF"
         << setw(7) << "GA"
         << setw(8) << "Points" << endl;
    cout << "-----------------------------------------------------------------------------\n";


    for (int i = 0; i < teamCount; ++i) {
    Team t = teams[i];
    cout << right << setw(2) << (i + 1) << ". "
         << left << setw(16) << t.name
         << right << setw(5) << t.played
         << setw(5) << t.wins
         << setw(5) << t.draws
         << setw(5) << t.losses
         << setw(7) << t.goals_for
         << setw(7) << t.goals_against
         << setw(8) << t.points << endl;
}
std::cout << "\nThe winner is: " << teams[0].name << " with " << teams[0].points << " points!" << std::endl;


    return 0;
}

