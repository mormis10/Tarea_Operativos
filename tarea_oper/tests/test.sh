#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
PROGRAM="$SCRIPT_DIR/../bin/tarea_oper"

pass_count=0
fail_count=0

echo "Iniciando pruebas:"

for input_file in "$SCRIPT_DIR"/entrada*.txt; do
    test_num=$(basename "$input_file" | grep -oP '\d+')
    expected_file="$SCRIPT_DIR/salida${test_num}.txt"

    if [[ ! -f "$expected_file" ]]; then
        echo "No se encontraron resultados para entrada $test_num"
        continue
    fi

    # Ejecutar programa para cada entradaX.txt
    output=$("$PROGRAM" "$input_file")

    # Extraer distancias (cilindros), el resto no importa
    output_numbers=$(echo "$output" | grep -oP '\d+')
    expected_numbers=$(grep -oP '\d+' "$expected_file")

    if [[ "$output_numbers" == "$expected_numbers" ]]; then
        echo "> Prueba $test_num aprobada!"
        ((pass_count++))
    else
        echo " >>> Prueba $test_num fallida!"
        echo "    Esperado:"
        echo "$expected_numbers" | sed 's/^/    /'
        echo "    Obtenido:"
        echo "$output_numbers" | sed 's/^/    /'
        ((fail_count++))
    fi
done

echo "Finalizado: $pass_count exitoso(s), $fail_count fallido(s)."

