
echo "Removing earlier computed file"
rm -f Results.csv
echo "Starting Sleep Jobs"
echo "Starting Sleep Jobs" >> Results.csv
echo "Thread Num, Sleep Duration (usec), Execution Time, Theoritical Time" >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 10 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 10 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 10 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 210 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 210 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 210 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 410 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 410 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 410 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 610 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 610 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 610 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 810 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 810 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 810 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 1010 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 1010 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 1010 >> Results.csv

echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 1210 micro seconds"
echo "Num Threads: 240, Num Jobs: 240, Job Type: 1, Sleep Duration: 1210 micro seconds" >> Results.csv

./MIC_OpenMP 240 240 1 1210 >> Results.csv

echo "Finished!!!"
echo "Finished!!!" >> Results.csv
