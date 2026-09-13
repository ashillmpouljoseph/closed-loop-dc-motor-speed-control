#include <stdio.h>

/*
 * PWM-Based DC Motor Simulation
 *
 * PWM Duty Cycle
 *       ↓
 * Average Motor Voltage
 *       ↓
 * DC Motor
 *       ↓
 * Current + Speed
 */

int main(void)
{
    /* Motor parameters */
    double R  = 1.0;       // Resistance (ohm)
    double L  = 0.5;       // Inductance (H)
    double Kb = 0.05;      // Back-EMF constant
    double Kt = 0.05;      // Torque constant
    double J  = 0.01;      // Rotor inertia
    double b  = 0.001;     // Friction coefficient

    /* PWM settings */
    double supply_voltage = 12.0;
    double duty_cycle = 100.0;     // 50% PWM

    /* Convert PWM duty cycle to average voltage */
    double V = (duty_cycle / 100.0) * supply_voltage;

    /* Simulation settings */
    double dt = 0.001;
    double simulation_time = 2.0;

    /* Motor states */
    double current = 0.0;
    double speed = 0.0;

    printf("PWM-Based DC Motor Simulation\n");
    printf("=============================\n");

    printf("Supply Voltage : %.1f V\n", supply_voltage);
    printf("PWM Duty Cycle : %.1f %%\n", duty_cycle);
    printf("Average Voltage: %.2f V\n\n", V);

    printf("Time(s)\tCurrent(A)\tSpeed(rad/s)\n");

    /* Motor simulation */
    for (double time = 0.0; time <= simulation_time; time += dt)
    {
        /* Electrical equation */
        double di_dt =
            (V - R * current - Kb * speed) / L;

        /* Mechanical equation */
        double dw_dt =
            (Kt * current - b * speed) / J;

        /* Update motor states */
        current += di_dt * dt;
        speed += dw_dt * dt;

        /* Display every 0.1 seconds */
        if (((int)(time * 1000 + 0.5)) % 100 == 0)
        {
            printf("%.2f\t%.4f\t\t%.4f\n",
                   time, current, speed);
        }
    }

    printf("\nSimulation completed successfully.\n");

    return 0;
}