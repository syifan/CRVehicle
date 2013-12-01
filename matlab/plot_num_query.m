clc;
clear all;

figure;

query_ia = [];
query_noia = [];
query_purequery = [];

d = 20;
v = 20;

realData = [1,2,3];
x_axis = [0, -10, -20];


for i=1:1:length(realData)
    filename = strcat('../{PaperWithIA}d{',num2str(d),'}v{',num2str(v),'}r{',num2str(realData(i)),'}.csv');
    M = csvread(filename);
    query_ia(i) = M(end, 3);
    filename = strcat('../{PaperWithoutIA}d{',num2str(d),'}v{',num2str(v),'}r{',num2str(realData(i)),'}.csv');
    M = csvread(filename);
    query_noia(i) = M(end, 3);
    filename = strcat('../{PureQuery}d{',num2str(d),'}v{',num2str(v),'}r{',num2str(realData(i)),'}.csv');
    M = csvread(filename);
    query_csma(i) = M(end, 3);
end
query = [query_csma', query_noia', query_ia'];

set(0,'DefaultAxesFontName', 'Helvetica');
set(0,'DefaultAxesFontSize', 20)
set(0,'DefaultTextFontname', 'Helvetica');
set(0,'DefaultTextFontSize', 20)

bar(x_axis, query);

%title('Number of Queries vs. SNR')
legend('Pure Query', 'w/o IA', 'w/ IA', 'Location', 'SouthEast');
xlabel('Signal to Noise Ratio (dB)');
ylabel('Number of Queries');


[im_hatch, colorlist] = applyhatch_pluscolor(gcf, '\.x', 0, 0, [], 100);


