a = char('PaperWithoutIA', 'PaperWithIA', 'PureQuery');

[time,utilization] = parse_noia('{PaperWithoutIA}l{1.00}v{1}');
plot(time-time(1), utilization, '--g', 'LineWidth', 2);
hold on;

[time,utilization] = parse_withia('{PaperWithIA}l{1.00}v{1}');
plot(time-time(1), utilization, '-b', 'LineWidth', 2);

[time,utilization] = parse_purequery('{PureQuery}l{1.00}v{1}');
plot(time-time(1), utilization, '-.r', 'LineWidth', 2);

legend('w/o IA', 'w/ IA', 'pure query', 'Location', 'NorthWest');
xlabel('Simulation Time (s)');
ylabel('Channel Utilization (time slot)');
