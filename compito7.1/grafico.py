import matplotlib.pyplot as plt

rounds_per_run = []

with open("results.txt", "r") as file:
    for line in file:
        rounds = int(line.strip()) 
        rounds_per_run.append(rounds) 

plt.hist(rounds_per_run, bins=range(1, max(rounds_per_run) + 2), align='left', edgecolor='black')

plt.title('Numero di rounds per ogni run')
plt.xlabel('Numero di rounds')
plt.ylabel('Numero di run')
 
mean = sum(rounds_per_run) / len(rounds_per_run)
plt.axvline(mean, color='r', linestyle='dashed', linewidth=1)

plt.show()
