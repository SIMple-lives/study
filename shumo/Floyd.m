%如何使用
%使用前需要将矩阵w赋值给w
% clear;
% w=[0 9 inf 3 inf;
%    9 0 2 inf 7;
%    inf 2 0 2 4;
%    3 inf 2 0 inf;
%    inf 7 4 inf 0];%初始化权值矩阵
% %调用floyd函数
% [kk,DD,rr,mc,mk]=floyd(w);
% 将矩阵各个边准备好，两点之间无法到达的边设为inf
%调用floyd函数，得到最短路径矩阵，最短路径长度矩阵，最短路径

%%floyd代码%%%%%%
function [k,d,r,minC,minK]=floyd(w)
    n=size(w,1);d=w;   %赋权矩阵w作为初始距离矩阵
    for i=1:n
        for j=1:n
            r(i,j)=j;  %最优路径初值
        end
    end
    %如下计算最优距离d和最优路径r
    for k=1:n    
        for i=1:n
            for j=1:n
                if d(i,k)+d(k,j)<d(i,j)
                    d(i,j)=d(i,k)+d(k,j);
                    r(i,j)=r(i,k);
                end
            end
        end
        sprintf ('%s','迭代次数k:'),k,sprintf('%s','迭代后距离矩阵d:'),d
    end
    sprintf ('%s','最优路径矩阵r:'),r,C=zeros(1,n);%储存总费用
    for i=1:n
        for j=1:n
            C(i)=C(i)+d(i,j);%求各点费用
        end
    end
    minC=C(1);minK=1;k=2;
    while k<n+1   %比较各点总费用并求最小值
        if minC >C(k)
            minC=C(k);minK=k;
        elseif minC==C(k)
                minK=[[minK],k];
        end
        k=k+1;
    end
        sprintf ('%s','最小总费用值minC:'),minC
        sprintf ('%s','最优顶点编号minK:'),minK
        %%%%%%%%%%完整的floyd算法%%%%%%%%%%%%%%%
    