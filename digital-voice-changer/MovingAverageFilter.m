%»¬¶¯Æ½¾ùÂË²¨Æ÷
function filtereddata = MovingAverageFilter(data, windowSize)

    b = (1/windowSize)*ones(1, windowSize);
    a = 1;
    
    filtereddata = filter(b, a, data);

end