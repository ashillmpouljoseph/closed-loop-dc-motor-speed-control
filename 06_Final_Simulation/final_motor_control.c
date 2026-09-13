#include <stdio.h>
#include <math.h>

/*
 * TI-Based Intelligent Motor Speed Control
 * -----------------------------------------
 *
 * FINAL CLOSED-LOOP SIMULATION
 *
 * Desired Speed
 *      ↓
 *     PID
 *      ↓
 * PWM Duty Cycle
 *      ↓
 * Average Motor Voltage
 *      ↓
 * DC Motor
 *      ↓
 * Motor Shaft
 *      ↓
 * Encoder
 *      ↓
 * Measured Speed
 *      ↓
 *     Feedback
 *
 * PID is updated only when a new encoder
 * speed measurement is available.
 */

int main(void)
{
    /* =====================================================
       DC MOTOR PARAMETERS
       ===================================================== */

    double R  = 1.0;
    double L  = 0.5;
    double Kb = 0.05;
    double Kt = 0.05;
    double J  = 0.01;
    double b  = 0.001;


    /* =====================================================
       POWER SUPPLY
       ===================================================== */

    double supply_voltage = 12.0;


    /* =====================================================
       ENCODER
       ===================================================== */

    int pulses_per_revolution = 100;

    double encoder_position = 0.0;

    long previous_pulse_count = 0;


    /* =====================================================
       PID PARAMETERS
       ===================================================== */

    double setpoint = 50.0;

    double Kp = 1.0;
    double Ki = 0.5;
    double Kd = 0.2;

    double error = 0.0;
    double previous_error = 0.0;

    double integral = 0.0;
    double derivative = 0.0;

    double control_output = 0.0;


    /* =====================================================
       SIMULATION SETTINGS
       ===================================================== */

    double dt = 0.001;
    double simulation_time = 10.0;

    double measurement_interval = 0.1;


    /* =====================================================
       MOTOR STATE
       ===================================================== */

    double current = 0.0;
    double speed = 0.0;


    /* =====================================================
       CONTROL VARIABLES
       ===================================================== */

    double duty_cycle = 0.0;
    double motor_voltage = 0.0;

    double measured_speed = 0.0;


    /* =====================================================
       CSV FILE
       ===================================================== */

    FILE *file =
        fopen("06_Final_Simulation/final_motor_data.csv", "w");

    if (file == NULL)
    {
        printf("Error: Could not create CSV file.\n");
        return 1;
    }

    fprintf(file,
            "Time,Setpoint,ActualSpeed,MeasuredSpeed,"
            "DutyCycle,MotorVoltage,Current,EncoderPulses\n");


    /* =====================================================
       HEADER
       ===================================================== */

    printf("TI-Based Intelligent Motor Speed Control\n");
    printf("=========================================\n");

    printf("Supply Voltage : %.2f V\n", supply_voltage);
    printf("Desired Speed  : %.2f rad/s\n", setpoint);
    printf("Encoder PPR    : %d\n", pulses_per_revolution);

    printf("\nPID Gains:\n");
    printf("Kp = %.2f\n", Kp);
    printf("Ki = %.2f\n", Ki);
    printf("Kd = %.2f\n\n", Kd);

    printf("Time(s)\tActual Speed\tMeasured Speed\tPWM(%%)\n");
    printf("----------------------------------------------------\n");


    /* =====================================================
       MAIN MOTOR SIMULATION
       ===================================================== */

    for (double time = 0.0;
         time <= simulation_time;
         time += dt)
    {

        /* -------------------------------------------------
           1. DC MOTOR MODEL
           ------------------------------------------------- */

        double di_dt =
            (motor_voltage
             - R * current
             - Kb * speed) / L;

        double dw_dt =
            (Kt * current
             - b * speed) / J;


        /* Update motor */

        current += di_dt * dt;

        speed += dw_dt * dt;


        /* -------------------------------------------------
           2. ENCODER PULSE GENERATION
           ------------------------------------------------- */

        double revolutions_per_second =
            speed / (2.0 * M_PI);

        encoder_position +=
            revolutions_per_second
            * pulses_per_revolution
            * dt;

        long pulse_count =
            (long)encoder_position;


        /* -------------------------------------------------
           3. ENCODER MEASUREMENT
           ------------------------------------------------- */

        /*
         * New speed measurement every 0.1 seconds.
         */

        if (((int)(time * 1000 + 0.5)) % 100 == 0)
        {

            long pulses =
                pulse_count - previous_pulse_count;


            /*
             * Convert encoder pulses to RPM.
             */

            double measured_rpm =
                (pulses /
                 (double)pulses_per_revolution)
                * (60.0 / measurement_interval);


            /*
             * Convert RPM to rad/s.
             */

            measured_speed =
                measured_rpm *
                (2.0 * M_PI / 60.0);


            previous_pulse_count =
                pulse_count;


            /* -------------------------------------------------
               4. PID CONTROLLER
               ------------------------------------------------- */

            error =
                setpoint - measured_speed;


            /*
             * Integral term
             */

            integral +=
                error * measurement_interval;


            /*
             * Integral limiting
             * (anti-windup)
             */

            if (integral > 100.0)
                integral = 100.0;

            if (integral < -100.0)
                integral = -100.0;


            /*
             * Derivative term
             */

            derivative =
                (error - previous_error)
                / measurement_interval;


            /*
             * PID output
             */

            control_output =
                Kp * error
                + Ki * integral
                + Kd * derivative;


            /*
             * Limit PWM output.
             */

            if (control_output > 100.0)
                control_output = 100.0;

            if (control_output < 0.0)
                control_output = 0.0;


            duty_cycle =
                control_output;


            /* -------------------------------------------------
               5. PWM → MOTOR VOLTAGE
               ------------------------------------------------- */

            motor_voltage =
                (duty_cycle / 100.0)
                * supply_voltage;


            /*
             * Store previous error.
             */

            previous_error =
                error;


            /* -------------------------------------------------
               6. DISPLAY
               ------------------------------------------------- */

            printf("%.2f\t%.2f\t\t%.2f\t\t%.2f\n",
                   time,
                   speed,
                   measured_speed,
                   duty_cycle);


            /* -------------------------------------------------
               7. SAVE DATA
               ------------------------------------------------- */

            fprintf(file,
                    "%.2f,%.6f,%.6f,%.6f,"
                    "%.6f,%.6f,%.6f,%ld\n",
                    time,
                    setpoint,
                    speed,
                    measured_speed,
                    duty_cycle,
                    motor_voltage,
                    current,
                    pulses);
        }
    }


    /* =====================================================
       FINISH
       ===================================================== */

    fclose(file);


    printf("\n=========================================\n");
    printf("Final Simulation Completed Successfully.\n");
    printf("Data saved to:\n");
    printf("06_Final_Simulation/final_motor_data.csv\n");

    printf("\nFinal Motor Speed   : %.2f rad/s\n",
           speed);

    printf("Final Encoder Speed : %.2f rad/s\n",
           measured_speed);

    printf("Final PWM Duty Cycle: %.2f %%\n",
           duty_cycle);


    return 0;
}