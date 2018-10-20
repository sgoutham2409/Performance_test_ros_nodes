# Excercise1_performance_test

Performance tests package

1. There are four launch file for checking communication for 4 combinations of nodes.
2. Running the nodes individually and comapring the publish frequency with rostopic hz, the frequency limit for real time behaviour can be determined

I tried to change the loop rate dynamically based on a timer by incrementing the frequency, but this resulted in the downgrading of performance so I reverted the changes in pub.cpp
