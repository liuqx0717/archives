%����
function NewData = ProcessVoice( ...
    data, ...                  %��Ƶ�ź�
    SampleFreq, ...            %����Ƶ��(Hz)
    BaseFreqRatio, ...         %��Ƶ��Ϊԭ���Ķ��ٱ�
    DeltaResonantPeakFreq ...  %������ƶ�����Hz��������Ϊ����
)

    %һЩ�������趨��
    
    %֡�ĳ��ȣ��룩
    FrameLen = 0.01;  
    
    %����ĳһ֡LPCϵ������Ƶʱ����֡���ܸ���
    nLPCframes = 5;
    
    %LPC����
    LPCorder = 20;
    
    %����ƽ���˲�������С
    MovingAverageFilterWindowSize = 3;
    
    
    
    %���ݵĳ�ʼ����
    
    %��Ƶ���ݵĸ���
    nMax = length(data);
    
    %ÿһ֡�����ĵ���
    FrameLen = floor(SampleFreq*FrameLen);
    
    %����ĳһ֡LPCϵ������Ƶʱ����֡���ܵ���
    LPCframeLen = nLPCframes*FrameLen;
    
    %��Ҫ�����֡��
    nFrames = floor(nMax/FrameLen)-nLPCframes+1;
    
    %��ʼ������ֵ(�ϳ���������)
    NewData = zeros(nMax, 1);
    
    %������
    HammingWindow = hamming(LPCframeLen);
    
    %ÿһ֡�Ļ���Ƶ��(Hz)
    BaseWaveFreqs = zeros(nFrames-nLPCframes, 1);
    
    %Ԥ��������ڼ�����Ƶ�ϳ�ʱ����Դ�����Ĵ�С
    Errors = zeros(nFrames-nLPCframes, 1);
    
    %��Ƶ�ϳ�ʱh(n)����������Ӧ
    ziForSynthesize = zeros(LPCorder, 1);
    
    %��һ֡����Դ�ĵ�һ���������Ŀհ״�С
    NextPaddingHeadLen = 0;
    
    %ÿһ֡��LPCϵ��
    LPCcoefficients = zeros(nFrames-nLPCframes, LPCorder+1);

    
    %��ȡÿһ֡�Ļ���Ƶ��
    for n = nLPCframes : nFrames
        
        nLeft = n*FrameLen-LPCframeLen+1;    %��֡��ߵĶ˵�λ��
        nRight = n*FrameLen;                 %��֡�ұߵĶ˵�λ��
        
        %��֡��ǰ�����ɸ�֡�Ӵ�
        LPCframe = data(nLeft : nRight).*HammingWindow;
        
        %�����֡��LPCϵ������Ҫ�õ���֡�����Լ���֡��ǰ�漸��֡��
        [tmpLPCcoefficients, Errors(n)] = lpc(LPCframe, LPCorder);  

        %��ϵ���е�NaN����0
        tmpLPCcoefficients(~(abs(tmpLPCcoefficients)>0)) = 0;
        
        %����LPCcoefficients�ĵ�n��
        LPCcoefficients(n, : ) = tmpLPCcoefficients;

        %���Errors(n)ΪNaN�����任��0
        if ~(abs(Errors(n))>0)
            Errors(n) = 0;
        end
        
        %�����֡�Ļ���Ƶ�ʣ���Ҫ�õ���֡�����Լ���֡��ǰ�漸��֡��
        BaseWaveFreqs(n) = GetBaseFreq(data(nLeft : nRight), SampleFreq); 

    end

    
    %ȥ������Ұ��
    BaseWaveFreqs = Smooth(BaseWaveFreqs);
    BaseWaveFreqs = MovingAverageFilter( ...
        BaseWaveFreqs, ...
        MovingAverageFilterWindowSize ...
    );

    
    %ʹ��ƽ���������Ļ���Ƶ�ʺϳ�����
    for n = nLPCframes : nFrames

        %���ƹ������µ�LPCϵ��
        NewLPCcoefficients = ChangeResonantPeaks(...
            LPCcoefficients(n, : ), ...
            DeltaResonantPeakFreq*2*pi/SampleFreq...
        );

        %�ϳɴ�֡����
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

        %�Ѵ�֡��������ϳ�����������
        NewData((n-1)*FrameLen+1 : n*FrameLen) = NewFrameData;
    end


end
