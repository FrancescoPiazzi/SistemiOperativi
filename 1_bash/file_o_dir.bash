[ -f $DATA ] && echo "file" || ([ -d $DATA ] && echo "cartella" || echo "?")