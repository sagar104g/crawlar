#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include "html.h"
#include<sys/types.h>
#define seed_url "http://xnxx.com/"
#define HASH_SIZE 100
#define URL_LENGTH 1000
#define MAX_URL_PER_PAGE 1000
#define INTERVAL_TIME 10
struct NODE;
struct HASH;
int depth(char*);
struct HASH add_node(struct HASH,struct NODE*);
void add_file(char*);
struct HASH create_node(struct HASH,int,char*);
void getpage(char *url);
struct HASH visit_nodes(struct NODE*,struct HASH);
int NormalizeURL(char*);
void removeWhiteSpace(char*);
int check_url(char*);
int GetNextURL(char*, char*, char*, int);
int testDir(char*);
int create_key(int );
int vlalid_url(char*);
struct NODE{
int depth;
int visited;
//char url[1000];
char *url;
int key;
struct NODE *next;
};
struct HASH{
struct NODE *table[100];
};
struct HASH visit(struct HASH h1){
struct NODE *ptr=NULL;
for(int i=0;i<100;i++){
	  if(h1.table[i]!=NULL){
		ptr=h1.table[i];
		while(ptr!=NULL){
			if(ptr->depth>0&&ptr->visited==0){
				printf("cool\n");
				ptr->visited=1;
				h1=visit_nodes(ptr,h1);
				i=-1;
				break;
			}
			ptr=ptr->next;
		}
	}
}
printf("\nALL URLS DONE.............\n");
return h1;
}
int create_key(int i){
if(i<100){
	return i;	
	}else{
		return i%100;	
	}
}
struct HASH create_node(struct HASH h1,int a,char *b){
if(vlalid_url(b)){
	struct NODE *n=(struct NODE*) malloc(sizeof(struct NODE));
	//memset(buffer,0,strlen(n)+1);	
	int i;
	n->depth=a;
	printf("adding node..................\n");
	n->url=(char*) malloc(sizeof(char)*1000);
		memset(n->url,0,1000);	
		for(i=0;b[i]!='\0';i++){
		n->url[i]=b[i];
		printf("%c",n->url[i]);
	}
		printf("\n done adding................\n");
	n->url[i]='\0';	
	n->key=create_key(i);
	n->visited=0;
	n->next=NULL;
	h1=add_node(h1,n);
	add_file(b);
return h1;
}
}
struct HASH add_node(struct HASH h1,struct NODE *n){
	if(h1.table[n->key]==NULL){
		h1.table[n->key]=n;
		}else{
			struct NODE *ptr=h1.table[n->key];
			while(ptr->next!=NULL){
				ptr=ptr->next;
				}
			ptr->next=n;
			}
return h1;
}
void add_file(char *x){
	char ch;
	FILE *fp1;
	char *a=(char*) malloc(sizeof(char)*1000);
	memset(a,0,1000);
	strcpy(a,"nnn/");
	int j=4;	
	for(int i=0;x[i]!='\0'&&j<990;i++){
		if(x[i]>='a'&&x[i]<='z'||x[i]>='A'&&x[i]<='Z'){
			a[j]=x[i];
			j++;
		}
	}
	a[j]='.';
	j++;
	a[j]='t';
	j++;
	a[j]='x';
	j++;
	a[j]='t';
	j++;
	a[j]='\0';
	char urlbuffer[1000+300]={0};
	strcat(urlbuffer,"wget ");
	strcat(urlbuffer,x);
	strcat(urlbuffer," -O nnn/data.txt");
	system(urlbuffer);
	fp1=fopen(a,"w");
	free(a);
	FILE *fp2;
	fp2=fopen("nnn/data.txt","r");

while (1) {
      ch = fgetc(fp2);
      if (ch == EOF)
         break;
      else
         putc(ch, fp1);
   }
 printf("File copied Successfully!\n");
   fclose(fp1);
   fclose(fp2);
}
int check_node(struct HASH h1,char *ch){
struct NODE *ptr;
	for(int i=0;i<100;i++){
	ptr=h1.table[i];
		if(ptr!=NULL){
		struct NODE *ptr1=ptr;
			while(ptr1!=NULL){
			if(strcmp(ch,ptr1->url)==0){
			return 0;			
			}
			ptr1=ptr1->next;
			}
		}
	}
return 1;
}
struct HASH visit_nodes(struct NODE *n,struct HASH h1){
printf("p\np\np\np\np\np\np\np\n.....................\n");
char *aa=(char*) malloc(sizeof(char)*1000);
//char aa[50];
aa[0]='n';
aa[1]='n';
aa[2]='n';
aa[3]='/';
int j=4;
for(int i=0;n->url[i]!='\0'&&j<990;i++){
	if(n->url[i]>='a'&&n->url[i]<='z'||n->url[i]>='A'&&n->url[i]<='Z'){
		aa[j]=n->url[i];
		j++;
		}
	}
aa[j]='.';
j++;
aa[j]='t';
j++;
aa[j]='x';
j++;
aa[j]='t';
j++;
aa[j]='\0';
FILE *fl=fopen(aa,"r");
	fseek(fl, 0, SEEK_END);
	long long int file_size = ftell(fl);
	fseek(fl, 0, SEEK_SET);
char *size=(char*) malloc(sizeof(char)*file_size);
memset(size,0,file_size);
fprintf(fl,"%s",size);
long long int code_s = sizeof(char) * file_size;
size = malloc(code_s);
long long int result = fread(size, 1, file_size, fl);
int q=1;
free(aa);
//int hla=0;
for(int pp=0;pp<20;pp++){
	char *b=(char*) malloc(sizeof(char)*10000);
	char *bb=(char*) malloc(sizeof(char)*10000);	
	memset(b,0,10000);
	memset(bb,0,10000);
	q=GetNextURL(size,n->url,b,q);
	if(q==-1){
	free(b);
	free(bb);
	break;
	}
	printf("\nlink is\n\n\n\n");
		for(int t=0;b[t]!='\0';t++){
			printf("%c",b[t]);
		}
printf("\nlink is\n\n\n\n");
	printf("\nurl done\n");
	if(vlalid_url(b)){
	if(check_node(h1,b)){
	//hla++;
	h1=create_node(h1,n->depth-1,b);
	}
	}
	free(b);
	free(bb);
}
fclose(fl);
free(size);
return h1;
}
void removeWhiteSpace(char* html) 
{
  int i;
  char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
  memset(buffer,0,strlen(html)+1);
  for (i=0;html[i];i++) 
  {
    if(html[i]>32)
    {
      sprintf(p,"%c",html[i]);
      strcat(buffer,p);
    }
  }
  strcpy(html,buffer);
  free(buffer); free(p);
}
int GetNextURL(char* html, char* urlofthispage, char* result, int pos) 
{
  char c;
  int len, i, j;
  char* p1;  //!< pointer pointed to the start of a new-founded URL.
  char* p2;  //!< pointer pointed to the end of a new-founded URL.

  // NEW
  // Clean up \n chars
  if(pos == 0) {
    removeWhiteSpace(html);
  }
  // /NEW

  // Find the <a> <A> HTML tag.
  while (0 != (c = html[pos])) 
  {
    if ((c=='<') &&
        ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
      break;
    }
    pos++;
  }
  //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
  //! We try to find the quote mark in order to find the URL inside the quote mark.
  if (c) 
  {  
    // check for equals first... some HTML tags don't have quotes...or use single quotes instead
    p1 = strchr(&(html[pos+1]), '=');
    
    if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10)) 
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*(p1+1) == '\"' || *(p1+1) == '\'')
      p1++;

    p1++;    

    p2 = strpbrk(p1, "\'\">");
    if (!p2) 
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*p1 == '#') 
    { // Why bother returning anything here....recursively keep going...

      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (!strncmp(p1, "mailto:",7))
      return GetNextURL(html, urlofthispage, result, pos+1);
    if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4)) 
    {
      //! Nice! The URL we found is in absolute path.
      strncpy(result, p1, (p2-p1));
      return  (int)(p2 - html + 1);
    } else {
      //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
      if (p1[0] == '.') {
        //! Some URLs are like <a href="../../../a.txt"> I cannot handle this. 
	// again...probably good to recursively keep going..
	// NEW
        
        return GetNextURL(html,urlofthispage,result,pos+1);
	// /NEW
      }
      if (p1[0] == '/') {
        //! this means the URL is the absolute path
        for (i = 7; i < strlen(urlofthispage); i++)
          if (urlofthispage[i] == '/')
            break;
        strcpy(result, urlofthispage);
        result[i] = 0;
        strncat(result, p1, (p2 - p1));
        return (int)(p2 - html + 1);        
      } else {
        //! the URL is a absolute path.
        len = strlen(urlofthispage);
for (i = (len - 1); i >= 0; i--)
          if (urlofthispage[i] == '/')
            break;
        for (j = (len - 1); j >= 0; j--)
          if (urlofthispage[j] == '.')
              break;
        if (i == (len -1)) {
          //! urlofthis page is like http://www.abc.com/
            strcpy(result, urlofthispage);
            result[i + 1] = 0;
            strncat(result, p1, p2 - p1);
            return (int)(p2 - html + 1);
        }
        if ((i <= 6)||(i > j)) {
          //! urlofthis page is like http://www.abc.com/~xyz
          //! or http://www.abc.com
          strcpy(result, urlofthispage);
          result[len] = '/';
          strncat(result, p1, p2 - p1);
          return (int)(p2 - html + 1);
        }
        strcpy(result, urlofthispage);
        result[i + 1] = 0;
        strncat(result, p1, p2 - p1);
        return (int)(p2 - html + 1);
      }
    }
  }    
  return -1;
}

