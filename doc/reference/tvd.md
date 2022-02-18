# TVD limiter 



[toc]

在守恒律方程中使用TVD limiter
$$
U_t+ \nabla \cdot F(U)=0
$$
其中$U:\Omega \to \R^m$未知函数，$F(U)$已知。

针对$\Omega \sub \R$或者$\Omega \sub \R^2$，$m=1$或者$m \gt 1$，可以分成4类具体情形。



## 一维方程

$$
u_t + f(u)_x = 0 
$$

在每一个区间单元$I_j=[x_{j-1/2},x_{j+1/2}]$ 处，长度$h_j=\Delta x_j=|I_j|=x_{j+1/2}-x_{j-1/2}$。

一维的标准区间$[-1,1]$的正交基函数

|                     | $p^{(0)}$ | $p^{(1)}$ | $p^{(2)}$    | $p^{(3)}$     | $p^{(4)}$           |
| ------------------- | --------- | --------- | ------------ | ------------- | ------------------- |
| $p^{(\alpha)}(z)$   | $1$       | $z$       | $(3z^2-1)/2$ | $(5z^3-3z)/2$ | $(35z^4-30z^2+3)/8$ |
| $p^{(\alpha)}_z(z)$ | $0$       | $1$       | $3z$         | $(15z-3)/2$   | $(140z^3-60z)/8$    |



对应在区间 $I_j$ 的基函数

|                                     | $\phi^{(0)}_j$ | $\phi^{(1)}_j$        | $\phi^{(2)}_j$                                       | $\phi^{(3)}_j$                                               | $\phi^{(4)}_j$                                               |
| ----------------------------------- | -------------- | --------------------- | ---------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| $\phi^{(\alpha)}_j(x)$              | $1$            | $\frac{x-x_j}{h_j/2}$ | $\frac32 \left(\frac{x-x_j}{h_j/2}\right)^2-\frac12$ | $\frac52\left(\frac{x-x_j}{h_j/2}\right)^3-\frac32\left(\frac{x-x_j}{h_j/2}\right)$ | $\frac{35}8 \left(\frac{x-x_j}{h_j/2}\right)^4 - \frac{30}8 \left(\frac{x-x_j}{h_j/2}\right)^2 + \frac38$ |
| $\frac{d}{dx} \phi^{(\alpha)}_j(x)$ | $0$            | $\frac{2}{h_j}$       | $3\left(\frac{x-x_j}{h_j/2}\right) \frac{2}{h_j}$    | $\frac{2}{h_j}\left\{\frac{15}2 \left(\frac{x-x_j}{h_j/2}\right)-\frac23\right\}$ | $\frac{2}{h_j}\left\{\frac{140}8 \left(\frac{x-x_j}{h_j/2}\right)^3-\frac{60}8 \left(\frac{x-x_j}{h_j/2}\right)\right\}$ |



$$
u_h(x)|_{I_j} = \sum_{\alpha} c_j^{(\alpha)} \phi_j^{(\alpha)}(x) = \sum_\alpha c_j^{(\alpha)} p^{(\alpha)}(\frac{x-x_j}{h_j/2})
$$

对相邻的三个区间$I_{j-1},I_j,I_{j+1}$，单元均值
$$
\begin{aligned}
\overline{u}_j &= \frac{1}{h_j}\int_{I_j}u_h(x)\,dx = \frac{1}{h_j} (c^{(0)}_j h_j) = c^{(0)}_j,
\end{aligned}
$$
同理 $\overline{u}_{j-1}=c^{(0)}_{j-1} $,  $\overline{u}_{j+1}=c^{(0)}_{j+1} $。用$x^+$表示从右侧逼近的极限，边界值
$$
\begin{aligned}
&u_h(x_{j+1/2}^-) = \sum_\alpha c^{(\alpha)}_j p^{(\alpha)}(1),
&u_h(x_{j-1/2}^+) = \sum_i c^{(\alpha)}_j p^{(\alpha)}(-1)
\end{aligned}
$$
通过边界值和区间平均值定义 $\widetilde{u}_j,$$\widetilde{\widetilde{u}}_j$ 
$$
\begin{aligned}
 &\widetilde{u}_j = u_h(x_{j+1/2}^-) - \overline{u}_j,
& \widetilde{\widetilde{u}}_j = \overline{u}_j- u_h(x_{j-1/2}^+),
 \end{aligned}
