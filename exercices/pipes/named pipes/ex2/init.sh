# Nettoyage des anciens tubes si nécessaire
rm -f /tmp/fifo_a_to_b /tmp/fifo_b_to_a

# Création des tubes nommés
mkfifo /tmp/fifo_a_to_b
mkfifo /tmp/fifo_b_to_a

echo "Tubes créés. Vous pouvez lancer Bob puis Alice."