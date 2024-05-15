// patient.c

#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

// Fonction pour ajouter un patient
void ajouterPatient() {
    FILE *fichierPatients = fopen("patients.txt", "a");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    Patient nouveauPatient;

    printf("Entrez les informations du nouveau patient :\n");
    printf("ID : ");
    scanf("%d", &nouveauPatient.id);
    printf("Nom : ");
    scanf("%s", nouveauPatient.nom);
    printf("Prenom : ");
    scanf("%s", nouveauPatient.prenom);
    printf("Âge : ");
    scanf("%d", &nouveauPatient.age);

    // Utiliser un séparateur virgule sans espace après la virgule
    fprintf(fichierPatients, "%d,%s,%s,%d\n", nouveauPatient.id, nouveauPatient.nom, nouveauPatient.prenom, nouveauPatient.age);

    fclose(fichierPatients);

    printf("Patient ajouté avec succès.\n");
}


// Fonction pour afficher tous les patients
void afficherPatients() {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    printf("Liste des patients :\n");

    Patient patientActuel;
    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        printf("%d,%s,%s,%d\n",
               patientActuel.id, patientActuel.nom, patientActuel.prenom, patientActuel.age);
    }

    fclose(fichierPatients);
}


// Fonction pour mettre à jour les informations d'un patient
void mettreAJourPatient(int id) {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "a"); // Ouvrir en mode ajout
    if (tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp.txt");
        fclose(fichierPatients);
        return;
    }

    Patient patientActuel;
    int patientTrouve = 0;

    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        if (patientActuel.id == id) {
            printf("Nouvelles informations pour le patient %d :\n", id);
            printf("Nom : ");
            scanf("%s", patientActuel.nom);
            printf("Prenom : ");
            scanf("%s", patientActuel.prenom);
            printf("Âge : ");
            scanf("%d", &patientActuel.age);
            patientTrouve = 1;
        }
        fprintf(tempFile, "%d,%s,%s,%d\n", patientActuel.id, patientActuel.nom, patientActuel.prenom, patientActuel.age);
    }

    fclose(fichierPatients);
    fclose(tempFile);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (patientTrouve) {
        printf("Mise à jour réussie.\n");
    } else {
        printf("Patient avec l'ID %d non trouvé.\n", id);
    }
}


// Fonction pour supprimer un patient
void supprimerPatient(int id) {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w"); // Ouvrir en mode écriture, mais pas en mode "w"
    if (tempFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier temp.txt");
        fclose(fichierPatients);
        return;
    }

    Patient patientActuel;
    int patientTrouve = 0;

    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        if (patientActuel.id == id) {
            patientTrouve = 1;
        } else {
            fprintf(tempFile, "%d,%s,%s,%d\n", patientActuel.id, patientActuel.nom, patientActuel.prenom, patientActuel.age);
        }
    }

    fclose(fichierPatients);
    fclose(tempFile);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (patientTrouve) {
        printf("Patient avec l'ID %d supprimé avec succès.\n", id);
    } else {
        printf("Patient avec l'ID %d non trouvé.\n", id);
    }
}


// Fonction pour trier les patients par ID dans le fichier
void trierPatientsParID() {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    // Lire tous les patients dans un tableau
    int nombrePatients = 0;
    while (fscanf(fichierPatients, "%*d,%*[^,],%*[^,],%*d\n") != EOF) {
        nombrePatients++;
    }

    rewind(fichierPatients);

    Patient *patients = malloc(nombrePatients * sizeof(Patient));
    if (patients == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(fichierPatients);
        return;
    }

    for (int i = 0; i < nombrePatients; i++) {
        fscanf(fichierPatients, "%d,%[^,],%[^,],%d\n", &patients[i].id, patients[i].nom, patients[i].prenom, &patients[i].age);
    }

    fclose(fichierPatients);

    // Trier les patients par ID
    qsort(patients, nombrePatients, sizeof(Patient), comparerPatients);

    // Réécrire les patients triés dans le fichier
    fichierPatients = fopen("patients.txt", "w");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        free(patients);
        return;
    }

    for (int i = 0; i < nombrePatients; i++) {
        fprintf(fichierPatients, "%d,%s,%s,%d\n", patients[i].id, patients[i].nom, patients[i].prenom, patients[i].age);
    }

    fclose(fichierPatients);
    free(patients);

    printf("Patients triés par ID avec succès.\n");
}

