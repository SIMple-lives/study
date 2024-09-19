% 读取整个Excel表格
dataTable = readtable('intersection_points.xlsx', 'Sheet', 'Sheet1');

% 直接将第三列的数据存入数组
% 假设 dataArray 是读取的数组
dataArray = dataTable{:, 1}; % 读取第一列数据

% 将数组划分为每222个数据为一组
groupSize = 449;
numGroups = ceil(length(dataArray) / groupSize); % 计算分组数量

% 初始化一个空数组来存储重新排列的数据
reshapedData = NaN(groupSize, numGroups); % 用 NaN 填充，避免维度不一致

% 将数据填入 reshapedData 中
for i = 1:numGroups
    startIdx = (i - 1) * groupSize + 1;
    endIdx = min(i * groupSize, length(dataArray));
    reshapedData(1:(endIdx-startIdx+1), i) = dataArray(startIdx:endIdx);
end

% 将数组转换为表格
newTable = array2table(reshapedData);

% 为每一列添加名称
for i = 1:numGroups
    newTable.Properties.VariableNames{i} = ['Column' num2str(i)];
end

% 将表格写入新的 Excel 文件
writetable(newTable, 'nb.xlsx');


