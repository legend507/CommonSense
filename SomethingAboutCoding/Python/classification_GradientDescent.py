# An example of How Gradient Descent works in linear regressing

# m is slope, b is y-intercept
# The model is y = mx + b   
# Error calculation is 
def computeErrorForLineGivenPoints(b, m, points):
    totalError = 0
    for i in range(0, len(points)):
        totalError += (points[i].y - (m * points[i].x + b)) ** 2
    return totalError / float(len(points))

def stepGradient(b_current, m_current, points, learningRate):
    b_gradient = 0    
    m_gradient = 0
    N = float(len(points))
    for i in range(0, len(points)):
        b_gradient += -(2/N) * (points[i].y - ((m_current*points[i].x) + b_current))                    # Error对b求微分，可以理解为斜率
        m_gradient += -(2/N) * points[i].x * (points[i].y - ((m_current * points[i].x) + b_current))    # Error对m求微分，可以理解为斜率
    new_b = b_current - (learningRate * b_gradient)
    new_m = m_current - (learningRate * m_gradient)
    return [new_b, new_m]