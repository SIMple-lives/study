H_s% 参数初始化
clear;
H_S_L = 2.86; % 头部片段长度
B_S_l = 1.65; % 身体片段长度
S_w = 0.30; % 片段宽度
half_S_w = S_w * 0.5; % 内外偏移量
S_p = 0.55; % 螺旋的间距
H_s = 1; % 头部运动速度
I_a_t = 16 * 2 * pi; % 初始角度θ
t_s_t = 440; % 总模拟时间
n_b_s = 223; % 身体片段数

% 计算头部初始半径及角速度
i_r_o_h = S_p * I_a_t / (2 * pi);
a_v_o_h = H_s / i_r_o_h;

% 数据存储结构体
segment_positions = struct('x_coord', [], 'y_coord', [], 'x_inner_coord', [], 'y_inner_coord', [], 'x_outer_coord', [], 'y_outer_coord', []);

% 遍历每个时间步长并计算每个部分的位置
for current_time = 0:t_s_t
    current_angle = I_a_t - a_v_o_h * current_time;
    current_head_radius = S_p * current_angle / (2 * pi);

    % 计算头部的位置
    [x_head_coord, y_head_coord, x_head_inner_coord, y_head_inner_coord, x_head_outer_coord, y_head_outer_coord] = compute_segment_position(current_angle, current_head_radius, half_S_w);
    
    % 存储头部数据
    segment_positions(current_time+1).x_coord = [x_head_coord];
    segment_positions(current_time+1).y_coord = [y_head_coord];
    segment_positions(current_time+1).x_inner_coord = [x_head_inner_coord];
    segment_positions(current_time+1).y_inner_coord = [y_head_inner_coord];
    segment_positions(current_time+1).x_outer_coord = [x_head_outer_coord];
    segment_positions(current_time+1).y_outer_coord = [y_head_outer_coord];

    % 当前角度和半径
    temp_angle = current_angle;
    temp_radius = current_head_radius;

    % 计算身体各部分的位置
    for segment_idx = 2:n_b_s
        if segment_idx == 2
            arc_length = H_S_L;
        else
            arc_length = B_S_l;
        end
        delta_angle = arc_length / temp_radius;
        temp_angle = temp_angle + delta_angle;
        temp_radius = S_p * temp_angle / (2 * pi);

        [x_segment_coord, y_segment_coord, x_inner_segment_coord, y_inner_segment_coord, x_outer_segment_coord, y_outer_segment_coord] = compute_segment_position(temp_angle, temp_radius, half_S_w);
        
        % 存储身体各片段的位置数据
        segment_positions(current_time+1).x_coord = [segment_positions(current_time+1).x_coord, x_segment_coord];
        segment_positions(current_time+1).y_coord = [segment_positions(current_time+1).y_coord, y_segment_coord];
        segment_positions(current_time+1).x_inner_coord = [segment_positions(current_time+1).x_inner_coord, x_inner_segment_coord];
        segment_positions(current_time+1).y_inner_coord = [segment_positions(current_time+1).y_inner_coord, y_inner_segment_coord];
        segment_positions(current_time+1).x_outer_coord = [segment_positions(current_time+1).x_outer_coord, x_outer_segment_coord];
        segment_positions(current_time+1).y_outer_coord = [segment_positions(current_time+1).y_outer_coord, y_outer_segment_coord];
    end
end

% 绘制螺旋轨迹
theta_values = linspace(0, I_a_t, 1000);
radius_values = S_p * theta_values / (2 * pi);
x_spiral_path = radius_values .* cos(theta_values);
y_spiral_path = radius_values .* sin(theta_values);

% 用户输入时间点
input_time = input('输入time:');

if input_time > t_s_t || input_time < 0
    error('出错');
end

% 绘制位置图
figure;
hold on;
plot(x_spiral_path, y_spiral_path, 'b', 'LineWidth', 1.5);
plot(segment_positions(input_time+1).x_inner_coord, segment_positions(input_time+1).y_inner_coord, '-o');
plot(segment_positions(input_time+1).x_outer_coord, segment_positions(input_time+1).y_outer_coord, '-o');
title(['时间点', num2str(input_time), ' 秒的位置']);
xlabel('x 轴 (米)');
ylabel('y 轴 (米)');
grid on;

% 显示位置数据
disp('时间点: ');
disp(input_time);
disp('位置数据：');
disp([segment_positions(input_time+1).x_coord; segment_positions(input_time+1).y_coord]);

% 将函数定义放在文件末尾
function [x, y, x_inner, y_inner, x_outer, y_outer] = compute_segment_position(angle, radius, offset)
    inner_radius = radius - offset;
    outer_radius = radius + offset;
    x = radius * cos(angle);
    y = radius * sin(angle);
    x_inner = inner_radius * cos(angle);
    y_inner = inner_radius * sin(angle);
    x_outer = outer_radius * cos(angle);
    y_outer = outer_radius * sin(angle);
end
