%计算共振峰搬移后的LPC系数
function NewLPCcoefficients = ChangeResonantPeaks( ...
    LPCcoefficients, ...    %当前LPC系数
    DeltaOmega ...          %将共振峰向左/向右搬移
)
    
    Roots = roots(LPCcoefficients);   %H(z)的极点
    
    %搬移极点
    for n = 1 : length(Roots)
        if imag(Roots(n))>0
            Roots(n) = Roots(n)*exp(1j*DeltaOmega);
        elseif imag(Roots(n))<0
            Roots(n) = Roots(n)*exp(-1j*DeltaOmega);
        end
    end
    
    %新的LPC系数
    NewLPCcoefficients = poly(Roots);

end