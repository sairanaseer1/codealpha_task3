#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

struct Poll {
    string title;
    vector<string> options;
    map<int, int> voteCount;         // option index → vote count
    map<string, bool> hasVoted;      // username → voted or not
    time_point<steady_clock> endTime;
};

int main() {
    Poll poll;

    int numOptions, durationMinutes;

    cout << "Enter poll title: ";
    getline(cin, poll.title);

    cout << "Enter number of options: ";
    cin >> numOptions;
    cin.ignore();

    poll.options.resize(numOptions);
    for (int i = 0; i < numOptions; ++i) {
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, poll.options[i]);
        poll.voteCount[i] = 0;
    }

    cout << "Enter poll duration in minutes: ";
    cin >> durationMinutes;

    // Set end time
    poll.endTime = steady_clock::now() + minutes(durationMinutes);

    cout << "\n--- Poll Started ---\n";
    cout << "Title: " << poll.title << endl;

    while (steady_clock::now() < poll.endTime) {
        string username;
        int choice;

        cout << "\nEnter your name to vote (or type 'exit' to stop early): ";
        cin >> username;

        if (username == "exit") break;

        if (poll.hasVoted[username]) {
            cout << "You have already voted!\n";
            continue;
        }

        // Show options
        cout << "Options:\n";
        for (int i = 0; i < numOptions; ++i) {
            cout << i << ": " << poll.options[i] << endl;
        }

        cout << "Enter option number to vote: ";
        cin >> choice;

        if (choice < 0 || choice >= numOptions) {
            cout << "Invalid option number.\n";
            continue;
        }

        // Register vote
        poll.voteCount[choice]++;
        poll.hasVoted[username] = true;

        cout << "Vote casted for: " << poll.options[choice] << "\n";
    }

    cout << "\n--- Poll Ended ---\n";

    // Determine the winner
    int maxVotes = -1, winnerIndex = -1;
    for (int i = 0; i < numOptions; ++i) {
        if (poll.voteCount[i] > maxVotes) {
            maxVotes = poll.voteCount[i];
            winnerIndex = i;
        }
    }

    cout << "Winning Option: " << poll.options[winnerIndex] << " with " << maxVotes << " votes.\n";

    return 0;
}
