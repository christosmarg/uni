#include <stdio.h>
#include <string.h>
#include <string>
#include <new>
#include <iostream>

using namespace std;

class BigInt
{
public:
    static int MaxSize;
    static char *MaxNumb;
    static void PrintMax ();
private:
    int size;
	char *numb;
public:
	BigInt ();
	BigInt (const char *);
	BigInt (int);
	BigInt (const BigInt &);
	~BigInt ();
	void Print () const;
    void operator+= (const BigInt &);
    void operator+= (int );
    BigInt operator+ (BigInt &); 
    BigInt operator+ (const char *);
    BigInt operator+ (const int);
    BigInt operator* (const BigInt &);
    BigInt operator= (const BigInt &);
    BigInt operator++ ();
    BigInt operator++ (int);
    BigInt operator-- ();
    BigInt operator-- (int);
    int operator== (const BigInt &);
    int operator!= (const BigInt &);

};

class LibExc 
{
public:
    int ErrCode;
    string ErrMess;
    LibExc (int C, string M)
    {
        ErrCode = C;
        ErrMess = M;
    }
};

int BigInt::MaxSize = 0;

char *BigInt::MaxNumb = NULL;

void BigInt::PrintMax () 
{
    int i;
    if (MaxNumb)
    {
        printf ("*");
        for ( i = MaxSize - 1; i >= 0; i--)
            printf ("%c", MaxNumb[i] + 48);
        printf ("*\n");
    }
}

BigInt::BigInt ()
{
	size = 1;
	numb = new (nothrow) char [1];
    if (numb == NULL)
        throw (1);
	numb[0] = 0;
}

BigInt::BigInt (const char *s)
{
	//printf("constructing string %s \n",s);
	int i;
	int l = strlen(s);
    for (i = 0; i <l; i++)
    {
        if (s[i] < '0' || s[i] > '9')
            throw (2);
    }
	if (l)
	{
		numb = new (nothrow) char [l];
        if (!numb)
            throw (1);
		for(i = 0; i < l; i++)
			numb[i] = s[l - 1 - i] - 48;
		size = l;
	}
	if (l > BigInt::MaxSize)
    {
        MaxSize = l;
        MaxNumb = numb;
    }
}

BigInt::BigInt (int nu)
{
	//printf("constructing int %d\n",nu);
	char *s;
	s = new char [12];
	sprintf (s, "%d", nu);
	int i;
	int l = strlen(s);
	if (l)
	{
		numb = new (nothrow) char [l];
        if (numb == NULL)
            throw (1);
		for(i = 0; i < l; i++)
			numb[i] = s[l - 1 - i] - 48;
		size = l;
	}
	delete[] s;
    if (l > BigInt::MaxSize)
    {
        MaxSize = l;
        MaxNumb = numb;
    }
}

BigInt::BigInt (const BigInt &x)     //Σβήστε το const και δείτε τι  συμβαίνει!!!
{
	//printf("Copy constructing\n");
	size = x.size;
	numb = new (nothrow) char [size];
    if (numb == NULL)
        throw (1);
	memcpy (numb, x.numb, size);
}

