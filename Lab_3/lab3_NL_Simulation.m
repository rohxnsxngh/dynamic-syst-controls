L = 0.23; %meters
m1 = 0.78; %kg
m2 = 1.15; %kg
u = 0.037959; % * coulomb friction
k = 294; % N/m
c = 0.002433766; % viscous friction Nms/rad*
g = 9.81; %m/s^2
Ic = 0.0014; %kg*M^2
x = 0.025; %m
t = 35*(pi/180); % theta

% load("F.m")

x0 = [x, 0, t, 0];
tspan = [0,30];

options  = odeset('mass', @(t,x) MNL(t,x,L,m1,m2,u,k,c,g,Ic));
[t,x]=ode45(@(t,x) FNL(t,x,L,m1,m2,u,k,c,g,Ic),tspan,x0,options);
