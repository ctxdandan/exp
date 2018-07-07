#!/usr/bin/env bash
scp ~/CLionProjects/exp/tol.cpp n1:~/exp/
scp -r ~/CLionProjects/exp/lib n1:~/exp/
ssh n1 "cd ~/exp;g++ tol.cpp -o graphTool;echo 'compile succeed'"
echo "transfer succeed"