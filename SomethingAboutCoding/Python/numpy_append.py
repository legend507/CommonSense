>>> a = []
>>> b = [1, 2, 3]
>>> c = [4, 5]
>>> a.append(b)
>>> a
[[1, 2, 3]]
>>> a.append(c)
>>> a
[[1, 2, 3], [4, 5]]
>>> 

# after this, do numpy.array(a)
# then u get what u want ...