$$
定义minmod函数
$$
m(a_1,\cdots,a_l)=
\begin{aligned}
\begin{cases}
s \min(|a_1|,\cdots,|a_l|) &\text{if}\, s = \text{sign}(a_1)=\cdots=\text{sign}(a_l),\\
0 &\text{otherwise},
\end{cases}
\end{aligned}
$$
利用minmod函数对 $\widetilde{u}_j,$$\widetilde{\widetilde{u}}_j$ 进行修正
$$
\begin{aligned}
&\widetilde{u}_j^{mod} 
= m(\widetilde{u}_j,\overline{u}_{j+1}-\overline{u}_j,\overline{u}_{j}-\overline{u}_{j-1}),
&\widetilde{\widetilde{u}}_j^{mod} 
= m(\widetilde{\widetilde{u}}_j,\overline{u}_{j+1}-\overline{u}_j,\overline{u}_{j}-\overline{u}_{j-1}),
\end{aligned}
$$
对左右端点值进行修正
$$
\begin{aligned}
&u^{mod}_h(x_{j+1/2}^-) = \overline{u}_j + \widetilde{u}_j^{mod},
&u^{mod}_h(x_{j-1/2}^+) = \overline{u}_j - \widetilde{\widetilde{u}}_j^{mod},
\end{aligned}
$$


接下来使用$u^{mod}_h(x_{j+1/2}^-)$，$u^{mod}_h(x_{j-1/2}^+)$，$\overline{u}_j$ 重建 $I_j$ 上的多项式$u_h(x)|_{I_j}$：

* $k=0$ 分段常值，无需limiter，
* $k=1$ 分段线性，由于对称性$\widetilde{u}_j=\widetilde{\widetilde{u}}_j$，修正后仍然有 $u^{mod}_h(x_{j+1/2}^-)=u^{mod}_h(x_{j-1/2}^+)$，存在唯一的一次多项式满足要求，
* $k=2$ 可以求解出唯一的二次多项式满足要求，

* $k \gt 2$ 直接求解系数方程组则存在无穷多解，因此限制$c_j^{(0)},c_j^{(1)},c_j^{(2)}$之后的系数全为0，可以得到唯一解。



