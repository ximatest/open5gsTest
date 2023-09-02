pkill -9 open5gs
level="warn"
spsno=1

if [ -n "$1" ] ;then
    if [ $1 -le 16 ] ;then
        spsno=$1
    else
        level=$1
    fi
fi

if [  -n "$2" ] ;then
    spsno=$2
fi

./build/src/nrf/open5gs-nrfd -e $level &
./build/src/amf/open5gs-amfd -e $level &
./build/src/ausf/open5gs-ausfd -e $level &
./build/src/udm/open5gs-udmd -e $level &
./build/src/pcf/open5gs-pcfd -e $level &
./build/src/nssf/open5gs-nssfd -e $level &
./build/src/bsf/open5gs-bsfd -e $level &
./build/src/udr/open5gs-udrd -e $level &
./build/src/upf/open5gs-upfd -e $level &
#./build/src/upf/open5gs-upfd -e $level -c ./install/etc/open5gs/upf2.yaml &
for ((i=1; i<=$spsno; i++))
do
    ./build/src/amf/open5gs-amf-spsd -i ${i} -e $level -l ./install/var/log/open5gs/amf_sps${i}.log &
done
./build/src/smf/open5gs-smfd -e $level &
#./build/src/smf/open5gs-smfd -e $level -c ./install/etc/open5gs/smf2.yaml &
