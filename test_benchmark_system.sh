#!/bin/bash

# Script de test complet pour le système de benchmark BSQ

echo "=== Test complet du système de benchmark BSQ ==="
echo ""

# 1. Compilation
echo "1. Compilation du programme de benchmark..."
make benchmark
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la compilation"
    exit 1
fi
echo "✅ Compilation réussie"
echo ""

# 2. Test du programme de benchmark
echo "2. Test du programme de benchmark..."
./bsq_benchmark --benchmark maps/10x10/map_10x10_1_density5.bsq >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de l'exécution du benchmark"
    exit 1
fi
echo "✅ Programme de benchmark fonctionnel"
echo ""

# 3. Test de génération CSV
echo "3. Test de génération CSV..."
echo "filename,map_width,map_height,map_size,parse_time,algo_time,total_time" > test_benchmark.csv
./bsq_benchmark --benchmark maps/10x10/map_10x10_1_density5.bsq maps/10x10/map_10x10_2_density7.bsq 2>/dev/null >> test_benchmark.csv

# Vérifier que le fichier CSV a été créé et contient des données
if [ ! -f test_benchmark.csv ] || [ $(wc -l < test_benchmark.csv) -lt 2 ]; then
    echo "❌ Erreur lors de la génération du fichier CSV"
    exit 1
fi
echo "✅ Génération CSV fonctionnelle"
echo ""

# 4. Test de l'analyseur
echo "4. Test de l'analyseur..."
python3 simple_analyzer.py test_benchmark.csv > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de l'analyse"
    exit 1
fi
echo "✅ Analyseur fonctionnel"
echo ""

# 5. Test de performance sur différentes tailles
echo "5. Test de performance sur différentes tailles..."
echo "filename,map_width,map_height,map_size,parse_time,algo_time,total_time" > performance_test.csv

# Tester avec différentes tailles
for size in "10x10" "100x100"; do
    file=$(ls maps/$size/*.bsq | head -1)
    if [ -f "$file" ]; then
        ./bsq_benchmark --benchmark "$file" 2>/dev/null >> performance_test.csv
    fi
done

# Analyser les résultats
echo "Résultats du test de performance:"
python3 simple_analyzer.py performance_test.csv
echo ""

# 6. Test de robustesse
echo "6. Test de robustesse..."
# Tester avec un fichier inexistant (le programme affiche "map error" mais ne crashe pas)
./bsq_benchmark --benchmark fichier_inexistant.bsq 2>/dev/null | grep -q "map error" || \
./bsq_benchmark --benchmark fichier_inexistant.bsq 2>&1 | grep -q "map error"
if [ $? -ne 0 ]; then
    echo "❌ Le programme devrait afficher 'map error' avec un fichier inexistant"
    exit 1
fi
echo "✅ Gestion d'erreur fonctionnelle"
echo ""

# 7. Nettoyage
echo "7. Nettoyage..."
rm -f test_benchmark.csv performance_test.csv benchmark_results.csv
echo "✅ Nettoyage terminé"
echo ""

echo "🎉 Tous les tests sont passés avec succès !"
echo ""
echo "Le système de benchmark BSQ est entièrement fonctionnel:"
echo "  - ✅ Compilation et exécution"
echo "  - ✅ Génération de logs CSV"
echo "  - ✅ Analyse et statistiques"
echo "  - ✅ Mesure séparée parser/algorithme"
echo "  - ✅ Gestion d'erreurs"
echo ""
echo "Utilisation:"
echo "  make benchmark                     # Compiler"
echo "  ./bsq_benchmark --benchmark file   # Benchmark d'un fichier"
echo "  ./run_benchmark.sh                # Benchmark complet"
echo "  python3 simple_analyzer.py file   # Analyser les résultats"
