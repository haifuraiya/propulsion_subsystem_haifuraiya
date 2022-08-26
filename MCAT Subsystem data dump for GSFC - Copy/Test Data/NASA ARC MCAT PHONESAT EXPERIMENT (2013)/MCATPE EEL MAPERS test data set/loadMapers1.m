%% matlab script to load in data from RD532-MAPERS-1 data set
% Samudra Haque, 8/30/2013 samudra@gwu.edu
clear;
close all;
fn='CSV_RD532-MAPERS-1.txt';
delimiterIn=',';
A=importdata(fn,delimiterIn);
[A_rows,A_cols]=size(A);
sampleStart=1; %sample
sampleEnd=A_rows; %sample
timestamp=A(sampleStart:sampleEnd,6); %1st col. of data timestamp
P15=A(sampleStart:sampleEnd,1); %2nd col. of data P15 current draw
P15H=A(sampleStart:sampleEnd,2); %3rd col. of data P15H current draw
% TP=A(sampleStart:sampleEnd,4); %4th col. of data - unused Trigger Pulse
createfigure1(timestamp,horzcat(P15,P15H),sampleStart,sampleEnd);

figure; %new figure
subplot(2,1,1);
x_min=3150;
x_max=3200;
x_count=x_max-x_min
x=x_min:x_max; %number of samples from experiment start.
xA=A(x,:); %take 'x' number of samples as test
xP15L=A(x,2); %P15L data
xP15H=A(x,3); %P15H data
%xP15_norm=xP15/norm(xP15);
xTS=A(x,1); %timestamp
plot(xTS,horzcat(xP15L,xP15H)); %use horzcat here for more signals.. 
title_211=sprintf('t=%d samples, begin=%d, end=%d',x_count,x_min,x_max)
title({'P15L/P15H Low-Side Current Plot (0.649s intervals)';title_211});
grid on;

subplot(2,1,2);
resample_A=100;
resample_B=154;
%xP15_resample=resample(xP15,resample_A,resample_B);
xAr=resample(xA,resample_A,resample_B);
x_min_time=A(x_min,1)
x_max_time=A(x_max,1)
[x_rows, x_cols]=size(xAr)
x_resample_interval=(x_max_time-x_min_time)/(x_rows-1)
x_resampleTS=x_min_time:x_resample_interval:x_max_time;
%plot(x_resampleTS,xP15_resample);
plot(x_resampleTS,horzcat(xAr(:,2),xAr(:,3)));
title_212=sprintf('Rate (%d/%d), %d samples, begin=%d, end=%d',resample_A,resample_B,x_count,x_min,x_max)
title({'P15L/P15H (Resampled) Low-Side Current Plot (1s intervals)';title_212});
grid on;




