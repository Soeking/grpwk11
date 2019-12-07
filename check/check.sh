# shellcheck disable=SC2086
# shellcheck disable=SC2164
# shellcheck disable=SC2046
cd $(cd $(dirname $0); pwd)
cd ../src
make
./grpwk11 ../data/dat0_in ../out/dat0_out &
./grpwk11 ../data/dat1_in ../out/dat1_out
./grpwk11 ../data/dat2_in ../out/dat2_out &
./grpwk11 ../data/dat3_in ../out/dat3_out
./grpwk11 ../data/dat4_in ../out/dat4_out 

cd ../check
javac Check.java
java Check 0
java Check 1
java Check 2
java Check 3
java Check 4
