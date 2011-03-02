#include "treedata.hpp"
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<iostream>
#include<sstream>

using namespace std;

Treedata::Treedata(string fname, bool is_featurerows):
  targetidx_(-1),
  nsamples_(0),
  nfeatures_(0),
  ncatfeatures_(0),
  nnumfeatures_(0),
  catfeatureheaders_(0),
  numfeatureheaders_(0),
  catfeatureics_(0),
  numfeatureics_(0)
{

  cout << "Treedata: reading matrix from file '" << fname << "'" << endl;

  //Initialize stream to read from file
  ifstream featurestream;
  featurestream.open(fname.c_str());
  assert(featurestream.good());

  string field;
  string row;

  //Remove upper left element from the matrix as useless
  getline(featurestream,field,'\t');

  //Count the number of columns
  getline(featurestream,row);
  stringstream ss(row);
  size_t ncols = 0;
  while(getline(ss,field,'\t'))
    {
      ++ncols;
    }

  //Count the number of rows
  size_t nrows = 0;
  while(getline(featurestream,row))
    {
      ++nrows;
    }

  //Reset streams and remove upper left element from the matrix as useless
  featurestream.clear();
  featurestream.seekg(0, ios::beg);
  getline(featurestream,field,'\t');
  ss.clear();
  ss.str("");

  vector<string> colheaders(ncols);
  vector<string> rowheaders(nrows);
  vector<vector<string> > datamatrix(nrows);
  for(size_t i = 0; i < nrows; ++i)
    {
      datamatrix[i] = colheaders;
    }

  cout << "read " << datamatrix.size() << " rows and " << datamatrix[0].size() << " columns." << endl;

  getline(featurestream,row);
  ss << row;

  for(size_t i = 0; i < ncols; ++i)
    {
      getline(ss,colheaders[i],'\t');
      cout << '\t' << colheaders[i];
    }
  cout << endl;

  for(size_t i = 0; i < nrows; ++i)
    {
      getline(featurestream,row);
      ss.clear();
      ss.str("");
      ss << row;
      getline(ss,rowheaders[i],'\t');
      cout << rowheaders[i];
      for(size_t j = 0; j < ncols; ++j)
	{
	  getline(ss,datamatrix[i][j],'\t');
	  cout << '\t' << datamatrix[i][j];
	}
      cout << endl;
    }
  cout << endl;
  
  if(is_featurerows)
    {
      nfeatures_ = nrows;
      nsamples_ = ncols;
      sampleheaders_ = colheaders;
      for(size_t i = 0; i < nfeatures_; ++i)
	{
	  if(rowheaders[i][0] == 'N')
	    {
	      numfeatureheaders_.push_back(rowheaders[i]);
	      numfeatureics_.push_back(i);
	      ++nnumfeatures_;
	    }
	  else if(rowheaders[i][0] == 'C')
	    {
	      catfeatureheaders_.push_back(rowheaders[i]);
	      catfeatureics_.push_back(i);
	      ++ncatfeatures_;
	    }
	  else
	    {
	      cerr << "Data type must be either N or C!" << endl;
	      assert(false);
	    }
	}
    }
  else
    {
      cerr << "samples as rows not yet supported!" << endl;
      assert(false);
    }

  cout << ncatfeatures_ << " (C)ategorical and " << nnumfeatures_ << " (N)umerical features" << endl;
  cout << "Sample headers: ";
  for(size_t i = 0; i < nsamples_; ++i)
    {
      cout << " " << sampleheaders_[i];
    }
  cout << endl;
  cout << "(N)umerical feature headers: ";
  for(size_t i = 0; i < nnumfeatures_; ++i)
    {
      cout << "\t" << numfeatureheaders_[i] << "(row " << numfeatureics_[i] << ")"; 
    }
  cout << endl;
  cout << "(C)ategorical feature headers: ";
  for(size_t i = 0; i < ncatfeatures_; ++i)
    {
      cout << "\t" << catfeatureheaders_[i] << "(row " << catfeatureics_[i] << ")";
    }
  cout << endl;


}

Treedata::~Treedata()
{
}

void Treedata::transpose()
{
  
}



