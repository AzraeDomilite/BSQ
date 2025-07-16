#!/bin/bash

# Script de test de performance pour BSQ
# Teste tous les dossiers de maps et mesure le temps d'exécution

echo "====================================="
echo "BSQ Performance Test Suite"
echo "====================================="

# Vérifier si le programme BSQ existe
if [[ ! -f "./bsq" ]]; then
    echo "Error: BSQ executable not found. Please compile first with 'make'"
    exit 1
fi

# Vérifier si le dossier maps existe
if [[ ! -d "maps" ]]; then
    echo "Error: 'maps' directory not found"
    exit 1
fi

total_maps=0
total_success=0
total_failed=0

# Tester chaque dossier de maps
for map_dir in maps/*/; do
    if [[ -d "$map_dir" ]]; then
        dir_name=$(basename "$map_dir")
        echo "====================================="
        echo "Testing directory: $dir_name"
        echo "====================================="
        
        dir_success=0
        dir_failed=0
        dir_total=0
        
        # Parcourir tous les fichiers .bsq dans le dossier
        for map_file in "$map_dir"/*.bsq; do
            if [[ -f "$map_file" ]]; then
                map_name=$(basename "$map_file")
                echo "Testing: $map_name"
                
                # Mesurer le temps d'exécution
                start_time=$(date +%s.%N)
                
                # Exécuter BSQ avec timeout
                if timeout 30s ./bsq "$map_file" > /dev/null 2>&1; then
                    end_time=$(date +%s.%N)
                    # Utiliser awk pour les calculs en virgule flottante
                    execution_time=$(echo "$end_time $start_time" | awk '{printf "%.3f", $1 - $2}')
                    echo "✓ Success: ${execution_time}s"
                    ((dir_success++))
                    ((total_success++))
                else
                    end_time=$(date +%s.%N)
                    execution_time=$(echo "$end_time $start_time" | awk '{printf "%.3f", $1 - $2}')
                    echo "✗ Failed/Timeout: ${execution_time}s"
                    ((dir_failed++))
                    ((total_failed++))
                fi
                
                ((dir_total++))
                ((total_maps++))
            fi
        done
        
        echo ""
        echo "Directory $dir_name statistics:"
        echo "Total files: $dir_total"
        echo "Successful: $dir_success"
        echo "Failed: $dir_failed"
        echo ""
    fi
done

echo "====================================="
echo "Global Statistics"
echo "====================================="
echo "Total maps tested: $total_maps"
echo "Total successful: $total_success"
echo "Total failed: $total_failed"
echo "Success rate: $(echo "$total_success $total_maps" | awk '{printf "%.2f%%", ($1/$2)*100}')"
echo "====================================="
echo "Test Complete"
echo "====================================="
