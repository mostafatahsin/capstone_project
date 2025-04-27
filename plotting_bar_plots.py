import matplotlib.pyplot as plt

# categories = ['10', '20', '30', '40', '50']
# ratios = [2, 8, 34, 70.5, 120]

categories = ['10', '20', '30', '40', '50']
ratios = [20, 160, 1010, 2820, 6000]

plt.figure(figsize=(8, 6))
plt.bar(categories, ratios)


plt.xlabel("Row length", fontsize=14)
plt.ylabel('k (in thousands)', fontsize=14)
# plt.title('k (at which itemset outperforms binary)  row length', fontsize=14)


plt.grid(axis='y', linestyle='--', alpha=0.7)

plt.xticks(fontsize=12)
plt.yticks(fontsize=12)


plt.savefig('k_bar_plot.pdf')

plt.show()
