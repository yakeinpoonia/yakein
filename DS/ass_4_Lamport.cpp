// Lamports_Clock_Simulation.cpp

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Represents a process in the distributed system
class Process {
private:
    int id;
    int logical_clock;

public:
    Process(int process_id) : id(process_id), logical_clock(0) {}

    // Rule 1: Internal event (C_i = C_i + 1)
    void internalEvent(const string& event_name) {
        logical_clock++;
        cout << "[P" << id << "] Internal Event: " << event_name << " (Clock: " << logical_clock << ")" << endl;
    }

    // Rule 2a: Send message (C_i = C_i + 1; send C_i)
    int sendMessage() {
        logical_clock++; // Increment before sending
        cout << "[P" << id << "] **sends** message." << " (Time Sent: " << logical_clock << ")" << endl;
        return logical_clock;
    }

    // Rule 2b: Receive message (C_j = max(C_j, t); C_j = C_j + 1)
    void receiveMessage(int received_time, int sender_id) {
        // C_j = max(C_j, t)
        int old_clock = logical_clock;
        logical_clock = max(logical_clock, received_time);
        
        // C_j = C_j + 1
        logical_clock++; 

        cout << "[P" << id << "] **receives** from P" << sender_id 
             << " (Local T: " << old_clock << ", Received T: " << received_time << ") -> **New Clock: " 
             << logical_clock << "**" << endl;
    }
};

void lamportClockSimulation() {
    cout << "## Lamport's Logical Clock Simulation" << endl;
    cout << "------------------------------------" << endl;

    // Initialize three processes
    Process P1(1);
    Process P2(2);
    Process P3(3);

    // Initial Events
    P1.internalEvent("A"); // Clock P1: 1
    P2.internalEvent("D"); // Clock P2: 1

    // --- Communication 1: P1 -> P2 ---
    cout << "\n--- P1 sends to P2 ---" << endl;
    int time_p1_to_p2 = P1.sendMessage(); // Clock P1: 2
    P2.receiveMessage(time_p1_to_p2, 1);  // Clock P2: max(1, 2) + 1 = 3

    // Further internal event on P3
    P3.internalEvent("G"); // Clock P3: 1

    // --- Communication 2: P2 -> P3 ---
    cout << "\n--- P2 sends to P3 ---" << endl;
    int time_p2_to_p3 = P2.sendMessage(); // Clock P2: 4
    P3.receiveMessage(time_p2_to_p3, 2);  // Clock P3: max(1, 4) + 1 = 5

    // P1's next internal event
    cout << "\n--- Internal Event P1 ---" << endl;
    P1.internalEvent("C"); // Clock P1: 3
}

int main() {
    lamportClockSimulation();
    return 0;
}