#!/bin/bash
if [ "$#" -ne 1 ]; then
 echo "Le nombre d'arguments est invalide"
 exit 1
fi

CLHEP_DIR=/home/local.isima.fr/thcliquot/shared/ZZ3/IDM/tp5/Random/
pids=""
start=$SECONDS

#Compilation of the file
g++ -o piSimuSPMD piSimuSPMD.cc -I $CLHEP_DIR/include -L $CLHEP_DIR/lib -lCLHEP-Random-2.1.0.0 -static

#Clear the result file
> $1

#Launch every script simultaneously
for i in {0..9}
do
    fileName="./status/status_$i"
   ./piSimuSPMD $fileName >> $1 &
    pids="$pids $!"
done

wait $pids
duration=$(($SECONDS - $start))
echo "end of all simulation, duration: $duration"