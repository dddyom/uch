import matplotlib.pyplot as plt

lst = []
with open("res.txt") as f:
    for i in f:
        lst.append(int(i))
        
print(lst)

plt.plot(lst)
plt.show()        
