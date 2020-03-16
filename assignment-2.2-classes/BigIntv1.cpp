#include <stdio.h>
#include <string.h>
#include <string>
#include <new>

using namespace std;

class BigInt
{
	int size;
	char *numb;
public:
	BigInt ();
	BigInt (const char *);
	BigInt (int);
	BigInt (const BigInt &);
	~BigInt ();
	void Print () const;

};

BigInt::BigInt ()
{
	size = 1;
	numb = new char [1];
	numb[0] = 0;
}

BigInt::BigInt (const char *s)
{
	printf("constructing string %s \n",s);
	int i;
	int l = strlen(s);
	if (l)
	{
		numb = new char [l];
		for(i = 0; i < l; i++)
			numb[i] = s[l - 1 - i] - 48;
		size = l;
	}
}

BigInt::BigInt (int nu)
{
	printf("constructing int %d\n",nu);
	char *s;
	s = new char [12];
	sprintf (s, "%d", nu);
	int i;
	int l = strlen(s);
	if (l)
	{
		numb = new char [l];
		for(i = 0; i < l; i++)
			numb[i] = s[l - 1 - i] - 48;
		size = l;
	}
	delete[] s;
}

BigInt::BigInt (const BigInt &x)     //Σβήστε το const (εδώ και στο πρότυπο της κλάσης) και δείτε τι  συμβαίνει!!!
{
	printf("Copy constructing\n");
	size = x.size;
	numb = new char [size];
	memcpy (numb, x.numb, size);
}

BigInt::~BigInt ()
{
	printf("deleting ");
	Print();
	delete [] numb;
}

void BigInt::Print () const
{
	int i;
	printf ("*");
	for ( i = size - 1; i >= 0; i--)
		printf ("%c", numb[i] + 48);
	printf ("*\n");
}


void XXX (BigInt x)    //Τι συμβαίνει αν μπει αναφορά; Πως είναι καλύτερα;
{
    //Some functionality
    x.Print ();
}

int main()
{
    BigInt a;
    a.Print ();
    BigInt b = "123456789987654321";
    b.Print ();
    BigInt c = 100;
    c.Print ();
    BigInt d (123);            //Είναι ΑΚΡΙΒΩΣ το ίδιο με το προηγούμενο;; Σε τι θα μπορούσε να διαφέρει;;;
    d.Print ();
    BigInt e = b;
    e.Print ();
    BigInt f(b);
    f.Print ();
    printf ("================================\n");
    XXX (b);                    //Τι αλλάζει αν υπάρχει και όταν δεν υπάρχει αντιγραφέας;
    b.Print ();  
    
    XXX (25);
    
    //string q = "123";
    //BigInt z = q;
    //z.Print ();
}

