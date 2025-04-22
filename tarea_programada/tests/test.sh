#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
PROGRAM="$SCRIPT_DIR/../bin/tarea_programada"

pass_count=0
fail_count=0

echo "Iniciando pruebas:"

# Se usan todas las entradas.txt con su respectiva salida
for input_file in "$SCRIPT_DIR"/entrada*.txt; do
    test_num=$(basename "$input_file" | grep -oP '\d+')
    expected_file="$SCRIPT_DIR/salida${test_num}.txt"

    if [[ ! -f "$expected_file" ]]; then
        echo "No se encontraron resultados para entrada $test_num"
        continue
    fi

    # Si es una prueba RANK, se usa lógica diferente
    if grep -q "RANK" "$input_file"; then
        echo "Prueba $test_num en modo RANK:"

        # Ejecutar el programa
        output=$("$PROGRAM" "$input_file" 2>&1)

        # Normalizar números (distancias)
        output_numbers=$(echo "$output" | grep -oP '\d+' | tr '\n' ' ' | xargs)
        expected_numbers=$(grep -oP '\d+' "$expected_file" | tr '\n' ' ' | xargs)

        # Comparar distancias esperadas y obtenidas
        if [[ "$output_numbers" == "$expected_numbers" ]]; then
            echo "> Prueba $test_num aprobada"
            ((pass_count++))
        else
            echo ">>> Prueba $test_num fallida"
            echo "    Esperado:"
            echo "$expected_numbers" | sed 's/^/    /'
            echo "    Obtenido:"
            echo "$output_numbers" | sed 's/^/    /'
            ((fail_count++))
        fi

        # Comparar rankings: limpiar \r, espacios y líneas vacías
        output_ranking=$(echo "$output" | grep -A 6 --no-group-separator "Puesto #" | tr -d '\r' | sed 's/[[:space:]]*$//' | sed '/^$/d')
        expected_ranking=$(grep -A 6 --no-group-separator "Puesto #" "$expected_file" | tr -d '\r' | sed 's/[[:space:]]*$//' | sed '/^$/d')

        if [[ "$output_ranking" == "$expected_ranking" ]]; then
            echo "> Ranking correcto"
            ((pass_count++))
        else
            echo "Error en el ranking de algoritmos"
            echo "    Esperado:"
            echo "$expected_ranking" | sed 's/^/    /'
            echo "    Obtenido:"
            echo "$output_ranking" | sed 's/^/    /'
            ((fail_count++))
        fi

    else
        echo "Prueba $test_num:"

        # Ejecutar el programa normalmente
        output=$("$PROGRAM" "$input_file" 2>&1)

        # Normalizar números para comparar distancias
        output_numbers=$(echo "$output" | grep -oP '\d+' | tr '\n' ' ' | xargs)
        expected_numbers=$(grep -oP '\d+' "$expected_file" | tr '\n' ' ' | xargs)

        if [[ "$output_numbers" == "$expected_numbers" ]]; then
            echo "> Prueba $test_num aprobada"
            ((pass_count++))
        else
            echo ">>> Prueba $test_num fallida"
            echo "    Esperado:"
            echo "$expected_numbers" | sed 's/^/    /'
            echo "    Obtenido:"
            echo "$output_numbers" | sed 's/^/    /'
            ((fail_count++))
        fi
    fi
done

echo "Finalizado: $pass_count exitoso(s), $fail_count fallido(s)."
