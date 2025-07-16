#!/bin/bash

# Test de solidité du parser BSQ
echo "=== Tests de solidité du parser BSQ ==="

# Test 1: Fichier avec caractères identiques
echo "Test 1: Caractères identiques"
cat > test_invalid_chars.bsq << 'EOF'
3...
...
...
...
EOF
./bsq test_invalid_chars.bsq
echo "Résultat: $?"

# Test 2: Fichier avec caractères non-printables
echo -e "\nTest 2: Caractères non-printables"
printf "3.\x01X\n...\n...\n...\n" > test_non_printable.bsq
./bsq test_non_printable.bsq
echo "Résultat: $?"

# Test 3: Lignes de longueur différente
echo -e "\nTest 3: Lignes de longueur différente"
cat > test_different_length.bsq << 'EOF'
3.oX
.o.
.o
.o.
EOF
./bsq test_different_length.bsq
echo "Résultat: $?"

# Test 4: Fichier vide
echo -e "\nTest 4: Fichier vide"
touch test_empty.bsq
./bsq test_empty.bsq
echo "Résultat: $?"

# Test 5: Nombre de lignes incorrect
echo -e "\nTest 5: Nombre de lignes incorrect"
cat > test_wrong_lines.bsq << 'EOF'
5.oX
.o.
.o.
EOF
./bsq test_wrong_lines.bsq
echo "Résultat: $?"

# Test 6: Caractères invalides dans la map
echo -e "\nTest 6: Caractères invalides dans la map"
cat > test_invalid_map_chars.bsq << 'EOF'
3.oX
.o.
.x.
.o.
EOF
./bsq test_invalid_map_chars.bsq
echo "Résultat: $?"

# Test 7: Fichier valide (doit fonctionner)
echo -e "\nTest 7: Fichier valide"
cat > test_valid.bsq << 'EOF'
3.oX
.o.
.o.
.o.
EOF
./bsq test_valid.bsq
echo "Résultat: $?"

# Nettoyage
rm -f test_*.bsq

echo -e "\n=== Tests terminés ==="
echo "Les tests 1-6 doivent échouer (code de retour != 0)"
echo "Le test 7 doit réussir (code de retour = 0)"
