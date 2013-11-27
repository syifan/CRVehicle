v = [1.0, 5.0, 10, 15, 20, 25, 30];
u_ia = [];
u_noia = [];

parfor i=1:1:length(v)
    [~, u] = parse_noia(strcat('{PaperWithoutIA}l{1.0}v{',num2str(v(i)),'}'));
    u_noia(i) = u(end);
    [~, u] = parse_withia(strcat('{PaperWithIA}l{1.0}v{',num2str(v(i)),'}'));
    u_ia(i) = u(end);
    
end
plot(v, u_noia, '--g');
hold on;
plot(v, u_ia, '-b');
