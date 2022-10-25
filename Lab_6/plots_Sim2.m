w_20 = load("Sim2_20.mat");
w_34 = load("Sim2_34.mat");
w_48 = load("Sim2_48.mat");
w_62 = load("Sim2_62.mat");
w_76 = load("Sim2_76.mat");
w_90 = load("Sim2_90.mat");
figure;
plot(w_20.omega.time, w_20.omega.signals.values,'DisplayName', 'w = 20')
hold on;
plot(w_34.omega.time, w_34.omega.signals.values,'DisplayName', 'w = 34')
plot(w_48.omega.time, w_48.omega.signals.values,'DisplayName', 'w = 48')
plot(w_62.omega.time, w_62.omega.signals.values,'DisplayName', 'w = 62')
plot(w_76.omega.time, w_76.omega.signals.values,'DisplayName', 'w = 76')
plot(w_90.omega.time, w_90.omega.signals.values,'DisplayName', 'w = 90')
hold off;
xlabel('Time(s)') 
ylabel('Angular Velocity') 
legend;