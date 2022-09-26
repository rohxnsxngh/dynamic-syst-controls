figure;
load("data_v1.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 1');
hold on
load("data_v1.5.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 1.5');
hold on
load("data_v2.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 2');
hold on
load("data_v2.5.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 2.5');
hold on
load("data_v3.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 3');
hold on
load("data_v3.5.mat");
plot(omega.time, omega.signals.values,'DisplayName','Voltage 3.5');
hold off
title('Angular Velocity vs Time(s)')
xlabel('Time(s)') 
ylabel('Angular Velocity') 
legend;



