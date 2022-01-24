import operator
from CNF_Creator import *
import os
import time
import random
import random
import itertools
import csv
import matplotlib.pyplot as plt

def ReadCNFfromCSVfile():
    with open('CNF.csv') as csvfile:
        rows = csv.reader(csvfile)
        rows = list(rows)
    sen = [[int(i) for i in ro] for ro in rows]
    return sen


def ReadCNFfromCSVfile2():
    with open('CNF2.csv') as csvfile:
        rows = csv.reader(csvfile)
        rows = list(rows)
    sen = [[int(i) for i in ro] for ro in rows]
    return sen


def ReadCNFfromCSVfile3():
    with open('CNF3.csv') as csvfile:
        rows = csv.reader(csvfile)
        rows = list(rows)
    sen = [[int(i) for i in ro] for ro in rows]
    return sen


def ReadCNFfromCSVfile4():
    with open('CNF4.csv') as csvfile:
        rows = csv.reader(csvfile)
        rows = list(rows)
    sen = [[int(i) for i in ro] for ro in rows]
    return sen


def ReadCNFfromCSVfile5():
    with open('CNF5.csv') as csvfile:
        rows = csv.reader(csvfile)
        rows = list(rows)
    sen = [[int(i) for i in ro] for ro in rows]
    return sen


def fitness_value(a, sentence):
    # This function is used to calculate the fitness value of a population or an instance of the population.
    # Not the weight but the actual values.
    fitness_of_population = [value(0, a[i], sentence)/len(sentence) * 100 for i in range(len(a))]
    return fitness_of_population


def weights_population(a, sentence):
    # This function is used to calculate the weights for the population or an instance of the population.
    # Weights are used for selection and what not.
    fitness_of_population = [value(0, a[i], sentence)**3 for i in range(len(a))]
    total = sum(fitness_of_population)
    fitness_of_population = [x/total for x in fitness_of_population]
    return fitness_of_population


def value(count, instance, sentence):
    # This function is used to calculate how many clauses a particular instance of a population satisfy.
    # value is for 1 instance and is used in other functions.
    instance_clause = [instance[y-1] if y > 0 else not instance[-1*y - 1] for x in sentence for y in x]
    lol = [1 for i in range(len(sentence)) if any(instance_clause[j] for j in range(3*i, 3*i+3))]
    return sum(lol) + count


def reproduce(parent1, parent2):
    # This function is used to create 2 children from parents using a random crossover point
    # Crossover point is chosen at random.
    cross_point = random.choice(range(len(parent1)))
    #for cross_point in cross_points:
    #    temp = parent1[cross_point]
    #    parent1[cross_point] = parent2[cross_point]
    #    parent2[cross_point] = temp
    child1 = parent1[:cross_point] + parent2[cross_point:]
    child2 = parent2[:cross_point] + parent1[cross_point:]
    # if random.choice(range(0, 100)) < 2:
    #     arr = random.choices([True, False], weights=None, k=50)
    #     for i in range(len(arr) - 1):
    #         if arr[i]:
    #             child1[i] = parent1[i]
    #             child2[i] = parent2[i]
    #         else:
    #             child1[i] = parent2[i]
    #             child2[i] = parent1[i]
    return [child1, child2]


def mutate(ch):
    # This function is used to mutate a child
    # Mutation rate is 5%
    xyy = random.choice(range(0,500))
    if xyy < 50:
        ch[xyy] = not ch[xyy]
    return ch


def get_next_gen(a, b, sentence):
    # This function is Crucial and is used to get new generation using culling and elitism
    # We take the best 20% parents and we take best 80 % of child generation and then select the remaining 80% for the
    # new population stochastically
    # new_population = []
    # n = len(a)
    # for i in range(n):
    #     new_population.append(a[n-i-1])
    # n = 2*len(a)
    # for i in range(n):
    #     new_population.append(b[n-i-1])
    # bigger_set_fitness, bigger_set = zip(*sorted(zip(fitness_value(new_population,sentence), new_population)))
    # new_population = list(bigger_set)
    parents, parents_fit = zip(*sorted(zip(fitness_value(a, sentence), a)))
    #child_s, child_fit = zip(*sorted(zip(fitness_value(b, sentence), b)))
    parent_sort = list(parents_fit)
    res = [parent_sort[i] for i in range(30, 40)]
    #child_sort = list(child_fit)
    #res1 = [child_sort[i] for i in range(30, 100)]
    res_i = random.choices(b, weights_population(b, sentence), k=30)
    for i in range(len(res_i)):
        res.append(res_i[i])
    # next_gen = [new_population[i] for i in range(len(a), 3*len(a))]
    #return random.choices(next_gen, weights_population(next_gen, sentence), k=len(a))
    return res


def new_generation(old_generation, sentence):
    # This function is used to create the new generation by calling other functions
    weights = weights_population(old_generation, sentence)
    prv_gen = []
    child_gen = []
    for i in range(len(old_generation)):
        parent = random.choices(old_generation, weights, k=2)
        child = reproduce(parent[0], parent[1])
        child_gen.append(mutate(child[1]))
        child_gen.append(mutate(child[0]))
    return get_next_gen(old_generation, child_gen, sentence)


def genetic_algo(sent):
    # This function where our genetic algo takes place where we hard stop it wrt time or if it achieves
    # 100% rate or if it is stable for 200+ generations
    sentence = sent
    population = [random.choices([True, False], weights=None, k=50) for i in range(40)]
    best_population = population
    best_population_fit = max(fitness_value(population, sentence))
    initial = time.time()
    final = initial+45
    maximum_count = 0
    count = 0
    old_fit_val = best_population_fit
    for i in range(0, 10000):
        if time.time() > final:
            break
        population = new_generation(population, sentence)
        new_fit_val = max(fitness_value(population, sentence))
        if old_fit_val == new_fit_val:
            count += 1
        else:
            if maximum_count < count:
                maximum_count = count
            count = 0
        if count == 120:
            population = [random.choices([True, False], weights=None, k=50) for i in range(40)]
            old_fit_val = new_fit_val
            count = 0
        if new_fit_val > best_population_fit:
            best_population = population
            best_population_fit = new_fit_val
        if best_population_fit == 100:
            break
        old_fit_val = new_fit_val
    return best_population_fit, time.time()-initial, i, best_population


def main():
    cnfC = CNF_Creator(n=50)
    sentence = cnfC.ReadCNFfromCSVfile()
    x,y,z,w = genetic_algo(sentence)
    best_modal = 0
    currmax = 0.0
    for i in w:
      if fitness_value([i], sentence)[0] == x:
        best_modal = i
        currmax = fitness_value([i], sentence)
    best_modal_print = [ i+1 if best_modal[i] else -1*(i+1) for i in range(len(best_modal))]
    print('\n\n')
    print('Roll No : 2018B4A70827G')
    print('Number of clauses in CSV file : ',len(sentence))
    print('Best model : ',best_modal_print)
    print('Fitness value of best model :',x, '%')
    print('Time taken :',y,' seconds')
    print('\n\n')


if __name__ == '__main__':
    main()