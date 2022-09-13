data = load('Lab3_slider_data.mat');
figure;
plot(data.slider.time, data.slider.signals.values);
legend;
