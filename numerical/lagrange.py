def lagrangeInterpolation(x:list, y:list, xp: float ):
    n= len(x)
    yp=0

    for i in range(n):
        p=1

        for j in range(n):
             if i!=j:
                 p=p*(xp-x[j])/(x[i]-x[j])
        
        yp = yp +p*y[i]

    return yp

x=[1,2,3]
y=[1,4,9]
xp=2.5

yp = lagrangeInterpolation(x,y,xp)

print(f"the interpolation value is: {yp}")