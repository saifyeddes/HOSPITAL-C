// main.c

#include <stdio.h>
#include "patient.h"

int main() {
    int choix;
    int id;
    char nomRecherche[50];

    do {
        // Afficher le menu et obtenir le choix de l'utilisateur
        printf("\n1. Ajouter un patient\n");
        printf("2. Afficher les patients\n");
        printf("3. Mettre à jour un patient\n");
        printf("4. Supprimer un patient\n");
        printf("5. Rechercher un patient par ID\n");
        printf("6. Rechercher un patient par nom\n");
        printf("7. Trie les patients par ID\n");
        printf("8. exporterPatientsCSV\n");
        printf("9. afficherStatistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterPatient();
                break;
            case 2:
                afficherPatients();
                break;
            case 3:
                printf("Entrez l'ID du patient à mettre à jour : ");
                scanf("%d", &id);
                mettreAJourPatient(id);
                break;
            case 4:
                printf("Entrez l'ID du patient à supprimer : ");
                scanf("%d", &id);
                supprimerPatient(id);
                break;
            case 5:
                printf("Entrez l'ID du patient à rechercher : ");
                scanf("%d", &id);
                rechercherPatientParID(id);
                break;
            case 6:
                printf("Entrez le nom du patient à rechercher : ");
                scanf("%s", nomRecherche);
                rechercherPatientParNom(nomRecherche);
                break;
            case 7:
                trierPatientsParID();
                break;
                // ...
case 8:
    exporterPatientsCSV();
    break;
// ...
// ...
case 9:
    afficherStatistiques();
    break;
// ...


            case 0:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}
