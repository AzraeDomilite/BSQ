#!/usr/bin/env python3

"""
Analyseur simple de résultats de benchmark BSQ
Génère un rapport de synthèse depuis un fichier CSV
"""

import csv
import sys
import os
from collections import defaultdict

def analyze_benchmark_results(csv_file):
    """Analyse les résultats de benchmark depuis un fichier CSV"""
    
    if not os.path.exists(csv_file):
        print(f"Erreur: Fichier {csv_file} non trouvé")
        return False
    
    # Lire les résultats
    results = defaultdict(list)
    total_files = 0
    
    try:
        with open(csv_file, 'r') as f:
            # Ignorer les lignes de commentaires
            lines = [line for line in f if not line.strip().startswith('#')]
            
        # Créer un reader à partir des lignes filtrées
        from io import StringIO
        csv_content = StringIO(''.join(lines))
        reader = csv.DictReader(csv_content)
        
        for row in reader:
            if 'filename' in row and row['filename'].startswith('map_'):
                size = row['filename'].split('_')[1]  # Extraire "10x10", "100x100", etc.
                results[size].append({
                    'parse_time': float(row['parse_time']),
                    'algo_time': float(row['algo_time']),
                    'total_time': float(row['total_time']),
                    'map_size': int(row['map_size'])
                })
                total_files += 1
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier: {e}")
        return False
    
    if total_files == 0:
        print("Aucun résultat trouvé dans le fichier")
        return False
    
    # Générer le rapport
    print("=== Rapport de synthèse ===")
    print()
    print(f"Total de fichiers analysés: {total_files}")
    print()
    print("Taille       | Nb fichiers | Parse (moy) | Algo (moy)  | Total (moy) | Parse (max) | Algo (max)  | Total (max)")
    print("-------------|-------------|-------------|-------------|-------------|-------------|-------------|-------------")
    
    for size in sorted(results.keys(), key=lambda x: int(x.split('x')[0])):
        data = results[size]
        if not data:
            continue
        
        count = len(data)
        avg_parse = sum(d['parse_time'] for d in data) / count
        avg_algo = sum(d['algo_time'] for d in data) / count
        avg_total = sum(d['total_time'] for d in data) / count
        max_parse = max(d['parse_time'] for d in data)
        max_algo = max(d['algo_time'] for d in data)
        max_total = max(d['total_time'] for d in data)
        
        print(f"{size:12} | {count:11} | {avg_parse:11.6f} | {avg_algo:11.6f} | {avg_total:11.6f} | {max_parse:11.6f} | {max_algo:11.6f} | {max_total:11.6f}")
    
    print()
    print("Temps en secondes")
    print()
    
    # Statistiques globales
    all_parse_times = []
    all_algo_times = []
    all_total_times = []
    
    for data_list in results.values():
        for data in data_list:
            all_parse_times.append(data['parse_time'])
            all_algo_times.append(data['algo_time'])
            all_total_times.append(data['total_time'])
    
    print("=== Statistiques globales ===")
    print(f"Parse - Min: {min(all_parse_times):.6f}s, Max: {max(all_parse_times):.6f}s, Moyenne: {sum(all_parse_times)/len(all_parse_times):.6f}s")
    print(f"Algo  - Min: {min(all_algo_times):.6f}s, Max: {max(all_algo_times):.6f}s, Moyenne: {sum(all_algo_times)/len(all_algo_times):.6f}s")
    print(f"Total - Min: {min(all_total_times):.6f}s, Max: {max(all_total_times):.6f}s, Moyenne: {sum(all_total_times)/len(all_total_times):.6f}s")
    
    # Ratio parsing/algorithme
    print()
    print("=== Ratio Parse/Algo ===")
    for size in sorted(results.keys(), key=lambda x: int(x.split('x')[0])):
        data = results[size]
        if not data:
            continue
        
        avg_parse = sum(d['parse_time'] for d in data) / len(data)
        avg_algo = sum(d['algo_time'] for d in data) / len(data)
        ratio = avg_parse / avg_algo if avg_algo > 0 else 0
        
        print(f"{size:12} | Parsing représente {ratio:.2f}x le temps de l'algorithme")
    
    return True

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 simple_analyzer.py <fichier_csv>")
        sys.exit(1)
    
    csv_file = sys.argv[1]
    
    if not analyze_benchmark_results(csv_file):
        sys.exit(1)
    
    print()
    print("Analyse terminée!")

if __name__ == "__main__":
    main()
