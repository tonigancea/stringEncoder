#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//definire structura
typedef struct pereche {
	char *sir;
	double power;
} pereche;

//functia adauga campurile structuri ordonate in vectorul final pentru afisare
void addtostring2 (pereche *a, char *q, int n, int *size2) {
	
	for(int i=0;i<n;i++){
		strcat(q,a[i].sir);
			if(strlen(q) == *size2)
				break;
		strcat(q,a[n-i-1].sir);
			if(strlen(q) == *size2)
				break;
		}
	}

//functia schimba 2 structuri in vectorul de structuri
void schimba (pereche *a, pereche *b) {
	pereche aux;
	aux = *a;
	*a = *b;
	*b = aux;
	}

//functia ordoneaza structurile in vectorul de structuri
void order (pereche *a, int n, int *x) {
	int done,i;	
	
	do {
		done = 1;
		for(i=0;i<n;i++) {
			if(a[i].power < a[i+1].power) {
				schimba(&a[i],&a[i+1]);
				done = 0;
				}
			if(a[i].power == a[i+1].power) //cazul in care power is equal
					if(strcmp(a[i].sir,a[i+1].sir) > 0 ){
						schimba(&a[i],&a[i+1]);
						done = 0;
						}
				}
		} while (!done);	
	}

//functia adauga complexitatea in structuri, pentru fiecare subsir
void power (char *b, double *x) {
	int i,nr;
	double s = 0;
	
	for(i=0;i<strlen(b);i++)
		s = s + (int)*(b+i);
	nr = (int)strlen(b);
	*x = s/nr;
	}

//functia imparte sirul in subsiruri si le organizeaza in structuri
void organizareStruct (char *v, int n, pereche *a, int *x) {
	int m = strlen(v), i;
	*x = m/n;
	char aux[m];
	
	for (i=0;i<n-1;i++) {
		strcpy(aux,v+(*x));
		strcpy(v+(*x),v+m);
		strcpy(a[i].sir,v);
		strcpy(v,aux);
		}
				//ultimul caz este tratat special pentru ca
	strcpy(a[n-1].sir,v); 	//impartirea poate da cu rest
	}

//functia aloca dinamic memorie pentru vectorul de structuri
void alocareStruct (char *v, int n, pereche *a) {
	int m = strlen(v);
	int i;

	for(i=0;i<n-1;i++)
		a[i].sir = malloc(m/n*sizeof(char));
	
	//ultima structura este tratat separat pentru cazul
	//in care impartirea da cu rest
	a[n-1].sir = malloc((m/n+m%n)*sizeof(char)); 
	}
//functia afla caracterele cele mai uzuale / cele mai putin uzuale din sir
//functia este necesara pentru codificare caracterelor
void codificarec (char *v, char *vec1, char *vec2) {
	int i,j;
	int nr, min = strlen(v), max = 1;
	int b[strlen(v)];

	for (i=0;i<strlen(v);i++) {
		nr = 0;
		for (j=0;j<strlen(v);j++)
			if (v[i] == v[j])
				nr++;
		b[i] = nr;
		if (nr <= min)
			min = nr;
		if (nr > max)
			max = nr;
		}
	for (i=0;i<strlen(v);i++) {
		if (b[i] == max) {
			max = i;
			break;
			}
		}
	for (i=0;i<strlen(v);i++) {
		if (b[i] == min) {
			min = i;
			break;
			}
		}
	*vec1 = v[max];
	*vec2 = v[min];
	}


//aflarea numarului de cifre ale unui numar
//functia este necesara in functia de codificare a numerelor
long dimCifre (long m) {
	long dim = 0;
	
	while(m>0) {
		dim++;
		m=m/10;
		}
	return dim;
	}

//functia face permutari
//functia este necesara in functia de codificare a numerelor
long rotatie (long m) {
	long q=1, z=m;
	
	while (z>9) {	
		z=z/10;
		q=q*10;
		}
	m=m%q*10+z;
	return m;
	}

//functia determina abs() pentru un long
//functia este necesara in functia de codificare a numerelor
long absolut (long m) {
	if(m>=0)
		return m;
	return -m; //evident m<0
	}

//functia afla extremele necesare
//functia este necesara in functia de codificare a numerelor
long minOrMax (long m) {
	int i;
	long p = absolut(m);
	long min =  2147483647;	//biggest for long in our range
	long max =  0;		//lowest for long in our range
	
	for (i=1;i<=dimCifre(p)+1;i++) {
		p = rotatie(p);
		if (p<min)
			min = p;
		if (p>max)
			max = p;
		}
	if (m>=0)
		return max;
	
	return min; // inseamna ca m<0
	}

//functia codifica numerele conform cerintei
long codificaren (long n) {
	
	return minOrMax(n);
	}


//functia adauga stringul in sir
void addtostring(char *d, char **v, int *size2, int *cap2) {
	
	if(*size2+50 > *cap2) {
		*v = (char*)realloc(*v,*cap2*2*sizeof(char));
		*(cap2) = *(cap2)*2;
		}

	strcat((*v+*size2),d);
	*(size2) = *(size2) + strlen(d);
	}



