%�ϳ�ĳһ֡������
function [NewData, zi_out, NextPaddingHeadLen] = Synthesize(...
    BaseFreq, ...          %����Ƶ��
    LPCcoefficients, ...   %LPCϵ��
    zi, ...                %h(n)����״̬��Ӧ
    Error, ...             %Ԥ������
    SampleFreq, ...        %����Ƶ��
    DataLen, ...           %���ݵ���
    PaddingHeadLen...     %��һ������ǰ�Ŀհ׳���
)

    BaseWaveLen = round(1/BaseFreq*SampleFreq);   %�������ȣ�������
    G = sqrt(Error*BaseWaveLen);                  %���������
     
    NewData = zeros(DataLen, 1);
    
    %����������ȴ���֡�����Ͳ�������������
    if 1+PaddingHeadLen>DataLen
        NextPaddingHeadLen = 0;
        zi_out = zeros(length(zi), 1);
        return;
    end
    
    %��������������Ϊ����Դ
    for n = 1+PaddingHeadLen : BaseWaveLen : DataLen
        NewData(n) = G;
    end
    
    %�ϳ�����
    [NewData, zi_out] = filter(1, LPCcoefficients, NewData, zi);

    %������һ֡��һ������ǰ�Ŀհ׳���
    NextPaddingHeadLen = BaseWaveLen-(DataLen-n);
    

end