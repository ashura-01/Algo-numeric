# Basic implementation of the Bisection Method to find a root of f(x) = x^2 - 4x - 10 for the interval [-2, -1]
# Stopping criteria -> relative error |b - a| / |b| becomes less than or equal to 0.000001
import math
def f(x:float):
    return x*x-4*x-10

def main():
    a=-2
    b=-1
    root:float

    if f(a)*f(b) > 0:
        print("wrong intrerval")
        return -1
    while True:
        root  = (a+b)/2
        if f(root)==0:
            break
        elif f(a)*f(root)<0:
            b=root
        else:
            a=root
        if abs((b-a)/b) <= 0.000001:
            break
    print("the final root is: ", root)        

if __name__=="__main__":
    main()