function caterpooly(x0 = 1, y0 = 1, left= -15, right= 15, bottom = 0, top = 14, speedXY = [1, 1])
    numOfCircles = 5;
    r = 2;
    circleColors = {'g', 'r', 'b', 'y', 'g'};

    X = x0 * ones(numOfCircles, 1);
    Y = y0 * ones(numOfCircles, 1);
    t = 0:pi/100:2*pi;

    figure;
    hold on;
    axis([left-30, right+30, bottom-30, top+30]);

    circles = cell(1, numOfCircles);

    for i = 1:numOfCircles
        x = r * cos(t) + X(i);
        y = r * sin(t) + Y(i);

        circles{i} = plot(x, y, 'Color', circleColors{i}, 'LineWidth', 2);
    end

    rectangle('Position', [left, bottom, right-left, top-bottom], 'EdgeColor', 'r');

    for i = 1:1000
        newX = X(1) + speedXY(1);
        newY = Y(1) + speedXY(2);

        if newX < left || newX > right
            speedXY(1) = -speedXY(1);
            newX = X(1) + speedXY(1);
        end

        if newY > top || newY < bottom
            speedXY(2) = -speedXY(2);
            newY = Y(1) + speedXY(2);
        end

        X = [newX; X(1:end-1)];
        Y = [newY; Y(1:end-1)];

        for j = 1:numOfCircles
            x = r * cos(t) + X(j);
            y = r * sin(t) + Y(j);

            set(circles{j}, 'XData', x, 'YData', y);
        end

        pause(0.05);
        drawnow;
    end
end
