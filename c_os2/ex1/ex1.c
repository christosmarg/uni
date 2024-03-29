#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 1: Άσκηση 1 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex1.c -o ex1`
 */

int
main(int argc, char *argv[])
{
	pid_t pid1, pid2, pid3, pid4, pid5;

	/*
	 * Το παρακάτω πρόγραμμα παράγει 7 διεργασίες. Το παρακάτω διάγραμμα
	 * περιγράφει την συγγένεια μεταξύ των διεργασιών που δημιουργήθηκαν.
	 *
	 *		P0
	 *	      / | \
	 *	     P2 P1 P3
	 *	    /	|
	 *	   P3	P4
	 *		|
	 *		P5
	 *
	 * Πιο αναλυτικά, το πρόγραμμα λειτουργεί ως εξής:
	 * - pid1 = fork(): δημιουργείται από την αρχική διεργασία ένα
	 * child.
	 * - Αν βρισκόμαστε στον πατέρα, τότε
	 *	- pid2 = fork();
	 *	- pid3 = fork();
	 *	Δηλαδή δημιουργούμε άλλες 3 διεργασίες.
	 * - Αν βρισκόμαστε στο παιδί, δημιουργούμε άλλη μία διεργασία
	 *   με την pid4 = fork().
	 * - Το παιδί που δημιουργεί η παραπάνω διεργασία, παράγει άλλη
	 *   μία διεργασία με την pid5 = fork().
	 */

	if ((pid1 = fork()) != 0) {
		pid2 = fork();
		pid3 = fork();
	} else {
		if ((pid4 = fork()) == 0)
			pid5 = fork();
	}

	return 0;
}
