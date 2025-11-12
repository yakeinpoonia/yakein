// NTP_Client_Simulation.cpp

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace chrono;

// Helper function to get the current time in milliseconds since epoch
long long getCurrentTimeMs() {
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}

/**
 * @brief Simulates the NTP server's process: T2 (Receive) and T3 (Send).
 * In a real scenario, this would be a network call to a different machine.
 */
pair<long long, long long> simulateNtpServerResponse() {
    // Simulate initial network delay
    this_thread::sleep_for(milliseconds(30)); 
    long long server_t2 = getCurrentTimeMs(); // T2: Time server received request
    
    // Simulate server processing time
    this_thread::sleep_for(milliseconds(10)); 
    long long server_t3 = getCurrentTimeMs(); // T3: Time server sent response
    
    return {server_t2, server_t3};
}

void ntpClientSimulation() {
    cout << "## NTP Client Synchronization Simulation" << endl;
    cout << "---------------------------------------" << endl;

    // 1. Client sends request (T1)
    long long t1_client_send = getCurrentTimeMs();
    cout << "1. Client Sends Request (T1): " << t1_client_send << " ms" << endl;
    
    // 2. Server processes and responds (T2, T3)
    pair<long long, long long> server_times = simulateNtpServerResponse();
    long long t2_server_receive = server_times.first;
    long long t3_server_send = server_times.second;
    
    // 3. Client receives response (T4)
    // Simulate return network delay
    this_thread::sleep_for(milliseconds(25)); 
    long long t4_client_receive = getCurrentTimeMs();
    cout << "2. Server Receives (T2):      " << t2_server_receive << " ms" << endl;
    cout << "3. Server Sends (T3):         " << t3_server_send << " ms" << endl;
    cout << "4. Client Receives (T4):      " << t4_client_receive << " ms" << endl;

    // --- Calculation ---
    
    // Round-Trip Delay (d): d = (T4 - T1) - (T3 - T2)
    long double delay = (t4_client_receive - t1_client_send) - (t3_server_send - t2_server_receive);

    // Clock Offset (theta): theta = ((T2 - T1) + (T3 - T4)) / 2
    long double offset = ((t2_server_receive - t1_client_send) + (t3_server_send - t4_client_receive)) / 2.0;

    // --- Results ---
    cout << fixed << setprecision(2);
    cout << "\nCalculated Delay (Latency): " << delay << " ms" << endl;
    cout << "**Calculated Clock Offset:** " << offset << " ms" << endl;

    long long local_clock_offset = (long long)round(offset);
    cout << "\nClient adjusts its clock by: **" << local_clock_offset << " ms**" << endl;
}

int main() {
    ntpClientSimulation();
    return 0;
}