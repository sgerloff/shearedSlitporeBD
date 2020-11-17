# shearedSlitporeBD

![Alt text](https://github.com/sgerloff/shearedSlitporeBD/blob/master/fancy_system_plot.jpg?raw=true "Stress Relaxation Curve")

This simulation is writen in C++ and intends to provide a very basic framework to build Brownian Dynamics simualtions. It is not exactly lightweight, but instead gathers some of the key components I have found useful for performing these simulations. Most tools are intended to be used for serialized parallel computation, where you can submit large batches of single jobs to a computation cluster. This allows to sample ensembles or perform large paramter scan.

While working out of the box, this should not be treated as finished simulations, but as a starting point! Have fun.

# Basic Usage
First, compile the source code, using your favorite method. For example:
```sh
mkdir build
cd build
cmake ..
cmake --build .
```
Importantly: Before starting you need to edit the ```src/main.cpp``` file to specify the intended folder "```defaultOutputDir```" for numeric output. 
Then you can simply execute the pre-scripted sample calculation by providing the target shear rate and ensemble index:
```sh
build/shearedSlitporeBD 400 0
```
which output some system data, and track the progress of the running simulation.
```sh
Argument list: 
arguments[0] = 400
arguments[1] = 0
sysId: 2layer
dWall = 2.2             density = 0.85          numberOfParticles = 1058
charge = 35             diameter = 1
ssIS = 1                wallIS = 1

Set particle positions to 2 quadratic layers with 23 sides!
Initialized System: config/configuration_shear_0__Dwall_2.2_L_23.786_rho_0.85_N_1058_Wforce_-0_Zp_35.txt

Initialized System: config/configuration_shear_0__Dwall_2.2_L_23.786_rho_0.85_N_1058_Wforce_-0_Zp_35.txt

/home/sgerloff2/projects/shearedSlitporeBD/output/configContainer//ensembleContainer_shear_0__Dwall_2.2_L_23.786_rho_0.85_N_1058_Wforce_-0_Zp_35.txt
Run stress relaxation   0%|....|....|....|....|....|....|....|....|....|....|100% 
/home/sgerloff2/projects/shearedSlitporeBD/output/configContainer//ensembleContainertest_shear_400__Dwall_2.2_L_23.786_rho_0.85_N_1058_Wforce_-0_Zp_35.txt
```
Once the simualtion is finished you can use the provided gnuplot script to plot the result:
```sh
gnuplot plotStressCurve.gp 
```
![Alt text](https://github.com/sgerloff/shearedSlitporeBD/blob/master/stress_curve.png?raw=true "Stress Relaxation Curve")
