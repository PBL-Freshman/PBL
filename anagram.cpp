#include <stdio.h> 

#include <string.h> 

#define MAX 100 

int anagram(char s[], char t[]); 

main() 

{ 

  char s[MAX], t[MAX]; 

  printf("s: "); gets(s); 

  printf("t: "); gets(t); 

  if (anagram(s,t)) printf("anagram"); 

  else printf("Not anagram"); 

} 

int anagram(char s[], char t[]) 

{ 

  int n, i, as[256]={0}, at[256]={0} ; 

  n=strlen(s); 

  if (strlen(t)!=n) return 0; 

  for (i=0; i<n; i++){ 

    as[s[i]]+=1; 

    at[t[i]]+=1; 

  } 
  printf("%d", as[s[i]]);
  printf("%d", at[t[i]]);
  

  i=0; 

  while (i<256 && as[i]==at[i]) i++; 

  return i>255; 

} 
