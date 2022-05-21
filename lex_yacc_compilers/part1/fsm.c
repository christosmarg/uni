#include <stdio.h>
#include <string.h>
#include<stdlib.h>

//////////////////// GLOBALS /////////////////////////////

#define MAXSTATE 130
#define MAXLINE 1010

const int EOFCHAR=128, ALLCHAR=129, NOINPUT=0;

// Comments_1:
// eksigeiste ti simainoun ta diafora fields tou struct state
typedef struct { 
	char * name;						
	int number;							
	int accepting;						
	int nextstate[MAXSTATE];			
} state ;

int numstates=0, statesize=0, trace=0, tracein=0;
state ** states;						

typedef struct entry {
	struct entry *next;
	state * contents;
} tableEntry;

tableEntry * table = NULL;	//Comments_2:  Se ti xrisimeuei auto?

char line[MAXLINE]; 
char filename[300];
int pos=0, linenum=0;
char symbol[110];
FILE *fin;

//////////////////// LOOKUP //////////////////////////////
// Comments_3: Ti apotelesma exei auti i sunartisi?
state *lookup(char *name) { 

	//Comments_4:  Ti akribws kanei auto to loop?
	if (table != NULL) {
		tableEntry *runner = table;
		while (runner != NULL) {
			if (strcmp(runner->contents->name, name) == 0) 
				return runner->contents;
			runner = runner->next;
		}
	}
		

	// Comments_5: Pote ekteleitai o parakatw kwdikas (mexri to telos tis sunartisis)
	// kai ti apotelesmata/synepeies exei?
	state *p= (state*) malloc(1*sizeof(state));
	p->name=strdup(name);						 
	numstates+=1;								

	int i; // Comments_6: Giati einai aparaitito auto to if-statement?
	if (numstates>=statesize) { 				
		int newsz=statesize*2;					
		state ** newst=(state **) malloc(newsz*sizeof(state *));
		for (i=0; i<numstates; i+=1)
			newst[i]=states[i];
		free(states);
		states=newst;
		statesize=newsz; 
	}

	states[numstates]=p;						
	p->number=numstates;
	p->accepting=0;
	for (i=0; i<MAXSTATE; i+=1) { 
		p->nextstate[i]=0;
	}
	tableEntry * newEntry = (tableEntry *) malloc (1*sizeof( tableEntry));
	newEntry->contents = p;
	newEntry->next = table;
	table = newEntry;
	return p; 
}


/////////////////// LOWER ///////////////////////////////

// Comments_7: Perigrapste ti apotelesma exei i ektelesi autis tis sunartisis

void lower(char *s) { 
	int i;
	for (i=0; 1; i+=1) { 
		char c=s[i];
		if (c==0) 		
			break;
		if (c>='A' && c<='Z') 
			s[i]=c+'a'-'A'; 
	} 
}

//////////////////// DECODE ///////////////////////////////

int decode(char *s) { 
	if (s[0]=='\\')
		return s[1];
	if (s[0]=='*' && s[1]==0)
		return ALLCHAR;
	if (strcasecmp(s, "EOF")==0)
		return EOFCHAR;
	if (s[1]==0)
		return s[0];
	fprintf(stderr, "fsm: Line %d of %s: '%s' is not a valid character representation\n", linenum, filename, s);
	exit(1);
	return 0; 
}

//////////////////// CHARSTRING ///////////////////////////

char *charstring(int c) { 
	static char s[10];
	if (c==ALLCHAR) return "ALL";
	if (c==EOFCHAR) return "EOF";
	if (c==NOINPUT) return "NONE";
	if (c=='\t') return "\\t";
	if (c=='\n') return "\\n";
	if (c==' ') return "\\s";
	if (c>' ' && c<127) { 
		s[0]=c;
		s[1]=0;
		return s; 
	}
	sprintf(s, "\\%03o", c);
	return s; 
}

///////////////////// VALIDSTATE ///////////////////////////

// Comments_8: Ti apotelesma exei auti i sunartisi?

