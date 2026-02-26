import csv
import matplotlib.pyplot as plt
from tkinter import Tk, filedialog
import statistics

# --- Boîte de dialogue pour choisir le fichier ---
Tk().withdraw()
csv_file = filedialog.askopenfilename(
    title="Choisir un fichier CSV",
    filetypes=[("Fichiers CSV", "*.csv")]
)

if not csv_file:
    raise SystemExit("Aucun fichier sélectionné.")

# --- Lecture du CSV ---
data = []
with open(csv_file, "r") as f:
    reader = csv.reader(f)
    for row in reader:
        for v in row:
            data.append(float(v))

# --- Statistiques ---
minimum = min(data)
maximum = max(data)
moyenne = statistics.mean(data)
variance = statistics.variance(data)

# Gestion du mode (peut lever une erreur si pas unique)
try:
    mode = statistics.mode(data)
except statistics.StatisticsError:
    mode = "Pas de mode unique"

print("\n--- Statistiques ---")
print(f"Min      : {data[0]}")
print(f"Max      : {data[1]}")
print(f"Moyenne  : {data[2]}")
print(f"Variance : {data[3]}")
print(f"Mode     : {data[4]}")

# --- Supprimer les 5 premières valeurs ---
data = data[5:]

# Axe X
x = range(len(data))

# --- Plot ---
plt.figure(figsize=(10, 4))
plt.plot(x, data, color="red", linewidth=1)
plt.fill_between(x, data, color="red", alpha=0.15)
plt.axis("off")
plt.tight_layout()
plt.show()
