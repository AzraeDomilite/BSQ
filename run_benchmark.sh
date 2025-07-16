#!/bin/bash

# Script de benchmark automatisé pour BSQ
# Teste les performances sur différentes tailles de maps

echo "=== BSQ Benchmark Suite ==="
echo "Compilation du programme de benchmark..."

# Compilation du programme de benchmark
make benchmark
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation"
    exit 1
fi

echo "Compilation terminée ✓"
echo ""

# Créer le dossier de résultats si nécessaire
mkdir -p benchmark_results

# Timestamp pour les fichiers de log
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_FILE="benchmark_results/benchmark_${TIMESTAMP}.csv"

echo "Début du benchmark..."
echo "Fichier de log: $LOG_FILE"
echo ""

# Fonction pour benchmarker un dossier de maps
benchmark_folder() {
    local folder="$1"
    local size_name="$2"
    
    echo "Benchmark des maps $size_name..."
    
    # Compter le nombre de fichiers
    file_count=$(ls -1 "maps/$folder"/*.bsq 2>/dev/null | wc -l)
    
    if [ $file_count -eq 0 ]; then
        echo "  Aucun fichier trouvé dans maps/$folder"
        return
    fi
    
    echo "  Traitement de $file_count fichiers..."
    
    # Traiter chaque fichier
    for map_file in "maps/$folder"/*.bsq; do
        if [ -f "$map_file" ]; then
            ./bsq_benchmark --benchmark "$map_file" 2>/dev/null >> "$LOG_FILE"
        fi
    done
    
    echo "  $size_name terminé ✓"
}

# Initialiser le fichier de log avec l'en-tête
echo "# BSQ Benchmark Results - $TIMESTAMP" > "$LOG_FILE"
echo "# Format: filename,map_width,map_height,map_size,parse_time(s),algo_time(s),total_time(s)" >> "$LOG_FILE"
echo "filename,map_width,map_height,map_size,parse_time,algo_time,total_time" >> "$LOG_FILE"

# Benchmarker chaque taille de map
benchmark_folder "10x10" "10x10"
benchmark_folder "100x100" "100x100"
benchmark_folder "1000x1000" "1000x1000"
benchmark_folder "5000x5000" "5000x5000"

echo ""
echo "Benchmark terminé!"
echo "Résultats sauvegardés dans: $LOG_FILE"
echo ""

# Générer un rapport de synthèse
echo "Génération du rapport de synthèse..."
python3 simple_analyzer.py "$LOG_FILE"

echo ""
echo "Rapport terminé!"
echo ""
echo "Pour visualiser les résultats détaillés:"
echo "  cat $LOG_FILE"
echo ""
echo "Pour analyser les résultats:"
echo "  python3 -c \"import pandas as pd; df = pd.read_csv('$LOG_FILE'); print(df.describe())\""
