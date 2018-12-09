function filtereddata=BandPassFilter(data,samplefreq,freq_c1,freq_c2)
    spectrum=fft(data);
    nmax=length(spectrum);
    ratio1=freq_c1/samplefreq;
    ratio2=freq_c2/samplefreq;
    middle=floor(nmax/2);
    nthreshold1=floor(ratio1*middle);
    nthreshold2=floor(ratio2*middle);
    
    
    H1=zeros(nmax,1);
    H2=zeros(nmax,1);
    
    H1(1:nthreshold1)=0;
    H1(nthreshold1+1:nmax-nthreshold1-1)=1;
    H1(nmax-nthreshold1:nmax)=0;
    
    H2(1:nthreshold2)=1;
    H2(nthreshold2+1:nmax-nthreshold2-1)=0;
    H2(nmax-nthreshold2:nmax)=1;
    
    filtereddata=real(ifft(spectrum.*H1.*H2));
end