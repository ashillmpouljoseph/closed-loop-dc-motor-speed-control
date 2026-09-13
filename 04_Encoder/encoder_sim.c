#include <stdio.h>
#include <math.h>

/*
 * DC Motor + Encoder Pulse Counting Simulation
 *
 * Motor speed produces shaft revolutions.
 * Shaft revolutions produce encoder pulses.
 * The controller counts those pulses and calculates RPM.
 */

int main(void)
{
    /* DC motor parameters */
    double R  = 1.0;
    double L  = 0.5;
    double Kb = 0.05;
    double Kt = 0.05;
    double J  = 0.01;
    double b  = 0.001;

    /* 50% PWM -> 6 V average */
    double voltage = 6.0;

    /* Encoder */
    int pulses_per_revolution = 100;

    /* Simulation */
    double dt = 0.001;
    double simulation_time = 2.0;

    /* Encoder measurement interval */
    double measurement_interval = 0.1;

    /* Motor state */
    double current = 0.0;
    double speed = 0.0;

    /* Encoder state */
    double encoder_position = 0.0;
    long previous_pulse_count = 0;

    printf("DC Motor + Encoder Pulse Simulation\n");
    printf("===================================\n");
    printf("Motor Voltage : %.2f V\n", voltage);
    printf("Encoder PPR   : %d\n", pulses_per_revolution);
    printf("\n");

    printf("Time(s)\tActual Speed\tEncoder Pulses\tMeasured RPM\n");
    printf("------------------------------------------------------\n");

    /* Motor simulation */
    for (double time = 0.0;
         time <= simulation_time;
         time += dt)
    {
        /* Electrical motor equation */
        double di_dt =
            (voltage - R * current - Kb * speed) / L;

        /* Mechanical motor equation */
        double dw_dt =
            (Kt * current - b * speed) / J;

        /* Update motor state */
        current += di_dt * dt;
        speed += dw_dt * dt;

        /* Convert angular speed to revolutions */
        double revolutions_per_second =
            speed / (2.0 * M_PI);

        /* Update encoder position */
        encoder_position +=
            revolutions_per_second *
            pulses_per_revolution *
            dt;

        /* Calculate encoder pulse count */
        long pulse_count =
            (long)encoder_position;

        /*
         * Every 0.1 seconds:
         * calculate RPM from counted pulses.
         */
        if (((int)(time * 1000 + 0.5)) % 100 == 0)
        {
            long pulses =
                pulse_count - previous_pulse_count;

            double measured_rpm =
                (pulses /
                 (double)pulses_per_revolution) *
                (60.0 / measurement_interval);

            printf("%.2f\t%.2f rad/s\t%ld\t\t%.2f RPM\n",
                   time,
                   speed,
                   pulses,
                   measured_rpm);

            previous_pulse_count = pulse_count;
        }
    }

    printf("\nSimulation completed successfully.\n");

    return 0;
}