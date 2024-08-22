

import numpy as np
import matplotlib.pyplot as plt	
import cmath
import scipy
import mpmath	
from mpl_toolkits.mplot3d import Axes3D	
plt.rc('text',usetex=True)	

	#基本几何参数	
delta =0.4810	#0.4810抛物面顶点偏移量	
R=300.4	#基准球面半径	
D_circle=500	#基准球面口径	
N_circle=10**5	#求作图离散点数	
p=0.466*2*R + 2*delta #抛物线参量p	
D_para=300	#抛物面口径	

N_para=round(N_circle*(D_para/D_circle))	
eps=10**(-7)	
#圆方程	
def circle(x):	
	z=-np.sqrt(R**2-x**2)	
	return z	

plt.figure(1)	
x_circle=np.linspace(-D_circle/2,D_circle/2,N_circle)	
plt.plot(x_circle,circle(x_circle),label="Basic Sphere")	


##抛物线方程
def para(x):	
	z=x**2/(2*p)-R-delta	
	return z

x_para=np.linspace(-D_para/2,D_para/2,N_para)
plt.plot(x_para,para(x_para),label="Woeking Paraboloid")

plt.plot("Figure for Basic Sphere  Working Paraboloid")
plt.legend()
plt.xlabel(r'$x$(m)')
plt.ylabel(r'$z$(m)')
#产生圆周法向量
def find_root(f,a,b):
    aa=a
    bb=b
    c=(aa+bb)/2
    if abs(f(c))<eps:
        return c
    else:
        if f(c)*f(aa)<0:
            aa=aa
            bb=c
            return find_root(f,aa,bb)
        else:
            aa=c
            bb=bb
            return find_root(f,aa,bb)
        
t_array=np.zeros(len(x_para))

#计算圆周上的各个结点需要的径向位移
for i in range(len(x_para)):
    x_temp=x_para[i]
    z_temp=circle(x_temp)
    normal_vec=np.array([(0-x_temp),(0-z_temp)])
    unit_normal_vec=normal_vec/(np.sqrt(normal_vec[0]**2+normal_vec[1]**2))
    def f(t):
        res=z_temp+t*unit_normal_vec[1]-((x_temp+t*unit_normal_vec[0])**2/(2*p)-R-delta)
        return res
    t_temp=find_root(f,-1,1)
    t_array[i]=t_temp
    
    
#径向位移图
plt.figure(2)
x_begin=round(len(x_para)/2)

plt.plot(x_para[x_begin],t_array[x_begin],linewidth=2)
plt.xlabel(r'$x$(m)')
plt.ylabel(r'$t$(m)')
plt.title("Distance Between Basic Sphere and Working Paraboloid")
plt.show()
#


