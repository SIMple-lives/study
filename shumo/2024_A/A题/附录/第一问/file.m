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

% 将坐标存储到一个数组中
coordinatesArray = [x, y];
% 遍历坐标数组并调用 plot_spiral_and_intersections 函数
for i = 1:size(coordinatesArray, 1)
    % 从数组中提取单个点的坐标
    x_A = coordinatesArray(i, 1); 
    y_A = coordinatesArray(i, 2);
    

    % 调用绘图函数
    plot_spiral_and_intersections(x_A, y_A);

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

    % 计算阿基米德螺线
    theta = linspace(0, theta_max, 10000); % 增加点的数量以提高精度
    r = b * theta;
    x = r .* cos(theta);
    y = r .* sin(theta);

    % 求解交点
    intersection_indices = [];
    R = 286; % 半径
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

    % 初始化数组
    x_max_i = [];
    y_max_i = [];
    x_index = [];

    % 添加初始最大交点
    if max_index > 0
        x_max_i(1) = x(max_index);
        y_max_i(1) = y(max_index);
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
        x_circle_new = x_max_i(i) + R_circle * cos(linspace(0, 2 * pi, 1000));
        y_circle_new = y_max_i(i) + R_circle * sin(linspace(0, 2 * pi, 1000));

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
        end
    end

    % 保存交点到Excel文件
    if ~isempty(x_max_i)
        % Combine x and y coordinates into a single column
        coordinates = [];
        for i = 1:length(x_max_i)
            coordinates = [coordinates; x_max_i(i); y_max_i(i)];
        end
        
        % Create a table with a single column
        data = table(coordinates, 'VariableNames', {'Coordinates'});
        
        % Append data to Excel file
        writetable(data, 'intersection_points.xlsx', 'WriteMode', 'append');
    end
end