具体细节为，系数方程组：
$$
\begin{pmatrix}
    1           & 0           & \cdots & 0           \\
    p^{(0)}(-1) & p^{(1)}(-1) & \cdots & p^{(k)}(-1) \\
    p^{(0)}(1)  & p^{(1)}(1)  & \cdots & p^{(k)}(1)  \\
  \end{pmatrix}
  \begin{pmatrix}
    c_j^{(0),mod} \\
    c_j^{(1),mod} \\
    \vdots        \\
    c_j^{(k),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_j^{(0)}              \\
    u_h^{mod}(x_{j-1/2}^+) \\
    u_h^{mod}(x_{j+1/2}^-) \\
  \end{pmatrix}
$$
例如 $k=1$
$$
\begin{pmatrix}
    1 & 0  \\
    1 & -1 \\
    1 & 1  \\
  \end{pmatrix}
  \begin{pmatrix}
    c_j^{(0),mod} \\
    c_j^{(1),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_j^{(0)}              \\
    u_h^{mod}(x_{j-1/2}^+) \\
    u_h^{mod}(x_{j+1/2}^-) \\
  \end{pmatrix}
  
  \rightarrow
  
  \begin{cases}
  c_j^{(0),mod} &= c_j^{(0)}\\
  c_j^{(1),mod} &= c_j^{(0)} -  u_h^{mod}(x_{j-1/2}^+) = u_h^{mod}(x_{j+1/2}^-) -c_j^{(0)}
  \end{cases}
$$
例如$k \ge 2$，舍弃高阶项系数
$$
\begin{pmatrix}
    1 & 0  & 0& \cdots & 0           \\
    1 & -1 & 1&\cdots & p^{(k)}(-1) \\
    1 & 1  & 1&\cdots & p^{(k)}(1)  \\
      &    & &\ddots &             \\
      &    &  &      & 1           \\
  \end{pmatrix}
  \begin{pmatrix}
    c_j^{(0),mod} \\
    c_j^{(1),mod} \\
    c_j^{(2),mod} \\
    c_j^{(3),mod} \\
    \vdots        \\
    c_j^{(k),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_j^{(0)}              \\
    u_h^{mod}(x_{j-1/2}^+) \\
    u_h^{mod}(x_{j+1/2}^-) \\
    0                      \\
    \vdots                 \\
    0                      \\
  \end{pmatrix}
  \rightarrow
    \left\{
  \begin{aligned}
    c_j^{(0),mod} & = c_j^{(0)}                                                                    \\
    c_j^{(1),mod} & =  - \frac12 u_h^{mod}(x_{j-1/2}^+) + \frac12 u_h^{mod}(x_{j+1/2}^-)           \\
    c_j^{(2),mod} & = - c_j^{(0)} +\frac12 u_h^{mod}(x_{j-1/2}^+) + \frac12 u_h^{mod}(x_{j+1/2}^-) \\
    c_j^{(3),mod} & = \cdots = c_j^{(k),mod}  = 0                                                  \\
  \end{aligned}
  \right.
$$






## 一维方程组



$$
\begin{aligned}
\overset{\rightarrow}{U}_t + \overset{\rightarrow}{f}(\overset{\rightarrow}{U})_x = 0
\end{aligned}
$$
其中自变量$\overset{\rightarrow}{U}$是未知函数，关于$\overset{\rightarrow}{U}$的函数$\overset{\rightarrow}{f}(\overset{\rightarrow}U)$已知。
$$
\begin{aligned}
&\overset{\rightarrow}{U} = 
\begin{pmatrix}
u_1\\
u_2\\
\vdots\\
u_m
\end{pmatrix},

&\overset{\rightarrow}{f}(\overset{\rightarrow}U) = 
\begin{pmatrix}
f_1(u_1,\cdots,u_m)\\
f_2(u_1,\cdots,u_m)\\
\vdots\\
f_m(u_1,\cdots,u_m)\\
\end{pmatrix},

\end{aligned}
$$


对它的处理首先进行对角化，
$$
J(\overset{\rightarrow}{f})=
\begin{pmatrix}
\frac{\partial f_1}{\partial u_1} & \frac{\partial f_1}{\partial u_2} & \cdots& \frac{\partial f_1}{\partial u_m}\\
\frac{\partial f_2}{\partial u_1} & \frac{\partial f_2}{\partial u_2} & \cdots& \frac{\partial f_2}{\partial u_m}\\
\vdots & \vdots & \ddots& \vdots \\
\frac{\partial f_m}{\partial u_1} & \frac{\partial f_m}{\partial u_2} & \cdots& \frac{\partial f_m}{\partial u_3}\\
\end{pmatrix}
=
R(\overset{\rightarrow}U) \Lambda(\overset{\rightarrow}U) R^{-1}(\overset{\rightarrow}U)
$$
其中$\Lambda(\overset{\rightarrow}U)$为对角阵，对角元即为Jacobi矩阵的特征值，
$$
\begin{aligned}
\overset{\rightarrow}{U}_t + \overset{\rightarrow}{f}(\overset{\rightarrow}{U})_x =\overset{\rightarrow}{U}_t + J(\overset{\rightarrow}{f})\,\overset{\rightarrow}{U}_x = 0\\
 R^{-1}(\overset{\rightarrow}U)\overset{\rightarrow}{U}_t +  \Lambda(\overset{\rightarrow}U)  R^{-1}(\overset{\rightarrow}U)\overset{\rightarrow}{U}_x=0
\end{aligned}
$$


由于区间长度趋于0，在区间$I_j$上近似取常数矩阵$\Lambda \approx \Lambda(\overset{\rightarrow}{U})(x_j)$，$R \approx R(\overset{\rightarrow}{U})(x_j)$，$R^{-1} \approx R^{-1}(\overset{\rightarrow}{U})(x_j)$，变换$\overset{\rightarrow}{V}(x) = R^{-1} \,\overset{\rightarrow}{U}(x)$，则 $\overset{\rightarrow}{V}$ 在$I_j$应该近似满足
$$
\overset{\rightarrow}{V}_t + \Lambda \overset{\rightarrow}{V}_x = 0
$$
从而$\overset{\rightarrow}V$的各个分量相互独立，可以按照一维标量的TVD分别进行处理得到$\overset{\rightarrow}V^{mod}$，然后再变换回来  $\overset{\rightarrow}U^{mod}=R \overset{\rightarrow}V^{mod}$。



具体细节为：

1. 首先获取原始变量的3个单元均值向量，以及4个边界值向量

$$
\overline{\overset{\rightarrow}{U}}_{j-1},\,\,\, \overline{\overset{\rightarrow}{U}}_{j},\,\,\, \overline{\overset{\rightarrow}{U}}_{j+1},\\
\overset{\rightarrow}{U}_h(x_{j-1/2}^-),\,\,\, \overset{\rightarrow}{U}_h(x_{j-1/2}^+),\,\,\, 
\overset{\rightarrow}{U}_h(x_{j+1/2}^-),\,\,\, \overset{\rightarrow}{U}_h(x_{j+1/2}^+),
$$

2. 然后通过过渡矩阵$R^{-1}$变换，得到相应的7个点值向量

$$
\overline{\overset{\rightarrow}{V}}_{j-1},\,\,\, \overline{\overset{\rightarrow}{V}}_{j},\,\,\, \overline{\overset{\rightarrow}{V}}_{j+1},\\
\overset{\rightarrow}{V}_h(x_{j-1/2}^-),\,\,\, \overset{\rightarrow}{V}_h(x_{j-1/2}^+),\,\,\, 
\overset{\rightarrow}{V}_h(x_{j+1/2}^-),\,\,\, \overset{\rightarrow}{V}_h(x_{j+1/2}^+),
$$

3. 逐个分量使用minmod函数修改，得到4个边界值向量，并且通过矩阵 $R$ 变换为原始变量

$$
\overset{\rightarrow}{V}^{mod}_h(x_{j-1/2}^-),\,\,\, \overset{\rightarrow}{V}^{mod}_h(x_{j-1/2}^+),\,\,\, 
\overset{\rightarrow}{V}^{mod}_h(x_{j+1/2}^-),\,\,\, \overset{\rightarrow}{V}^{mod}_h(x_{j+1/2}^+),\\

\overset{\rightarrow}{U}^{mod}_h(x_{j-1/2}^-),\,\,\, \overset{\rightarrow}{U}^{mod}_h(x_{j-1/2}^+),\,\,\, 
\overset{\rightarrow}{U}^{mod}_h(x_{j+1/2}^-),\,\,\, \overset{\rightarrow}{U}^{mod}_h(x_{j+1/2}^+),\\
$$

4. 再加上均值向量$\overline{\overset{\rightarrow}{U}}_{j}$共5个点值向量，可以重建$I_{i,j}$上的多项式向量。

$$
\left.
\begin{aligned}
\overline{\overset{\rightarrow}{U}}_{j}\\
\overset{\rightarrow}{U}^{mod}_h(x_{j-1/2}^-),\,\,\, \overset{\rightarrow}{U}^{mod}_h(x_{j-1/2}^+)\\ 
\overset{\rightarrow}{U}^{mod}_h(x_{j+1/2}^-),\,\,\, \overset{\rightarrow}{U}^{mod}_h(x_{j+1/2}^+)\\
\end{aligned}
\right\}
\rightarrow
\overset{\rightarrow}{U}_h^{mod}|_{I_{j}}
$$









## 二维方程(矩形单元)


$$
u_t + f(u)_x + g(u)_y=0
$$
其中$f(u),g(u)$已知，未知函数$u=u(x,y)$，

在每一个矩形单元$I_{i,j}=[x_{i-1/2},x_{i+1/2}]\times[y_{j-1/2},y_{j+1/2}]$ ，记$\Delta x_i=x_{i+1/2}-x_{i-1/2}$，$\Delta y_j= y_{j+1/2}-y_{j-1/2}$。



二维的标准单元$[-1,1]^2$的正交基函数

|                               | $p^{(0)}$ | $p^{(1)}$ | $p^{(2)}$ | $p^{(3)}$      | $p^{(4)}$   | $p^{(5)}$       |
| ----------------------------- | --------- | --------- | --------- | -------------- | ----------- | --------------- |
| $p^{(\alpha)}(\xi,\eta)$      | 1         | $\xi$     | $\eta$    | $(3\xi^2-1)/2$ | $\xi\,\eta$ | $(3\eta^2-1)/2$ |
| $p^{(\alpha)}_\xi(\xi,\eta)$  | $0$       | $1$       | $0$       | $3\xi$         | $\eta$      | $0$             |
| $p^{(\alpha)}_\eta(\xi,\eta)$ | $0$       | $0$       | $1$       | $0$            | $\xi$       | $3\eta$         |



对应在矩形单元 $I_{i,j}$ 的基函数

|                                                         | $\phi^{(0)}_{i,j}$ | $\phi^{(1)}_{i,j}$            | $\phi^{(2)}_{i,j}$            | $\phi^{(3)}_{i,j}$                                           | $\phi^{(4)}_{i,j}$                                           | $\phi^{(5)}_{i,j}$                                           |
| ------------------------------------------------------- | ------------------ | ----------------------------- | ----------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| $\phi^{(\alpha)}_{i,j}(x,y)$                            | $1$                | $\frac{x-x_i}{\Delta x_i /2}$ | $\frac{y-y_j}{\Delta y_j /2}$ | $\frac32 \left(\frac{x-x_i}{\Delta x_i /2} \right)^2-\frac12$ | $\left(\frac{x-x_i}{\Delta x_i /2}\right)\left( \frac{y-y_j}{\Delta y_j /2}\right)$ | $\frac32 \left(\frac{y-y_j}{\Delta y_j /2} \right)^2-\frac12$ |
| $\frac{\partial}{\partial x}\phi^{(\alpha)}_{i,j}(x,y)$ | $0$                | $1$                           | $0$                           | $3\left(\frac{x-x_i}{\Delta x_i /2}\right) \frac{2}{\Delta x_i}$ | $\frac{2}{\Delta x_i} \left(\frac{y-y_j}{\Delta y_j /2}\right)$ | $0$                                                          |
| $\frac{\partial}{\partial y}\phi^{(\alpha)}_{i,j}(x,y)$ | $0$                | $0$                           | $1$                           | $0$                                                          | $\frac{2}{\Delta y_j}\left(\frac{x-x_i}{\Delta x_i /2}\right)$ | $3\left(\frac{y-y_j}{\Delta y_j /2}\right)\frac{2}{\Delta y_j}$ |


$$
u_h(x,y)|_{I_{i,j}} = \sum_{\alpha} c_{i,j}^{(\alpha)} \phi_{i,j}^{(\alpha)}(x,y) = \sum_\alpha c_{i,j}^{(\alpha)} p^{(\alpha)}(\frac{x-x_i}{\Delta x_i/2},\frac{y-y_j}{\Delta y_j/2})
$$
涉及当前单元$I_{i,j}$，以及相邻的四个单元$I_{i,j-1},I_{i+1,j},I_{i,j+1},I_{i-1,j}$，单元均值（亦即矩形中点的值）
$$
\overline{u}_{i,j} = \frac{1}{\Delta x_i \Delta y_j} \int_{I_{i,j}} u_h(x,y)\,dx\,dy = c^{(0)}_{i,j}
$$
在矩形单元四条边中点的边界值，其中$x^+$表示从右侧逼近的极限，$y^+$表示从上侧逼近的极限。
$$
\begin{aligned}
(u_{left})_{i,j} &= u_h(x_{i-1/2}^+,y_{j})\\
(u_{right})_{i,j}&= u_h(x_{i+1/2}^-,y_j)\\
(u_{down})_{i,j} &= u_h(x_i,y_{j-1/2}^+)\\
(u_{up})_{i,j} &= u_h(x_i,y_{j+1/2}^-)
\end{aligned}
$$
通过minmod函数修改四个边界值
$$
\begin{aligned}
(u_{left})_{i,j}^{mod} &= \overline{u}_{i,j} - m(\overline{u}_{i,j}-(u_{left})_{i,j},\overline{u}_{i+1,j}-\overline{u}_{i,j},\overline{u}_{i,j}-\overline{u}_{i-1,j})\\
(u_{right})_{i,j}^{mod} &= \overline{u}_{i,j} + m((u_{right})_{i,j}-\overline{u}_{i,j},\overline{u}_{i+1,j}-\overline{u}_{i,j},\overline{u}_{i,j}-\overline{u}_{i-1,j})\\
(u_{down})_{i,j}^{mod} &= \overline{u}_{i,j} - m(\overline{u}_{i,j}-(u_{down})_{i,j},\overline{u}_{i,j+1}-\overline{u}_{i,j},\overline{u}_{i,j}-\overline{u}_{i,j-1})\\
(u_{up})_{i,j}^{mod} &= \overline{u}_{i,j} + m((u_{up})_{i,j}-\overline{u}_{i,j},\overline{u}_{i,j+1}-\overline{u}_{i,j},\overline{u}_{i,j}-\overline{u}_{i,j-1})\\
\end{aligned}
$$
利用修改后的四个边界值以及保持单元均值，来重建单元上的多项式$u_h(x,y)|_{I_{i,j}}$：

* $k=0$，无需修改，
* $k=1$，只有三个基函数$\phi_{i,j}^{(0)},\phi_{i,j}^{(1)},\phi_{i,j}^{(2)}$，由于$u_h$是线性函数，和一维一样具有对称性，因此可以重建唯一的多项式，

* $k=2$，有6个基函数 $\{\phi_{i,j}^{(\alpha)},\alpha=0,\dots,5\}$，但是我们只有5个限制条件，解不唯一，因此选择的策略为：
  * 如果minmod函数修改了任一边界值，则强制取$\phi_{i,j}^{(4)}(x,y)$的系数$c_{i,j}^{(4)}=0$，其他五个系数通过方程组可以解出唯一多项式，
  * 如果minmod函数没有修改边界值，则整体保持不变，

* $k \gt 2$，对于后面的基函数$\{\phi_{i,j}^{\alpha}(x,y),\alpha \ge 6\}$，系数强制取为0，前6个系数的确定同$k=2$，





具体细节为，系数方程组：
$$
\begin{pmatrix}
    1           & 0           & \cdots & 0           \\
    p^{(0)}(-1,0) & p^{(1)}(-1,0) & \cdots & p^{(k)}(-1,0) \\
    p^{(0)}(1,0) & p^{(1)}(1,0) & \cdots & p^{(k)}(1,0) \\
    p^{(0)}(0,-1) & p^{(1)}(0,-1) & \cdots & p^{(k)}(0,-1) \\
    p^{(0)}(0,1) & p^{(1)}(0,1) & \cdots & p^{(k)}(0,1) \\
  \end{pmatrix}
  \begin{pmatrix}
    c_{i,j}^{(0),mod} \\
    c_{i,j}^{(1),mod} \\
    \vdots        \\
    c_{i,j}^{(k),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_j^{(0)}              \\
    (u_{left})_{i,j}^{mod} \\
    (u_{right})_{i,j}^{mod} \\
    (u_{down})_{i,j}^{mod} \\
    (u_{up})_{i,j}^{mod} \\
  \end{pmatrix}
$$
例如$k=1$，有3个基函数
$$
\begin{pmatrix}
    1           & 0    		  & 0  			  \\
    1           & -1    	  & 0  			  \\
    1           & 1    		  & 0  			  \\
    1           & 0    		  & -1  			  \\
    1           & 0    		  & 1  			  \\
  \end{pmatrix}
  \begin{pmatrix}
    c_{i,j}^{(0),mod} \\
    c_{i,j}^{(1),mod} \\
    c_{i,j}^{(2),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_{i,j}^{(0)}              \\
    (u_{left})_{i,j}^{mod} \\
    (u_{right})_{i,j}^{mod} \\
    (u_{down})_{i,j}^{mod} \\
    (u_{up})_{i,j}^{mod} \\
  \end{pmatrix}
   \rightarrow
    \left\{
  \begin{aligned}
    c_{i,j}^{(0),mod} & = c_{i,j}^{(0)}     \\
    c_{i,j}^{(1),mod} & =  c_{i,j}^{(0)}-(u_{left})^{mod}_{i,j} = (u_{right})^{mod}_{i,j} - c _{i,j}^{(0)}        \\
    c_{i,j}^{(2),mod} & = c_{i,j}^{(0)}-(u_{down})^{mod}_{i,j} = (u_{up})^{mod}_{i,j} - c _{i,j}^{(0)}\\
  \end{aligned}
  \right.
$$
例如$k = 2$，修改了边界值时，强制取$c_{i,j}^{(4),mod}=0$，
$$
\begin{pmatrix}
    1           & 0    		  & 0  			&0  &0 \\
    1           & -1    	  & 0  		  &1  &0 \\
    1           & 1    		  & 0  			&1  &0 \\
    1           & 0    		  & -1  		&0	&1  \\
    1           & 0    		  & 1  			&0  &1\\
  \end{pmatrix}
  \begin{pmatrix}
    c_{i,j}^{(0),mod} \\
    c_{i,j}^{(1),mod} \\
    c_{i,j}^{(2),mod} \\
    c_{i,j}^{(3),mod} \\
    c_{i,j}^{(5),mod} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
    c_{i,j}^{(0)}              \\
    (u_{left})_{i,j}^{mod} \\
    (u_{right})_{i,j}^{mod} \\
    (u_{down})_{i,j}^{mod} \\
    (u_{up})_{i,j}^{mod} \\
  \end{pmatrix}
$$
解得
$$
\left\{
\begin{aligned}
c^{(0),mod}_{i,j} &= c^{(0)}_{i,j}\\
c^{(1),mod}_{i,j} &= -\frac12 (u_{left})_{i,j}^{mod} +\frac12 (u_{right})_{i,j}^{mod}\\
c^{(2),mod}_{i,j} &= -c^{(0)}_{i,j} + \frac12 (u_{left})_{i,j}^{mod} + \frac12 (u_{right})_{i,j}^{mod}\\
c^{(3),mod}_{i,j} &= -\frac12 (u_{ldown})_{i,j}^{mod} +\frac12 (u_{up})_{i,j}^{mod}\\
c_{i,j}^{(4),mod}&=0\\
c^{(5),mod}_{i,j} &= -c^{(0)}_{i,j} + \frac12 (u_{down})_{i,j}^{mod} + \frac12 (u_{up})_{i,j}^{mod}\\
\end{aligned}
\right.
$$








## 二维方程组(矩形单元)





$$
\begin{aligned}
\overset{\rightarrow}{U}_t + \overset{\rightarrow}{f}(\overset{\rightarrow}{U})_x 
+\overset{\rightarrow}{g}(\overset{\rightarrow}{U})_y= 0
\end{aligned}
$$
其中自变量$\overset{\rightarrow}{U}$是未知函数，关于$\overset{\rightarrow}{U}$的函数 $\overset{\rightarrow}{f}(\overset{\rightarrow}U)$，$\overset{\rightarrow}{g}(\overset{\rightarrow}U)$ 已知。
$$
\begin{aligned}
&\overset{\rightarrow}{U} = 
\begin{pmatrix}
u_1\\
u_2\\
\vdots\\
u_m
\end{pmatrix},
&\overset{\rightarrow}{f}(\overset{\rightarrow}U) = 
\begin{pmatrix}
f_1(u_1,\cdots,u_m)\\
f_2(u_1,\cdots,u_m)\\
\vdots\\
f_m(u_1,\cdots,u_m)\\
\end{pmatrix},
\,\,\,\,\,\,\,\,\,
&\overset{\rightarrow}{g}(\overset{\rightarrow}U) = 
\begin{pmatrix}
g_1(u_1,\cdots,u_m)\\
g_2(u_1,\cdots,u_m)\\
\vdots\\
g_m(u_1,\cdots,u_m)\\
\end{pmatrix},
\end{aligned}
$$

对它的处理首先进行对角化，
$$
\begin{aligned}
J(\overset{\rightarrow}{f})=
\begin{pmatrix}
\frac{\partial f_1}{\partial u_1} & \frac{\partial f_1}{\partial u_2} & \cdots& \frac{\partial f_1}{\partial u_m}\\
\frac{\partial f_2}{\partial u_1} & \frac{\partial f_2}{\partial u_2} & \cdots& \frac{\partial f_2}{\partial u_m}\\
\vdots & \vdots & \ddots& \vdots \\
\frac{\partial f_m}{\partial u_1} & \frac{\partial f_m}{\partial u_2} & \cdots& \frac{\partial f_m}{\partial u_3}\\
\end{pmatrix}
=
R^x(\overset{\rightarrow}U) \Lambda^x(\overset{\rightarrow}U) ({R^x})^{-1}(\overset{\rightarrow}U)\\

J(\overset{\rightarrow}{g})=
\begin{pmatrix}
\frac{\partial g_1}{\partial u_1} & \frac{\partial g_1}{\partial u_2} & \cdots& \frac{\partial g_1}{\partial u_m}\\
\frac{\partial g_2}{\partial u_1} & \frac{\partial g_2}{\partial u_2} & \cdots& \frac{\partial g_2}{\partial u_m}\\
\vdots & \vdots & \ddots& \vdots \\
\frac{\partial g_m}{\partial u_1} & \frac{\partial g_m}{\partial u_2} & \cdots& \frac{\partial g_m}{\partial u_3}\\
\end{pmatrix}
=
R^y(\overset{\rightarrow}U) \Lambda^y(\overset{\rightarrow}U) (R^y)^{-1}(\overset{\rightarrow}U)
\end{aligned}
$$
其中$\Lambda^x(\overset{\rightarrow}U),\Lambda^y(\overset{\rightarrow}U)$为对角阵，对角元即为两个Jacobi矩阵的特征值，

在两个方向上，利用相应过渡矩阵变换，各修正两个边界值向量，然后加上均值向量重建多项式向量。



具体细节为：

1. 首先获取原始变量的5个单元均值向量以及8个边界值向量，（其中记号$(\overset{\rightarrow}{U}_{left})_{i,j}=\overset{\rightarrow}{U}_h(x_{i-1/2}^+,y_j)$，其他类似）

$$
\overline{\overset{\rightarrow}{U}}_{i,j},
\overline{\overset{\rightarrow}{U}}_{i-1,j},
\overline{\overset{\rightarrow}{U}}_{i+1,j},
\overline{\overset{\rightarrow}{U}}_{i,j-1},
\overline{\overset{\rightarrow}{U}}_{i,j+1}\\
$$

$$
&(\overset{\rightarrow}{U}_{right})_{i-1,j},\,\,(\overset{\rightarrow}{U}_{left})_{i,j},
&(\overset{\rightarrow}{U}_{right})_{i,j},\,\,(\overset{\rightarrow}{U}_{left})_{i+1,j},\\
&(\overset{\rightarrow}{U}_{up})_{i,j-1},\,\,(\overset{\rightarrow}{U}_{down})_{i,j},
&(\overset{\rightarrow}{U}_{up})_{i,j},\,\,(\overset{\rightarrow}{U}_{down})_{i,j+1},\\
$$

2. 沿着x方向把3个均值和4个边界值，通过过渡矩阵$(R^{x})^{-1} = (R^{x})^{-1}(\overset{\rightarrow}{U})(x_i,y_j)$变换为$\overset{\rightarrow}{V} = (R^x)^{-1} \,\overset{\rightarrow}{U}$

$$
\overline{\overset{\rightarrow}{V}}_{i,j},
\overline{\overset{\rightarrow}{V}}_{i-1,j},
\overline{\overset{\rightarrow}{V}}_{i+1,j},\\
(\overset{\rightarrow}{V}_{right})_{i-1,j},\,\,(\overset{\rightarrow}{V}_{left})_{i,j},
(\overset{\rightarrow}{V}_{right})_{i,j},\,\,(\overset{\rightarrow}{V}_{left})_{i+1,j},\\
$$

3. 逐个分量使用minmod函数修改得到x方向的2个边界向量值，并且通过矩阵 $R^x$ 变换为原始变量

$$
(\overset{\rightarrow}{V}_{left})_{i,j}^{mod},
(\overset{\rightarrow}{V}_{right})_{i,j}^{mod},\\
(\overset{\rightarrow}{U}_{left})_{i,j}^{mod},
(\overset{\rightarrow}{U}_{right})_{i,j}^{mod},\\
$$

4. 沿着y方向把3个均值和4个边界值，通过过渡矩阵$(R^{y})^{-1} = (R^{y})^{-1}(\overset{\rightarrow}{U})(x_i,y_j)$变换为$\overset{\rightarrow}{W} = (R^y)^{-1} \,\overset{\rightarrow}{U}$

$$
\overline{\overset{\rightarrow}{W}}_{i,j},
\overline{\overset{\rightarrow}{W}}_{i,j-1},
\overline{\overset{\rightarrow}{W}}_{i,j+1},\\
(\overset{\rightarrow}{W}_{up})_{i,j-1},\,\,(\overset{\rightarrow}{W}_{down})_{i,j},
(\overset{\rightarrow}{W}_{up})_{i,j},\,\,(\overset{\rightarrow}{W}_{down})_{i,j+1},\\
$$

5. 逐个分量使用minmod函数修改得到y方向的2个边界向量值，并且通过矩阵 $R^y$ 变换为原始变量

$$
(\overset{\rightarrow}{W}_{down})_{i,j}^{mod},
(\overset{\rightarrow}{W}_{up})_{i,j}^{mod},\\
(\overset{\rightarrow}{U}_{down})_{i,j}^{mod},
(\overset{\rightarrow}{U}_{up})_{i,j}^{mod},\\
$$

6. 利用单元均值和四个边界修改后的向量值，重建多项式向量。

$$
\left.
\begin{aligned}
\overline{\overset{\rightarrow}{U}}_{i,j}\\
(\overset{\rightarrow}{U}_{left})^{mod},\,\,\, (\overset{\rightarrow}{U}_{right})^{mod}\\ 
(\overset{\rightarrow}{U}_{down})^{mod},\,\,\, (\overset{\rightarrow}{U}_{up})^{mod}\\
\end{aligned}
\right\}
\rightarrow
\overset{\rightarrow}{U}_h^{mod}|_{I_{i,j}}
$$





