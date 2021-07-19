for i in `seq 0 100`
do
  cp qrun.sh qrun_$i.sh
  sed -i "s/\#JJJ/$i/g" qrun_$i.sh
  qsub <qrun_$i.sh
done