void NormalizeWord(char* word) {
  int i = 0;
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}
int NormalizeURL(char* URL) 
{
  int len = strlen(URL);
  if (len <= 1 )
    return 0;
  //! Normalize all URLs.
  if (URL[len - 1] == '/') 
  {
    URL[len - 1] = 0;
    len--;
  }
  int i, j;
  len = strlen(URL);
  //! Safe check.
  if (len < 2)
    return 0;
  //! Locate the URL's suffix.
  for (i = len - 1; i >= 0; i--)
    if (URL[i] =='.')
      break;
  for (j = len - 1; j >= 0; j--)
    if (URL[j] =='/')
      break;
  //! We ignore other file types.
  //! So if a URL link is to a file that are not in the file type of the following
  //! one of four, then we will discard this URL, and it will not be in the URL list.
  if ((j >= 7) && (i > j) && ((i + 2) < len)) 
  {
    if ((!strncmp((URL + i), ".htm", 4))
        ||(!strncmp((URL + i), ".HTM", 4))
        ||(!strncmp((URL + i), ".php", 4))
        ||(!strncmp((URL + i), ".jsp", 4))
        ) 
    {
      len = len; // do nothing.
    } 
    else 
    {
      return 0; // bad type
    }
  }
  return 1;
}
void getpage(char *url){
char urlbuffer[1300]={0};
strcat(urlbuffer,"wget ");
strcat(urlbuffer, url);
strcat(urlbuffer," -O nnn/b.txt");
system(urlbuffer);
}
int vlalid_url(char *ch){
	char command[10000]="wget -q --spider";
	int i;
	for(i=0;command[i]!='\0';i++);
		command[i]=' ';
	i++;
	for(int k=0;ch[k]!='\0';i++,k++){
		command[i]=ch[k];
	}
	command[i]='\0';
	if(!system(command)){
		printf("Valid URL");
		return 1;
	}
	else{
		printf("Invalid URL");
	}
return 0;
}

int testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 ) 
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
   return 0;
    }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) ) 
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    return 0;
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
   return 0;
  }
return 1;
}

int check_url(char *link){
	for(int i=0;seed_url[i]!='\0';i++){
		if(seed_url[i]!=link[i]){
			return 0;
		}
	}
	return 1;
}
int depth(char *ch){ 
	if(ch[0]-'0'<=3&&ch[0]-'0'>=0){ 
		return 1; 
	} 
	return 1; 
} 
int check_node1(struct HASH h1){
struct NODE *ptr;
	for(int i=0;i<100;i++){
	ptr=h1.table[i];
		if(ptr!=NULL){
		struct NODE *ptr1=ptr;
			while(ptr1!=NULL){
			printf("%s----%d----%d\n",ptr1->url,ptr1->depth,ptr->visited);
			ptr1=ptr1->next;
			}
		}
	}
return 1;
}
int main(int argc,char *argv[]){ 
	struct HASH h1;
	struct NODE *head;
	for(int i=0;i<100;i++){
		h1.table[i]=(struct NODE*) malloc(sizeof(struct NODE));
		h1.table[i]=NULL;
	} 
	if(argc==4){ 
		if(depth(argv[1])){
			if(check_url(argv[2])){
				if(testDir(argv[3])){
					if(vlalid_url(argv[2])){
						int a=argv[1][0]-'0';
						char *b=(char*) malloc(sizeof(char)*100);
						memset(b,0,100);		
						int i;
						for(i=0;argv[2][i]!='\0';i++){
							b[i]=argv[2][i];
						}
					b[i]='\0';
					h1=create_node(h1,a,b);
					free(b);
					h1=visit(h1);
				}
			}
		}
	 }
} 
check_node1(h1);
return 0;
}

