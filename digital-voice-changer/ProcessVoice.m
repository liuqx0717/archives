%变声
function NewData = ProcessVoice( ...
    data, ...                  %音频信号
    SampleFreq, ...            %采样频率(Hz)
    BaseFreqRatio, ...         %基频变为原来的多少倍
    DeltaResonantPeakFreq ...  %共振峰移动多少Hz（以向右为正）
)

    %一些常数的设定：
    
    %帧的长度（秒）
    FrameLen = 0.01;  
    
    %计算某一帧LPC系数、基频时所需帧的总个数
    nLPCframes = 5;
    
    %LPC阶数
    LPCorder = 20;
    
    %滑动平均滤波器窗大小
    MovingAverageFilterWindowSize = 3;
    
    
    
    %数据的初始化：
    
    %音频数据的个数
    nMax = length(data);
    
    %每一帧包含的点数
    FrameLen = floor(SampleFreq*FrameLen);
    
    %计算某一帧LPC系数、基频时所需帧的总点数
    LPCframeLen = nLPCframes*FrameLen;
    
    %需要处理的帧数
    nFrames = floor(nMax/FrameLen)-nLPCframes+1;
    
    %初始化返回值(合成语音数据)
    NewData = zeros(nMax, 1);
    
    %汉明窗
    HammingWindow = hamming(LPCframeLen);
    
    %每一帧的基波频率(Hz)
    BaseWaveFreqs = zeros(nFrames-nLPCframes, 1);
    
    %预测误差方差，用于计算音频合成时激励源能量的大小
    Errors = zeros(nFrames-nLPCframes, 1);
    
    %音频合成时h(n)的零输入响应
    ziForSynthesize = zeros(LPCorder, 1);
    
    %下一帧激励源的第一个脉冲左侧的空白大小
    NextPaddingHeadLen = 0;
    
    %每一帧的LPC系数
    LPCcoefficients = zeros(nFrames-nLPCframes, LPCorder+1);

    
    %获取每一帧的基音频率
    for n = nLPCframes : nFrames
        
        nLeft = n*FrameLen-LPCframeLen+1;    %此帧左边的端点位置
        nRight = n*FrameLen;                 %此帧右边的端点位置
        
        %此帧与前面若干个帧加窗
        LPCframe = data(nLeft : nRight).*HammingWindow;
        
        %计算此帧的LPC系数（需要用到此帧本身以及此帧的前面几个帧）
        [tmpLPCcoefficients, Errors(n)] = lpc(LPCframe, LPCorder);  

        %将系数中的NaN换成0
        tmpLPCcoefficients(~(abs(tmpLPCcoefficients)>0)) = 0;
        
        %存入LPCcoefficients的第n行
        LPCcoefficients(n, : ) = tmpLPCcoefficients;

        %如果Errors(n)为NaN，则将其换成0
        if ~(abs(Errors(n))>0)
            Errors(n) = 0;
        end
        
        %计算此帧的基因频率（需要用到此帧本身以及此帧的前面几个帧）
        BaseWaveFreqs(n) = GetBaseFreq(data(nLeft : nRight), SampleFreq); 

    end

    
    %去除部分野点
    BaseWaveFreqs = Smooth(BaseWaveFreqs);
    BaseWaveFreqs = MovingAverageFilter( ...
        BaseWaveFreqs, ...
        MovingAverageFilterWindowSize ...
    );

    
    %使用平滑处理过后的基因频率合成语音
    for n = nLPCframes : nFrames

        %搬移共振峰后新的LPC系数
        NewLPCcoefficients = ChangeResonantPeaks(...
            LPCcoefficients(n, : ), ...
            DeltaResonantPeakFreq*2*pi/SampleFreq...
        );

        %合成此帧语音
        [NewFrameData, ziForSynthesize, NextPaddingHeadLen] = ...
        Synthesize( ...
            BaseWaveFreqs(n)*BaseFreqRatio, ...
            NewLPCcoefficients, ...
            ziForSynthesize, ...
            Errors(n), ...
            SampleFreq, ...
            FrameLen, ...
            NextPaddingHeadLen ...
        );

        %把次帧语音存入合成语音数据中
        NewData((n-1)*FrameLen+1 : n*FrameLen) = NewFrameData;
    end


end
