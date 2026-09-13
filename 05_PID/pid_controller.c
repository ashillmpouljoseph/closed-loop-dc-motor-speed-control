#include <stdio.h>

/*
 * PID Controller Simulation
 *
 * Goal:
 * Control motor speed to reach a desired speed.
 *
 * PID:
 *     P = Proportional
 *     I = Integral
 *     D = Derivative
 *
 * Error:
 *     error = setpoint - actual_speed
 *
 * PID output:
 *     output = Kp*error + Ki*integral + Kd*derivative
 */

int main(void)
{
    /* Desired motor speed */
    double setpoint = 50.0;       // rad/s

    /* Initial motor speed */
    double actual_speed = 0.0;

    /* PID gains */
    double Kp = 2.0;
    double Ki = 2.0;
    double Kd = 0.1;

    /* Simulation settings */
    double dt = 0.1;              // Time step (s)
    double simulation_time = 5.0; // Total simulation time (s)

    /* PID variables */
    double error = 0.0;
    double previous_error = 0.0;
    double integral = 0.0;
    double derivative = 0.0;
    double control_output = 0.0;

    /* Create CSV file */
    FILE *file = fopen("05_PID/pid_data.csv", "w");

    if (file == NULL)
    {
        printf("Error: Could not create pid_data.csv\n");
        return 1;
    }

    /* CSV header */
    fprintf(file, "Time,ActualSpeed,Error,PIDOutput\n");

    printf("Basic PID Controller Simulation\n");
    printf("===============================\n");

    printf("Desired Speed : %.2f rad/s\n\n", setpoint);

    printf("Time(s)\tActual Speed\tError\tPID Output\n");
    printf("---------------------------------------------\n");

    /* PID simulation */
    for (double time = 0.0;
         time <= simulation_time;
         time += dt)
    {
        /* Calculate error */
        error = setpoint - actual_speed;

        /* Integral term */
        integral += error * dt;

        /* Derivative term */
        derivative =
            (error - previous_error) / dt;

        /* PID controller */
        control_output =
            Kp * error
            + Ki * integral
            + Kd * derivative;

        /* Limit controller output */
        if (control_output > 100.0)
        {
            control_output = 100.0;
        }

        if (control_output < 0.0)
        {
            control_output = 0.0;
        }

        /*
         * Simple motor response model.
         *
         * The motor speed moves toward
         * the PID controller output.
         */
        actual_speed +=
            (control_output - actual_speed) * 0.1;

        /* Save current error */
        previous_error = error;

        /* Display results */
        printf("%.1f\t%.2f\t\t%.2f\t%.2f\n",
               time,
               actual_speed,
               error,
               control_output);

        /* Save results to CSV */
        fprintf(file,
                "%.2f,%.6f,%.6f,%.6f\n",
                time,
                actual_speed,
                error,
                control_output);
    }

    /* Close CSV file */
    fclose(file);

    printf("\nPID simulation completed successfully.\n");
    printf("Data saved to: 05_PID/pid_data.csv\n");

    return 0;
}