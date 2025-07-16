#!/bin/bash

# Script pour générer des maps de différentes tailles avec différentes densités
# Utilise le script Perl mapgen.pl pour générer les maps

# Définir les tailles de maps
sizes=(
    "10x10:10:10"
    "100x100:100:100"
    "1000x1000:1000:1000"
    "5000x5000:5000:5000"
)

# Créer le dossier principal pour les maps
mkdir -p maps

# Chemin vers le script Perl
PERL_SCRIPT="mapgen.pl"

# Vérifier que le script Perl existe
if [ ! -f "$PERL_SCRIPT" ]; then
    echo "Erreur: Script Perl $PERL_SCRIPT non trouvé!"
    exit 1
fi

echo "Génération des maps en cours..."

# Pour chaque taille
for size_info in "${sizes[@]}"; do
    # Extraire les informations (nom:largeur:hauteur)
    IFS=':' read -ra SIZE_PARTS <<< "$size_info"
    size_name="${SIZE_PARTS[0]}"
    width="${SIZE_PARTS[1]}"
    height="${SIZE_PARTS[2]}"
    
    echo "Génération des maps $size_name..."
    
    # Créer le dossier pour cette taille
    mkdir -p "maps/$size_name"
    
    # Générer 100 maps avec différentes densités
    for i in $(seq 1 100); do
        # Générer une densité aléatoire entre 1 et 9
        density=$((RANDOM % 9 + 1))
        
        # Nom du fichier de map
        map_file="maps/$size_name/map_${size_name}_${i}_density${density}.bsq"
        
        # Générer la map avec le script Perl
        perl "$PERL_SCRIPT" "$width" "$height" "$density" > "$map_file"
        
        # Afficher le progrès tous les 10 fichiers
        if [ $((i % 10)) -eq 0 ]; then
            echo "  $size_name: $i/100 maps générées"
        fi
    done
    
    echo "  $size_name: 100/100 maps générées ✓"
done

echo ""
echo "Génération terminée!"
echo "Structure des dossiers créée:"
echo "maps/"
for size_info in "${sizes[@]}"; do
    IFS=':' read -ra SIZE_PARTS <<< "$size_info"
    size_name="${SIZE_PARTS[0]}"
    count=$(ls -1 "maps/$size_name" | wc -l)
    echo "  $size_name/ ($count fichiers)"
done
