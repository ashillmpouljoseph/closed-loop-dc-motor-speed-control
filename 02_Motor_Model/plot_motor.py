import csv
import matplotlib.pyplot as plt

# CSV file location
filename = "02_Motor_Model/motor_data.csv"

# Lists to store data
time = []
speed = []

# Read the CSV file
with open(filename, "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        time.append(float(row["Time"]))
        speed.append(float(row["Speed"]))

# Create the graph
plt.figure(figsize=(10, 6))

plt.plot(time, speed)

plt.title("DC Motor Speed Response")
plt.xlabel("Time (s)")
plt.ylabel("Speed (rad/s)")

plt.grid(True)

plt.tight_layout()

# Save the graph
plt.savefig("02_Motor_Model/motor_speed_response.png", dpi=300)

# Display the graph
plt.show()