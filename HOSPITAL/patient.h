#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

// Structure de données pour représenter un patient
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    int age;
} Patient;

// Prototypes des fonctions CRUD pour les patients
void ajouterPatient();
void afficherPatients();
void mettreAJourPatient(int id);
void supprimerPatient(int id);
void trierPatientsParID(); // Nouvelle fonction
// Prototypes des fonctions de recherche pour les patients
void rechercherPatientParID(int id);
void rechercherPatientParNom(const char *nom);
// Prototype de la fonction d'exportation des patients au format CSV
void exporterPatientsCSV();
// Prototype de la fonction pour afficher les statistiques des patients
void afficherStatistiques();



// Fonction de comparaison pour qsort
int comparerPatients(const void *a, const void *b);

#endif // PATIENT_H_INCLUDED
