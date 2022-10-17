pkg load signal
pkg load control

[y,fs] =  audioread("audio.wav");

alpha = [0.6,0.4,0.2]
k =[0.05,0.25,0.5]* fs
for i=1:3
    i
    ki = k(i)
    alphai = alpha(i)

    a = zeros(1,ki+1);
    a(1) = 1;
    a(ki+1) = -alphai;
    
    b = zeros(1,ki+1);
    b(1) = 1-alphai;

    tf(b,a,1/fs)
    ys=filter(b,a,y);
    
    audiowrite(strcat("filter",num2str(i),".wav"),ys,fs)
end
