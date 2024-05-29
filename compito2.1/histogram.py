import matplotlib.pyplot as plt

data = []

with open('comparisons.txt', 'r') as file:
    for line in file:
        data.append(int(line.strip()))

plt.hist(data, bins=50, color='skyblue', edgecolor='black')

plt.xlabel('Numero di confronti')
plt.ylabel('Frequenza')
plt.title('Istogramma dei confronti')

plt.show()