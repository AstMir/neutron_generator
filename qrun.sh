#PBS -N geant4_#JJJ 
#PBS -l walltime=09:50:00
#PBS -o /afs/jinr.ru/user/j/jemtchou/simpledet/log/

JOBID=#JJJ
HOME=/afs/jinr.ru/user/j/jemtchou
source ${HOME}/SetGeant4.sh
cd ${TMPDIR}
${HOME}/simpledet/build/simpledet.exe $JOBID >& out_$JOBID.out
mv _nt_NTuple.csv ntuple_$JOBID.csv
gzip *.csv
gzip *.out
mv ntuple_$JOBID.csv.gz ${HOME}/simpledet/result
mv out_$JOBID.out.gz ${HOME}/simpledet/log