BigInt::~BigInt ()
{
	if (numb == MaxNumb)
        MaxNumb = NULL;
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

void BigInt::operator+= (const BigInt &x)
{
    int S1, S2, m, Kr = 0;
    int i;
    
    for(i = 0; i < size; i++)
    {
        numb[i] += x.numb[i] + Kr;
        if (numb[i] > 10)
        {
            numb[i] -= 10;
            Kr = 1;
        }
        else
            Kr = 0;
    }
}

void BigInt::operator+= (int i)
{
    printf ("I will not add %d\n", i);
}

BigInt BigInt::operator+ (BigInt &x)
{
    int i, j, s, Kr = 0, r, D1, D2, D;
    s = (size > x.size) ? size : x.size;
    char buf[s + 1];
    char buf1[s + 2];
    for (i = 0; i < s; i++)
    {
        D1 = (i < size) ? numb[i] : 0;
        D2 = (i < x.size) ? x.numb[i] : 0;
        D = D1 + D2 + Kr;
        Kr = 0;
        if (D > 9)
        {
            D -= 10;
            Kr = 1;
        }
        buf[i] = D;
    }
    if (Kr) 
        buf[i] = Kr;
    else
        i--;
    for (j = 0; i >= 0; j++, i--)
        buf1[j] = buf[i] + 48;
    buf1[j] = '\0';
    BigInt Q(buf1);
    return Q;
}

BigInt BigInt::operator+ (const char *s)
{
    BigInt Tmp(s);
    return *this + Tmp;
}   

BigInt BigInt::operator+ (int s)
{
    BigInt Tmp(s);
    return *this + Tmp;
}   

BigInt BigInt::operator= (const BigInt &x)    //Σβήστε το const και δείτε τι συμβαίνει
{
    delete[] numb;
    size = x.size;
    numb = new (nothrow) char [size];
    if (numb == NULL)
        throw (1);
    memcpy (numb, x.numb, size);
    return *this;
}

BigInt BigInt::operator++()
{
    int i;
    numb[0]++;
    for(i = 0; i < size - 1; i++)
        if (numb[i] == 10)
        {
            numb[i] = 0;
            numb[i + 1]++;
        }
    if (numb[size - 1] == 10)
    {
        numb[size - 1] = 0;
        char *buf1 = new (nothrow) char[++size];
        if (numb == NULL)
            throw (1);
        memcpy (buf1, numb, size - 1);
        buf1[size - 1] = 1;
        delete [] numb;
        numb = buf1;
    }
    return *this;
}

BigInt BigInt::operator++ (int )
{
    int i;
    BigInt tmp = *this;
    numb[0]++;
    for(i = 0; i < size - 1; i++)
        if (numb[i] == 10)
        {
            numb[i] = 0;
            numb[i + 1]++;
        }
    if (numb[size - 1] == 10)
    {
        numb[size - 1] = 0;
        char *buf1 = new (nothrow) char[++size];
        if (numb == NULL)
            throw (1);
        memcpy (buf1, numb, size - 1);
        buf1[size - 1] = 1;
        delete [] numb;
        numb = buf1;
    }
    return tmp;
}

BigInt BigInt::operator* (const BigInt &x)
{
    BigInt res = "0";
    BigInt t = x;
    BigInt z = 0;
    while (t != z)
    {
        res = res + *this;
//      printf("----");
//      res.Print();
        --t;
    }
    return res;
}


BigInt BigInt::operator-- ()
{
    int i;
    if ((numb[0] == 0) && (size == 1))
        return *this;
    numb[0]--;
    for(i = 0 ; i < size; i++)
    {
        if (numb[i] == -1)
        {
            numb[i] = 9;
            numb[i + 1]--;
        }
    }
    if (numb[size - 1] == 0 && size > 1)
    {
        char *buf1 = new char[--size];
        memcpy (buf1, numb, size);
        delete [] numb;
        numb = buf1;
    }
            
    return *this;
}

BigInt BigInt::operator--(int)
{
    BigInt tmp = *this;
    --*this;
    return tmp;
}

int BigInt::operator== (const BigInt &x)
{
    if (size != x.size) 
        return 0;
    for(int i = 0; i < size; i++)
        if (numb[i] != x.numb[i])
            return 0;
    return 1;
}

int BigInt::operator != (const BigInt &x)
{
    if (*this == x)
        return 0;
    return 1;
}

BigInt BigProduct (BigInt Num)
{
    Num++;
    BigInt I = 1;
    BigInt P = 1;
    while (I != Num)
    {
        P = P * I;
        I = I + 1;
    }
    return P;
}

BigInt Power (char *B, int E) 
{
    if (E < 0)
    {
        string m("Invalid Expmponent");
        LibExc e(2, m);
        throw e;
    }
    try
    {
        BigInt Ex(E);
        BigInt Ba(B);
        BigInt Res = 1;
        BigInt I = 0;
        while (I != Ex)
        {
            Res = Res * Ba;
            I++;
            //Res.Print ();
            //cout << endl;
        }
        return Res;
    }
    catch (int e)
    {
        if (e == 1)
            throw;
        if (e == 2)
            throw LibExc (1, *(new string ("Invalid Base:")));
    }
}

main ()
{
    int i;
    char N[100];
    bool cont;
    do
    {
        cont = false;
        try
        {
            cout << "Enter Number to find Product:"; 
            cin >> N;
            BigInt x;
            BigInt k(N);
            x = BigProduct (k);
            x.Print();
        }
        catch (int e)
        {
            if (e == 1)
            {
                cout << "Memory Error: " << BigInt::MaxNumb;
                cout << BigInt::MaxSize << "  "; BigInt::PrintMax ();
            }
            if (e == 2)
            {
                cout << "Initialization Error" << endl;
                cont = true;
            }
        }
    }
    while (cont);
    cout << "========================================================================" << endl;
    try
    {
        char B[100];
        int E;
        cout << "Base: ";
        cin >> B;
        cout << "Exponent: ";
        cin >> E;
        BigInt a = Power (B, E);
        a.Print ();
    }
    catch (int e)
    {
        cout << "Memory Error: " << BigInt::MaxNumb;
        cout << BigInt::MaxSize << "  "; BigInt::PrintMax ();
    }
    catch (LibExc e)
    {
        cout << "Parameter Error" << endl;
        cout << e.ErrCode << " " << e.ErrMess << endl;
    }
}
