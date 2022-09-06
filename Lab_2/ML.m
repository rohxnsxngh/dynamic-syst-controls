% L = 0.23; %meters
% m1 = 0.78; %kg
% m2 = 1.15; %kg
% u = 0.03; % * coulomb friction
% k = 294; % N/m
% c = 0.005; % viscous friction Nms/rad*
% g = 9.81; %m/s^2
% Ic = 0.0014; %kg*M^2
% x = -0.1; %m
% t = pi/6; % theta

function M = ML(t,x,L,m1,m2,u,k,c,g,Ic)
x1 = x(1); %unused
x2 = x(2);
x3 = x(3);
x4 = x(4); %unused

M = [1, 0, 0, 0;
    0, m1+m2, 0, m1*L;
    0, 0, 1, 0;
    0, m1*L, 0, Ic+m1*L^2;];

end