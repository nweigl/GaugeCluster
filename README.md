# GaugeCluster
DISCLAIMER: I am merely an electronics hobbyist and this is a work in progress. Replicate this work at your own risk.

This project is an effort to retrofit gauges in classic vehicles with modern stepper motors using modern sensors.

In use are x27 stepper motors commonly used in modern GM dash clusters. These are driven by AX1201728SG 4 channel stepper motor drivers, controlled by an Arduino Nano.

In the initial prototype, I will be retrofitting the mechanical oil pressure and speedometer gauges on my 1976 Chevy K5 Blazer. The speedometer input will come from a 16ppr hall effect sensor mounted to the output housing of the NP205 transfer case. The oil pressure input will be connected to a voltage divider measuring the resistance of a VDO 360-003 oil pressure sending unit (0-80 PSI = 10-184 ohm resistance).
