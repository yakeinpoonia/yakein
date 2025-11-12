#include <bits/stdc++.h>
using namespace std;

class BullyElection {
    vector<int> processes;
    int coordinator;
public:
    BullyElection(vector<int> p) {
        processes = p;
        coordinator = *max_element(processes.begin(), processes.end());
    }

    void displayProcesses() {
        cout << "Active processes: ";
        for (int p : processes) cout << p << " ";
        cout << "\nCurrent coordinator: " << coordinator << "\n\n";
    }

    void fail(int id) {
        cout << "Process " << id << " has failed.\n";
        processes.erase(remove(processes.begin(), processes.end(), id), processes.end());
        if (id == coordinator)
            cout << "Coordinator " << id << " failed. Election will start.\n";
        cout << endl;
    }

    void startElection(int initiator) {
        cout << "Election initiated by Process " << initiator << "...\n";
        int newCoordinator = initiator;

        for (int p : processes) {
            if (p > initiator) {
                cout << "Process " << initiator << " sends election message to Process " << p << "\n";
                cout << "Process " << p << " responds OK\n";
                newCoordinator = max(newCoordinator, p);
            }
        }

        coordinator = newCoordinator;
        cout << "New Coordinator is Process " << coordinator << "\n\n";
    }
};

int main() {
    vector<int> processes = {1, 2, 3, 4, 5};
    BullyElection bully(processes);

    bully.displayProcesses();
    bully.fail(5);
    bully.startElection(2);
    return 0;
}
