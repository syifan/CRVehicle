clc; 
clear all;
figure;

d = [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000 ];
v = 20;

u_ia = [];
u_noia = [];
u_csma = [];
u_pq = [];

for i=1:length(d)
    filename = strcat('../{PaperWithIA}d{',num2str(d(i)),'}v{',num2str(v),'}.csv');
    M = csvread(filename);
    u_ia(i) = M(end, 2);
    filename = strcat('../{PaperWithoutIA}d{',num2str(d(i)),'}v{',num2str(v),'}.csv');
    M = csvread(filename);
    u_noia(i) = M(end, 2);
    filename = strcat('../{CSMA}d{',num2str(d(i)),'}v{',num2str(v),'}.csv');
    M = csvread(filename);
    u_csma(i) = M(end, 2)*4;
    filename = strcat('../{PureQuery}d{',num2str(d(i)),'}v{',num2str(v),'}.csv');
    M = csvread(filename);
    u_pq(i) = M(end, 2);
    
end
semilogx(1./flipdim(d,2), flipdim(u_noia,2), '--gd', 'LineWidth', 2, 'markers', 10);
hold on;
semilogx(1./flipdim(d,2), flipdim(u_ia, 2), '-b*', 'LineWidth', 2, 'markers', 10);
semilogx(1./flipdim(d,2), flipdim(u_csma, 2), '-.ms', 'LineWidth', 2, 'markers', 10);
semilogx(1./flipdim(d,2), flipdim(u_pq, 2), '-.k+', 'LineWidth', 2, 'markers', 10);

legend('w/o IA', 'w/ IA', 'CSMA', 'Pure Query', 'Location', 'NorthWest');
xlabel('Vehicle Density (vehicles/m)');
ylabel('Channel Utilization (time slot)');
%title(strcat('Channel Utilization vs Vehicle Density at speed: ', num2str(v), '(m/s)'));
