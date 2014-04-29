#! /bin/bash

DIR=`dirname "$0"`

CPP="cpp -C -P"

BYMOC_PRC="$DIR/../../../bymoc_prc/CodeGen"
BYMOC_ASM="perl -I$DIR/../.. $DIR/../../bymoc_asm.pl"
BYMOC_VM="$DIR/../../bymoc_vm"

SPIN="spin"
GCC="gcc"

if (( $# < 1 ))
then
  echo "call Benchmark.sh for a demonstation"
  echo "usage: $0 <promela-file> [<var> <min> <max>]"
  exit 0
fi

FILE=$1
if (( $# >= 4 ))
then
  USE_VAR=1
  VAR=$2
  MIN=$3
  MAX=$4
else
  USE_VAR=0
  VAR="IGNORE"
  MIN="0"
  MAX="0"
fi

echo "$FILE"
echo "$FILE" >$FILE.log
if (( $USE_VAR ))
then
  echo "$VAR   VM_STATES      VM_TIME           VM_ST/S        SPIN_STATES    SPIN_TIME         SPIN_ST/S"
  echo "$VAR   VM_STATES      VM_TIME           VM_ST/S        SPIN_STATES    SPIN_TIME         SPIN_ST/S" >>$FILE.log
else
  echo "   VM_STATES      VM_TIME           VM_ST/S        SPIN_STATES    SPIN_TIME         SPIN_ST/S"
  echo "   VM_STATES      VM_TIME           VM_ST/S        SPIN_STATES    SPIN_TIME         SPIN_ST/S" >>$FILE.log
fi

for (( VAL = $MIN; VAL <= $MAX; VAL++ ))
do

  if (( $USE_VAR ))
  then
    $CPP -D$VAR=$VAL $FILE >$FILE.pr
  else
    $CPP $FILE >$FILE.pr
  fi

  $BYMOC_PRC $FILE.pr >/dev/null 2>&1
  $BYMOC_ASM $FILE.pr.s >/dev/null 2>&1
  $BYMOC_VM -B $FILE.pr.b -b 384 -h 4096 8 >vm.tmp 2>&1
  if grep "RUNTIME ERROR" vm.tmp
  then
    exit 0
  fi

  VM_STATES=`<vm.tmp grep "states visited:" | sed 's/^ *states visited: *//'`
  VM_TIME=`<vm.tmp grep "total time:" | sed 's/^ *total time: *//;s/ s//'`

  $SPIN -a -o1 -o3 $FILE.pr >/dev/null 2>&1
  $GCC -DBFS -DNOREDUCE -O2 -o pan pan.c >/dev/null 2>&1
  { time ./pan; } >spin.tmp 2>&1

  SPIN_STATES=`<spin.tmp grep "nominal states" | sed 's/^[^0-9]*\([0-9]*\).*$/\1/'`
  SPIN_TIME_STR=`<spin.tmp grep "real" | tr '\t' ' ' | sed 's/^real *//'`
  SPIN_TIME=$[`echo $SPIN_TIME_STR | sed 's/\([0-9]\+\)m\([0-9]\+\)\.\([0-9]\+\)s/\1*60+\2/'`]"."`echo $SPIN_TIME_STR | sed 's/\([0-9]\+\)m\([0-9]\+\)\.\([0-9]\+\)s$/\3/'`

  if (( $USE_VAR ))
  then
    echo "$VAL $VM_STATES $VM_TIME $SPIN_STATES $SPIN_TIME" | awk '{printf("%2d   %10d   %15.9f   %15.9f    %10d   %15.9f   %15.9f\n",$1,$2,$3,$2/$3,$4,$5,$4/$5);}'
    echo "$VAL $VM_STATES $VM_TIME $SPIN_STATES $SPIN_TIME" | awk '{printf("%2d   %10d   %15.9f   %15.9f    %10d   %15.9f   %15.9f\n",$1,$2,$3,$2/$3,$4,$5,$4/$5);}' >>$FILE.log
  else
    echo "$VM_STATES $VM_TIME $SPIN_STATES $SPIN_TIME" | awk '{printf("%10d   %15.9f   %15.9f    %10d   %15.9f   %15.9f\n",$1,$2,$1/$2,$3,$4,$3/$4);}'
    echo "$VM_STATES $VM_TIME $SPIN_STATES $SPIN_TIME" | awk '{printf("%10d   %15.9f   %15.9f    %10d   %15.9f   %15.9f\n",$1,$2,$1/$2,$3,$4,$3/$4);}' >>$FILE.log
  fi

done

rm -f *.pr *.xml *.s *.b *.l pan.* pan *.tmp

