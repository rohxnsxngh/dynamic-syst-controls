omega = 0.12;
zeta = 0.45594;
alpha = 10*zeta*omega;
h1o = 10;
h2o = 10;
c1 = 6.7767; % lab 5
c2 = 6.5198; % lab 5
km = 3.614; % Lab 5
A = pi*2.25^2;
gv1 = c1 / (2*sqrt(h1o));
gv2 = c2 / (2*sqrt(h2o));
b1 = (gv1 * km) / A^2 ;
b2 = (gv1 + gv2) / A;
b3 = (gv1 *gv2) / A^2;

Kd = (2*zeta*omega + alpha - b2) / b1;
Kp = (omega^2 + 2*alpha*zeta*omega - b3) / b1;
Ki = (alpha*omega^2) / b1;