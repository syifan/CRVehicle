function [ time, utilization ] = parse_noia( filename )
%PARSE_NOIA Summary of this function goes here
%   Detailed explanation goes here

    time = [];
    utilization = [];
    slotused = 0;
    carcovered = 0;

    i = 1;
    logFile = fopen(strcat('../',filename,'.log'));
    tline = fgetl(logFile);
    while ischar(tline)
        tokens = strsplit(tline);
        if(strcmp(tokens(3), 'query_database'))
            slotused = slotused + 2;
        elseif(strcmp(tokens(3), 'broadcast_correlation'))
            slotused = slotused + 1;
        elseif(strcmp(tokens(3), 'channel_found'))
            carcovered = carcovered+1;
            time(i) = str2double(tokens(1));
            utilization(i) = slotused; 
            i = i+1;
        end

        tline = fgetl(logFile);
    end

end

