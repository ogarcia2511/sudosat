# sudosat

A project I created as a final assignment for COEN 177, where the request was to make a project of any type as long as it dealt with some topic in the field of Operating Systems.


To run the provided C++ programs (make sure all are in same directory): 
 - g++ -std=c++11 -pthreads -o sudosat sudosat.cpp
 - g++ -std=c++11 -o test test_client.cpp
 - ./sudosat [PORT NUMBER]
 - ./test [SERVER IP ADDRESS]

NOTE: PORT NUMBER in the "test_client.cpp" file is hardcoded to be 5000, so using a different port on the server-side requires a change to the "test_client.cpp" file as well. 
