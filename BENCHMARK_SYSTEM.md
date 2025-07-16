# BSQ Benchmark System

## 🚀 **Overview**

Ce système de benchmark complet permet de mesurer les performances du programme BSQ en séparant les temps de **parsing** et d'**algorithme**. Il génère des logs détaillés et des analyses statistiques.

## 📁 **Fichiers créés**

### **Code source**
- `includes/benchmark.h` - Header pour le système de benchmark
- `srcs/benchmark.c` - Implémentation des fonctions de benchmark
- `srcs/main_benchmark.c` - Version benchmark du main

### **Scripts**
- `run_benchmark.sh` - Script automatisé pour lancer les benchmarks
- `analyze_benchmark.py` - Analyseur de résultats avec graphiques

### **Compilation**
- Makefile modifié avec la target `benchmark`

## 🔧 **Utilisation**

### **Compilation**
```bash
make benchmark    # Compile bsq_benchmark
```

### **Benchmark d'un fichier**
```bash
./bsq_benchmark --benchmark map_file.bsq
```

### **Benchmark automatisé**
```bash
./run_benchmark.sh
```

### **Analyse des résultats**
```bash
python3 analyze_benchmark.py benchmark_results.csv
```

## 📊 **Format des logs**

### **Fichier CSV de sortie**
```csv
filename,map_width,map_height,map_size,parse_time,algo_time,total_time
map_10x10_1_density5.bsq,10,10,100,0.000009,0.000005,0.000014
```

### **Métriques mesurées**
- **parse_time**: Temps de parsing du fichier (en secondes)
- **algo_time**: Temps d'exécution de l'algorithme BSQ (en secondes)
- **total_time**: Temps total (parsing + algorithme)
- **map_size**: Taille totale de la map (width × height)

## 🎯 **Fonctionnalités**

### **Timing précis**
- Utilise `gettimeofday()` pour une précision microseconde
- Mesure séparément le parsing et l'algorithme
- Logs en temps réel + fichier CSV

### **Analyse automatisée**
- Statistiques par taille de map
- Graphiques de performance (si matplotlib disponible)
- Rapport de complexité

### **Robustesse**
- Gestion des erreurs de fichiers
- Validation des entrées
- Nettoyage automatique des ressources

## 📈 **Exemple d'utilisation**

```bash
# 1. Compilation
make benchmark

# 2. Test simple
./bsq_benchmark --benchmark maps/10x10/map_10x10_1_density5.bsq

# 3. Benchmark complet
./run_benchmark.sh

# 4. Analyse
python3 analyze_benchmark.py benchmark_results/benchmark_20250716_163000.csv
```

## 📋 **Résultats typiques**

### **Exemple de sortie**
```
BENCHMARK: map_10x10_1_density5.bsq - Parse: 0.000009s, Algo: 0.000005s, Total: 0.000014s
BENCHMARK: map_100x100_1_density2.bsq - Parse: 0.000127s, Algo: 0.000045s, Total: 0.000172s
```

### **Rapport de synthèse**
```
Taille       | Nb fichiers | Parse (moy) | Algo (moy)  | Total (moy)
-------------|-------------|-------------|-------------|-------------
10x10        |         100 |   0.000008  |   0.000005  |   0.000013
100x100      |         100 |   0.000125  |   0.000043  |   0.000168
1000x1000    |         100 |   0.012456  |   0.004321  |   0.016777
```

## 🔍 **Optimisations**

### **Performance**
- Compilation avec optimisations : `COMPILE=cc -O3 -Werror -Wextra -Wall`
- Mesure précise au niveau microseconde
- Gestion efficace de la mémoire

### **Facilité d'utilisation**
- Scripts automatisés
- Logs formatés en CSV
- Analyse graphique des résultats

## 📝 **Notes techniques**

- **Précision**: Mesure en microsecondes
- **Overhead**: Minimal (< 1µs par mesure)
- **Compatibilité**: macOS, Linux
- **Dépendances**: Aucune (matplotlib optionnel pour graphiques)

## 🎯 **Prochaines améliorations**

1. **Profiling détaillé** : Mesure par fonction
2. **Comparaison d'algorithmes** : Benchmark A/B
3. **Génération de rapports HTML** : Interface web
4. **Tests de charge** : Stress testing automatisé

---

**Le système de benchmark BSQ est maintenant opérationnel et prêt pour l'analyse de performance !** 🚀
