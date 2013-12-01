clc;
clear all;

figure;
a = char('PaperWithoutIA', 'PaperWithIA', 'PureQuery');
d = 5;
v = 30;
s = 49;
for i = 1:size(a,1)
    filename = strcat('../{',a(i,:),'}d{',num2str(d),'}v{',num2str(v),'}.csv');
    M = csvread( filename);
    if i==1
        linesp = '--gd';
    elseif i==2
        linesp = '-b*';
    elseif i==3
        linesp = '-.r+';
    elseif i==4
        linesp = '--ms';
    end
        
    plot(M([1:s:end end], 1), M([1:s:end end],2)./M([1:s:end end],5), linesp, 'LineWidth', 2, 'markers', 10);
    hold on;
end



legend('w/o IA', 'w/ IA', 'Pure Query', 'CSMA', 'Location', 'NorthWest');
xlabel('Simulation Time (s)');
ylabel({'Channel Utilization per Vehicle', '(time slot)'});
%title(strcat('Channel Utilization for Density: ', num2str(1/d), '(vehicle/m), Speed: ', num2str(v), '(m/s)'));
