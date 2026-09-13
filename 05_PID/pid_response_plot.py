import pandas as pd
import matplotlib.pyplot as plt

# Load PID simulation data
data = pd.read_csv("05_PID/pid_data.csv")

# Create graph
plt.figure(figsize=(8, 5))

plt.plot(data["Time"], data["ActualSpeed"], label="Actual Speed")
plt.axhline(
    y=50,
    linestyle="--",
    label="Desired Speed"
)

plt.title("PID Controller Speed Response")
plt.xlabel("Time (s)")
plt.ylabel("Motor Speed (rad/s)")

plt.legend()
plt.grid(True)
plt.tight_layout()

# Save graph
plt.savefig("05_PID/pid_response.png", dpi=300)

# Display graph
plt.show()