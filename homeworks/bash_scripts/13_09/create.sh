#!/bin/bash

if [[ $# -gt 0 ]]

then

    mkdir "$1"
    cd "$1" || exit

    subjects=("Алгебра и геометрия"  "Мат.анализ"  "Дискретная математика"  "Основы программирования")

    FIO=("Ведякова А.О" "Платонов А.В" "Максимов А.Ю" "Погожев С.В")
    num=0

    for f in "${subjects[@]}"
        do
            mkdir "${f}"
            filename="${f}/$(date "+%Y-%m-%d").log"
            touch "${filename}"
            echo "${FIO[num]}" >> "${filename}"
        num=$((num + 1))
    done
    cd ..
    cp op.sh "${1}/${subjects[3]}"
    cp algem.sh "${1}/${subjects[0]}"
else
    echo "No arguments entered"
fi
