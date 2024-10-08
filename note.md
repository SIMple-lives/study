# note

**注释**以`;`开始

伪指令:是汇编指令的一种，没有对应的机器指令，不是及其指令的助记符，仅仅在编译阶段有编译器执行.

`DB`字节

`DW`字数据

`DD`双字

`DQ`四字

## div

1. 16位的二进制数除以8位的二进制数

   **被除数**在寄存器`AX`中，除数由通用寄存器或者内存单元提供，**商**在`AL`中，余数在`AH`中

2. 32位的二进制数除以16位的二进制数

​	在做除法之前，先将两段进行切割，分别装入`DX`和`AX`，通常用"DX:AX"来描述32位的被除数.**商**在`AX`中，余数在`DX`中.

## xor

异或，互斥或，互斥的或运算

> 一般地,xor 指令的两个操作数应当具有相同的数据宽度。因此,其指令格式可以总结为
> 以下几种情况:
>
> xor 8 位通用寄存器,8 位立即数,例如:xor al,0x55
> xor 8 位通用寄存器,指向 8 位实际操作数的内存地址,例如:xor cl,[0x2000]
> xor 8 位通用寄存器,8 位通用寄存器,例如:xor bl,dl
> xor 16 位通用寄存器,16 位立即数,例如:xor ax,0xf033
> xor 16 位通用寄存器, 指向 16 位实际操作数的内存地址,例如:xor bx,[0x2002]
> xor 16 位通用寄存器,16 位通用寄存器,例如:xor dx,bx
> xor 指向 8 位实际操作数的内存地址,8 位立即数,例如:xor byte[0x3000],0xf0
> xor 指向 8 位实际操作数的内存地址,8 位通用寄存器,例如:xor [0x06],al
> xor 指向 16 位实际操作数的内存地址,16 位立即数,例如:xor word [0x2002],0x55aa
> xor 指向 16 位实际操作数的内存地址,16 位通用寄存器,例如:xor [0x20],dx



`\` 是续行符

## 批量传送数据

1. `movsb`

   以字节为单位

2. `movsw`

   以字位单位

执行指令时，原始数据串的段地址由`DS`指定，偏移地址有`SI`指定.简写为`DS:SI`,要传送的地址由`ES:DI`指定，传送的字节数由`CX`指定.
还需要指定是正向传送还是反向传送，正向传送是指传送操作的方向是从内存区域的**低地址端**到**高地址端**;反向则相反.

## cld 

方向标志清零.`cld`将DF标志清零，以指示传送的方向是正方向.

## 8086寻址方式

### 寄存器寻址

操作的数位于寄存器中，直接从寄存器取得.

```assembly
mov ax,dx
add bx,0xf000
inc dx
```

### 立即寻址

立即寻址又叫做立即数寻址.指令的操作是一个立即数.

```assembly
add bx,0xf000
mov dx,label_a
```

### 内存寻址

采用段地址左移4位，然后加上偏移地址，来形成20为物理地址.段地址由四个寄存器之一来提供，偏移地址由指令来提供.

**`直接寻址`	**

使用该寻址方式的操作数是一个偏移地址，而且给出了该偏移地址的具体数值.

```assembly
mov ax,[0x5c0f] ;将数据段寄存器DS的内容左移四位，加上0x5c0f.
add word [0x0230],0x5000
xor byte [es:label_b],0x05
```

但凡表示内存地址的，都必须用中括号扩起来.

**`基址寻址`**

在指令的地址部分使用基址寄存器BX或者BP来提供偏移地址.

```txt
mov [bx],dx
;执行时，处理器将数据段寄存器DS的内容左移4位,加上基址寄存器BX的内容，形成20位物理地址
add byte [bx],0x55
;将数据段寄存器DS的内容左移4位，加上寄存器BX中的内容，形成20位物理地址，然后将立即数加到该地址处的字节单元里
```

**`变址寻址`**

类似于`基址寻址`，这种寻址方式使用的是变址寄存器(或者索引寄存器)SI和DI

```assembly
mov [si],dx
add ax,[di]
xor word [si],0x8000
```

这种操作数的指令执行时，除非使用段超越前缀,处理器会访问由段寄存器DS指向的数据段，偏移地址由寄存器SI或者DI提供.

**`基址变址寻址`**

基址变址的操作数可以使用一个基址寄存器(BX或者BP),外加一个变址寄存器(SI或者DI).基本形式：

```assembly
mov ax,[bx+si]
add word [bx+di],0x3000
```

```assembly
mov bx,string
 ;数据区首地址
