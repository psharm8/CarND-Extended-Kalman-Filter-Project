# Extended Kalman Filter Project
Self-Driving Car Engineer Nanodegree Program

# [Rubric](https://review.udacity.com/#!/rubrics/748/view) points
## Compiling

### Your code should compile

The code compiles with `cmake` and `make` on Linux, WSL and MinGW32 (provided MinGW has uWebSockets installed).

## Accuracy

### px, py, vx, vy output coordinates must have an RMSE <= [.11, .11, 0.52, 0.52] when using the file: "obj_pose-laser-radar-synthetic-input.txt which is the same data file the simulator uses for Dataset 1"

RMSE for Dataset 1 = [0.097, 0.085, 0.45, 0.43]

RMSE for Dataset 2 = [0.072, 0.096, 0.42, 0.49]

## Follows the Correct Algorithm

### Your Sensor Fusion algorithm follows the general processing flow as taught in the preceding lessons
The starter code was structured with the correct flow already. The required code was implemented at the approproate TODO placeholders.

### Your Kalman Filter algorithm handles the first measurements appropriately
The first measurement is used to initialize the state vector based on the sensor type.

### Your Kalman Filter algorithm first predicts then updates
On receiving the measurement, after the first, the algorithm first performs a prediction and then performs the update based on the sensor type.

### Your Kalman Filter can handle radar and lidar measurements
The filter handles both lidar and radar data. The algorthm flow is always the same except at two places. 

1. First measurement: Updates the state vector. In case of radar coordinates are first converted from polar to cartesian, whereas no such conversion is required in case of lidar data.
2. Update step: Radar update step requires extra calculation of jacobian matrix hence the different update functions are called based on the sensor type.

## Code Efficiency

### Your algorithm should avoid unnecessary calculations
Values have been reused wherever possible.
1. Calculating 2nd, 3rd and 4th power of timestamp difference
2. Sine and Cosine of Phi 
3. Identity matrix for update step is always (4,4) which is made a member variable.
