% 读取整个Excel表格数据
dataTable = readtable('cosine.xlsx', 'Sheet', 'Sheet1');

% 将数据转换为数组
dataArray = table2array(dataTable);

% 设定分组大小
groupSize = 222;

% 确定有多少完整的组
numGroups = ceil(size(dataArray, 1) / groupSize);

% 预分配一个数组来存储重塑后的数据
reshapedData = NaN(groupSize, numGroups);

% 对数组进行重塑，将每222个数据分为一列
for i = 1:numGroups
    startIdx = (i - 1) * groupSize + 1;
    endIdx = min(i * groupSize, size(dataArray, 1));
    
    reshapedData(1:(endIdx-startIdx+1), i) = dataArray(startIdx:endIdx);
end

% 初始化一个数组来存储每一列的累计乘积结果
resultMatrix = NaN(groupSize, numGroups); % 用 NaN 初始化避免维度不一致

% 对每一列执行累计乘积操作
for col = 1:numGroups
    currentProduct = 1;
    for row = 1:groupSize
        if ~isnan(reshapedData(row, col)) % 忽略 NaN 值
            currentProduct = currentProduct * reshapedData(row, col);
            resultMatrix(row, col) = currentProduct;
        end
    end
end

% 将累计乘积结果转换为表格
resultTable = array2table(resultMatrix);

% 为每一列添加名称
for col = 1:numGroups
    resultTable.Properties.VariableNames{col} = ['Column' num2str(col) '_Product'];
end

% 将结果写入到新的 Excel 文件中
writetable(resultTable, 'updated_cosine_values.xlsx', 'Sheet', 'Sheet1');

% 打印完成信息
disp('累计乘积计算完成，并已写入到 updated_cosine_values.xlsx 文件中。');
