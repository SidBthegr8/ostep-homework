import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("tlb_results.csv")
plt.figure(figsize=(8,5))

plt.plot(data["num_pages"], data["avg_time_ns"], marker="o", linestyle="-")
plt.xscale("log", base=2)  # Log-scale x-axis
plt.xlabel("Number of Pages Accessed")
plt.ylabel("Average Time per Access (ns)")
plt.title("TLB Size Measurement")
plt.grid(True)

plt.savefig("tlb_graph.png")
plt.show()
