%合成某一帧的语音
function [NewData, zi_out, NextPaddingHeadLen] = Synthesize(...
    BaseFreq, ...          %基音频率
    LPCcoefficients, ...   %LPC系数
    zi, ...                %h(n)的零状态响应
    Error, ...             %预测误差方差
    SampleFreq, ...        %采样频率
    DataLen, ...           %数据点数
    PaddingHeadLen...     %第一个脉冲前的空白长度
)

    BaseWaveLen = round(1/BaseFreq*SampleFreq);   %基波长度（点数）
    G = sqrt(Error*BaseWaveLen);                  %脉冲的能量
     
    NewData = zeros(DataLen, 1);
    
    %如果基波长度大于帧长，就不产生脉冲序列
    if 1+PaddingHeadLen>DataLen
        NextPaddingHeadLen = 0;
        zi_out = zeros(length(zi), 1);
        return;
    end
    
    %产生脉冲序列作为激励源
    for n = 1+PaddingHeadLen : BaseWaveLen : DataLen
        NewData(n) = G;
    end
    
    %合成语音
    [NewData, zi_out] = filter(1, LPCcoefficients, NewData, zi);

    %计算下一帧第一个脉冲前的空白长度
    NextPaddingHeadLen = BaseWaveLen-(DataLen-n);
    

end