data = load('Lab3_pend_data_1.mat');
figure;
plot(data.pend.time, data.pend.signals.values);
legend;