// Fonction de comparaison pour qsort
int comparerPatients(const void *a, const void *b) {
    return ((const Patient *)a)->id - ((const Patient *)b)->id;
}

// Fonction pour rechercher un patient par ID
void rechercherPatientParID(int id) {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    Patient patientActuel;
    int patientTrouve = 0;

    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        if (patientActuel.id == id) {
            printf("Patient trouvé :\n");
            printf("ID : %d\n", patientActuel.id);
            printf("Nom : %s\n", patientActuel.nom);
            printf("Prénom : %s\n", patientActuel.prenom);
            printf("Âge : %d\n", patientActuel.age);
            patientTrouve = 1;
            break;  // Stop searching once the patient is found
        }
    }

    fclose(fichierPatients);

    if (!patientTrouve) {
        printf("Patient avec l'ID %d non trouvé.\n", id);
    }
}

// Fonction pour rechercher un patient par nom
void rechercherPatientParNom(const char *nom) {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    Patient patientActuel;
    int patientTrouve = 0;

    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        if (strcmp(patientActuel.nom, nom) == 0) {
            printf("Patient trouvé :\n");
            printf("ID : %d\n", patientActuel.id);
            printf("Nom : %s\n", patientActuel.nom);
            printf("Prénom : %s\n", patientActuel.prenom);
            printf("Âge : %d\n", patientActuel.age);
            patientTrouve = 1;
            // You can continue searching to find all patients with the same name
        }
    }

    fclose(fichierPatients);

    if (!patientTrouve) {
        printf("Patient avec le nom %s non trouvé.\n", nom);
    }
}

// Fonction pour exporter les patients au format CSV
void exporterPatientsCSV() {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    FILE *fichierExportCSV = fopen("patients_export.csv", "w");
    if (fichierExportCSV == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients_export.csv");
        fclose(fichierPatients);
        return;
    }

    fprintf(fichierExportCSV, "ID,Nom,Prénom,Âge\n");

    Patient patientActuel;
    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        fprintf(fichierExportCSV, "%d,%s,%s,%d\n", patientActuel.id, patientActuel.nom, patientActuel.prenom, patientActuel.age);
    }

    fclose(fichierPatients);
    fclose(fichierExportCSV);

    printf("Patients exportés au format CSV avec succès.\n");
}

// Fonction pour afficher les statistiques des patients
void afficherStatistiques() {
    FILE *fichierPatients = fopen("patients.txt", "r");
    if (fichierPatients == NULL) {
        perror("Erreur lors de l'ouverture du fichier patients.txt");
        return;
    }

    int totalAge = 0;
    int nombrePatients = 0;
    int ageMin = INT_MAX;
    int ageMax = INT_MIN;

    Patient patientActuel;

    while (fscanf(fichierPatients, "%d,%[^,],%[^,],%d", &patientActuel.id, patientActuel.nom, patientActuel.prenom, &patientActuel.age) == 4) {
        // Calculer la somme totale des âges
        totalAge += patientActuel.age;

        // Mettre à jour l'âge minimum et maximum
        if (patientActuel.age < ageMin) {
            ageMin = patientActuel.age;
        }

        if (patientActuel.age > ageMax) {
            ageMax = patientActuel.age;
        }

        nombrePatients++;
    }

    fclose(fichierPatients);

    if (nombrePatients > 0) {
        // Calculer la moyenne des âges
        double moyenneAge = (double)totalAge / nombrePatients;

        printf("Statistiques des patients :\n");
        printf("Nombre total de patients : %d\n", nombrePatients);
        printf("Âge moyen des patients : %.2f\n", moyenneAge);
        printf("Âge minimum parmi les patients : %d\n", ageMin);
        printf("Âge maximum parmi les patients : %d\n", ageMax);
    } else {
        printf("Aucun patient trouvé pour calculer les statistiques.\n");
    }
}

