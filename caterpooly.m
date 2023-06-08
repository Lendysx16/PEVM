clear;

n = 10;
r = 0.3;
path = 0:0.05:8*pi;

pls = [plot(0, 0)];
hold on;
axis equal;

for i = 2:n
  pls = [pls, plot(0, 0)];
endfor

hold off;

xtraj = @(t) t.*cos(t);
ytraj = @(t) t.*sin(t);

xs = xtraj(path);
ys = ytraj(path);

set(gca, 'xlim', [min(xs) - 4*r, max(xs) + 4*r], 'ylim', [min(ys) - 4*r, max(ys) + 4*r]);

circ = 0:0.1:2*pi;
xcirc = r * cos(circ);
ycirc = r * sin(circ);

t0 = 0;
d = 1e-3;
step = @(t0, t) (xtraj(t0 + t) - xtraj(t0))^2 + (ytraj(t0 + t) - ytraj(t0))^2 - 4*r^2;

for i = path
  t0 = i;
  for j = 1:n
    set(pls(j), 'XData', xtraj(t0) + xcirc, 'YData', ytraj(t0) + ycirc);
    t0 = t0 + fzero(@(t) step(t0, t), r);
  endfor
  drawnow;
endfor

