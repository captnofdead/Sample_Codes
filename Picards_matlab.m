%% Author Dhairy Agrawal (2018B4A70827G)
%% Description 
% This Matlab Code is for Picard iterations for System of ODE which maybe non
% linear. It takes the number of inputs from the user itself i.e. the number of equations and all the equations. 
% The things which are used here were - Cell which is an array of undefined
% structure and we can then change it to anything and is used to store the funtion
% , Function handle which lets us to define variables in the string and is
% used in ODE solver.
% This code stores the function in cell converts it to string
% and then stores, converts it to sym logic and then uses it to integerate
% and converts back to string to store it. For plotting, we convert the string
% to numerical function and use ODE45 and compare the solution obtained
% from these two methods.
%% Instructions to the user 
% function to be put which consists of variables t, x(1), x(2) and so on.
% enclose the variable in brackets in case of power terms of the variables 
% For example, (x(2))^2.
% Number of iterations is been taken as a stopping criteria instead of
% Error
%% Taking inputs and defining the funtion 
% Here we will take the input from the user which is commented
% n = input('Enter the number of equations in the system');
n = 3;
F = cell(1,n);
x0 = zeros(1,n);
% t0 = ('Input the initial point t0');
F = {'t^2+(x(2))^2','t^3+(x(3))^2+(x(1))','t+(x(1))*(x(2))'};
x0(1) = 1;
x0(2) = 0;
x0(3) = -1;
t0=0;

% The Input taking is commented out 
% Enter variables as t,x(1),x(2),x(3).....
% for i=1:n  
%     fprintf('Enter %d Function with variables as t,x(1),x(2).....', i);
%     F{1,i} = input(':','s');
% end
% 
% for i=1:n
%     fprintf('Enter initial value for the solution of x(%d)',i);
%     x0(i) = input('-');
% end

% Nmax = input('Enter the maximum number of iteration you want to perform for picard');

picardrepFunctions = string(F);

disp('Given system is :')
for i=1:n
 y_str = 'y('+string(i)+')';
 fprintf(" %s' = %s \t",y_str,picardrepFunctions(i));
 fprintf(" %s(%d) = %d \n",y_str,t0,x0(i));
end

for i=1:n
    xstr = 'x('+string(i)+')';
    for j=1:n
        picardrepFunctions(j) = strrep(picardrepFunctions(j),xstr,string(x0(i)));
    end
end
Nmax = 3;
%% Performing Picard Iterations 
% Already explained how this works, here we store the solutions obtained after every iteration in the
% picardSolutionFunctions as a string, we also need to update the yn in all
% the function and therefore we use strrep to replace variables with their
% last picard solution obtained and thus we proceed. Note that variables
% are of the form x(1) not x1.
picardSolutionFunctions = string(F);
for i=1:Nmax+1
    for j=1:n
        syms g(t) t;
        g(t) = str2sym(picardrepFunctions(j));
        picardSolutionFunctions(j) = string(x0(j)+int(g(t),t,t0,t));
    end
    fprintf('The Picard Iteration functions for the %d iteration\n', i);
    fprintf('\n');
    for j=1:n
        fprintf('The %d function i.e. (x(%d) = ) - \n', j, j);
        picardSolutionFunctions(j)
    end
    picardrepFunctions = string(F);
    for k=1:n
        s = 'x('+string(k)+')';
        for l=1:n
            picardrepFunctions(l) = strrep(picardrepFunctions(l),s,picardSolutionFunctions(k));
            warning("off")
        end
    end
end
%% Displaying expressions for obtained picard solution
% We display the final solution from the picard iteration 
for i = 1:n
 fprintf('%d Solution from last Picard iteration : ',i);
 picardSolutionFunctions(i)
end

%% ODE45SOlver
% Here we do this so as to convert the whole string into the format which
% ODE45 can accept as a numerical function with the function vairables as
% function handle 
h = "[";
for i = 1:n
    if i < n
        h = h + string(F(i)) + ";";
    else
        h = h + string(F(i));
    end
end
h = h + "]";
fn = str2func(['@(t,x) '+ string(h)]);
warning('off')
[tnum,x] = ode45(fn,[t0 t0+1],x0)
%% Plotting for comparision
% Final plotting of all the curves and the picard solutions obtained.
% Note that it can differ as the picard iteration doesnt always converge
% directly to the solution and converges slowly and may differ.
% sometimes it may be very close as in our example for small range 
for i=1:n
    figure(i);
    syms p(t) t;
    % Picard Solution
    p(t) = str2sym(picardSolutionFunctions(i));
    fplot(p,[t0 t0+1]);
    % ODE solution
    hold on;
    plot(tnum,x(:,i));
    xlabel('t');
    ylabel('function values');
    title('Function solution '+string(i)+' Comparision with ODE vs Picard');
    legend('Picard Solution '+string(i),'ODE45 Solution '+string(i));
    hold off;
end

