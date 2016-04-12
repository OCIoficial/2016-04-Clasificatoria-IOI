#Subtask 1
for i in {1..10}; do echo 1 >n$i.in; echo $i >>n$i.in; done
for i in $(seq 68 49 1000); do echo 1 >n$i.in; echo $i >>n$i.in; done

#Subtask 3
for n in {1..7}; do for k in $(seq $(((n-1)*n*(n+1)/8-2)) $(((n-1)*n*(n+1)/8+n+1))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done

#Subtask 4
for n in 8 15 16; do for k in $(seq $(((n-1)*n*(n+1)/8-1)) $(((n-1)*n*(n+1)/8+n))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in 9 10 13 14; do for k in $(seq $(((n-1)*n*(n+1)/8+n/2)) $(((n-1)*n*(n+1)/8+n/2))); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done

#Subtask 5
for n in $(seq 24 16 100); do for k in $(((n-1)*n*(n+1)/8)) $(((n-1)*n*(n+1)/8+n/2)); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in $(seq 31 16 100); do for k in $(((n-1)*n*(n+1)/8+n-1)) $(((n-1)*n*(n+1)/8+n/2)); do echo 3 >n${n}k${k}.in; echo $n $k $((n*(n+1))) >>n${n}k${k}.in; done; done
for n in 48 55 63 96; do echo 3 >n${n}k${k}.in; echo $n $(((n-1)*n*(n+1)-1)) $((n*(n+1))) >>n${n}k${k}.in; done
for n in 32 56 79 95; do echo 3 >n${n}k${k}.in; echo $n $(((n-1)*n*(n+1)+n)) $((n*(n+1))) >>n${n}k${k}.in; done
for n in 38 66 76 85; do echo 3 >n${n}k${k}.in; echo $n $(((n-1)*n*(n+1)+n/2)) $((n*(n+1))) >>n${n}k${k}.in; done
