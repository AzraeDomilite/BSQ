#!/usr/bin/env python3

"""
Analyseur de résultats de benchmark BSQ
Génère des graphiques et statistiques détaillées
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os
from datetime import datetime

def load_benchmark_data(csv_file):
    """Charge les données de benchmark depuis un fichier CSV"""
    try:
        df = pd.read_csv(csv_file)
        return df
    except Exception as e:
        print(f"Erreur lors du chargement du fichier: {e}")
        return None

def extract_map_info(df):
    """Extrait les informations sur les maps (taille, densité)"""
    df['map_type'] = df['filename'].str.extract(r'map_(\d+x\d+)_')[0]
    df['density'] = df['filename'].str.extract(r'density(\d+)')[0].astype(int)
    return df

def generate_performance_plots(df, output_dir):
    """Génère des graphiques de performance"""
    os.makedirs(output_dir, exist_ok=True)
    
    # Graphique 1: Temps vs taille de map
    plt.figure(figsize=(12, 8))
    
    plt.subplot(2, 2, 1)
    for map_type in df['map_type'].unique():
        data = df[df['map_type'] == map_type]
        plt.scatter(data['map_size'], data['parse_time'], label=f'{map_type} - Parse', alpha=0.7)
    plt.xlabel('Taille de la map')
    plt.ylabel('Temps de parsing (s)')
    plt.title('Temps de parsing vs taille de map')
    plt.legend()
    plt.yscale('log')
    plt.xscale('log')
    
    plt.subplot(2, 2, 2)
    for map_type in df['map_type'].unique():
        data = df[df['map_type'] == map_type]
        plt.scatter(data['map_size'], data['algo_time'], label=f'{map_type} - Algo', alpha=0.7)
    plt.xlabel('Taille de la map')
    plt.ylabel('Temps d\'algorithme (s)')
    plt.title('Temps d\'algorithme vs taille de map')
    plt.legend()
    plt.yscale('log')
    plt.xscale('log')
    
    plt.subplot(2, 2, 3)
    for map_type in df['map_type'].unique():
        data = df[df['map_type'] == map_type]
        plt.scatter(data['map_size'], data['total_time'], label=f'{map_type} - Total', alpha=0.7)
    plt.xlabel('Taille de la map')
    plt.ylabel('Temps total (s)')
    plt.title('Temps total vs taille de map')
    plt.legend()
    plt.yscale('log')
    plt.xscale('log')
    
    plt.subplot(2, 2, 4)
    parse_ratio = df['parse_time'] / df['total_time']
    algo_ratio = df['algo_time'] / df['total_time']
    
    for map_type in df['map_type'].unique():
        data = df[df['map_type'] == map_type]
        ratio_data = parse_ratio[df['map_type'] == map_type]
        plt.scatter(data['map_size'], ratio_data, label=f'{map_type} - Parse ratio', alpha=0.7)
    
    plt.xlabel('Taille de la map')
    plt.ylabel('Ratio parsing/total')
    plt.title('Ratio temps parsing/total')
    plt.legend()
    plt.xscale('log')
    
    plt.tight_layout()
    plt.savefig(f'{output_dir}/performance_analysis.png', dpi=300, bbox_inches='tight')
    plt.close()
    
    # Graphique 2: Impact de la densité
    plt.figure(figsize=(12, 6))
    
    plt.subplot(1, 2, 1)
    for map_type in df['map_type'].unique():
        data = df[df['map_type'] == map_type]
        plt.scatter(data['density'], data['algo_time'], label=f'{map_type}', alpha=0.7)
    plt.xlabel('Densité d\'obstacles')
    plt.ylabel('Temps d\'algorithme (s)')
    plt.title('Impact de la densité sur les performances')
    plt.legend()
    plt.yscale('log')
    
    plt.subplot(1, 2, 2)
    df.boxplot(column='algo_time', by='map_type', ax=plt.gca())
    plt.title('Distribution des temps d\'algorithme par taille')
    plt.suptitle('')
    plt.yscale('log')
    
    plt.tight_layout()
    plt.savefig(f'{output_dir}/density_analysis.png', dpi=300, bbox_inches='tight')
    plt.close()

def generate_statistics_report(df, output_file):
    """Génère un rapport statistique détaillé"""
    with open(output_file, 'w') as f:
        f.write("# BSQ Benchmark Analysis Report\n")
        f.write(f"# Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
        
        f.write("## Overall Statistics\n")
        f.write(f"Total files analyzed: {len(df)}\n")
        f.write(f"Map types: {', '.join(df['map_type'].unique())}\n")
        f.write(f"Size range: {df['map_size'].min()} - {df['map_size'].max()}\n\n")
        
        f.write("## Performance Summary\n")
        f.write("| Metric | Min | Max | Mean | Std |\n")
        f.write("|--------|-----|-----|------|-----|\n")
        
        metrics = ['parse_time', 'algo_time', 'total_time']
        for metric in metrics:
            stats = df[metric].describe()
            f.write(f"| {metric} | {stats['min']:.6f} | {stats['max']:.6f} | {stats['mean']:.6f} | {stats['std']:.6f} |\n")
        
        f.write("\n## Performance by Map Type\n")
        for map_type in sorted(df['map_type'].unique()):
            data = df[df['map_type'] == map_type]
            f.write(f"\n### {map_type}\n")
            f.write(f"- Files: {len(data)}\n")
            f.write(f"- Parse time: {data['parse_time'].mean():.6f}s (±{data['parse_time'].std():.6f}s)\n")
            f.write(f"- Algo time: {data['algo_time'].mean():.6f}s (±{data['algo_time'].std():.6f}s)\n")
            f.write(f"- Total time: {data['total_time'].mean():.6f}s (±{data['total_time'].std():.6f}s)\n")
            
            # Ratio parsing/total
            ratio = data['parse_time'] / data['total_time']
            f.write(f"- Parse ratio: {ratio.mean():.3f} (±{ratio.std():.3f})\n")
        
        f.write("\n## Complexity Analysis\n")
        f.write("Estimated complexity (based on size scaling):\n")
        
        # Analyse de complexité simple
        for map_type in sorted(df['map_type'].unique()):
            data = df[df['map_type'] == map_type]
            if len(data) > 1:
                correlation = data['map_size'].corr(data['algo_time'])
                f.write(f"- {map_type}: correlation size/algo_time = {correlation:.3f}\n")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 analyze_benchmark.py <benchmark_results.csv>")
        sys.exit(1)
    
    csv_file = sys.argv[1]
    if not os.path.exists(csv_file):
        print(f"Fichier non trouvé: {csv_file}")
        sys.exit(1)
    
    print("Chargement des données...")
    df = load_benchmark_data(csv_file)
    if df is None:
        sys.exit(1)
    
    print("Extraction des informations sur les maps...")
    df = extract_map_info(df)
    
    # Créer le dossier de sortie
    output_dir = "benchmark_analysis"
    os.makedirs(output_dir, exist_ok=True)
    
    print("Génération des graphiques...")
    try:
        generate_performance_plots(df, output_dir)
        print(f"Graphiques sauvegardés dans {output_dir}/")
    except ImportError:
        print("matplotlib non disponible, génération des graphiques ignorée")
    
    print("Génération du rapport...")
    generate_statistics_report(df, f"{output_dir}/analysis_report.md")
    
    print("\nAnalyse terminée!")
    print(f"Résultats disponibles dans: {output_dir}/")
    print(f"- analysis_report.md: Rapport détaillé")
    print(f"- performance_analysis.png: Graphiques de performance")
    print(f"- density_analysis.png: Analyse de l'impact de la densité")

if __name__ == "__main__":
    main()
