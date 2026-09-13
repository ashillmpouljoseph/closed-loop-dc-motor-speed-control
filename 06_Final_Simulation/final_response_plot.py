import pandas as pd
import matplotlib.pyplot as plt

# Load final simulation data
data = pd.read_csv("06_Final_Simulation/final_motor_data.csv")

# Create graph
plt.figure(figsize=(9, 5))

plt.plot(
    data["Time"],
    data["ActualSpeed"],
    label="Actual Motor Speed"
)

plt.plot(
    data["Time"],
    data["MeasuredSpeed"],
    label="Encoder Measured Speed"
)

plt.plot(
    data["Time"],
    data["Setpoint"],
    linestyle="--",
    label="Desired Speed"
)

plt.title("Closed-Loop PID Motor Speed Control")
plt.xlabel("Time (s)")
plt.ylabel("Motor Speed (rad/s)")

plt.legend()
plt.grid(True)
plt.tight_layout()

# Save graph
plt.savefig(
    "06_Final_Simulation/final_response.png",
    dpi=300
)

plt.show()