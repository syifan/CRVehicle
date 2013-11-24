[time,utilization] = parse_noia('noia');
plot(time-time(1), utilization);
hold on;

[time,utilization] = parse_withia('ia');
plot(time-time(1), utilization);