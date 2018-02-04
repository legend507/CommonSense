'''
How mean shift work?
- 把dataset想象成一个橡胶平面，点越多的地方越往下陷，然后用gradient descent的想法，所有点都向下陷的地方滚；那个下陷的最低点就是一个cluster的中心
'''

# calc Euclidean distance
def euclid_distance(x, xi):
    return np.sqrt(np.sum((x - xi)**2))

# choose all x in X that is neear x_centroid
def neighbourhood_points(X, x_centroid, distance = 5):
    eligible_X = []
    for x in X:
        distance_between = euclid_distance(x, x_centroid)
        # print('Evaluating: [%s vs %s] yield dist=%.2f' % (x, x_centroid, distance_between))
        if distance_between <= distance:
            eligible_X.append(x)
    return eligible_X

# a gaussian radial base function
def gaussian_kernel(distance, bandwidth):
    val = (1/(bandwidth*math.sqrt(2*math.pi))) * np.exp(-0.5*((distance / bandwidth))**2)
    return val


# -------------------------------------------------------------------------------------------

X = np.copy(original_X)

past_X = []
n_iterations = 5
for it in range(n_iterations):
    for i, x in enumerate(X):
        ### Step 1. For each datapoint x ∈ X, find the neighbouring points N(x) of x.
        neighbours = neighbourhood_points(X, x, look_distance)
        
        ### Step 2. For each datapoint x ∈ X, calculate the mean shift m(x).
        numerator = 0
        denominator = 0
        for neighbour in neighbours:
            distance = euclid_distance(neighbour, x)
            weight = gaussian_kernel(distance, kernel_bandwidth)    # For every x's neighbour, calc weight using RBF <- this is the so called kernel, a weighting function 
            numerator += (weight * neighbour)
            denominator += weight
        
        new_x = numerator / denominator
        
        ### Step 3. For each datapoint x ∈ X, update x ← m(x).
        X[i] = new_x
    
    past_X.append(np.copy(X))