import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

# 使用 LaTeX 渲染文本
plt.rc('text', usetex=True)

 # 读取数据
data1 = pd.read_csv('附件1.csv', encoding='ISO-8859-1')
data1 = np.array(data1)
data = np.zeros((2226, 5), dtype='object')
data[:, 0:4] = data1

 # 中心点坐标和单位向量计算
center = np.array([-49.3194, -36.889, -294.0187])
n_0 = -center / np.linalg.norm(center)
node_arr = data1[:, 1:]

 # 计算各节点据抛物线对称轴的距离
for i in range(2226):
     vec_temp = node_arr[i, :] - center
     h_temp = np.dot(vec_temp, n_0)
     rho_temp = np.sqrt(np.linalg.norm(((((((((((vec_temp)))))))))))**2 - h_temp**2)
     data[i, 4] = rho_temp
     
 # 数据导出到 Excel 进行排序
data_df = pd.DataFrame(data)
data_df.to_excel('data.xlsx', index=False)

# 排序后的数据导入程序
data2 = pd.read_excel('data.xlsx')
data2 = np.array(data2)

# 基础几何参数
R = 300.4
D_circle = 500
delta = 0.4810
p = 0.466 * 2 * R + 2 * delta
D_para = 300

eps = 10**-7

# 圆方程
def circle(x):
    return -np.sqrt(R**2 - x**2)

# 抛物线方程
def para(x):
    return x**2 / (2 * p) - R - delta

# 方程求根函数 (使用二分法)
def find_root(f, a, b, tol=eps):
    while abs(b - a) > tol:
        c = (a + b) / 2
        if abs(f(c)) < tol:
            return c
        elif f(a) * f(c) < 0:
            b = c
        else:
            a = c
    return (a + b) / 2

# 数据准备
data3 = np.zeros((2226, 7), dtype='object')
data3[:, :5] = data2

data4 = np.zeros((2226, 7), dtype='object')
data4[:, 0] = data3[:, 0]

t_arr = np.zeros(2000)
for i in range(692):
    rho_temp = data3[i, 4]
    x_temp = rho_temp
    z_temp = circle(x_temp)
    vec = np.array([-x_temp, -z_temp])
    vec_unit = vec / R

    # 定义待求根函数
    def f(t):
        return (x_temp + t * vec_unit[0])**2 / (2 * p) - R - delta - z_temp - t * vec_unit[1]

    t_i = find_root(f, -1, 1)
    x0, y0, z0 = -data3[i, 1], -data3[i, 2], -data3[i, 3]
    vec0 = np.array([x0, y0, z0])
    vec_unit0 = vec0 / np.linalg.norm(vec0)
    x1 = -x0 + vec_unit0[0] * t_i
    y1 = -y0 + vec_unit0[1] * t_i
    z1 = -z0 + vec_unit0[2] * t_i
    data4[i, 1:4] = [x1, y1, z1]
    data4[i, 4] = t_i

# 数据整理，为作图做准备
x_arr = data4[:692, 1]
y_arr = data4[:692, 2]
z_arr = data4[:692, 3]

x_arr2 = np.zeros(1540)
y_arr2 = np.zeros(1540)
z_arr2 = np.zeros(1540)

x_arr2[:1534] = data3[692:, 1]
y_arr2[:1534] = data3[692:, 2]
z_arr2[:1534] = data3[692:, 3]

# 构造等比例 600x600x600 坐标
x_arr2[1535] = 300
y_arr2[1535] = 300
z_arr2[1535] = 300

x_arr2[1537] = -300
y_arr2[1537] = -300
z_arr2[1537] = -300

x_arr2[1539] = -300
y_arr2[1539] = -300
z_arr2[1539] = 300

# 3D 作图
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_title('Working State In Question2')

ax.scatter(x_arr, y_arr, z_arr, c='r', label='Working Paraboloid')
ax.scatter(x_arr2, y_arr2, z_arr2, c='b', label='Basic Sphere')
ax.set_xlabel('X(m)')
ax.set_ylabel('Y(m)')
ax.set_zlabel('Z(m)')
plt.legend()
plt.show()
