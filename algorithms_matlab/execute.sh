rm *.c~
rm -rf ./bin
mkdir ./bin

cd ./lib
./lib.sh

cd ../cm
make
mv cm ../bin
make clean

cd ../fast-newman
make
mv fn ../bin
make clean

cd ../fcm
make
mv fcm ../bin
make clean

cd ../fec
make
mv fec ../bin
make clean

cd ../girvan-newman
make
mv gn ../bin
make clean

cd ../sa
make
mv sa ../bin
make clean

cd ../kernighan_lin
make
mv kl ../bin
make clean

cd ../kmeans
make
mv kmeans ../bin
make clean

cd ../isodata
make
mv isodata ../bin
make clean

cd ../lib
rm *.o
