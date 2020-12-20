/*
Sai Kathika 
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4194304 bytes
    associativity = 16
mystery1:
    block size = 4 bytes 
    cache size = 4096 bytes
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4096 bytes 
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  int c_size = 1;
  flush_cache();
  do{
    c_size <<= 1;
    for(int i = 0; i <= c_size; i += block_size){
      access_cache(i);
    }
  }
  while(access_cache(0));
  return c_size;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  flush_cache();
  for(int num = 0; 1; num += size){
    access_cache(num);
    for(int i = 0; i <= num ; i += size){
      if(!access_cache(i)){
        return num/size;
      }
    }
  }
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  int num = 0;
  access_cache(0);
  while(access_cache(num))  {                             
    num++;
  }
  return num;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
