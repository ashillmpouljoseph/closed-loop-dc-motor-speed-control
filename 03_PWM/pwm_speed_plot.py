import matplotlib.pyplot as plt

# PWM duty cycle values
duty_cycle = [25, 50, 75, 100]

# Motor speed at 1.90 seconds
speed = [18.5727, 37.1455, 55.7182, 74.2909]

# Create graph
plt.figure(figsize=(8, 5))

plt.plot(duty_cycle, speed, marker='o')

plt.title("PWM Duty Cycle vs Motor Speed")
plt.xlabel("PWM Duty Cycle (%)")
plt.ylabel("Motor Speed (rad/s)")

plt.grid(True)
plt.tight_layout()

# Save graph
plt.savefig("03_PWM/pwm_speed_response.png", dpi=300)

# Display graph
plt.show()