clear;
clc;

% Open, read and close file
dataFile = fopen('./coronaResults.txt', 'r');
fgets(dataFile);

timeData = fgets(dataFile);

fgets(dataFile);

population = fgets(dataFile);
noCycles = fgets(dataFile);
noSwitches = fgets(dataFile);
incubationPeriod = fgets(dataFile);
contagionFactor = fgets(dataFile);
% deathRate = fgets(dataFile);

dataCell = textscan(dataFile, '%d %d %d %d %d', 'headerlines', 2);
fclose(dataFile);

dataArray = cell2mat(dataCell);

% Plot the results individually
figure(1);
plot(dataArray(:,1), dataArray(:,2), 'g', dataArray(:,1), dataArray(:,3), 'm', dataArray(:,1), dataArray(:,4), 'b', dataArray(:,1), dataArray(:,5), 'r', 'linewidth', 2);
set(gca, 'Fontsize', 20);
xlabel('Iteration'); ylabel('Number of People');
title('Progression of Virus');
legend('Healthy', 'Sick', 'Healed', 'Dead');
%annotation('textbox', 'FitBoxToText', 'on', 'String',"Population: " + population + "Number of Cycles: " + noCycles + "Number of Switches: " + noSwitches + "Incubation Period: " + incubationPeriod + "Contagion Factor: " + contagionFactor + "Death Rate: " + deathRate(1:end-1));

% Plot the results in a stacked bar graph
figure(2);
ba = bar(dataArray(:,2:5), 'stacked', 'FaceColor', 'Flat');
ba(1).CData = [0 1 0];
ba(2).CData = [1 0 1];
ba(3).CData = [0 0 1];
ba(4).CData = [1 0 0];
set(gca, 'Fontsize', 20);
xlabel('Iteration'); ylabel('Number of People');
axis([0 str2num(noCycles) 0 str2num(population)]);
title('Progression of Virus');
legend('Healthy', 'Sick', 'Healed', 'Dead');

%% Animation of the virus's progression in the population over time
% KNOWN BUG: pcolor uses a colormap to choose what color a cell should be.
% This is bad, because our custom colormap relies on their being 4 integers
% on the grid (healthy, infected, recovered, dead). After enough time has
% progressed and there are no more people that are healthy, there is only 3
% integers, so the colormap re-scales and suddenly all the recovered people
% turn red because there is no more black... I'm trying to find a way to
% fix this but I'm stuck right now.

run completeHistory.m % Gets the simulation data "outMat"
figure(3)
Q = size(outMat,3);
W = outMat(:,:,1);
h = pcolor(W);
map = [0 0 0; 1 1 1; 1 0 0; 0 1 0];
colormap(map)
drawnow();
title("Simulation Progression: Day 1")
pause(0.5);
for K = 2 : Q
    W = outMat(:,:,K);
    set(h, 'CData', W);
    drawnow();
    str = sprintf("Simulation Progression: Day %d", K);
    title(str)
    pause(0.5);
end









