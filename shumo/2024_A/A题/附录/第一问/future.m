% 参数设置
p = 55; % 螺距为55cm
b = p / (2 * pi); % 计算 b
theta_max = 32 * pi; % 16圈的最大角度

% 计算终点E的极角
theta_E = theta_max;

% 定义螺线长度的函数
L_theta = @(theta) (b / 2) * (theta .* sqrt(1 + theta.^2) + log(theta + sqrt(1 + theta.^2)));

% 计算终点E的长度
L_E = L_theta(theta_E);
 
% 计算点A的极径和坐标
r_A = b * theta_A;
x_A = r_A * cos(theta_A);
y_A = r_A * sin(theta_A);

% 绘制阿基米德螺线
theta = linspace(0, theta_max, 10000); % 增加点的数量以提高精度
r = b * theta;
x = r .* cos(theta);
y = r .* sin(theta);

figure;
plot(x, y, 'b', 'LineWidth', 1.5);
hold on;

% 标记终点E
r_E = b * theta_E;
x_E = r_E * cos(theta_E);
y_E = r_E * sin(theta_E);
plot(x_E, y_E, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
text(x_E, y_E, 'E', 'FontSize', 12, 'HorizontalAlignment', 'right');

% 标记点A
plot(x_A, y_A, 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'g'); % 点A用绿色圆点表示
text(x_A, y_A, 'A', 'FontSize', 12, 'HorizontalAlignment', 'right');

% 以点A为圆心，半径R=286cm，绘制圆
R = 286;
theta_circle = linspace(0, 2 * pi, 1000);
x_circle = x_A + R * cos(theta_circle);
y_circle = y_A + R * sin(theta_circle);
plot(x_circle, y_circle, 'm--', 'LineWidth', 1.5);

% 求解交点
intersection_indices = [];
for i = 1:length(x) - 1
    d1 = sqrt((x(i) - x_A)^2 + (y(i) - y_A)^2) - R;
    d2 = sqrt((x(i+1) - x_A)^2 + (y(i+1) - y_A)^2) - R;
    if d1 * d2 < 0
        intersection_indices = [intersection_indices, i];
    end
end

% 计算点A到E的螺线长
L_AE = L_theta(theta_E) - L_theta(theta_A);

% 筛选出满足条件的最大交点
max_length = -inf;
max_index = -1;

for i = 1:length(intersection_indices)
    idx = intersection_indices(i);
    theta_intersection = theta(idx); % 直接用角度值计算
    L_intersection = L_theta(theta_E) - L_theta(theta_intersection);

    if L_intersection < L_AE && L_intersection > max_length
        max_length = L_intersection;
        max_index = idx;
    end
end

% 打印出该交点的信息
if max_index > 0
    x_max = x(max_index);
    y_max = y(max_index);
    fprintf('最大交点坐标: (%.2f, %.2f)\n', x_max, y_max);

    % 标记满足条件的最大交点
    plot(x_max, y_max, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k');
    text(x_max, y_max, 'P_{max}', 'FontSize', 12, 'HorizontalAlignment', 'right');
end

% 初始化数组
x_max_i = [];
y_max_i = [];
x_index = [];

% 添加初始最大交点
if max_index > 0
    x_max_i(1) = x_max;
    y_max_i(1) = y_max;
    x_index(1) = max_index;
end

% 设置迭代次数
n = 222;
R_circle = 165; % 圆的半径

for i = 1:n
    % 确保索引 i 在数组范围内
    if i > length(x_max_i)
        error('Index i exceeds the number of elements in x_max_i.');
    end

    % 以新交点为圆心绘制新圆
    x_circle_new = x_max_i(i) + R_circle * cos(theta_circle);
    y_circle_new = y_max_i(i) + R_circle * sin(theta_circle);
    % plot(x_circle_new, y_circle_new, 'c--', 'LineWidth', 1.5);

    % 求解新圆的交点
    new_I_i = [];
    for j = 1:length(x) - 1
        if (sqrt((x(j) - x_max_i(i))^2 + (y(j) - y_max_i(i))^2) - R_circle) * ...
           (sqrt((x(j+1) - x_max_i(i))^2 + (y(j+1) - y_max_i(i))^2) - R_circle) < 0
            new_I_i = [new_I_i, j];
        end
    end

    % 筛选新交点
    max_n_l = -inf;
    max_n_I = -1;
    if i <= length(x_index) % Ensure index is valid
        ce_t_E_d = L_theta(theta_E) - L_theta(theta(x_index(i)));
    else
        ce_t_E_d = L_theta(theta_E) - L_theta(theta_A); % Fallback value
    end

    for j = 1:length(new_I_i)
        index = new_I_i(j);
        L_new = L_theta(theta_E) - L_theta(theta(index));
        if L_new < ce_t_E_d && L_new > max_n_l
            max_n_l = L_new;
            max_n_I = index;
        end
    end

    % 更新最大交点坐标
    if max_n_I > 0
        % 扩展数组
        x_max_i(end + 1) = x(max_n_I);
        y_max_i(end + 1) = y(max_n_I);
        x_index(end + 1) = max_n_I;

        plot(x(max_n_I), y(max_n_I), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
        text(x(max_n_I), y(max_n_I), 'P_{new}', 'FontSize', 12, 'HorizontalAlignment', 'right');
        fprintf('新交点坐标: (%.2f, %.2f)\n', x(max_n_I), y(max_n_I));
    else
        fprintf('未找到有效交点 (iteration %d).\n', i);
    end
end

% 设置图形比例、标题和图例
axis equal;
title('螺线及交点');
xlabel('X (cm)');
ylabel('Y (cm)');
grid on;
hold off;