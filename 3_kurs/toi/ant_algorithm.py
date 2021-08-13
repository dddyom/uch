"""
Муравьиный алгоритм
Решение коммивояжера используя муравьиный алгоритм
"""

import numpy as np
from numpy import inf

# матрица расстояний

d = np.array([[0, 200, 2, 6000, 1898]
          	,[200,0, 13, 15, 235]
          	,[2, 13, 0, 9, 1456]
          	,[6000, 15, 9, 0, 165]
          	,[1898, 235, 1456, 165, 0]])


SIZE_OF_RESULT = 5
iteration = 1000
n_ants = 5
n_citys = 5

m = n_ants
n = n_citys
e = .5         # испарение феромона
alpha = 1     # Мера значимости феромона
beta = 2       # -/\/- расстрояний

# рассчёт меры расстояний

visibility = 1/d
visibility[visibility == inf ] = 0

# Создание первичных значений, характ количество феромона

pheromne = .1*np.ones((m,n))

# Создание маршрута с добавлением фиктивного города (для возвращения муравья в исходный)

rute = np.ones((m,n+1))




for ite in range(iteration):
    
    rute[:,0] = 1          # установка старта для каждого
    
    for i in range(m):
        
        temp_visibility = np.array(visibility)         # Массив с 1/d
        
        for j in range(n-1):
            # print(rute)
            
            combine_feature = np.zeros(SIZE_OF_RESULT)     # Массив для записи пройденных путей
            cum_prob = np.zeros(SIZE_OF_RESULT)            # -/\/- вероятностей выбора след путей
            
            cur_loc = int(rute[i,j]-1)        # Текущий город 
            
            temp_visibility[:,cur_loc] = 0     # Обнуление 1/d в текущ городе
            
            p_feature = np.power(pheromne[cur_loc,:],beta)         # рассчёт феромона 
            v_feature = np.power(temp_visibility[cur_loc,:],alpha) # рассчёт 1/d
            
            p_feature = p_feature[:,np.newaxis]                     # Добавление оси в массив с вероятностями
            v_feature = v_feature[:,np.newaxis]                     # -/\/- 1/d
            
            combine_feature = np.multiply(p_feature,v_feature)     # рассчёт и внесение результатов в массив
                        
            total = np.sum(combine_feature)                        # сумма путей муравья
            
            probs = combine_feature/total   # нахождение вероятности
            
            cum_prob = np.cumsum(probs)     # все вероятности
            #print(cum_prob)
            r = np.random.random_sample()   # случайное число между 0 и 1
            #print(r)
            city = np.nonzero(cum_prob>r)[0][0]+1       # выбор города исходя из r
            #print(city)
            
            rute[i,j+1] = city              # добавление города в маршрут 
           
        left = list(set([i for i in range(1,n+1)])-set(rute[i,:-2]))[0]     # поиск непройденных городов
        
        rute[i,-2] = left                   # добавление их в маршрут
       
    rute_opt = np.array(rute)               # создание оптимального пути
    
    dist_cost = np.zeros((m,1))             # общее расстояние(init) 
    
    for i in range(m):
        
        s = 0
        for j in range(n-1):
            
            s = s + d[int(rute_opt[i,j])-1,int(rute_opt[i,j+1])-1]   #  рассчёт общего расстояния
        
        dist_cost[i]=s                      # из города i до города i 
       
    dist_min_loc = np.argmin(dist_cost)             # оптимальный путь у каждого муравья (цена)
    dist_min_cost = dist_cost[dist_min_loc]         # самый оптимальный путь (цена)
    
    best_route = rute[dist_min_loc,:]               # эффективный путь (координаты)(init)
    pheromne = (1-e)*pheromne                       # испарение феромона(1-e)
    
    for i in range(m):
        for j in range(n-1):
            dt = 1/dist_cost[i]
            pheromne[int(rute_opt[i,j])-1,int(rute_opt[i,j+1])-1] = pheromne[int(rute_opt[i,j])-1,int(rute_opt[i,j+1])-1] + dt   
            # обновление феромона после прохождения

print('Лучшие пути каждого из муравьёв :')
print(rute_opt)
print()
print('Лучший путь :',best_route)
print('Его цена',int(dist_min_cost[0]) + d[int(best_route[-2])-1,0])
