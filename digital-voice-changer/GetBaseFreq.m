%��ȡ����Ƶ��
function basefreq = GetBaseFreq(data, SampleFreq)

    freq_c1 = 0;          %��ͨ�˲�����ֹƵ��
    freq_c2 = 1000;       %��ͨ�˲�����ֹƵ��
    resamplefreq = 8000;  %�ز���Ƶ��
    
    %��ͨ�˲�
    FiltereDdata = BandPassFilter(data, SampleFreq, freq_c1, freq_c2);
    
    nMax = length(FiltereDdata);      %�����ܳ���
    n_add = SampleFreq/resamplefreq;  %�������
    nMax2 = floor((nMax-1)/n_add);    %�ز��������ܳ���
    ResampledData = zeros(nMax2, 1);   %�ز���������
    
    %�ز���
    for n = 1 : nMax2
        ResampledData(n) = FiltereDdata(round(1+(n-1)*n_add));
    end

    %���ز�����������ȡ����Ƶ��
    basefreq = base_GetBaseFreq(ResampledData, resamplefreq);

    
end


function basefreq = base_GetBaseFreq(data, samplefreq)

    nMax = length(data);           %�����ܳ���
    kmax = floor(0.64*nMax);       %����������
    kmin = 20*samplefreq/8000;     %�������С���

    R = zeros(kmax, 1);
    for k = kmin : kmax
        R(k) = data(kmax+1 : nMax)'*data(kmax+1-k : nMax-k);
    end
    [R1, T1] = max(R(floor(0.56*kmax) : kmax));
    T1 = T1+floor(0.56*kmax)-1;
    R1 = R1/(norm(data(kmax+1-T1 : nMax-T1))+1);
    [R2, T2] = max(R(floor(0.28*kmax) : floor(0.56*kmax)-1));
    T2 = T2+floor(0.28*kmax)-1;
    R2 = R2/(norm(data(kmax+1-T2 : nMax-T2))+1);
    [R3, T3] = max(R(floor(0.14*kmax) : floor(0.28*kmax)));
    T3 = T3+floor(0.14*kmax)-1;
    R3 = R3/(norm(data(kmax+1-T3 : nMax-T3))+1);
    Top = T1;
    Rop = R1;
    if R2>= 0.85*Rop
        Rop = R2;
        Top = T2;
    end
    if R3>0.85*Rop
        Rop = R3;
        Top = T3;
    end
    basefreq = samplefreq/Top;
    return

end