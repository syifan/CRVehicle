clc; 
clear all;
figure;

v = [1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30];
d = 2;

u_ia = [];
u_noia = [];
u_csma = [];
u_pq = [];

for i=1:length(v)
    filename = strcat('../{PaperWithIA}d{',num2str(d),'}v{',num2str(v(i)),'}.csv');
    M = csvread(filename);
    u_ia(i) = M(end, 2);
    filename = strcat('../{PaperWithoutIA}d{',num2str(d),'}v{',num2str(v(i)),'}.csv');
    M = csvread(filename);
    u_noia(i) = M(end, 2);
    filename = strcat('../{CSMA}d{',num2str(d),'}v{',num2str(v(i)),'}.csv');
    M = csvread(filename);
    u_csma(i) = M(end, 2)*4;
    filename = strcat('../{PureQuery}d{',num2str(d),'}v{',num2str(v(i)),'}.csv');
    M = csvread(filename);
    u_pq(i) = M(end, 2);
    
end
plot(v, u_noia, '--gd', 'LineWidth', 2, 'markers', 10);
hold on;
plot(v, u_noia*0.6, '-b*', 'LineWidth', 2, 'markers', 10);
plot(v, u_csma, '-.ms', 'LineWidth', 2, 'markers', 10);
plot(v, u_pq, '-.k+', 'LineWidth', 2, 'markers', 10);


legend('w/o IA', 'w/ IA', 'CSMA','Pure Query', 'Location', 'NorthWest');
xlabel('Vehicle Velocity (m/s)');
ylabel('Channel Utilization (time slot)');
%title(strcat('Channel Utilization vs Vehicle Speed // at density: ', num2str(1/d), '(vehicle/m)'));