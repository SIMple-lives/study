% 读取Excel表格，并保留原始列标题
opts = detectImportOptions('螺线坐标.xlsx', 'Sheet', 'Sheet1');
opts.VariableNamingRule = 'preserve'; % 保留原始列标题
dataTable = readtable('螺线坐标.xlsx', opts);

% 检查列名以确保坐标数据存储在正确的列
if ismember('X', dataTable.Properties.VariableNames) && ismember('Y', dataTable.Properties.VariableNames)
    % 将坐标从单元格数组转换为数字
    x = str2double(dataTable.X); % 读取 X 坐标数据并转换为数字
    y = str2double(dataTable.Y); % 读取 Y 坐标数据并转换为数字
else
    % 如果列名不是预期的，可以使用列索引
    x = str2double(table2array(dataTable(:, 3))); % 读取第三列数据并转换为数字
    y = str2double(table2array(dataTable(:, 4))); % 读取第四列数据并转换为数字
end

% 过滤掉包含 NaN 的行
valid_rows = ~isnan(x) & ~isnan(y);
x = x(valid_rows);
y = y(valid_rows);

% 将坐标存储到一个数组中
coordinatesArray = [x, y];

% 创建一个空的表格来存储每次循环的余弦值
numIterations = size(coordinatesArray, 1);
cosineValuesTable = table();

% 遍历坐标数组并调用 plot_spiral_and_intersections 函数
for i = 1:numIterations
    % 从数组中提取单个点的坐标
    x_A = coordinatesArray(i, 1); 
    y_A = coordinatesArray(i, 2);
    
    plot_spiral_and_intersections(x_A, y_A)
   
end 

function plot_spiral_and_intersections(x_A, y_A)
    % 参数设置
    p = 55; % 螺距为55cm
    b = p / (2 * pi); % 计算 b
    theta_max = 40 * pi; % 20圈的最大角度

    % 计算终点E和终点F的极角
    theta_E = 32 * pi;
    theta_F = theta_max;

    % 计算螺线长度的函数
    L_theta = @(theta) (b / 2) * (theta .* sqrt(1 + theta.^2) + log(theta + sqrt(1 + theta.^2)));

    % 计算终点E和终点F的长度
    L_E = L_theta(theta_E);
    L_F = L_theta(theta_F);

    % 计算点A的极角 theta_A
    L_A_target = L_E - 30000; % 转换为cm
    theta_A = fzero(@(theta) L_theta(theta) - L_A_target, theta_E);

    % 计算点A的极径和坐标
    r_A = b * theta_A;

    % 绘制扩展后的阿基米德螺线
    theta = linspace(0, theta_max, 10000); % 增加点的数量以提高精度
    r = b * theta;
    x = r .* cos(theta);
    y = r .* sin(theta);

    figure;
    %plot(x, y, 'b', 'LineWidth', 1.5);
    hold on;
    axis equal; % 确保 x 和 y 轴比例一致

    % 标记终点E
    r_E = b * theta_E;
    x_E = r_E * cos(theta_E);
    y_E = r_E * sin(theta_E);
    %plot(x_E, y_E, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
    %text(x_E, y_E, 'E', 'FontSize', 12, 'HorizontalAlignment', 'right');

    % 标记终点F
    r_F = b * theta_F;
    x_F = r_F * cos(theta_F);
    y_F = r_F * sin(theta_F);
    %plot(x_F, y_F, 'bo', 'MarkerSize', 8, 'MarkerFaceColor', 'b');
    %text(x_F, y_F, 'F', 'FontSize', 12, 'HorizontalAlignment', 'right');

    % 标记点A
    %plot(x_A, y_A, 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'g'); % 点A用绿色圆点表示
    %text(x_A, y_A, 'A', 'FontSize', 12, 'HorizontalAlignment', 'right');

    % 以点A为圆心，半径R=286cm，绘制圆
    R = 286;
    theta_circle = linspace(0, 2 * pi, 1000);
    x_circle = x_A + R * cos(theta_circle);
    y_circle = y_A + R * sin(theta_circle);
    %plot(x_circle, y_circle, 'm--', 'LineWidth', 1.5);

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
        %plot(x_max, y_max, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k');
        %text(x_max, y_max, 'P_{max}', 'FontSize', 12, 'HorizontalAlignment', 'right');
        
        % 从点A到最大交点绘制连线
        %plot([x_A, x_max], [y_A, y_max], 'k--', 'LineWidth', 1.5);
        % 计算连线中点位置
        mid_x = (x_A + x_max) / 2;
        mid_y = (y_A + y_max) / 2;
        % 添加连线编号
        %text(mid_x, mid_y, '1', 'FontSize', 12, 'HorizontalAlignment', 'center', 'BackgroundColor', 'w');
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

            %plot(x(max_n_I), y(max_n_I), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
            %text(x(max_n_I), y(max_n_I), 'P_{new}', 'FontSize', 12, 'HorizontalAlignment', 'right');
            %fprintf('新交点坐标: (%.2f, %.2f)\n', x(max_n_I), y(max_n_I));
            
            % 从前一个交点到当前交点绘制连线
            if length(x_max_i) > 1
                %plot([x_max_i(end-1), x_max_i(end)], [y_max_i(end-1), y_max_i(end)], 'k--', 'LineWidth', 1.5);
                % 计算连线中点位置
                mid_x = (x_max_i(end-1) + x_max_i(end)) / 2;
                mid_y = (y_max_i(end-1) + y_max_i(end)) / 2;
                % 添加连线编号
                %text(mid_x, mid_y, sprintf('%d', length(x_max_i) - 1), 'FontSize', 12, 'HorizontalAlignment', 'center', 'BackgroundColor', 'w');
            end
        else
            fprintf('未找到有效交点 (iteration %d).\n', i);
        end
    end

    % 计算相邻连线夹角的余弦值
    cos_values = [];
    for i = 1:length(x_max_i)-2
        % 连线向量
        v1 = [x_max_i(i+1) - x_max_i(i), y_max_i(i+1) - y_max_i(i)];
        v2 = [x_max_i(i+2) - x_max_i(i+1), y_max_i(i+2) - y_max_i(i+1)];

        % 向量点积
        dot_product = dot(v1, v2);

        % 向量模长
        norm_v1 = norm(v1);
        norm_v2 = norm(v2);

        % 计算余弦值
        cos_theta = dot_product / (norm_v1 * norm_v2);
        cos_values = [cos_values; cos_theta];
    end

    % 创建仅包含余弦值的表格
    T = array2table(cos_values, 'VariableNames', {'CosineValue'});

    % 写入 Excel 文件，只写入余弦值
    % 写入 Excel 文件，追加余弦值到文件中
    writetable(T, 'cosine.xlsx', 'WriteMode', 'append');


    % 打印余弦值到命令窗口
    for i = 1:size(cos_values, 1)
        fprintf('连线 %d 和 %d 之间的夹角余弦值: %.2f\n', i, i+1, cos_values(i));
    end

    % 关闭保持图像
    hold off;
end
