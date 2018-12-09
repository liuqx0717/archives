%���㹲�����ƺ��LPCϵ��
function NewLPCcoefficients = ChangeResonantPeaks( ...
    LPCcoefficients, ...    %��ǰLPCϵ��
    DeltaOmega ...          %�����������/���Ұ���
)
    
    Roots = roots(LPCcoefficients);   %H(z)�ļ���
    
    %���Ƽ���
    for n = 1 : length(Roots)
        if imag(Roots(n))>0
            Roots(n) = Roots(n)*exp(1j*DeltaOmega);
        elseif imag(Roots(n))<0
            Roots(n) = Roots(n)*exp(-1j*DeltaOmega);
        end
    end
    
    %�µ�LPCϵ��
    NewLPCcoefficients = poly(Roots);

end