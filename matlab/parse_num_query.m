function [ time, num_query ] = parse_num_query( filename )
%PARSE_NUM_QUERY Summary of this function goes here
%   Detailed explanation goes here
    fprintf('Parsing %s\n', strcat('../' , filename , '.log') )
    time = [];
    num_query = [];
    query_used = 0;
    carcovered = 0;

    i = 1;
    logFile = fopen(strcat('../',filename,'.log'));
    tline = fgetl(logFile);
    fprintf('Parsing %s\n', strcat('../' , filename , '.log') )
    while ischar(tline)
        tokens = strsplit(tline);
        if(strcmp(tokens(3), 'query_database'))
            query_used = query_used + 2;
            time(i) = str2double(tokens(1));
            num_query(i) = query_used; 
            i = i+1;
        end

        tline = fgetl(logFile);
    end

end

