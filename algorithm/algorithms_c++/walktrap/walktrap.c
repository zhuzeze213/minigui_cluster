#include "graph.h"
#include "communities.h"
#include "../include/set.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void info() {
  printf("WalkTrap v0.2 -- Finds community structure of networks using random walks.\n");
  printf("Copyright (C) 2004 Pascal Pons.\n\n");
}

void help(char* prog_name) {
  info();
  printf("usage: %s  [input_file] [-o output_file] [-i index_file] [options]\n\n",prog_name);
  printf( "input_file: read the network from this file. stdin if not specified\n");
  printf( "output_file: stdout if not specified\n");
  printf( "index_file: index of the real name of the vertices\n\n");
  printf( "options:\n");
  printf( "-s\t(silent) do not display the progress.");
  printf( "-tx\tset the length of random walks to x (default = 4).\n");
  printf( "-dx\tset to x the detail level of the output (0 <= x <= 4, default = 1).\n"); 
  printf( "-px\tprint the partition with x communities\n" );
  printf( "-b\tprint the best modularity partition\n" );
  printf( "-mx\tlimit the memory usage to x MB\n" );
  printf( "-h\tprint this help\n\n"); 
  printf( "see readme.txt for more details\n");
  exit(0);
}



int main(int argc, char** argv)
{  
  int length = 4;
  int details = 2;
  long max_memory = -1;
  bool silent = false;
  bool print_best_modularity = false;
  char* output_file = 0;
  char* input_file = 0;
  char* index_file = 0;
  set<int> print_partition;

  for (int i = 1; i < argc; i++) 
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
	case 't':
	  length = atoi(argv[i]+2);
	  if (length <= 0) help(argv[0]);
	  break;
	case 's':
	  if(argv[i][2] != 0) help(argv[0]);
	  silent = true;
	  break;
	case 'o':
	  if(argv[i][2] != 0) help(argv[0]);
	  if(++i < argc) 
	    if(!output_file) {
	      output_file = argv[i];
	      break;
	    }
	  help(argv[0]);
	case 'd':
	  details = atoi(argv[i]+2);
	  if((argv[i][2] != '0' || argv[i][3] != 0) && details <= 0) help(argv[0]);
	  break;
	case 'p':
	  if (atoi(argv[i]+2) <= 0) help(argv[0]);
	  print_partition.insert(atoi(argv[i]+2));
	  break;
	case 'b':
	  print_best_modularity = true;
	  break;	  
	case 'm':
	  max_memory = atol(argv[i]+2)*1024*1024;
	  if (max_memory <= 0) help(argv[0]);
	  break;
	case 'i':
	  if(argv[i][2] != 0) help(argv[0]);
	  if(++i < argc) 
	    if(!index_file) {
	      index_file = argv[i];
	      break;
	    }
	  help(argv[0]);
	default:
	  help(argv[0]);
      }
    }
    else {
      if(!input_file) input_file = argv[i];
      else help(argv[0]);
    }

  if(output_file) {
    ifstream ftmp;
    File *fp=fopen(output_file,"r");
    if(fp) {printf("file %s already exists\n",output_file); exit(0);}
    fp=fopen(output_file,"w");
  }

  if(!silent) info();
  time_t begin = clock();
  
/*  Graph* G = new Graph;

  if(input_file) {
    ifstream f;
    f.open(input_file, ios::in);
    if(!f.is_open()) {
      cerr << "unable to open file " << input_file << endl; 
      exit(0);
    }
    if(!silent) cerr << "loading graph from file: \"" << input_file << "\""<<  endl;
    f >> *G;
    f.close();
  }
  else {
    if(!silent) cerr << "loading graph from standard input..." << endl;
    cin >> *G;
  }
  if(!silent) cerr << G->nb_vertices << " vertices and " << G->nb_edges << " edges sucessfuly loaded." << endl << endl;

  if(index_file) {
    if(!silent) cerr << "loading index from file " << index_file << endl;
    if(G->load_index(index_file)) 
      if(!silent) cerr << "index sucessfuly loaded" << endl << endl;
  }
  
  Communities C(G, length, silent, details, max_memory);  

  if(!silent) cerr << "merging the communities:";

  while(!C.H->is_empty()) {
    C.merge_nearest_communities();
  }

  if(!silent) cerr << endl;

  if(print_best_modularity)
    C.print_best_modularity_partition();
  
  for(set<int>::iterator it = print_partition.begin(); it != print_partition.end(); ++it)
    if(*it <= G->nb_vertices) C.print_partition(*it);
  
  if(!silent) cerr << endl << "computation successfully terminated in " << double(clock() - begin) / double(CLOCKS_PER_SEC) << "s" << endl;
  delete G;
  if(output_file) fclose(stdout);
  return 0;
}
*/
