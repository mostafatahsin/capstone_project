import pandas as pd
import matplotlib.pyplot as plt

# Corrected data (without extra k value)
# data = {
#     "k": [130, 140, 150, 160, 170, 180],
#     "binary_exec_time": [
#         0.5458033333,
# 0.5524543333,
# 0.6004293333,
# 0.6337026667,
# 0.674661,
# 0.7763036667
#     ],
#     "itemset_exec_time": [
#         0.612571,
# 0.6184266667,
# 0.6229976667,
# 0.6125196667,
# 0.6527016667,
# 0.6352373333
#     ],
# }

data = {
    "k": [2700,
2800,
2900,
3100],
    "binary_exec_time": [
       11.14944067,
12.80710067,
13.43290167,
14.75494367
    ],
    "itemset_exec_time": [
        11.74562567,
13.62032233,
13.23510533,
14.26956367
    ],
}


df = pd.DataFrame(data)


df["binary_exec_time"] = df["binary_exec_time"].round(6)  # rounding to 6 decimal places
df["itemset_exec_time"] = df["itemset_exec_time"].round(6)

# plot data
plt.figure(figsize=(10, 6))
plt.plot(df["k"], df["binary_exec_time"], label="Binary representation", marker='o')
plt.plot(df["k"], df["itemset_exec_time"], label="Itemset representation", marker='o')

plt.xlabel("Total number of attribute-value pair, k (in thousands)", fontsize=14)
plt.ylabel("Execution time (seconds)", fontsize=14)
plt.title("Maximum row length = 40", fontsize=14)  #change
plt.legend(fontsize=12)

plt.xticks(fontsize=12)
plt.yticks(fontsize=12)

plt.grid(True)
plot_filename = "execution_time_40.pdf"   #change
plt.savefig(plot_filename, format='pdf')
plt.show()


