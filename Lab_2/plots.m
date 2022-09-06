subplot(4,1,1);
y1 = x(1:625,1);
plot(t,y1)
xlabel('Time(s)')
ylabel('Position(m)')
title('Position vs. Time')

subplot(4,1,2); 
y2 = x(1:625,2);
plot(t,y2)
xlabel('Time(s)')
ylabel('Velocity(m/s)')
title('Velocity vs. Time')

subplot(4,1,3); 
y3 = x(1:625,3);
plot(t,y3)
xlabel('Time(s)')
ylabel('Position(rad)')
title('Angular Position vs. Time')

subplot(4,1,4); 
y4 = x(1:625,4);
plot(t,y4)
xlabel('Time(s)')
ylabel('Velocity(rad/s)')
title('Angular Velocity vs. Time')