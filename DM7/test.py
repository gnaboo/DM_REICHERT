def elimination(arr):
    dico = dict()
    for el in arr:
        if dico.get(el) != None:
            dico[el] += 1
        else:
            dico[el] = 1
    for key in dico.keys():
        if dico[key] == 2:
            return key
    return None

print(elimination([2, 5, 34, 1, 22, 1]))