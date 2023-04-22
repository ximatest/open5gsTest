pkill -9 open5gs
level="warn"

if [ ! -n "$1" ] ;then
	level="info"
else
	level=$1
fi

./build/src/nrf/open5gs-nrfd -e $level &
./build/src/amf/open5gs-amfd -e $level &


./build/src/amf/open5gs-amf-spsd -i 1 -e $level -l ./install/var/log/open5gs/amf_sps1.log &
./build/src/amf/open5gs-amf-spsd -i 2 -e $level -l ./install/var/log/open5gs/amf_sps2.log &
./build/src/amf/open5gs-amf-spsd -i 3 -e $level -l ./install/var/log/open5gs/amf_sps3.log &
./build/src/amf/open5gs-amf-spsd -i 4 -e $level -l ./install/var/log/open5gs/amf_sps4.log &
./build/src/amf/open5gs-amf-spsd -i 5 -e $level -l ./install/var/log/open5gs/amf_sps5.log &
