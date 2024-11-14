#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

// Simulate reading CO2 concentration from a sensor (range from 400 ppm to 1500 ppm)
int readCO2Sensor() {
    return rand() % 1101 + 400;  // CO2 concentration between 400 and 1500 ppm
}

// Function to send email alert (simulated, no actual email sending in this code)
void sendEmailAlert(int co2Concentration) {
    cout << "\033[1;31mALERT:\033[0m CO2 concentration is too high! (" 
         << co2Concentration << " ppm)" << endl;
    // You can add code here to actually send an email if needed (via an SMTP server, for example)
}

// Function to simulate fan control based on CO2 levels
void controlFan(bool& fanStatus, int co2Concentration, int CO2_THRESHOLD) {
    if (co2Concentration > CO2_THRESHOLD) {
        // CO2 level is too high, turn the fan ON if it's not already on
        if (!fanStatus) {
            cout << "Fan ON" << endl;
            fanStatus = true;
        }
        sendEmailAlert(co2Concentration);
    } else {
        // CO2 level is safe, turn the fan OFF if it's on
        if (fanStatus) {
            cout << "Fan OFF" << endl;
            fanStatus = false;
        }
    }
}

// Function to run the monitoring system for a set number of iterations
void runCO2Monitoring(int maxIterations, int CO2_THRESHOLD) {
    bool fanStatus = false;  // Fan starts OFF
    int iterationCount = 0;

    while (iterationCount < maxIterations) {
        // Simulate CO2 concentration from the sensor
        int co2Concentration = readCO2Sensor();

        // Display the simulated CO2 concentration
        cout << "CO2 Concentration: " << co2Concentration << " ppm" << endl;

        // Control the fan and send alerts based on CO2 levels
        controlFan(fanStatus, co2Concentration, CO2_THRESHOLD);

        // Wait for 1 second before checking again
        sleep(1);

        // Increment the iteration count
        iterationCount++;
    }

    cout << "\nSimulation complete. Exiting..." << endl;
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    const int CO2_THRESHOLD = 1000;  // Threshold for high CO2 concentration
    const int MAX_ITERATIONS = 10;   // Stop after 10 iterations

    // Start CO2 monitoring
    runCO2Monitoring(MAX_ITERATIONS, CO2_THRESHOLD);

    return 0;
}
