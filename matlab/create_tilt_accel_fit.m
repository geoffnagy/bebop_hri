function [fitresult, gof] = create_tilt_accel_fit(tilt_angle, accel, title_str)
%CREATEFIT(tilt_angle,accel)
%  Create a fit.
%
%  Data for 'accel_rotation_fit' fit:
%      X Input : tilt_angle
%      Y Output: accel
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  See also FIT, CFIT, SFIT.

%  Auto-generated by MATLAB on 20-Jan-2016 15:54:23


%% Fit: 'accel_rotation_fit'.
[xData, yData] = prepareCurveData( tilt_angle, accel );

% Set up fittype and options.
ft = fittype( 'poly1' );
opts = fitoptions( 'Method', 'LinearLeastSquares' );
opts.Normalize = 'on';
opts.Robust = 'Bisquare';

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft, opts );

% Plot fit with data.
figure( 'Name', 'accel_rotation_fit' );
h = plot( fitresult, xData, yData );
title(title_str);
legend( h, 'accel vs. tilt_angle', 'accel_rotation_fit', 'Location', 'NorthEast' );
% Label axes
xlabel tilt_angle
ylabel accel
grid on

