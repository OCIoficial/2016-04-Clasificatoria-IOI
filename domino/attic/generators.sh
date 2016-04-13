#Subtask 1
for i in {1..10}; do echo 1 >n$i.in; echo $i >>n$i.in; done
for i in $(seq 68 49 1000); do echo 1 >n$i.in; echo $i >>n$i.in; done

#Subtask 2
for n in 7 8 15 16; do for k in $(seq $((n*(n+1)*(n-1)/8)) $((n*(n+1)*(n-1)/8+n-1))); do echo 2 >n${n}k${k}bueno.in; echo $n $((n*(n+1))) >>n${n}k${k}bueno.in; echo 3 $n $k $((n*(n+1))) | ./domino | tail -n 1 >>n${n}k${k}bueno.in; done; done

#Subtask 3
for n in {1..7}; do for k in $(seq $(((n-1)*n*(n+1)/8-2)) $(((n-1)*n*(n+1)/8+n+1))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done

#Subtask 4
for n in 8 15 16; do for k in $(seq $(((n-1)*n*(n+1)/8-1)) $(((n-1)*n*(n+1)/8+n))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in 9 10 13 14; do for k in $(seq $(((n-1)*n*(n+1)/8+n/2)) $(((n-1)*n*(n+1)/8+n/2))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done

#Subtask 5
for n in $(seq 24 232 1000); do for k in $(((n-1)*n*(n+1)/8)) $(((n-1)*n*(n+1)/8+n/2)); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in $(seq 31 232 1000); do for k in $(((n-1)*n*(n+1)/8+n-1)) $(((n-1)*n*(n+1)/8+n/2)); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in 96 472 559 631 984; do echo 3 >n${n}k$(((n-1)*n*(n+1)/8-1)).in; echo $n $(((n-1)*n*(n+1)/8-1)) $((n*(n+1))) >>n${n}k$(((n-1)*n*(n+1)/8-1)).in; done
for n in 95 320 567 792 959; do echo 3 >n${n}k$(((n-1)*n*(n+1)/8+n)).in; echo $n $(((n-1)*n*(n+1)/8+n)) $((n*(n+1))) >>n${n}k$(((n-1)*n*(n+1)/8+n)).in; done
#for n in 85 381 606 763 860; do echo 3 >n${n}k$(((n-1)*n*(n+1)+n/2)).in; echo $n $(((n-1)*n*(n+1)+n/2)) $((n*(n+1))) >>n${n}k$(((n-1)*n*(n+1)+n/2)).in; done
