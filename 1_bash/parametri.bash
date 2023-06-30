echo "nome script: $0"
echo "primo parametro: $1"
echo "tutti i parametri: $@"
if [[ $# > 1 ]]; then
    shift
    echo "tutti i parametri dopo lo shift: $@"
else
    echo "troppi pochi parametri perchè lo shift sia utile"
fi