//functia afla divizorul maxim - necesar in functia codificarew
int divizormax (int n) {
	int i,max;
	
	max = 0;	
	for(i=1;i<=n/2;i++)
		if(n%i==0 && i>max)
			max = i;
	return max;
	}

//functia codifica cuvintele
void codificarew (char *c) {
	char aux[50];
	int i,ok=0;
	char p[50];
	
	for (i=0;i<strlen(c);i++)
		if ( (int)c[i] >= 48 && (int)c[i] <= 57 )
			ok=1;
	
	//partea a doua a cuvantului se copiaza in auxiliar
	strcpy(aux,c+divizormax(strlen(c)));

	//se sterge partea a doua a cuvantului din sirul original
	strcpy(c+divizormax(strlen(c)),c+strlen(c));

	//auxiliarul se inverseaza (daca e necesar)
	if(ok == 1)
		for(i=0;i<strlen(aux)/2;i++) {
			p[i] = aux[i];
			aux[i] = aux[strlen(aux)-i-1];
			aux[strlen(aux)-i-1] = p[i];
			}
	
	//concatenarea celor doua parti
	strcat(aux,c);
	
	//auxiliarul se copiaza in locatia sirului
	strcpy(c,aux);
	}

//functia testare, testeaza fiecare termen.
//daca termenul ete cuvant, functia scoate return 1
//daca termenul este caracter, functia scoate return 2
//daca termenul este numar, functia scoate return 3
int testare (char *b) {
	
	int a,i,ok1=0,ok2=0,ok3=0;
	
	//testare caracter
	if (strlen(b) == 1) {
		a = (int)b[0];
		if ( (a >= 32 && a <= 47 ) || ( a >= 58 && a <= 126 ) )
		return 2;
		}
	
	//testare numar
	for (i=0;i<strlen(b);i++) {
		a = (int)b[i];
		if (!(a >= 49 && a <= 57))
			ok1 = 1;
			}

	if ( (int)b[0] == 45 ) {
		for (i=1;i<strlen(b);i++) {
			a = (int)b[i];
			if (!(a >= 49 && a <= 57))
				ok2=1;
			}
		if(ok2 == 0) {
			return 3;
			}
		}

	if (ok1 == 0) {
		return 3;
		}
		
	//testare cuvant
	for (i=0;i<strlen(b);i++) {	
		a = (int)b[i];
		if (!(a >= 32 && a <= 126))
			ok3=1;
		}

	if (ok3 == 0) {
		return 1;
		}
	
	return 0;
	}

//functia este folosita in cazul realocarii
void realocare(char*** s, int* cap) {
	*s = (char**)realloc(*s,*cap*2*sizeof(char*));
	(*cap) = (*cap)*2;
	}

//functia citeste termeni pana la intalnirea lui END
void citire (char*** s, int *size, int *cap) {
	char termen[50]; 

	while (scanf("%s",termen)) {
		if(strcmp("END",termen) == 0)
			break;

		if (*cap == *size) {
			//realocare, cand size ajunge la capacitate
			realocare(s,cap);
			}

		//alocare dinamica pentru fiecare termen citit
		(*s)[*size] = (char*) malloc ((strlen(termen)+1)*sizeof(char));
		strcpy ((*s)[*size], termen);

		(*size)++;
		
		}
	}

//alocare initiala
void alocare (char*** s, int* cap) {	
	*s = (char**)malloc(*cap*sizeof(char*));
	}

int main()
{
char **s;
int size = 0, cap = 5000, j;
int wc=0, cc=0, nc=0;
int size2 = 0, cap2 = 5000;
char *v;
long w;
char *vec1, *vec2;
int n;
pereche *a;
char *q;
int x;

vec1 = (char*)malloc(sizeof(char));
vec2 = (char*)malloc(sizeof(char));

s = (char**)malloc(cap*sizeof(char*));
citire(&s,&size,&cap);

for(j=0;j<size-1;j++) {
	switch(testare(s[j])) { 
		case 1:
		wc++; break;
		case 2:
		cc++; break;
		case 3:
		nc++; break;
		}
}

printf("%d %d %d\n",wc,cc,nc);

v = (char*)malloc(cap2*sizeof(char));

for(j=0;j<size-1;j++)
	switch(testare(s[j])) {
		case 1:
		codificarew(s[j]);
		addtostring(s[j],&v,&size2,&cap2);
		break;
		case 2:
		codificarec(v,vec1,vec2);
		addtostring(vec1,&v,&size2,&cap2);
		addtostring(s[j],&v,&size2,&cap2);
		addtostring(vec2,&v,&size2,&cap2);
		break;
		case 3:
		w=(codificaren(atol(s[j])));
		sprintf(s[j],"%ld",w);
		addtostring(s[j],&v,&size2,&cap2);
		break;
		}


printf("%s\n",v);

n = atoi(s[size-1]);
a = malloc(n*sizeof(struct pereche));

alocareStruct(v,n,a);
organizareStruct(v,n,a,&x);

int m = strlen(v);
for(j=0;j<n;j++)
	power(a[j].sir,&a[j].power);

order(a,n,&x);
//free(s);

q = (char*)malloc(m*sizeof(char));
addtostring2(a,q,n,&size2);
printf("%s\n",q);

free(v);
free(a);

return 0;
}
