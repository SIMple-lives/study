% 参数设置
S = 55 / (2 * pi); % 螺距为 55 cm
F = 0; % 设置 a 为 0，这样螺线从原点开始
spacing = linspace(0, 32 * pi, 10000); % 设置 θ 的范围，增加点的密度以提高精度

% 极坐标方程
r = F + S * spacing;

% 转换为直角坐标
x = r .* cos(spacing);
y = r .* sin(spacing);

% 定义 dx/dtheta 和 dy/dtheta
dr_dF = S; % 因为 r = a + b*theta，所以 dr/dtheta = b
dx_dF = dr_dF * cos(spacing) - r .* sin(spacing);
dy_dF = dr_dF * sin(spacing) + r .* cos(spacing);

% 计算每小段的弧长 ds = sqrt((dx/dtheta)^2 + (dy/dtheta)^2) * dtheta
ds = sqrt(dx_dF(1:end-1).^2 + dy_dF(1:end-1).^2) .* diff(spacing); % 使用 diff(theta) 计算 dtheta
s = [0, cumsum(ds)]; % 螺线的累计弧长

% 打印螺线总弧长
total_length = s(end);
fprintf('螺线总弧长: %.2f cm\n', total_length);

% 找到从终点开始每隔1米处的点
distance_interval = 100; % 1米 = 100 cm
num_points = floor(s(end) / distance_interval); % 计算总共需要多少个点
target_distances = s(end) - (0:num_points-1) * distance_interval; % 从终点反向计算目标距离

% 只选择300个点
num_plot_points = min(num_points, 300); % 确保不超过300个点
target_distances = target_distances(1:num_plot_points);

% 绘制螺线
figure;
hold on;
plot(x, y, 'b', 'LineWidth', 1.5); % 绘制螺线

% 绘制起始点
plot(x(1), y(1), 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k'); % 用黑色标记起始点

% 绘制从终点开始每隔1米的点
for i = 1:num_plot_points
    idx = find(s >= target_distances(i), 1); % 找到最接近目标距离的索引
    plot(x(idx), y(idx), 'ro', 'MarkerSize', 6, 'MarkerFaceColor', 'r'); % 在螺线上绘制点
end

% 绘制终点
plot(x(end), y(end), 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'g'); % 用绿色标记终点

title('阿基米德等距螺线及从终点开始的标记点');
xlabel('x (cm)');
ylabel('y (cm)');
axis equal;
grid on;
hold off;
