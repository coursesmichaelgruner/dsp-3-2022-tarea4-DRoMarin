pkg load signal

a = 0.8;
k = 10;

B = 1-a
A = zeros(1,k+1);
A(1) = 1;
A(k+1) = -a


zplane(B,A)

pause
