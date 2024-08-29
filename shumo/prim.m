clc;clear;
a=zeros(7);
a(1,2)=50;a(1,3)=60;
a(2,4)=65;a(2,5)=40;
a(3,4)=52;a(3,7)=45;
a(4,5)=50;a(4,6)=30;a(4,7)=42;
a(5,6)=70;
a=a+a';a(find(a==0))=inf;
result=[];p=1;tb=2:length(a);
while length(result)~=length(a)-1
    temp=a(p,tb);temp=temp(:);
    d=min(temp);
    [jb,kb]=find(a(p,tb)==d);
    j=p(jb(1));k=tb(kb(1));
    result=[result,[j;k;d]];
    p=[p,k];
    tb(find(tb==k))=[];
end
result  %result的第一行，第二行，第三行表示弧的起点终点和权值

function re=biaoji(j,biao)  %ÅÐ¶ÏjµãÊÇ·ñÒÑ±»±ê¼Ç
    l=length(biao);
    for i=1:l
       if j==biao(i) 
            re=1;
            return;
       end
    end
    re=0;
    return;
end

clear all;
close all;
clc;

G=[0 4 0 0 0 0 0 8 0;
   4 0 8 0 0 0 0 11 0;
   0 8 0 7 0 4 0 0 2;
   0 0 7 0 9 14 0 0 0;
   0 0 0 9 0 10 0 0 0;
   0 0 4 14 10 0 2 0 0;
   0 0 0 0 0 2 0 1 6;
   8 11 0 0 0 0 1 0 7;
   0 0 2 0 0 0 6 7 0];

[m n]=size(G);

q=[1];      %已经被标记的元素
k=1;        %已经标记的元素个数
A=[];       %最后产生的最小生成树
while length(q)~=m
    e=[];
    for i=1:k
        for j=1:n
            if G(q(i),j)~=0 && ~biaoji(j,q) %不在数中的元素
                e=[e;G(q(i),j) q(i) j];
            end
        end
    end
    
    [junk index]=min(e(:,1));    %求与当前标记的所有元素相邻的权重最小的边的索引
    A=[A;e(index,:)];       %最小生成树的三元组表示
    q=[q e(index,3)];
    k=k+1;  
end