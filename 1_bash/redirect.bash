A=(4 6 "yeee" "wee" 55)

for i in ${!A[@]}; do
    if [ $((i%2)) -eq 0 ]; then
        echo "pari: ${A[i]}"
    else
        echo "dispari: ${A[i]}" 1>&2
    fi
done