%Topsis 优劣解距离法，是一种常用的综合评价方法。
% Topsis算法的优点是计算简单，计算时间短，计算结果准确。
% 层次分析法的前传后传法，适用于评价对象较少的情况，当评价对象较多时，计算量过大，计算时间过长，且结果不够准确。
% Topsis算法的缺点是指标权重难以确定，且对指标数据要求较高，需要先进行数据标准化处理。
% Topsis算法的适用范围较广，可以用于评价、选择、排序等许多领域。
function [a]=intervaltransfer(qujian,lb,ub,x)
%qujian：最优区间，lb：下界，ub：上界
%x：待转换的向量
%[m,n]=size(x);
% for i=1:m

clear 
a=[0.1 5 5000 4.7 % 两者比较的指标，有四个指标，1 2 3 4
   0.2 6 6000 5.6];
[m,n]=size(a);
qujian=[5 ,6];lb=2;ub=12;%最优区间，下界，上界
a(:,2)=intervaltransfer(qujian,lb,ub,a(:,2));
%其余向量指标规范化
for j=1:n
    b(:,j)=a(:,j)/norm(a(:,j));
end
w=[0.2,0.3,0.4,0.1];  %各个评价指标的权重
c=b.*repmat(w,m,1);%求加权矩阵
cstar=max(c);%求正理想解（针对效益型变量）
cstar(4)=min(c(:,4));%针对属性4，成本型
c0=min(c);%求负理想解
c0(4)=max(c(:,4));%属性4为成本型
for i=1:m
    sstar(i)=norm(c(i,:)-cstar);  %求到正理想解的距离
    s0(i)=norm(c(i,:)-c0);
end
f=s0./(sstar+s0);
[sf,ind]=sort(f,'descend');%求排序结果
sf

% 用法：
% function x2 =intervaltransfer(qujian,lb,ub,x)
% TOPSIS法，对区间型变量的规范化处理，qijian表示最优属性区间，lb表示下界，ub表示上界
%    x2=(1-(qujian(1)-x)./(qujian(1)-lb)).*(x>=lb&x<qujian(1))+(x>=qujian(1)&x<=qujian(2))+(1-(x-qujian(2))./(ub-qujian(2))).*(x>qujian(2)&x<=ub);
    
%    end