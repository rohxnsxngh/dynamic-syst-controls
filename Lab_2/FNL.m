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

function F = FNL(t,x,L,m1,m2,u,k,c,g,Ic)
x1 = x(1);
x2 = x(2);
x3 = x(3);
x4 = x(4);

uhat = u * sign(x2);

F = [x2;(-m1*L*(uhat*cos(x3) - sin(x3))*(x4^2) -uhat*(m1 + m2)*g - 2*k*x1);
    x4;
    -c*x4 - m1*g*L*sin(x3);
    
    ];
end