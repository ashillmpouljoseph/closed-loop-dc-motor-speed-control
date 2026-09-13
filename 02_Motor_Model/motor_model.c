#include <stdio.h>

/*
 * DC Motor Mathematical Model
 *
 * Electrical equation:
 *     V = L(di/dt) + R*i + Kb*w
 *
 * Mechanical equation:
 *     J(dw/dt) = Kt*i - b*w
 *
 * Where:
 *     V  = armature voltage (V)
 *     i  = armature current (A)
 *     w  = motor speed (rad/s)
 *     R  = armature resistance (ohm)
 *     L  = armature inductance (H)
 *     Kb = back-EMF constant
 *     Kt = torque constant
 *     J  = rotor inertia (kg.m^2)
 *     b  = viscous friction coefficient
 */

int main(void)
{
    /* Motor parameters */
    double R  = 1.0;       // Armature resistance (ohm)
    double L  = 0.5;       // Armature inductance (H)
    double Kb = 0.05;      // Back-EMF constant
    double Kt = 0.05;      // Torque constant
    double J  = 0.01;      // Rotor inertia (kg.m^2)
    double b  = 0.001;     // Viscous friction coefficient

    /* Supply voltage */
    double V = 12.0;

    /* Simulation settings */
    double dt = 0.001;     // Time step (s)
    double simulation_time = 2.0;

    /* Motor state variables */
    double current = 0.0;  // Armature current (A)
    double speed = 0.0;    // Angular speed (rad/s)

    /* Create CSV file */
    FILE *file = fopen("02_Motor_Model/motor_data.csv", "w");

    if (file == NULL)
    {
        printf("Error: Could not create motor_data.csv\n");
        return 1;
    }

    /* CSV header */
    fprintf(file, "Time,Current,Speed\n");

    printf("DC Motor Simulation\n");
    printf("==================\n");
    printf("Time(s)\tCurrent(A)\tSpeed(rad/s)\n");

    /* Numerical simulation using Euler method */
    for (double time = 0.0; time <= simulation_time; time += dt)
    {
        /* Electrical dynamics */
        double di_dt = (V - R * current - Kb * speed) / L;

        /* Mechanical dynamics */
        double dw_dt = (Kt * current - b * speed) / J;

        /* Update motor states */
        current += di_dt * dt;
        speed += dw_dt * dt;

        /* Save data to CSV file */
        fprintf(file, "%.4f,%.6f,%.6f\n",
                time, current, speed);

        /* Print every 0.1 seconds */
        if (((int)(time * 1000)) % 100 == 0)
        {
            printf("%.2f\t%.4f\t\t%.4f\n",
                   time, current, speed);
        }
    }

    /* Close CSV file */
    fclose(file);

    printf("\nSimulation completed successfully.\n");
    printf("Data saved to: 02_Motor_Model/motor_data.csv\n");

    return 0;
}