mov si,0
 ;正向索引
mov di,25
 ;反向索引
order:
mov ah,[bx+si]
mov al,[bx+di]
mov [bx+si],al
mov [bx+di],ah
 ;以上 4 行用于交换首尾数据
inc si
dec di
cmp si,di
jl order
 ;首尾没有相遇,或者没有超越,继续
```

规范的程序，应该包括代码、数据段、附加段和堆栈段.

## 段定义语句

**`vstart`**:在定义段时，如果由vstart=0;则在该段中的标号代表的汇编地址是从该段开始从0开始计算.否则就是从程序开头计算.

## equ

常数伪指令是由equ声明的.

用`equ`声明的数值不占用任何汇编地址，也不会在运行时占用任何内存地址。他仅仅代表一个数值.

## 端口访问

端口的访问不能使用类似于`mov`这样的指令，取而代之的是`in`和`out`指令

**`in`**指令是从端口读，一般形式

```assembly
in al,dx
in ax,dx
```

**`in`**的目的操作数必须是寄存器`AX`或者`AL`，当访问8位的端口时，使用`AL`，当访问16位的端口时，使用`AX`.**`in`**的源操作数应当是寄存器`DX`.

**`out`**与in相反，通过端口向外围设备发送数据

目的操作数可以是8位立即数或者寄存器DX,源操作数必须是寄存器AL或者AX.

## 逻辑扇区

最早的逻辑扇区编址方法是L B A 28,使用28个比特来表示逻辑扇区号,从逻辑扇区0x0000000到0xFFFFFFF,共可以表示2^28 - 268435456个扇区,每个扇区512字节，所以LBA28可以管理128GB的硬盘

## 硬盘读取扇区数据

1. 设置要读取的扇区数量
2. 设置起始LBA扇区号
3. 向端口0x1f7写入0x20,请求硬盘读取
4. 等待读写操作完成
5. 连续读出数据

## 调用过程

调用过程指令**`call`**

8086处理器支持4种调用方式.

**`16位相对近调用`**

`近调用`的意思是被调用的目标过程位于当前代码段内,而非另一
个不同的代码段,所以只需要得到偏移地址即可。

`16位相对近调用`是3字节指令、操作码为0xE8,后跟16位的操作数.

**`16位间接绝对近调用`**

指令的操作数不是偏移量，而是被调用过程的真实偏移地址.

这个偏移地址不是直接出现在指令中，而是由16位的通用寄存器或者16位的内存单元给出.

它可以调用当前代码段任何位置处的过程.

**`16位直接绝对远调用`**

偏移地址在前，段地址在后.

处理器在执行时,首先将代码段寄存器 CS 的当前内容压栈,接着再把指令指针寄存器 IP 的当
前内容压栈。紧接着,用指令中给出的段地址代替 CS 原有的内容,用指令中给出的偏移地址代替
IP 原有的内容。这直接导致处理器从新的位置开始执行。

**`16位间接绝对远调用`**

间接远调用必须使用关键字**`far`**.

```assembly
call far [0x2000]
call far [proc_1]
call far [bx]
call far [bx+si]
```

## 返回指令

**`ret`**和**`retf`**经常用作**`call`**和**`call far`**的配对指令.

`ret`是近返回指令.

`retf`是远返回指令.

## shr

**`shr`**逻辑右移指令，逻辑右移指令执行时，会将操作数连续地向右移动指定的次数，每移动一次，"挤"出来的比特被移动到标志寄存位`CF`位，左边空出来的位置用比特"0"填充.

```assembly
shr r/m8,1
shr r/m16,1
shr r/m8,imm8
shr r/m16,imm8
shr r/m8,cl
shr r/m16,cl
```

如果**`shr`**的源操作数是寄存器，则只能使用CL.和一般的指令不同，寄存器CL只用来提供移动次数.对于目的操作数是内存地址的情况，必须使用关键字byte或者word等来加以限定.

注意,和 8086 处理器不同,80286 之后的 IA-32 处理器在执行本指令时,会先将源操作数的高
3 位清零。也就是说,最大的移位次数是 31。

与shr配对的指令是逻辑左移**`shl`**.

### ror

循环右移，循环右移指令执行，每右移一次，移出的比特既送到标志寄存器CF位，也送进左边空出的位.

ror的配对指令是循环左移指令rol. **`ror rol shl shr`**的指令格式都是相同的.

## 8086处理器的无条件转移指令

1. **`相对短转移`**

   相对短转移的操作码位0xEB,操作数是相对于目标位置的偏移量，仅一个字节，所以只允许转移到距离当前指令-128～127字节的地方，相对短转移指令必须使用关键字"short".

   相对短转移指令的汇编语言操作数只能是标号和数值.

   ```assembly
   jmp short infinite
   ```

2. **`16位相对近转移`**

   16位相对近转移指令应当使用关键字"near".

   ```assembly
   jmp near infinite
   jmp nar 0x3000
   ```

3. **`16位间接绝对近转移`**

   转移的目标偏移地址不是在指令中直接给出的，而是用一个16位的通用寄存器或者内存地址来间接给出.

   ```assembly
   jmp near bx
   jmp near cx
   ```

4. **`16位直接绝对远转移`**

   16位仅仅用来限定偏移地址部分，指偏移地址是16位的.

   ```assembly
   jmp 0x0000:0x7c00
   ```

5. **`16位间接绝对远转移`**(jmp far)

   ```assembly
   jmp far [bx]
   jmp far [bx+si]
   ```

## 保留字节

**`resb resw resd`**是从当前的字节开始，保留指定数量的字节，但不初始化他们的值。在源程序编译时，编译器会保留一段内存区域，用来存放编译后的内容。

当看到这条指令时，他仅仅只是跳过指定数量的字节，而不管里面的原始内容.内存是反复使用的,谁也无法知道以前的使用者在这里留下了什么。也就是说,跳过的这段空间,每个字节的值是不确定的

`resb`保留字节    `resw`保留字    `resd`保留双字

**实模式下，堆栈的空间最大是64KB,每执行一次过程调用需要2字节或者是4字节.**

## mul

**`mul`**和**`div`**相反，mul是乘法指令.

```assembly
mul r/m8                                 ;AX = L*r/m8
mul r/m16                                ;DX:AX = AX*r/m16
```

“r”表示通用寄存器,“m”表示内存单元。就是说,mul 指令可以用 8 位的通用寄存器
或者内存单元中的数和寄存器 AL 中的内容相乘,结果是 16 位,在 AX 寄存器中;也可以用 16 位
的通用寄存器或者内存单元中的数和寄存器 AX 中的内容相乘,结果是 32 位,高 16 位和低 16 位
分别在 DX 和 AX 中

## 信号引线

**`NMI(非屏蔽中断)    INTR`**

Intel处理器规定，NMI中断信号由0跳到1后，至少要维持4个以上的时钟周期才算是有效的，才能够被识别.

几乎所有出发**`NMI`**的事件对处理器来说都是致命的，甚至是不可纠正的.

NMI被赋予了统一的中断号2.一旦发生二号中断，处理器和软件通常会放弃正常工作"念头".

## IMR

**`IMR`**中断屏蔽寄存器.8位寄存器，对应着该芯片的8个中断输入引脚，对应的位是0还是1,决定该引脚来中断信号是否能够通过8259送往处理器.

中断的最终控制权在处理器手上，处理器内部，标志寄存器有一个标志位IF,这就是中断标志，如果为1,处理器可以接受和响应中断.

**`CLI`**用于清除IF标志位，**`sti`**用于置位IF标志.

总体上来说,中断的优先级和引脚是相关的,主片的 IR0 引脚优先级最高,IR7
引脚最低,从片也是如此。当然,还要考虑到从片是级联在主片的 IR2 引脚上。
最后,当一个中断事件正在处理时,如果来了一个优先级更高的中断事件时,允许暂时中止当
前的中断处理,先为优先级较高的中断事件服务,这称为中断嵌套。

## BCD编码

一个字节的高四位、低四位分别表示一个十进制数.

用BCD编码的数，高四位和低四位都不允许大于1001.
