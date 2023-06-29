A=(1 "ciao" 12.3)
A+=(44 "haha")

echo "size:  ${#A[@]}"

for i in ${!A[@]}; do
    echo ${A[i]}
done

echo ""

for e in ${A[@]:1:3}; do    # ${A[@]:s:n}  prende n elementi da A, partendo dall'elemento s
    echo ${e}
done

echo ""

lsres=( $(ls) )
echo "ls: "
for e in ${lsres[@]}; do
    echo ${e}
done
