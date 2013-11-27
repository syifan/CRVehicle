l = [0.05, 0.1, 0.5, 1.0];
l_str = char('0.05', '0.1', '0.5', '1.0');
u_ia = [];
u_noia = [];

parfor i=1:length(l)
    [~, u] = parse_noia(strcat('{PaperWithoutIA}l{',l_str(i,:),'}v{30}'));
    u_noia(i) = u(end);
    [~, u] = parse_withia(strcat('{PaperWithIA}l{',l_str(i,:),'}v{30}'));
    u_ia(i) = u(end);
    
end
plot(l, u_noia, '--g');
hold on;
plot(l, u_ia, '-b');
