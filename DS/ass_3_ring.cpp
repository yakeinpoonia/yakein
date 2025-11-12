#include <bits/stdc++.h>
using namespace std;

class RingElection {
    vector<int> processes;
    int coordinator;
public:
    RingElection(vector<int> p) {
        processes = p;
        coordinator = *max_element(processes.begin(), processes.end());
    }

    void displayProcesses() {
        cout << "Ring: ";
        for (int p : processes) cout << p << " ";
        cout << "\nCurrent coordinator: " << coordinator << "\n\n";
    }

    void fail(int id) {
        cout << "Process " << id << " has failed.\n";
        processes.erase(remove(processes.begin(), processes.end(), id), processes.end());
        cout << "Coordinator " << id << " failed. Election will start.\n\n";
    }

    void startElection(int initiator) {
        cout << "Election initiated by Process " << initiator << "...\n";
        vector<int> electionMsg;
        int idx = find(processes.begin(), processes.end(), initiator) - processes.begin();

        int n = processes.size();
        for (int i = 0; i < n; i++) {
            int curr = processes[(idx + i) % n];
            cout << "Process " << curr << " passes election message.\n";
            electionMsg.push_back(curr);
        }

        int newCoordinator = *max_element(electionMsg.begin(), electionMsg.end());
        coordinator = newCoordinator;
        cout << "\nProcess " << coordinator << " becomes new coordinator.\n";

        cout << "Coordinator message circulates the ring...\n";
        for (int i = 0; i < n; i++)
            cout << "Process " << processes[(idx + i) % n] << " acknowledges coordinator " << coordinator << "\n";
        cout << endl;
    }
};

int main() {
    vector<int> processes = {1, 2, 3, 4, 5};
    RingElection ring(processes);

    ring.displayProcesses();
    ring.fail(5);
    ring.startElection(2);
    return 0;
}