int validstate(char *s) { 
	int i;
	for (i=0; 1; i+=1) { 
		char c=s[i];
		if (c==0) 
			return 1;
		if (c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9') 
			continue;
		if (c=='$' || c=='_' || c=='.') 
			continue;
		return 0; 
	} 
}

/////////////////////// SNEAKCH ////////////////////////////

// Comments_9: Poios einai o skopos autis tis sunartisis. Ti epistrefei?

char sneakch() { 
	char c=line[pos];
	pos+=1;
	while (c>0 && c<=' ' && c!='\n') { 
		c=line[pos];
		pos+=1; 
	}
	pos-=1;
	return c; 
} 

/////////////////////// GETSYM //////////////////////////////
// Comments_10: Poios einai o skopos autis tis sunartisis. 

void getsym() { 
	int len=0;
	char c=line[pos];
	pos+=1;
	while (c>0 && c<=' ' && c!='\n') { 
		c=line[pos];
		pos+=1; 
	}
	symbol[0]=c;
	symbol[1]=0;
	switch (c) { 
	case 0: { 
				pos-=1;
				fprintf(stderr, "fsm: Line %d of %s: Line Too Long\n", linenum, filename);
				exit(1); 
			}
	case '\n': 	pos-=1;
      			return;
    case 'a': case 'h': case 'o': case 'v': case 'C': case 'J': case 'Q': case 'X': case '4': case '_':
    case 'b': case 'i': case 'p': case 'w': case 'D': case 'K': case 'R': case 'Y': case '5': case '.':
    case 'c': case 'j': case 'q': case 'x': case 'E': case 'L': case 'S': case 'Z': case '6':
    case 'd': case 'k': case 'r': case 'y': case 'F': case 'M': case 'T': case '0': case '7':
    case 'e': case 'l': case 's': case 'z': case 'G': case 'N': case 'U': case '1': case '8':
    case 'f': case 'm': case 't': case 'A': case 'H': case 'O': case 'V': case '2': case '9':
    case 'g': case 'n': case 'u': case 'B': case 'I': case 'P': case 'W': case '3': case '$':
			{ 
				while (c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9' || c=='$' || c=='_' || c=='.') { 
					symbol[len]=c;
					len+=1;
					if (len>100) { 
						symbol[10]=0;
						fprintf(stderr, "fsm: Line %d of %s: Symbol '%s...' too long\n", linenum, filename, symbol);
						exit(1); 
					}
					c=line[pos];
					pos+=1; 
				}
				pos-=1;
				symbol[len]=0;
				return; 
			}
    case '-': { 
				if (line[pos]=='>') { 	
					pos+=1;
					symbol[1]='>';
					symbol[2]=0; 
				}
				return; 
			}
	case '/': { 
				if (line[pos]=='/') { 
					pos-=1;
					line[pos]='\n';
					line[pos+1]=0;
					symbol[0]='\n'; 
				}
				return; 
			}
    case '\\': { 
				if (line[pos]>' ' && line[pos]<127) { 
					c=line[pos];
					pos+=1;
					if (c=='n') 
						c='\n';
					else if (c=='t') 
						c='\t';
					else if (c=='s') 
						c=' ';
					else if (c>='0' && c<='7') { 
						int n=0;
						while (c>='0' && c<='7') { 
							n=n*8+c-'0';
							c=line[pos];
							pos+=1; 
						}
						pos-=1;
						c=n; 
					}
					symbol[1]=c;
					symbol[2]=0; 
				} 
		} 
	} 
}

//////////////////// PARSEARGS //////////////////////////////////

// Comments_11: Poios einai o skopos autis tis sunartisis?

void parseargs(int argc, char *argv[]) {
	filename[0]=0;
	int i;
  	for (i=1; i<argc; i+=1)
    	if (argv[i][0]!='-')
      		strcpy(filename, argv[i]);
    	else if (strcasecmp(argv[i], "-trace")==0)
      		trace=1;
    	else if (strcasecmp(argv[i], "-list")==0)
      		tracein=1;
  
	if (filename[0]!=0 && strstr(filename, ".")==NULL)
    	strcat(filename, ".fsm");
  
	fin=stdin;

  	if (filename[0]!=0) { 
		fin=fopen(filename, "r");
     	if (fin==NULL) { 
			fprintf(stderr, "fsm: can not open input file '%s'\n", filename);
        	exit(1); 
		} 
	}
	else
		strcpy(filename, "<stdin>");
}

//////////////////// MAIN ///////////////////////////////////

int main (int argc, char *argv[]) { 

	int i, len;
	char c;
	int startstate=-1, anyaccepting=0;
	parseargs(argc, argv);

	numstates=0;
	states=(state **) malloc(2*sizeof(state *));
	statesize=2;
	state * currstate=NULL;
	state *s0=(state *) malloc(1*sizeof(state));
	s0->name="<DEAD>";
	s0->accepting=0;
	s0->number=0;

	for (i=0; i<MAXSTATE; i+=1) { 
		s0->nextstate[i]=0;
	}
	states[0]=s0;

	// Comments_12: Perigrapste se 2-3 grammes to skopo autou tou while loop.
	while (1) { 
		char *s=fgets(line, MAXLINE, fin);   
		pos=0;
		if (s==NULL) 
			break;
		linenum+=1;
		getsym();    					
		if (symbol[0]=='\n')			
			continue;
		len=strlen(symbol);
		c=sneakch();				
		if (c==':') { 	// Comments_13: Perigrapste to skopo autou tou if (c==':')				
			lower(symbol);				
			if (!validstate(symbol)) { 
				fprintf(stderr, "fsm: Line %d of %s, '%s' is not a valid state name\n", linenum, filename, symbol);
				exit(1); 
			}
			currstate=lookup(symbol);	 
			getsym();					
			getsym();
			if (symbol[0]=='\n')
				continue; 
		}
    	else if (c=='=') { 	// Comments_14: Perigrapste to skopo autou tou else if (c=='=')			
			if (strcasecmp(symbol, "START")==0) { 
				getsym();
				getsym();
				lower(symbol);
				if (!validstate(symbol)) { 
					fprintf(stderr, "fsm: Line %d of %s, '%s' is not a valid state name\n", linenum, filename, symbol);
					exit(1); 
				}
         		if (startstate!=-1) { 
					fprintf(stderr, "fsm: Line %d of %s, Start state specified twice\n", linenum, filename);
           			exit(1); 
				}
				state *s=lookup(symbol);
				startstate=s->number;
				if (tracein) printf("START STATE IS '%s'\n", symbol);
				getsym();
				if (symbol[0]!='\n') { 
					fprintf(stderr, "fsm: Line %d of %s, Line too long, '%s' is out of place\n", linenum, filename, symbol);
					exit(1); 
				}
         		continue; 
			}
      		fprintf(stderr, "fsm: Line %d of %s, '%s=...' is not permitted\n", linenum, filename, symbol);
      		exit(1); 
		}
    	else if (c=='(') { // Comments_15: Perigrapste to skopo autou tou else if (c=='(')
			getsym();
			getsym();
			int ok=strcasecmp(symbol, "OK")==0;
      		if (ok) { 
				getsym();
        		ok=symbol[0]==')'; 	
			}
      		if (ok) { 	
				getsym();
        		ok=symbol[0]==':'; 	
			}
			pos=0;
			getsym();
			if (ok) { 	
				lower(symbol);
				if (!validstate(symbol)) { 	
					fprintf(stderr, "fsm: Line %d of %s, '%s' is not a valid state name\n", linenum, filename, symbol);
					exit(1); 
				}
				currstate=lookup(symbol);
				getsym();
				getsym();
				getsym();
				getsym();
				getsym();
				anyaccepting=1;
				currstate->accepting=1;
				if (tracein) printf("STATE '%s' IS AN ACCEPTING STATE\n", currstate->name);
				if (symbol[0]=='\n')
					continue; 
			} 
		} 
    	if (currstate==NULL) { 
			fprintf(stderr, "fsm: Line %d of %s, no current state specified\n", linenum, filename);
			exit(1); 
		}
		if (tracein) 
			printf("STATE '%s' ", currstate->name);
		int nins=0;
		int said[MAXSTATE];
		for (i=0; i<MAXSTATE; i+=1)
			said[i]=0;
		if (strcasecmp(symbol, "none")==0) { 	
			nins=1;
			said[NOINPUT]=1;
			if (tracein) 
				printf("CONSUME NO INPUT: ");
			getsym();
			if (strcmp(symbol, "->")!=0) { 
				fprintf(stderr, "fsm: Line %d of %s, no inputs allowed after stating NONE\n", linenum, filename);
				exit(1); 
			} 
		} // Comments_16: Perigrapste se 2-3 grammes to skopo autou tou while loop.
		while (strcmp(symbol, "->")!=0 && symbol[0]!='\n') { 
			char in1[300], in2[300];
			strcpy(in1, symbol);
			in2[0]=0;
			nins+=1;
			getsym();
			if (strcmp(symbol, "-")==0) { 
				if (in1[1]!=0 || in1[0]=='*') { 
					fprintf(stderr, "fsm: Line %d of %s, symbol '%s' not allowed in a range\n", linenum, filename, in1);
					exit(1); 
				}
				getsym();
				if (strcmp(symbol, "-")==0 || strcmp(symbol, "->")==0) { 
					fprintf(stderr, "fsm: Line %d of %s, symbol '%s' not allowed after symbol '-'\n", linenum, filename, symbol);
					exit(1); 	
				}
				if (symbol[0]=='\n') { 
					fprintf(stderr, "fsm: Line %d of %s, Line incomplete\n", linenum, filename, symbol);
					exit(1); 
				}
				strcpy(in2, symbol);
				if (in2[1]!=0 || in2[0]=='*') { 
					fprintf(stderr, "fsm: Line %d of %s, symbol '%s' not allowed in a range\n", linenum, filename, in2);
					exit(1); 
				}
				getsym(); 
			}
			int c1=decode(in1);
			if (in2[0]!=0) { 
				int c2=decode(in2);
				if (c1>c2) { 
					char x1[10];
					strcpy(x1, charstring(c1));
					fprintf(stderr, "fsm: Line %d of %s, range %s - %s is empty or out of order\n", linenum, filename, x1, charstring(c2));
					exit(1); 
				}
				for (i=c1; i<=c2; i+=1)
					said[i]=1;
				if (tracein) 
					printf("INPUTS %s ", charstring(c1));
				if (tracein) 
					printf("TO %s: ", charstring(c2)); 
			}
			else if (c1==-1) { 
				said[EOFCHAR]=1;
				if (tracein) 
					printf("AT EOF: "); 
			}
			else if (c1==-2) { 
				said[ALLCHAR]=1;
				if (tracein) 
					printf("ALL OTHER INPUTS: "); 
			}
			else { 
				said[c1]=1;
				if (tracein) 
					printf("INPUT %s ", charstring(c1)); 
			} 
		}
		if (symbol[0]=='\n') { 
			fprintf(stderr, "fsm: Line %d of %s, line incomplete, no '->'\n", linenum, filename);
			exit(1); 
		}
		if (nins==0) { 
			fprintf(stderr, "fsm: Line %d of %s, line incomplete, no inputs specified\n", linenum, filename);
			exit(1); 
		}
		getsym();
		if (symbol[0]=='\n') { 
			fprintf(stderr, "fsm: Line %d of %s, line incomplete, no new state\n", linenum, filename);
			exit(1); 
		}
		lower(symbol);
		if (!validstate(symbol)) { 
			fprintf(stderr, "fsm: Line %d of %s, '%s' is not a valid state name\n", linenum, filename, symbol);
			exit(1); 
		}
		state *newst=lookup(symbol);
		if (tracein) 
			printf("NEW STATE '%s'", symbol);
		char out[300];
		out[0]=0;
		getsym();
		if (strcasecmp(symbol, "none")==0) { 
			getsym();
			if (symbol[0]!='\n') { 
				fprintf(stderr, "fsm: Line %d of %s, line too long, '%s' out of place\n", linenum, filename, symbol);
				exit(1); 
			} 
		}
		for (i=0; i<MAXSTATE; i+=1)
		if (said[i]) { 
			if (currstate->nextstate[i]!=0) { 
				fprintf(stderr, "fsm: Line %d of %s, Non-Deterministic: state='%s', input='%s'\n", linenum, filename, currstate->name, charstring(i));
				exit(1); 
			}
			currstate->nextstate[i]=newst->number;
		}
		if (tracein) 
			printf("\n");
		if (symbol[0]!='\n') { 
			fprintf(stderr, "fsm: Line %d of %s, line too long, '%s' out of place\n", linenum, filename, symbol);
			exit(1); 
		} 
	}
	for (i=1; i<=numstates; i+=1) { 
		state *s=states[i];
		int none=s->nextstate[NOINPUT], alls=s->nextstate[ALLCHAR];
		int j;
		for (j=0; j<MAXSTATE; j+=1) { 
			if (j!=NOINPUT) { 
				if (s->nextstate[j]==0) { 
					s->nextstate[j]=alls;
				}
				else if (none) { 
					fprintf(stderr, "fsm: in %s, Non-Deterministic, state='%s', no input and input='%s'\n", filename, s->name, charstring(j));
          			exit(1); 
				} 
			} 
		} 
	}

	fclose(fin);

	if (startstate==-1)
		startstate=1;
	if (startstate>numstates) { 	
		fprintf(stderr, "fsm: in %s, no start state\n", filename);
		exit(1); 
	}

	while (1) { 
		currstate=states[startstate];  // start at the start state
		int inc=0;
		// Comments_17: Perigrapste se 3-4 grammes ti leitourgia autou tou loop.
		while (1) { 	
			int nsn=currstate->nextstate[NOINPUT];
			if (nsn!=0) { 
				if (trace) 
					printf("%s () -> ", currstate->name);
				currstate=states[nsn];
				if (trace) 
					printf("%s ", currstate->name);
				if (trace) 
					printf("\n");
				continue; 
			}
			if (inc==EOFCHAR) 
				break;

			inc=getchar();     
			if (inc==EOF)
				inc=EOFCHAR;
			nsn=currstate->nextstate[inc]; 	 
			if (nsn==0) { 				
				if (inc!=EOFCHAR) { 
					anyaccepting=0;
					fprintf(stderr, "fsm: in %s, state '%s' input %s not accepted\n", filename, currstate->name, charstring(inc));
					exit(2); 	
				}
				break; 
			}
			if (trace) 
				printf("%s %s -> ", currstate->name, charstring(inc));
			currstate=states[nsn];
			if (trace) 
				printf("%s ", currstate->name);
			if (trace) 
				printf("\n"); 
		}
		if (anyaccepting) { 
			if (currstate->accepting)
				printf("YES\n");
			else
				printf("NO\n"); 
		}
		break; 
	}
	if (tracein) 
		printf("Done\n"); 
	return 0;
}

