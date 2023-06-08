clear;

n = 5;
r = 0.3;
a = 5;
b = 5;
x0 = 0;
y0 = 2;

x1 = 3;
y1 = 1;
norm = sqrt(x1^2 + y1^2);
x1 = x1 / norm;
y1 = y1 / norm;

dia = 2*r;

xtraj = @(t) x0 + t*x1;
ytraj = @(t) y0 + t*y1;

plot([-a, a, a, -a, -a], [-b, -b, b, b, -b]);
hold on;
axis equal;

pls = [plot(0, 0)];
for i = 2:n
  pls = [pls, plot(0, 0)];
endfor

hold off;

set(gca, 'xlim', [-a - dia, a + dia], 'ylim', [-b - dia, b + dia]);

circ = 0:0.1:2*pi;
xcirc = r * cos(circ);
ycirc = r * sin(circ);

d = 0.05;

t0 = 0;

while true
  t1 = fzero(@(t) min([a - abs(xtraj(t + (n-1)*dia)), b - abs(ytraj(t + (n-1)*dia))]) - r, t0 + 1);
  for i = t0:d:t1
    t0 = i;
    for j = 1:n
      set(pls(j), 'XData', xtraj(t0) + xcirc, 'YData', ytraj(t0) + ycirc);
      t0 = t0 + dia;
    endfor
    drawnow;
  endfor
  t1 = t1 + (n-1)*dia;
  if (a - abs(xtraj(t1)) < b - abs(ytraj(t1)))
    x1 = -x1;
    xtraj = @(t) abs(sign(t - t1) - 1) * xtraj(t) / 2 + abs(sign(t - t1) + 1) * (xtraj(t1) + x1*(t1 - t)) / 2;
  elseif (a - abs(xtraj(t1)) > b - abs(ytraj(t1)))
    y1 = -y1;
    ytraj = @(t) abs(sign(t - t1) - 1) * ytraj(t) / 2 + abs(sign(t - t1) + 1) * (ytraj(t1) + y1*(t1 - t)) / 2;
  else
    x1 = -x1;
    y1 = -y1;
    xtraj = @(t) abs(sign(t - t1) - 1) * xtraj(t) / 2 + abs(sign(t - t1) + 1) * (xtraj(t1) + x1*(t1 - t)) / 2;
    ytraj = @(t) abs(sign(t - t1) - 1) * ytraj(t) / 2 + abs(sign(t - t1) + 1) * (ytraj(t1) + y1*(t1 - t)) / 2;
  endif
  t0 = t1 - (n-1)*dia;
endwhile
