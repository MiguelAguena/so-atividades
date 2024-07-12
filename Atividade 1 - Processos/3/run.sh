g++ -o 3par 3.cpp
g++ -o 3seq 3_seq.cpp
echo "Timing Parallel"
time ./3par 10

echo "Timing Sequential"
time ./3seq 10
