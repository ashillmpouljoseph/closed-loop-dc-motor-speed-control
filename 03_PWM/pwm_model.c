#include <stdio.h>

/*
 * PWM Simulation
 *
 * PWM controls the average voltage applied to the motor.
 *
 * Average Voltage = Duty Cycle × Supply Voltage
 */

int main(void)
{
    /* Motor supply voltage */
    double supply_voltage = 12.0;

    /* Test different PWM duty cycles */
    double duty_cycles[] = {0, 25, 50, 75, 100};

    int number_of_values = 5;

    printf("PWM Motor Control Simulation\n");
    printf("============================\n");

    printf("Supply Voltage = %.1f V\n\n", supply_voltage);

    printf("Duty Cycle(%%)\tAverage Voltage(V)\n");
    printf("-----------------------------------\n");

    for (int i = 0; i < number_of_values; i++)
    {
        double duty = duty_cycles[i];

        /* Convert duty cycle into average voltage */
        double average_voltage =
            (duty / 100.0) * supply_voltage;

        printf("%.0f%%\t\t%.2f V\n",
               duty, average_voltage);
    }

    printf("\nPWM simulation completed successfully.\n");

    return 0;
}